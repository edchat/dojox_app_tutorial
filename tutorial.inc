<?php require("../../resources/tutHead.inc"); ?>

<h3>About dojox/app</h3>

<p><strong>dojox/app</strong> is a Dojo-based application framework that increases maintainability and reduces coding effort by providing:</p>
<ul>
	<li>A predefined JSON-based (possibly external) configuration file</li>
	<li>A typical application structure</li>
	<li>A notion of views, view templates, controllers and a transition system between the views</li>
	<li>A set of controllers that the application can leverage including layout and transition controllers</li>
	<li>A build system to bundle your application in a limited set of files to be downloaded or installed onto the system</li>
</ul>

<p>Even though dojox/app is built on top of Dojo, it is UI Toolkit agnostic.  The application views can be developed with:</p>
<ul>
	<li>Dijit</li>
	<li>Dojo Mobile</li>
	<li>Any other JavaScript/HTML5 toolkit like jQuery Mobile</li>
</ul>

<h3 id="tutorialParts">This tutorial will be broken down into three sections:</h3>

<ol>
	<li>Show how to create a very simple application to display a filtered <strong>list of contacts.</strong></li>
	<li>Show how to add a <strong>details view</strong> to the application, and how to add:
		<ul>
			<li>Support for contacts to be <strong>edited, added</strong> and <strong>deleted</strong>.</li>
			<li>Support to <strong>Transition</strong> from the <strong>list</strong> view to the <strong>details</strong> view.</li>
			<li><strong>History</strong> support to go back to the list view, using <strong>"has"</strong> based config support.</li>
			<li>Support for a <strong>tablet view</strong> in addition to a <strong>phone view</strong>, using <strong>"has"</strong> based config support.</li>
			<li><strong>NLS</strong> support for strings for the application and for each of the views.</li>
		</ul>
	<li>Show how to add support for a <strong>cordova</strong> based access to the contacts on a device.</li>
</ol>

<h3 id="createAnApp">Creating simple application to display a filtered list of contacts.</h3>

<p>To get started we will see how <strong>Contacts application data</strong> will be structured.  This data structure
	was chosen because it matches the contacts data structure used by cordova.
	The data will include an array of contacts with the following:</p>
<ul>
	<li><strong>"id"</strong>: a unique id.</li>
	<li><strong>"name"</strong>: which includes sub-fields of <strong>"givenName"</strong> and <strong>"familyName"</strong>.</li>
	<li><strong>"displayName"</strong>: which is created by joining the <strong>"givenName"</strong> and <strong>"familyName"</strong>.</li>
	<li><strong>"emails"</strong>: an array which contains entries which include sub-fields of <strong>"type"</strong> and <strong>"value"</strong>.</li>
	<li><strong>"phoneNumbers"</strong>: an array which contains entries which include sub-fields of <strong>"type"</strong> and <strong>"value"</strong>.</li>
</ul>


<h3 id="FirstList">First we will create the application with only the <strong>list</strong> view.</h3>
<div style="float: left; width: 100%; margin-top: 20px; margin-bottom: 20px;">
	<p>This is how the <strong>Contacts application list</strong> view will look on an <strong>iPhone</strong> iOS Simulator.</p>
	<div style="float: left; width: 50%;">
		<label  style="margin-left: 90px;">Contacts List</label>
		<img src="images/contactsList.png" alt="Phone Contacts List View" style="margin:0 auto;display:block;" />
	</div>
</div>

<h3 id="createhtml">Create the main HTML or php file for your application (contacts.php).</h3>

<p>Dojo must be loaded.</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"  
		src="path-to-dojo/dojo/dojo.js" data-dojo-config= "async: true"&gt;
 &lt;/script&gt;
</pre>

<p>The Dojo mobile CSS (if using Dojo Mobile):</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"  
	src="path-to-dojo/dojox/mobile/deviceTheme.js"&gt;
 &lt;/script&gt;
</pre>

<p>As well as your main application (AMD) module:</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"&gt;
	require(["contactsList/contacts"]);
 &lt;/script&gt;
</pre>

<h3 id="jsonConfig">The JSON configuration file.</h3>
<p>What the JSON Configuration Contains:</p>
<ul>
	<li>An application ID</li>
	<li>A set of application controllers</li>
	<li>A set of application dependencies</li>
	<li>A set of views with:</li>
		<ul>
			<li>Templates (View rendering)</li>
			<li>Controllers (View controllers)</li>
			<li>View Translation Files</li>
			<li>Possibly custom parameters</li>
		</ul>
	<li>A set of data stores that can be shared at application level or specific to a view</li>
</ul>
<p class="proTip">The configuration can leverage the dojo/has module to branch based on the targeted platform.</p>

<h3 id="createconfig1">Create the JSON configuration file for the simple <strong>Contacts List application</strong> (contacts.json).</h3>

<p>The JSON configuration for the List view Contacts Application includes the dependencies, controllers, the stores, nls,
	defaultView and the list view, as follows:</p>
<pre class="brush: js; html-script: true;">
	{
		"id": "contactsApp",
		"loaderConfig": {
			"paths": {
				"contactsApp": "../contactsList"
			}
		},
		"dependencies": [
			"dojo/store/Observable",
			"dojox/mobile/Heading",
			"dojox/mobile/ScrollableView",
			"dojox/mobile/ToolBarButton",
			"dojo/store/Memory"
		],
		"controllers": [
			"dojox/app/controllers/Load",
			"dojox/app/controllers/Transition",
			"dojox/app/controllers/Layout"
		],
		"defaultView": "list",
		"stores": {
			"contacts": {
				"type": "dojo/store/Memory",
				"observable": true,
				"params": {
					"data": [
						{
							"id": "1",
							"displayName": "Ed Chatelain",
							"name": {
								"givenName": "Ed",
								"familyName": "Chatelain"
							},
							"emails": [
								{
									"type": "home",
									"value": "me@myhome.com"
								}
							],
							"phoneNumbers": [
								{
									"type": "home",
									"value": "10-20-30-40"
								},
								{
									"type": "work",
									"value": "11-22-33-44"
								}
							],
							"organizations": []
						},
						{
							"id": "2",
							"displayName": "Christophe Jolif",
							"name": {
								"givenName": "Christophe",
								"familyName": "Jolif"
							},
							"emails": [
								{
									"type": "home",
									"value": "him@myhome.com"
								},
								{
									"type": "work",
									"value": "dev@dev.com"
								}
							],
							"phoneNumbers": [
								{
									"type": "home",
									"value": "11-43-81-63-19"
								},
								{
									"type": "work",
									"value": "11-48-07-13-38"
								}
							],
							"organizations": []
						}
					]
				}
			}
		},
		"views": {
			"list": {
				"controller": "contactsList/list",
				"template": "contactsList/list.html"
			}
		}
	}
</pre>

<h3 id="createmain">Create the main module for your application.</h3>
<p>The main module will define the configuration flags needed by the configuration file and load the configuration file
	to instantiate the application (contacts.js)</p>
<pre class="brush: js; html-script: true;">
	define(["dojo/json", "dojo/text!contactsList/contacts.json", "dojox/app/main",
			"dojox/mobile/common"],
		function(json, config, Application, common){
			Application(json.parse(config));
	});
</pre>

<h3 id="createviews">Create the <strong>"list" view</strong>, including template, and controller.</h3>
<p><strong>"list" view template</strong> (list.html) includes:</p>
<ul>
	<li>A dojox/mobile/Heading.</li>
	<li>A dojox/mobile/EdgeToEdgeStoreList with a dojox/mobile/FilteredListMixin.</li>
</ul>

<pre class="brush: html;">
	&lt;div class="mblBackground"&gt;
		&lt;div data-dojo-type="dojox/mobile/Heading"
			data-dojo-props="fixed: 'top'"&gt;
			Contacts
		&lt;/div&gt;
		&lt;div data-dojo-type="dojox/mobile/EdgeToEdgeStoreList"
				data-dojo-mixins="dojox/mobile/FilteredListMixin"
				data-dojo-attach-point="contacts"
				data-dojo-props="store: this.loadedStores.contacts,
								labelProperty: 'displayName',
								placeHolder: 'Search'"&gt;
		&lt;/div&gt;
	&lt;/div&gt;
</pre>

<p>The <strong>"list" view controller</strong> (list.js) includes:</p>
<ul>
	<li>The <strong>init</strong> function which is called when the controller is loaded the first time which will simply
		use <strong>on</strong> to watch for clicks in the list, and use alert to indicate which item was clicked.</li>
</ul>
<pre class="brush: js; html-script: true;">
	define(["dojox/mobile/EdgeToEdgeStoreList", "dojox/mobile/FilteredListMixin"],
		function(){
		return {
			init: function(){
				this.contacts.on("click", function(e){
					alert(e.target.innerHTML + ": was clicked.");
				});
			}
		};
	});
</pre>

<a class="demoBtn demo" href="demos/contactsList/contacts.php" target="_blank">Run the contactsList App</a>
<a href="https://github.com/edchat/dojox_app_tutorial">View the contactsList App source on github</a>


<h3 id="contactsAppBaseAddDetails">Next we will add the <strong>Details view</strong> to the Contacts Application</h3>
<p>And we will add:</p>
	<ul>
		<li>Support for contacts to be <strong>edited, added</strong> and <strong>deleted</strong>.</li>
		<li>Support to <strong>Transition</strong> from the <strong>list</strong> view to the <strong>details</strong> view.</li>
		<li><strong>History</strong> support to go back to the list view, using <strong>"has"</strong> based config support.</li>
		<li>Support for a <strong>tablet view</strong> in addition to a <strong>phone view</strong>, using <strong>"has"</strong> based config support.</li>
		<li><strong>NLS</strong> support for strings for the application and for each of the views.</li>
	</ul>

<p>The <strong>Contacts application</strong> will include two views.  The first view will include the filtered
	<strong>list of contacts</strong>, and the second view will show the <strong>details of a contact</strong> and
	allow the contact to be edited or deleted.</p>
<div style="float: left; width: 100%; margin-top: 20px;">
	<p>This is how the <strong>Contacts application</strong> will look on an <strong>iPhone</strong> iOS Simulator.</p>
	<div style="float: left; width: 50%;">
		<label  style="margin-left: 90px;">Contacts List</label>
		<img src="images/phoneImage1.png" alt="Phone Contacts List View" style="margin:0 auto;display:block;" />
	</div>
	<div style="float: left; width: 50%;">
		<label style="margin-left: 90px;">Contacts Details</label>
		<img src="images/phoneImage.png" alt="Phone Contacts Details View" style="margin:0 auto;display:block;" />
	</div>
</div>
<div style="float: left; width: 100%; margin-top: 20px; margin-bottom: 20px;">
		<p>This is how the <strong>Contacts application</strong> will look on an <strong>iPad</strong> iOS Simulator.</p>
		<label style="margin-left: 90px;">Contacts List and Details</label>
		<img src="images/tabletImage.png" alt="Tablet/Desktop Layout" style="margin:0 auto;display:block;width: 540px;height: 396px;" />
</div>

<h3 id="updatecss">Update the CSS for the application.</h3>

<p>We need to add the application CSS file to the html:</p>
<pre class="brush: js; html-script: true;">
&lt;link rel="stylesheet" href="contacts.css"&gt;
</pre>

<p>The (contacts.css) <strong>application CSS</strong> file includes a media query with a min-width of 501px,
	so that on a tablet/desktop sized screen the .leftpane will only be set with a width of 250px and a border,
	and the .backButton will be hidden. The CSS file looks like this:</p>
<pre class="brush: js; html-script: true;">
	@media screen and (min-width: 501px) {
	  	.leftpanel {
	    	width: 250px;
			border-right:1px solid black;
			z-index:100;
		}
		.backButton {
			display: none;
		}
	}

	.hidden {
		display: none;
	}
</pre>

<h3 id="updatejson">Update the JSON configuration file.</h3>

<p>The JSON configuration file <strong>contacts.json</strong> has to be updated to add the <strong>detail</strong>
	view controller, template and nls settings to the JSON file, and the <strong>list</strong> view is also updated
	so that when not on a phone it will use a constraint of left for the tablet layout.</p>
<pre class="brush: js; html-script: true;">
	"views": {
	  "list": {
	    "controller": "contactsApp/list",
	    "template": "contactsApp/list.html",
	    "nls": "contactsApp/nls/list",
	    "has": {
	      "!phone": {
	        "constraint": "left"
	      }
	   },
	   "detail": {
	     "controller": "contactsApp/detail",
	     "template": "contactsApp/detail.html",
	     "nls": "contactsApp/nls/detail"
	   }
	}
</pre>

<h3 id="updatemain">Update the main module of your application.</h3>
<p>The main module (contacts.js) will be updated to  to add the has check for <strong>phone and html5history</strong>.</p>
<pre class="brush: js; html-script: true;">
	// we use 'define' and not 'require' to workaround Dojo build system limitation that prevents from making of this file
	// a layer if it using 'require'
	define(["dojo/sniff", "dojo/request", "dojo/json", "dojo/text!contactsAppBase/contacts.json", "dojox/app/main", "dojox/mobile/common"],
		function(has, request, json, config, Application, common){

		 has.add("html5history", !has("ie") || has("ie") > 9);
		 has.add("phone", ((window.innerWidth || document.documentElement.clientWidth) <= common.tabletSize));
		 Application(json.parse(config));

	});
</pre>

<h3 id="updateviews">Update the <strong>"list"</strong> view, including template, and controller.</h3>
<p><strong>"list" view template</strong> (list.html) includes:</p>
<ul>
	<li>A dojo/require for dojo/has which is used to check for phone.</li>
	<li>A dojox/mobile/Heading which uses NLS strings like ${nls.contacts}, and includes an <strong>Add</strong> button.</li>
	<li>A dojox/mobile/EdgeToEdgeStoreList with a dojox/mobile/FilteredListMixin and uses ContactListItem as the itemRenderer.</li>
</ul>

<pre class="brush: html;">
	&lt;div class="leftpanel mblBackground"&gt;
		&lt;script type="dojo/require"&gt;
			has: "dojo/has"
		&lt;/script&gt;
		&lt;div data-dojo-type="dojox/mobile/Heading"
				data-dojo-props="fixed: 'top'"&gt;
			${nls.contacts}
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					style="position: absolute; right: 0"
					data-dojo-props="target: 'detail',
								transitionOptions: { params: { edit: true } }"
					data-dojo-attach-point="add"&gt;${nls.add}&lt;/button&gt;
		&lt;/div&gt;
		&lt;div data-dojo-type="dojox/mobile/EdgeToEdgeStoreList"
				data-dojo-mixins="dojox/mobile/FilteredListMixin"
				data-dojo-attach-point="contacts"
				data-dojo-props="store: this.loadedStores.contacts,
								labelProperty: 'displayName',
								itemRenderer: this.ContactListItem,
								placeHolder: '${nls.search}',
								stateful: !has('phone')"&gt;&lt;/div&gt;
	&lt;/div&gt;
</pre>


<p>The updated <strong>"list" view controller</strong> (list.js) includes:</p>
<ul>
	<li>Returns a specific ListItem subclass (ContactListItem) that deals in particular with handling the selection to
		transition to the detail view and with multi-channel (hiding the arrow on tablets).</li>
	<li>The <strong>init</strong> function which is called when the controller is loaded the first time handles selecting
		the new item when one is added to the list.</li>
	<li>And the <strong>beforeActivate</strong> function which is called before the view is activated each time it is
		shown, handles the tablet case where if no list item is selected it will select the first item by default.</li>
</ul>

<pre class="brush: js; html-script: true;">
	define(["dojo/_base/declare", "dojo/_base/array", "dojo/has", "dojox/mobile/ListItem",
		"dojox/mobile/EdgeToEdgeStoreList", "dojox/mobile/FilteredListMixin"],
		function(declare, array, has, ListItem){
		var ContactListItem = declare(ListItem, {
			target: "detail",
			clickable: true,
			// we don't get an arrow if we are on a two panes layout (tablet)
			noArrow: !has("phone"),
			postMixInProperties: function(){
				this.inherited(arguments);
				this.transitionOptions = {
					params: {
						"id" : this.id
					}
				}
			}
		});

		return {
			ContactListItem: ContactListItem,
			init: function(){
				var view = this;
				this.contacts.on("add", function(item){
					// select the newly added element
					if(!has("phone")){
						array.some(view.contacts.getChildren(), function(child){
							if(child.id == item.id){
								view.contacts.selectItem(child);
							}
							return false;
						});
					}
				});
				this.add.on("click", function(){
					view.contacts.deselectAll();
				});
			},
			beforeActivate: function(){
				// in tablet we want one to be selected at init
				if(!has("phone")){
					// check if something is selected
					var selected = array.some(this.contacts.getChildren(), function(child){
						return child.get("selected");
					});
					if(!selected){
						var item = this.contacts.getChildren()[0];
						this.contacts.selectItem(item);
						// transition
						this.app.transitionToView(this.domNode, {
							target: "detail",
							params: {
								id: item.id
							}
						});
					}
				}
			}
		};
	});
</pre>

<h3 id="updatedetailviews">Add the <strong>"detail"</strong> view, including template, and controller.</h3>


<p><strong>"detail" view template</strong> (detail.html) includes:</p>
<ul>
	<li>A dojox/mobile/Heading which uses NLS strings like ${nls.details}.</li>
	<li>The Heading also has dojox/mobile/ToolBarButton(s) for <strong>Back</strong>, and <strong>Edit</strong>, and
		when in <strong>Edit</strong> mode, buttons for <strong>Cancel</strong> and <strong>Ok</strong>.</li>
	<li>A dojox/mobile/ScrollableView with a dojox/mobile/FormLayout, and labels and fields for:</li>
	<ul>
		<li>Name (first name, and last name).</li>
		<li>Company</li>
		<li>Home and Work Phone</li>
		<li>Home and Work Email</li>
		<li>Delete button (in Edit mode)</li>
	</ul>
</ul>

<pre class="brush: html;">
	&lt;div&gt;
		&lt;div data-dojo-type="dojox/mobile/Heading"
			data-dojo-props="fixed: 'top'"&gt;
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					data-dojo-attach-point="backButton"
					data-dojo-props="arrow: 'left', target: 'list'"
					style="position: absolute; left: 0"
					class="backButton"&gt;${nls.contacts}&lt;/button&gt;
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					data-dojo-attach-point="cancelButton"
					style="position: absolute; left: 0; display: 'none'"
					data-dojo-props="target: 'detail',
						transitionOptions: { params: { edit: false } }"&gt;${nls.cancel}&lt;/button&gt;
			${nls.details}
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					data-dojo-attach-point="editButton"
					style="position: absolute; right: 0"
					data-dojo-props="target: 'detail',
						transitionOptions: { params: { } }"&gt;&lt;/button&gt;
		&lt;/div&gt;
		&lt;div data-dojo-type="dojox/mobile/ScrollableView"&gt;
			&lt;div data-dojo-type="dojox/mobile/FormLayout"&gt;
				&lt;div&gt;
					&lt;label for="company"&gt;${nls.name}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="firstname" name="firstname"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.first}'"
								data-dojo-attach-point="firstname"&gt;
						&lt;input id="lastname" name="lastname"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.last}'"
								data-dojo-attach-point="lastname"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;label for="company"&gt;${nls.company}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="company" name="company"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true"
								data-dojo-attach-point="company"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;label for="phone-home"&gt;${nls.home}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="phone-home" name="phone-home"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.phone}'"
								data-dojo-attach-point="phonehome"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;label for="phone-work"&gt;${nls.work}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="phone-work" name="phone-work"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.phone}'"
								data-dojo-attach-point="phonework"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;label for="mail-home"&gt;${nls.home}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="mail-home" name="mail-home"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.mail}'"
								data-dojo-attach-point="mailhome"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;label for="mail-work"&gt;${nls.work}&lt;/label&gt;
					&lt;fieldset&gt;
						&lt;input id="mail-work" name="mail-work"
								data-dojo-type="dojox/mobile/TextArea"
								data-dojo-props="readOnly: true, placeHolder: '${nls.mail}'"
								data-dojo-attach-point="mailwork"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				&lt;div&gt;
					&lt;div&gt;&lt;/div&gt;
					&lt;button data-dojo-type="dojox/mobile/Button"
							data-dojo-attach-point="deleteButton"
							data-dojo-attach-event="onClick: _deleteContact"
							class="mblRedButton" style="padding: 0 10px"&gt;${nls.delete}&lt;/button&gt;
				&lt;/div&gt;
			&lt;/div&gt;
		&lt;/div&gt;
	&lt;/div&gt;
</pre>


<p>The <strong>"detail" view controller</strong> handles the following:</p>
<ul>
	<li>Initializing the form with the values from the selected contact from the store using the loadedStores property.</li>
	<li>Changing from <strong>View</strong> mode (readOnly) to <strong>Edit</strong> mode to make updates
		or to <strong>Delete</strong> the contact.</li>
	<li>Support to <strong>Cancel</strong> or <strong>Save</strong> updates, and to <strong>Create</strong> a new
		contact when saving one that was added.</li>
	<li>Support to transition back to the <strong>List</strong> view when a contact is <strong>deleted</strong>.</li>
</ul>

<pre class="brush: js; html-script: true;">
	define(["dojo/_base/array", "dojo/_base/lang", "dojo/has", "dojo/when",
		"dojo/Deferred", "dojo/query", "dojo/dom-class","dijit/registry",
		"dojox/mobile/Button", "dojox/mobile/FormLayout", "dojox/mobile/TextArea"],
		function(array, lang, has, when, Deferred, query, domClass, registry){

		var DATA_MAPPING = {
			"phonehome": "phoneNumbers.home",
			"phonework": "phoneNumbers.work",
			"mailhome": "emails.home",
			"mailwork": "emails.work"
		};

		var getStoreField = function(arr, type){
			var index = array.indexOf(arr, function(item){
				return (item.type == type);
			});
			if(index == -1){
				// create one
				arr.push({
					type: type
				});
				index = arr.length - 1;
			}
			return arr[index];
		};

		return {
			beforeActivate: function(){
				// in case we are still under saving previous modifications, let's wait for
				// the operation to be completed as use resulting contact as input
				var view = this;
				when(view._savePromise, function(contact){
					view._savePromise = null;
					view._beforeActivate(contact);
				});
			},
			_beforeActivate: function(contact){
				// get the id of the displayed contact from the params if we don't have a contact
				// or from the contact if we have one
				if(contact){
					this.params.id = contact.id;
				}
				var id = this.params.id;

				// are we in edit mode or not? if we are we need to slightly update the view for that
				var edit = this.params.edit;
				// are we in create mode
				var create = (typeof id === "undefined");
				// change widgets readonly value based on that
				query("input", this.domNode).forEach(function(node){
					registry.byNode(node).set("readOnly", !edit);
				});
				// in edit mode change the label and params of the edit button
				this.editButton.set("label", edit?this.nls.ok:this.nls.edit);
				// put a listener to save the form when we are editing if there is no
				if(!this._onHandler && edit){
					this._onHandler = this.editButton.on("click", lang.hitch(this, this._saveForm));
				}else if(this._onHandler && !edit){
					this._onHandler.remove();
					this._onHandler = null;
				}
				var editButtonOptions = this.editButton.transitionOptions;
				editButtonOptions.params.edit = !edit;
				// also update the edit & ok button to reference the currently displayed item
				editButtonOptions.params.id = id;
				var cancelButtonOptions = this.cancelButton.transitionOptions;
				if(create){
					// if we cancel we want to go back to main view
					cancelButtonOptions.target = "list";
					if(cancelButtonOptions.params.id){
						delete cancelButtonOptions.params.id;
					}
				}else{
					cancelButtonOptions.target = "detail";
					cancelButtonOptions.params.id = id;
				}
				// hide back button in edit mode
				if(edit){
					domClass.add(this.backButton.domNode, "hidden");
				}else{
					domClass.remove(this.backButton.domNode, "hidden");
				}
				// cancel button must be shown in edit mode only,
				// same for delete button if we are not creating a new contact
				this.cancelButton.domNode.style.display = edit?"":"none";
				this.deleteButton.domNode.style.display = (edit&&(typeof id !== "undefined"))?"":"none";

				// let's fill the form with the currently selected contact
				// if nothing selected skip that part
				var view = this;
				var promise = null;
				if(!create && !contact){
					id = id.toString();
					// get the contact on the store
					promise = this.loadedStores.contacts.get(id);
				}else{
					promise = contact;
				}
				when(promise, function(contact){
					view.firstname.set("value", contact ? contact.name.givenName : null);
					view.lastname.set("value", contact ? contact.name.familyName : null);
					if(contact && contact.organizations && contact.organizations.length){
						view.company.set("value", contact.organizations[0].name);
					}else{
						view.company.set("value", null);
					}
					// reset binding fields
					for(var key in DATA_MAPPING){
						view[key].set("value", null);
					}
					if(contact){
						// set each phone number to the corresponding form field
						array.forEach(contact.phoneNumbers, function(number){
							// TODO deal with case where we don't support a particular field
							view["phone"+number.type].set("value",  number.value);
						});
						// set each mail field to the corresponding form field
						array.forEach(contact.emails, function(mail){
							// TODO deal with case where we don't support a particular field
							view["mail"+mail.type].set("value",  mail.value);
						});
					}
				});
			},
			_saveForm: function(){
				var id = this.params.id, view = this;
				view._savePromise = new Deferred();
				if(typeof id === "undefined"){
					view._createContact();
				}else{
					// get the contact on the store
					var promise = this.loadedStores.contacts.get(id.toString());
					when(promise, function(contact){
						view._saveContact(contact);
						// save the updated item into the store
						when(view.loadedStores.contacts.put(contact), function(contact){
							view._savePromise.resolve(contact);
						});
					});
				}
			},
			_createContact: function(){
				var contact = {
					"id": (Math.round(Math.random()*1000000)).toString(),
					"name": {},
					"displayName": "",
					"phoneNumbers": [],
					"emails": [],
					"organizations": []
				};
				var view = this;
				this._saveContact(contact);
				when(this.loadedStores.contacts.add(contact), function(contact){
					view._savePromise.resolve(contact);
				});
			},
			_saveContact: function(contact){
				// set back the values on the contact object
				var value, keys;
				// deal with name first
				var displayName = "";
				value = this.firstname.get("value");
				if(typeof value !== "undefined"){
					contact.name.givenName = value;
					displayName += value;
				}
				value = this.lastname.get("value");
				if(typeof value !== "undefined"){
					contact.name.familyName = value;
					displayName += " " + value;
				}
				contact.displayName = displayName;
				value = this.company.get("value");
				if(typeof value !== "undefined"){
					if(contact.organizations.length == 0){
						contact.organizations.push({});
					}
					contact.organizations[0].name = value;
				}
				for(var key in DATA_MAPPING){
					value = this[key].get("value");
					if(typeof value !== "undefined"){
						// there is a value, save it
						keys = DATA_MAPPING[key].split(".");
						getStoreField(contact[keys[0]], keys[1]).value = value;
					}
					// TODO remove existing value?
				}
			},
			_deleteContact: function(){
				this.loadedStores.contacts.remove(this.params.id.toString());
				// we want to be back to list
				this.app.transitionToView(this.domNode, { target: "list" });
			}
		}
	});
</pre>


<a class="demoBtn demo" href="demos/contactsAppBase/contacts.php" target="_blank">View Contacts App List and Details</a>

<h3 id="updatejsoncordova">Update the JSON configuration file for cordova.</h3>

<p>The JSON configuration file <strong>contacts.json</strong> has to be updated in two sections to support
	<strong>cordova</strong>
	view controller, template and nls settings to the JSON file, and the <strong>list</strong> view is also updated
	so that when not on a phone it will use a constraint of left for the tablet layout.</p>
<pre class="brush: js; html-script: true;">
	"views": {
	  "list": {
	    "controller": "contactsApp/list",
	    "template": "contactsApp/list.html",
	    "nls": "contactsApp/nls/list",
	    "has": {
	      "!phone": {
	        "constraint": "left"
	      }
	   },
	   "detail": {
	     "controller": "contactsApp/detail",
	     "template": "contactsApp/detail.html",
	     "nls": "contactsApp/nls/detail"
	   }
	}
</pre>



<h3 id="updatemaincordova">Update the main module of your application for cordova.</h3>
<p>The main module (contacts.js) will be updated to add the code to check for and support <strong>cordova</strong>.</p>
<ul>
	<li>The <strong>stores</strong> will be updated with a <strong>has</strong> check for cordova to use a dcordova/ContactsStore.</li>
	<li>A <strong>has</strong> check for cordova will be used to update the <strong>dependencies</strong> to use a dcordova/ContactsStore.</li>
</ul>

<pre class="brush: js; html-script: true; highlight: [5,6,7,8,25,26,27,28,29,30,31,32,33,34]">
	"stores": {
		"contacts": {
			"type": "dojo/store/Memory",
			"has": {
				"cordova": {
					"type": "dcordova/ContactsStore",
					"params": { "displayName": true }
				}
			},
			"observable": true,
			"params": {
				"data": [
				:  :  :
	"has": {
		"html5history": {
			"controllers": [
				"dojox/app/controllers/History"
			]
		},
		"!html5history": {
			"controllers": [
				"dojox/app/controllers/HistoryHash"
			]
		},
		"!cordova": {
			"dependencies": [
				"dojo/store/Memory"
			]
		},
		"cordova": {
			"dependencies": [
				"dcordova/ContactsStore"
			]
		}
	}
</pre>


<a class="demoBtn demo" href="demos/contactsAppFull/contacts.php" target="_blank">View Full Contacts App Demo</a>


<h3 id="createAppTips">Tips for creating an Application</h3>

<ul>
	<li>Leverage the View lifecycle methods to perform actions at the right moment in your View controller:
	<strong>init, beforeActivate, afterActivate, beforeDeactivate, afterDeactivate, destroy</strong></li>
	<li>Each view can access the data through the <strong>loadedStores</strong> property. Stores can either be shared or specific to a view.</li>
	<li>Each view can access its translation through the <strong>nls</strong> property. NLS can either be shared or specific to a view, they are inherited.</li>
	<li>In order to get a responsive design and the best performance, leverage <strong>CSS and CSS media queries</strong> where possible to layout/display/hide elements based on the destination channel characteristics.</li>
	<li>Define <strong>« has »</strong> flags that corresponds to your different channels.</li>
	<li>Leverage the <strong>« has »</strong> flags both in the configuration file to configure the layout of the application and in the view templates & controllers to possibly change the behavior of the application based on the channel.</li>
</ul>


<h3 id="buildApp">Building an Application</h3>

<p>In order to help you <strong>build</strong> your application from the configuration file dojox/app provides extensions
	to the Dojo build system.  The <strong>build profile</strong> for the Contacts Application (build.profile.js) looks like this:</p>
<pre class="brush: js; html-script: true;">
	require(["dojox/app/build/buildControlApp"], function(){
	});

	var profile = {
		// relative to this file
		basePath: "../..",
		// relative to base path
		releaseDir: "./contactsApp-release",
		action: "release",
		cssOptimize: "comments",
		mini: true,
		packages:[{
			name: "dojo",
			location: "./dojo"
		},{
			name: "dijit",
			location: "./dijit"
		},{
			name: "contactsApp",
			location: "./contactsApp"
		},{
			name: "dojox",
			location: "./dojox"
		}],
		selectorEngine: "acme",
		layers: {
			"dojo/dojo": {
				boot: true,
				customBase: true
			},
			"contactsApp/contacts": {
				include: ["contactsApp/contacts"]
			}
		}
	};
</pre>
<p>The command you would run to <strong>build</strong> your application would look like this:</p>
<pre class="brush: js; html-script: true;">
	./build.sh --profile ../../contactsApp/build/build.profile.js  
		--appConfigFile ../../contactsApp/contacts.json 
		--appConfigLayer=contactsApp/contacts
</pre>

<p>By default the extension uses the only layer in the profile to bundle all the modules for the application.
	You can specify an alternate layer you want to target by passing <strong>-appConfigLayer=layer/name</strong> on the command line.</p>

<p>Alternatively, you can make sure a layer per-view is built instead of a single layer for the entire application by
	having the <strong>multipleAppConfigLayers</strong> property set to true in your profile.
	This is useful if you have a lot of views that won't get navigated to in a typical usage of your application.
	In that case you might not want to load everything upfront. In this case the controller file of each view will be
	used as the layer for the view.</p>



<h3>Conclusion</h3>

<p>In this tutorial, we've learned how to build a Contacts Application with dojox/app.  To see the code used for this
Contacts application go to: <a href="https://github.com/cjolif/dojo-contacts-app">https://github.com/cjolif/dojo-contacts-app</a></p>

