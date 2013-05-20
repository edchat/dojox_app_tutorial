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

<h3 id="tutorialParts">This tutorial will be broken down into three sections, with three demos:</h3>

<ol>
	<li><strong>(contactsList)</strong>: Show how to create a very simple application to display a filtered <strong>list of contacts.</strong></li>
	<li><strong>(contactsAppBase)</strong>: Show how to add a <strong>details view</strong> to the application, and how to add:
		<ul>
			<li>Support for contacts to be <strong>edited, added</strong> and <strong>deleted</strong>.</li>
			<li>Support for a <strong>tablet layout</strong> in addition to a <strong>phone layout</strong>, using <strong>"has"</strong> based config support.</li>
			<li>Support to <strong>Transition</strong> from the <strong>list</strong> view to the <strong>details</strong> view in the phone layout.</li>
			<li><strong>History</strong> support for using the browser's back button, using <strong>"has"</strong> based config support.</li>
			<li><strong>NLS</strong> support for strings for the application and for each of the views.</li>
		</ul>
	<li><strong>(contactsAppFull)</strong>: Show how to add support for a <strong>cordova</strong> based access to the
	contacts on a device and build support.</li>
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

<p><strong>(contactsList)</strong> will have the following file structure:</p>

<pre>
	/contactsList/
			contacts.js
			contacts.json
			contacts.php
			/views/
				list.html
				list.js
</pre>

<h3 id="createhtml">Create the main HTML or php file for your application (contacts.php).</h3>

<p>The Dojo mobile CSS (if using Dojo Mobile):</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"  
	src="{path-to-dojox}/dojox/mobile/deviceTheme.js"&gt;
 &lt;/script&gt;
</pre>

<p>Dojo must be loaded, for this tutorial we use a php util like this Utils::printDojoScript(); to load the correct dojo, but normally it would look like this:</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"  
		src="{path-to-dojo}/dojo/dojo.js" data-dojo-config= "async: true"&gt;
 &lt;/script&gt;
</pre>

<p>As well as your main application (AMD) module:</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"&gt;
	require(["contactsList/contacts"]);
 &lt;/script&gt;
</pre>

<h3 id="jsonConfig">The JSON configuration file.</h3>
<p>The JSON Configuration file contains the following:</p>
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

<h3 id="createconfig1">Create the JSON configuration file for <strong>(contactsList)</strong> the file is named (contacts.json).</h3>

<p>The JSON configuration for the (contactsList) includes the dependencies, controllers, store
	defaultView and the list view, as follows:</p>
<pre class="brush: js; html-script: true; highlight: [2,3,10,16,17,56,57]">
	{
		"id": "contactsApp",
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
							:   :   :
						}
					]
				}
			}
		},
		"views": {
			"list": {
				"controller": "contactsList/views/list",
				"template": "contactsList/views/list.html"
			}
		}
	}
</pre>

<h3 id="createmain">Create the main module for your application.</h3>
<p>The main module will load the configuration file and instantiate the application (contacts.js)</p>
<pre class="brush: js; html-script: true; highlight: [4]">
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

<pre class="brush: html; highlight: [2,6,7,9]">
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
<pre class="brush: js; html-script: true; highlight: [5,6]">
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
<a class="demoBtn demo" href="https://github.com/edchat/dojox_app/tree/master/demos/contactsList">View the contactsList App source on github</a>


<h3 id="contactsAppBaseAddDetails">For <strong>(contactsAppBase)</strong> we will add the <strong>Details view</strong></h3>
<p>The <strong>(contactsAppBase)</strong> will include two views.  The first view will include the filtered
	<strong>list of contacts</strong>, and the second view will show the <strong>details of a contact</strong> and
	allow the contact to be edited or deleted.</p>
<div style="float: left; width: 100%; margin-top: 20px;">
	<p>This is how the <strong>(contactsAppBase)</strong> will look on an <strong>iPhone</strong> iOS Simulator.</p>
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
		<p>This is how the <strong>(contactsAppBase)</strong> will look on an <strong>iPad</strong> iOS Simulator.
			<strong>Take note of these differences between the phone and tablet views</strong>:</p>
		<ul>
			<li>The list on the phone includes the ">" but it is not included on the tablet.</li>
			<li>The list on the tablet highlights the selection, but not on the phone.</li>
			<li>The details view on the phone includes a "back" button with the label "Contacts", but on the tablet that button would not be displayed.</li>
			<li>The details view on the tablet is showing "edit" mode, the "edit" mode on the phone would look very similar to this.</li>
		</ul>
		<label style="margin-left: 90px;">Contacts List and Details (in edit mode)</label>
		<img src="images/tabletImage.png" alt="Tablet/Desktop Layout" style="margin:0 auto;display:block;width: 540px;height: 396px;" />
</div>

<p>In order to support the Details view we will also add:</p>
	<ul>
		<li>Support for contacts to be <strong>edited, added</strong> and <strong>deleted</strong>.</li>
		<li>Support for a <strong>tablet layout</strong> in addition to a <strong>phone layout</strong>, using <strong>"has"</strong> based config support.</li>
		<li>Support to <strong>Transition</strong> from the <strong>list</strong> view to the <strong>details</strong> view in the phone layout.</li>
		<li><strong>History</strong> support for using the browser's back button, using <strong>"has"</strong> based config support.</li>
		<li><strong>NLS</strong> support for strings for the application and for each of the views.</li>
	</ul>

<p><strong>(contactsAppBase)</strong> will have the following file structure:</p>

<pre>
	/contactsAppBase/
			contacts.css
			contacts.js
			contacts.json
			contacts.php
			/nls/
				contacts.js
				details.js
				list.js
				/fr/
					contacts.js
					details.js
					list.js
			/views/
				details.html
				details.js
				list.html
				list.js
</pre>


<h3 id="updatecss">Add the CSS for the application.</h3>

<p>We need to add the application CSS file to the html/php (contacts.php):</p>
<pre class="brush: js; html-script: true;">
&lt;link rel="stylesheet" href="contacts.css"&gt;
</pre>

<p>The (contacts.css) <strong>application CSS</strong> file includes a media query with a min-width of 501px,
	so that on a tablet/desktop sized screen the .leftpane will only be set with a width of 250px with a border on the right,
	and the .backButton will be hidden. There is also css related to the mblFormLayout and the input fields.
	The CSS file looks like this:</p>
<pre class="brush: js; html-script: true; highlight: [1,3,4,8]">
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
		display: none !important;
	}

	.mblFormLayout {
		margin: 8px;
		background-color: rgba(0, 0, 0, 0);
	}

	.mblFormLayout > * > *:first-child {
		font-weight: normal;
		color: gray;
	}

	.mblFormLayoutReadOnly .readOnlyHidden {
		display: none !important;
	}

	.mblFormLayoutReadOnly .mblTextArea {
		background-color: rgba(0, 0, 0, 0);
		border-width: 0px;
	}
	.android_theme .mblFormLayoutReadOnly .mblTextArea {
		background-color: #d3d3d3;
	}

	.mblFormLayout .mblTextArea {
		font-weight: bold;
	}
</pre>
<p class="proTip">If changes are made to the min-width in the media query, those changes would also have to be made
	in the has.add("phone"...) code in the main module (contacts.js).</p>


<h3 id="updatenls">Add the NLS files for the application.</h3>

<p>The nls files <strong>(contacts.js, details.js, and list.js)</strong> include the following:</p>
<pre class="brush: js; html-script: true; highlight: [1,9,30]">
	(contacts.js)
		define({
			root: {
				contacts: "Contacts"
			},
			fr: true
		});

	(details.js)
		define({
			root: {
				home: "Home",
				work: "Work",
				cell: "Cell",
				name: "Name",
				first: "Firstname",
				last: "Lastname",
				company: "Company",
				details: "Details",
				mail: "E-mail",
				phone: "Phone",
				edit: "Edit",
				cancel: "Cancel",
				ok: "Ok",
				remove: "Delete the contact"
			},
			fr: true
		});

	(list.js)
		define({
			root: {
				search: "Search",
				add: "Add"
			},
			fr: true
		});
</pre>

<h3 id="updatejson">Update the JSON configuration file.</h3>

<p>The JSON configuration file <strong>contacts.json</strong> has to be updated to add the <strong>details</strong>
	view controller, template and nls settings to the JSON file, and the <strong>list</strong> view is also updated
	so that when not on a phone it will use a constraint of left for the tablet layout.</p>
<pre class="brush: js; html-script: true; highlight: [5,8,12,13,14,15]">
	"views": {
		"list": {
			"controller": "contactsAppBase/views/list",
			"template": "contactsAppBase/views/list.html",
			"nls": "contactsAppBase/nls/list",
			"has": {
				"!phone": {
					"constraint": "left"
				}
			}
		},
		"details": {
			"controller": "contactsAppBase/views/details",
			"template": "contactsAppBase/views/details.html",
			"nls": "contactsAppBase/nls/details"
		}
	}
</pre>

<h3 id="updatemain">Update the main module of your application.</h3>
<p>The main module (contacts.js) will be updated to define the configuration flags needed by the configuration file
	using has.add for <strong>phone and html5history</strong>.</p>
<pre class="brush: js; html-script: true; highlight: [6,7]">
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

<pre class="brush: html; highlight: [3,7,12,14,15,19,21]">
	&lt;div class="leftpanel mblBackground"&gt;
		&lt;script type="dojo/require"&gt;
			has: "dojo/has"
		&lt;/script&gt;
		&lt;div data-dojo-type="dojox/mobile/Heading"
				data-dojo-props="fixed: 'top'"&gt;
			${nls.contacts}
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					style="position: absolute; right: 0"
					data-dojo-props="target: 'details',
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
	<li>Code to return a specific ListItem subclass <strong>(ContactListItem)</strong> that deals in particular with handling the selection to
		transition to the details view and with multi-channel (hiding the arrow on tablets).</li>
	<li>The <strong>init</strong> function, which is called when the controller is loaded the first time, handles clearing
		the selection when the "add" button is pressed, and selecting the new item when one is added to the list.</li>
	<li>And the <strong>beforeActivate</strong> function which is called before the view is activated each time it is
		shown, handles the tablet case where if no list item is selected it will select the first item by default.</li>
</ul>

<pre class="brush: js; html-script: true; highlight: [4,13,28,35,47,52]">
	define(["dojo/_base/declare", "dojo/_base/array", "dojo/has", "dojox/mobile/ListItem",
		"dojox/mobile/EdgeToEdgeStoreList", "dojox/mobile/FilteredListMixin"],
		function(declare, array, has, ListItem){
		var ContactListItem = declare(ListItem, {
			target: "details",
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
				// in tablet we want one to be selected each time but list must be completed for that
				if(!has("phone") && this._completed){
					// check if something is selected
					var selected = array.some(this.contacts.getChildren(), function(child){
						return child.get("selected");
					});
					if(!selected && this.contacts.getChildren().length > 0){
						var item = this.contacts.getChildren()[0];
						this.contacts.selectItem(item);
						// transition
						this.app.transitionToView(this.domNode, {
							target: "details",
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

<h3 id="updatedetailsviews">Add the <strong>"details"</strong> view, including template, and controller.</h3>


<p><strong>The "details" view template</strong> (details.html) includes:</p>
<ul>
	<li>A dojox/mobile/Heading which uses NLS strings like ${nls.details}.</li>
	<li>The Heading also has dojox/mobile/ToolBarButton(s) for <strong>Back</strong>, and <strong>Edit</strong>, and
		when in <strong>Edit</strong> mode, buttons for <strong>Cancel</strong> and <strong>Ok</strong>.</li>
</ul>

<pre class="brush: html;highlight: [1,5,10,14,16]">
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
					data-dojo-props="target: 'details',
						transitionOptions: { params: { edit: false } }"&gt;${nls.cancel}&lt;/button&gt;
			${nls.details}
			&lt;button data-dojo-type="dojox/mobile/ToolBarButton"
					data-dojo-attach-point="editButton"
					style="position: absolute; right: 0"
					data-dojo-props="target: 'details',
						transitionOptions: { params: { } }"&gt;&lt;/button&gt;
		&lt;/div&gt;
		:	:	:
	&lt;/div&gt;
</pre>


<p><strong>The "details" view template</strong> (details.html) also includes:</p>
<ul>
	<li>A dojox/mobile/ScrollableView with a dojox/mobile/FormLayout, and labels and fields for:</li>
	<ul>
		<li><strong>Name</strong> (first name, and last name). Shown below.</li>
		<li><strong>Company</strong>. Shown below.</li>
		<li><strong>Home and Work Phone</strong>. Not shown below, very similar to "Company".</li>
		<li><strong>Home and Work Email</strong>. Not shown below, very similar to "Company"</li>
		<li><strong>Delete button</strong> (in Edit mode). Shown below.</li>
	</ul>
</ul>

<pre class="brush: html; highlight: [9,13,22,31]">
	&lt;div&gt;
	:	:	:
	&lt;div data-dojo-type="dojox/mobile/ScrollableView"&gt;
			&lt;div data-dojo-type="dojox/mobile/FormLayout"
					data-dojo-attach-point="formLayout"&gt;
				&lt;div&gt;
					&lt;label for="firstname"&gt;${nls.name}&lt;/label&gt;
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
								data-dojo-props="readOnly: true, placeHolder: '${nls.company}'"
								data-dojo-attach-point="company"&gt;
					&lt;/fieldset&gt;
				&lt;/div&gt;
				:	:	:
				&lt;div&gt;
					&lt;div&gt;&lt;/div&gt;
					&lt;button data-dojo-type="dojox/mobile/Button"
							data-dojo-attach-point="deleteButton"
							data-dojo-attach-event="onClick: _deleteContact"
							class="mblRedButton" style="padding: 0 10px"&gt;${nls.remove}&lt;/button&gt;
				&lt;/div&gt;
			&lt;/div&gt;
		&lt;/div&gt;
	&lt;/div&gt;
</pre>


<p>The <strong>"details" view controller</strong> (details.js) handles the following:</p>
<ul>
	<li>Initializing the form with the values from the selected contact from the store using the loadedStores property.</li>
	<li>Hide form fields without a value set when in View Mode.</li>
</ul>

	<pre class="brush: js; html-script: true; highlight: [41,43,53,55,58,59,61,75,83, 87, 88]">
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
					:	:	:

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
								// TODO for now we just skip non supported fields, ideally we should have a generic mechanism to deal with them
								var phonekey = "phone"+number.type;
								if(view[phonekey]){
									view[phonekey].set("value",  number.value);
								}
							});
							// set each mail field to the corresponding form field
							array.forEach(contact.emails, function(mail){
								// TODO for now we just skip non supported fields, ideally we should have a generic mechanism to deal with them
								var mailkey = "mail"+mail.type;
								if(view[mailkey]){
									view[mailkey].set("value",  mail.value);
								}
							});
							// hide empty fields when not in edit mode
							if(!edit){
								view._hideEmptyFields(view);
							}
						}
					});
				},
				:	:	:
		});
	</pre>
<p>The <strong>"details" view controller</strong> also handles the following:</p>
<ul>
	<li>Changing the details from <strong>View</strong> mode (readOnly) to <strong>Edit</strong> mode to make updates
		and when called for a <strong>Create</strong>.</li>
</ul>
<pre class="brush: js; html-script: true; highlight: [12,17,23,33,51,52]">
	:	:	:
	return {
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
			cancelButtonOptions.target = "details";
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
		:	:	:
	},
	:	:	:
</pre>

<p>The <strong>"details" view controller</strong> also handles the following:</p>
<ul>
	<li>Support to <strong>Cancel</strong> or <strong>Save</strong> updates, and to <strong>Create</strong> a new
		contact when saving one that was added.</li>
	<li>Support to transition back to the <strong>List</strong> view when a contact is <strong>deleted</strong>.</li>
</ul>

<pre class="brush: js; html-script: true; highlight: [11,13,15,16,4,21,31,32,33,36,43,44,48,49,55,57,64,69,71,73]">
	:	:	:
	return {
		:	:	:
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
				if(!contact.organizations){
					contact.organizations = [{}];
				}else if(contact.organizations.length == 0){
					contact.organizations.push({});
				}
				contact.organizations[0].name = value;
			}
			for(var key in DATA_MAPPING){
				value = this[key].get("value");
				if(typeof value !== "undefined"){
					// there is a value, save it
					keys = DATA_MAPPING[key].split(".");
					if(contact[keys[0]] == null){
						contact[keys[0]] = [];
					}
					getStoreField(contact[keys[0]], keys[1]).value = value;
				}
				// TODO remove existing value?
			}
		},
		_hideEmptyFields: function(view){
			query(".readOnlyHidden", view.formLayout.domNode).forEach(function(node){
				domClass.remove(node, "readOnlyHidden");
			});
			query("input", view.formLayout.domNode).forEach(function(node){
				var val = registry.byNode(node).get("value");
				if(!val && node.parentNode.parentNode && node.id !== "firstname" && node.id !== "lastname"){
					domClass.add(node.parentNode.parentNode, "readOnlyHidden");
				}
			});

		},
		_deleteContact: function(){
			var view = this;
			when(this.loadedStores.contacts.remove(this.params.id.toString()), function(){
				// we want to be back to list
				view.app.transitionToView(view.domNode, { target: "list" });
			});
		}
	}
</pre>


<a class="demoBtn demo" href="demos/contactsAppBase/contacts.php" target="_blank">Run the contactsAppBase</a>
<a class="demoBtn demo" href="https://github.com/edchat/dojox_app/tree/master/demos/contactsAppBase">View the contactsAppBase source on github</a>


<h3 id="updatejsoncordova">For <strong>(contactsAppFull)</strong> we will update the Contacts Application to support
	<strong>cordova</strong> based access to the contacts on a device and build support.</h3>

<p><strong>(contactsAppFull)</strong> will have the following file structure:</p>

<pre>
	/contactsAppFull/
			contacts.css
			contacts.js
			contacts.json
			contacts.php
			contacts.profile.js
			package.json
			/build/
				build.profile.js
			/nls/  (the same as for contactsAppBase)
			/views/  (the same as for contactsAppBase)
</pre>

<p>The JSON configuration file <strong>contacts.json</strong> has to be updated in two sections to support
	<strong>cordova</strong>
<ul>
	<li>The <strong>stores</strong> will be updated with a <strong>has</strong> check for cordova to use a
		dcordova/ContactsStore. This shows the power of using <strong>has</strong> checking in the config along
	with the dojo/store so that the backend data can be swapped out without having to make any changes to the views or controllers.</li>
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

<h3 id="updatemaincordova">Update the main module of your application for cordova.</h3>
<p>The main module (contacts.js) will be updated to add the code to check for and support <strong>cordova</strong>.</p>
<pre class="brush: js; html-script: true; highlight: [19, 21,22,26]">
	// we use 'define' and not 'require' to workaround Dojo build system limitation that prevents from making of this file
	// a layer if it using 'require'
	define(["dojo/sniff", "dojo/request", "dojo/json", "dojo/text!contactsAppFull/contacts.json", "dojox/app/main", "dojox/mobile/common"],
		function(has, request, json, config, Application, common){

		// if we exclude the cordova trick the init could be as simple as:
		// has.add("html5history", !has("ie") || has("ie") > 9);
		// has.add("phone", ((window.innerWidth || document.documentElement.clientWidth) <= common.tabletSize));
		// Application(json.parse(config));

		// trick to know if cordova optional project is here or not
		var init = function(){
			// populate has flag on whether html5 history is correctly supported or not
			has.add("html5history", !has("ie") || has("ie") > 9);
			has.add("phone", ((window.innerWidth || document.documentElement.clientWidth) <= common.tabletSize));
			Application(json.parse(config));
		};
		// check if cordova project's here
		request("../dcordova/sniff.js").then(function(){
			// cordova project is here, sniff cordova features and load the app
			require(["dcordova/sniff"], function(){
				init();
			});
		}, function(){
			// cordova project is not here, directly load the app
			init();
		});
	});
</pre>


<h3 id="updateindexcordova">For cordova you will need to setup an idex.html file, and build the app for cordova.</h3>
<p>This index.html file was setup to work with <strong>cordova</strong>.</p>
<pre class="brush: js; html-script: true; highlight: [9,10,11,12,15]">
	&lt;!DOCTYPE html&gt;
	&lt;html&gt;
	    &lt;head&gt;
	        &lt;meta http-equiv="Content-Type" content="text/html; charset=UTF-8" /&gt;
	        &lt;meta name="format-detection" content="telephone=no" /&gt;
	        &lt;meta name="viewport" content="user-scalable=no, initial-scale=1, maximum-scale=1,
				minimum-scale=1, width=device-width, height=device-height, target-densitydpi=device-dpi" /&gt;
	        &lt;title&gt;Contacts App&lt;/title&gt;
	        &lt;link rel="stylesheet" href="{path_to_contactsApp}/contactsApp/contacts.css"&gt;
	    	&lt;script type="text/javascript" src="{path_to_dojox}/dojox/mobile/deviceTheme.js"&gt;&lt;/script&gt;
	        &lt;script type="text/javascript" src="cordova-2.7.0.js"&gt;&lt;/script&gt;
	        &lt;script type="text/javascript" src="{path_to_dojo}/dojo/dojo.js"
											data-dojo-config="app: {debugApp: 1}, async: true"&gt;&lt;/script&gt;
			&lt;script type="text/javascript"&gt;
	            require(["contactsApp/contacts"]);
			&lt;/script&gt;
	    &lt;/head&gt;
	    &lt;body&gt;
	    &lt;/body&gt;
	&lt;/html&gt;
</pre>

<p>We can not run in cordova a part of this demo, you will need to install cordova and build the app to run on cordova.
	See <a href="http://docs.phonegap.com/en/2.7.0/guide_getting-started_index.md.html#Getting%20Started%20Guides" target="_blank">The Cordova/Phone Gap Getting Started Guides</a> for more details.
	You can see how the <strong>has</strong> checking allows you to run the same code on a browser.</p>


<a class="demoBtn demo" href="demos/contactsAppFull/contacts.php" target="_blank">Run the Full Contacts App Demo</a>
<a class="demoBtn demo" href="https://github.com/edchat/dojox_app_tutorial/tree/master/demos/contactsAppFull">View the contactsAppFull source on github</a>


<h3 id="buildApp">Building an Application</h3>

<p>In order to help you <strong>build</strong> your application from the configuration file dojox/app provides extensions
	to the Dojo build system.  The <strong>build profile</strong> for the Contacts Application <strong>(build.profile.js)</strong> looks like this:</p>
<pre class="brush: js; html-script: true;">
	require(["dojox/app/build/buildControlApp"], function(){
	});

	var profile = {
		// relative to this file
		basePath: "../..",
		// relative to base path
		releaseDir: "./contactsAppFull-release",
		action: "release",
		cssOptimize: "comments",
		mini: true,
		packages:[{
			name: "dojo",
			location: "{path-to-dojo}/dojo"
		},{
			name: "dijit",
			location: "{path-to-dijit}/dijit"
		},{
			name: "contactsAppFull",
			location: "./contactsAppFull"
		},{
			name: "dojox",
			location: "{path-to-dojox}/dojox"
		}],
		selectorEngine: "acme",
		layers: {
			"dojo/dojo": {
				boot: true,
				customBase: true
			},
			"contactsAppFull/contacts": {
				include: ["contactsAppFull/contacts"]
			}
		}
	};
</pre>
<p>The command you would run to <strong>build</strong> your application would look like this:</p>
<pre class="brush: js; html-script: true;">
	./build.sh --profile {pathToApp}contactsAppFull/build/build.profile.js
		--appConfigFile {pathToApp}contactsAppFull/contacts.json
		--appConfigLayer=contactsAppFull/contacts
</pre>

<p>By default the extension uses the only layer in the profile to bundle all the modules for the application.
	You can specify an alternate layer you want to target by passing <strong>-appConfigLayer=layer/name</strong> on the command line.</p>

<p>Alternatively, you can make sure a layer per-view is built instead of a single layer for the entire application by
	having the <strong>multipleAppConfigLayers</strong> property set to true in your profile.
	This is useful if you have a lot of views that won't get navigated to in a typical usage of your application.
	In that case you might not want to load everything upfront. In this case the controller file of each view will be
	used as the layer for the view.</p>



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



<h3>Conclusion</h3>

<p>In this tutorial, we've learned how to build a Contacts Application with dojox/app.  To see the code used for this
Contacts application go to: <a href="https://github.com/cjolif/dojo-contacts-app">https://github.com/cjolif/dojo-contacts-app</a></p>

