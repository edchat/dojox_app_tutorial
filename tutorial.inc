<?php require("../../resources/tutHead.inc"); ?>

<h3>Getting Started</h3>

<p><strong>dojox/app</strong> is a Dojo-based application framework that increases maintainability and reduces coding effort by providing:</p>
<ul>
	<li>A predefined JSON-based (possibly external) configuration file</li>
	<li>A typical application structure</li>
	<li>A notion of views, view templates, controllers and a transition system between the views</li>
	<li>A set of controllers that the application can leverage including layout and transition controllers</li>
	<li>A build system to bundle your application in a limited set of files to be downloaded or installed onto the system</li>
</ul>

<p>Even if built on top of Dojo, dojox/app is UI Toolkit agnostic, and the application views can be developed with:</p>
<ul>
	<li>Dijit</li>
	<li>Dojo Mobile</li>
	<li>Any other JavaScript/HTML5 toolkit like jQuery Mobile</li>
</ul>

<h3 id="jsonConfig">What the JSON Configuration Contains</h3>
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

<p>Here is a small sample JSON configuration:</p>

<pre class="brush: js;">
{
  "id": "myApp",
  "controllers": [
    "dojox/app/controllers/Transition",
    "dojox/app/controllers/History"
  ],
 "stores": {
    "myStore": {
       "type": "myApp/MyStore"
     }
  }
  "views": {
    "list": {
         "template": "myApp/list.html",
          "nls": "myApp/nls/list"
     },
     "detail": {
          "controller" : "myApp/detail",
          "template":  "myApp/list",
          "nls": "myApp/nls/detail"
    }
}</pre>

<h3 id="createAnApp">Creating a Contacts Application</h3>

<p> The aim is to create a simple <strong>Contacts application</strong> based on <strong>Dojo Mobile & Application Framework 1.9</strong> with support to:</p>
<ul>
	<li><strong>List, search & display</strong> your contacts</li>
	<li><strong>Edit or Delete</strong> an existing contact</li>
	<li><strong>Add</strong> a new contact</li>
</ul>
<p> The <strong>Contacts application</strong> will include two views.  The first view will include a <strong>list of contacts</strong>, and the second view will show the <strong>details of a contact</strong> and allow the contact to be edited or deleted.</p>
<div style="float: left; width: 100%; margin-top: 20px;">
	<p> This is how the <strong>Contacts application</strong> will look on an <strong>iPhone</strong>.</p>
	<div style="float: left; width: 50%;">
		<label  style="margin-left: 90px;">Contacts List on iPhone</label>
		<img src="images/phoneImage1.png" alt="Phone Contacts List View" style="margin:0 auto;display:block;" />
	</div>
	<div style="float: left; width: 50%;">
		<label style="margin-left: 90px;">Contacts Details on iPhone </label>
		<img src="images/phoneImage.png" alt="Phone Contacts Details View" style="margin:0 auto;display:block;" />
	</div>
</div>
<div style="float: left; width: 100%; margin-top: 20px; margin-bottom: 20px;">
		<p>This is how the <strong>Contacts application</strong> will look on an <strong>iPad</strong>.</p>
		<label style="margin-left: 90px;">Contacts List and Details on iPad</label>
		<img src="images/tabletImage.png" alt="Tablet/Desktop Layout" style="margin:0 auto;display:block;width: 540px;height: 396px;" />
</div>

<h3 id="createhtml">Create the main HTML file for your application.</h3>

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

<p>Your application CSS file:</p>
<pre class="brush: js; html-script: true;">
&lt;link rel="stylesheet" href="contacts.css"&gt;
</pre>

<p>As well as your main application (AMD) module:</p>
<pre class="brush: js; html-script: true;">
&lt;script type="text/javascript"&gt;
	require(["contactsApp/contacts "]);
 &lt;/script&gt;
</pre>

<h3 id="createconfig1">Create the configuration file, contacts.json.</h3>

<p>It can be pretty minimal at first, just the controllers, the stores, no views:</p>
<pre class="brush: js; html-script: true;">
	"id": "contactsApp",
		"dependencies": [
		  "dojo/store/Memory",
		],
		"controllers": [
		  "dojox/app/controllers/Load",
		  "dojox/app/controllers/Transition",
		  "dojox/app/controllers/Layout",
		  "dojox/app/controllers/History"
		],
		"stores": {
		  "contacts": {
		    "type": "dojo/store/Memory",  
			"has": {" cordova" : { "type" : "dcordova/ContactsStore" } }, 
			"observable": true
	    }
	  }
</pre>

<p>Add views definition, layout & possible transitions to the JSON:</p>
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

<p>Add initial view declaration:</p>
<pre class="brush: js; html-script: true;">
	"defaultView": "list",
</pre>

<h3 id="createmain">Create the main module for your application.</h3>
<p>The main module will define the configuration flags needed by the configuration file and load the configuration file to instantiate the application</p>
<pre class="brush: js; html-script: true;">
	define(["dojox/app/main", "dojo/sniff", "dojo/json",        
			"dojo/text!./contacts.json“],    
	function(Application, has, json, config, common){
	   has.add("phone", (window.innerWidth <= 500));
	   Application(json.parse(config));
	});
</pre>

<h3 id="createviews">Create the views, including their templates, controllers, and nls translation files.</h3>
<p><strong>"list"</strong> view template</p>
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
							stateful: !has('phone')"&gt;
		&lt;/div&gt;
	&lt;/div&gt;</pre>

<p><strong>"detail"</strong> view template</p>
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

<p><strong>"CSS"</strong> file that will provide the CSS for the views:</p>
<pre class="brush: css;">
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

	.create {
		display: none;
	}
</pre>

<p>The <strong>"list"</strong> view controller returns a specific ListItem subclass that deals in particular with multi-channel (hiding the arrow on tablets).
	Followed by the <strong>init</strong> function which is called when the controller is loaded the first time
	and the <strong>beforeActivate</strong> function which is called before the view is activated each time it is shown.</p>
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

<p>The <strong>"deatil"</strong> view controller is in charge of both adjusting the display based on the channel as well as
	binding the data from the configuration store to the form, for it is using the loadedStores property:</p>
<pre class="brush: js; html-script: true;">
	define(["dojo/_base/array", "dojo/_base/lang", "dojo/has", "dojo/when", "dojo/query", "dojo/dom-class",
		"dijit/registry", "dojox/mobile/Button", "dojox/mobile/FormLayout", "dojox/mobile/TextArea"],
		function(array, lang, has, when, query, domClass, registry){

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
			beforeActivate: function(previousView){
				// get the id of the displayed contact from the params
				var id = this.params.id;

				// are we in edit mode or not? if we are we need to slightly update the view for that
				var edit = this.params.edit;
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
				if(typeof id === "undefined"){
					// if we cancel we want to go back to main view
					cancelButtonOptions.target = "list";
					if(cancelButtonOptions.params.id){
						delete cancelButtonOptions.params.id;
					}
					domClass.add(this.backButton.domNode, "create");
				}else{
					cancelButtonOptions.target = "detail";
					cancelButtonOptions.params.id = id;
					domClass.remove(this.backButton.domNode, "create");
				}
				// cancel button must be shown in edit mode only, same for delete button if we are not creating a new contact
				this.cancelButton.domNode.style.display = edit?"":"none";
				this.deleteButton.domNode.style.display = (edit&&(typeof id !== "undefined"))?"":"none";

				// let's fill the form with the currently selected contact
				// if nothing selected skip that part
				var view = this;
				var promise = null;
				if(typeof id !== "undefined"){
					id = id.toString();
					// get the contact on the store
					promise = this.loadedStores.contacts.get(id);
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
				if(typeof id === "undefined"){
					view._createContact();
				}else{
					// get the contact on the store
					var promise = this.loadedStores.contacts.get(id);
					when(promise, function(contact){
						view._saveContact(contact);
						// save the updated item into the store
						view.loadedStores.contacts.put(contact);
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
				// we created a new id update navigation
				var editButtonOptions = this.editButton.transitionOptions;
				editButtonOptions.params.id = contact.id;
				this._saveContact(contact);
				this.loadedStores.contacts.add(contact);
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
				this.loadedStores.contacts.remove(this.params.id);
				// we want to be back to list
				this.app.transitionToView(this.domNode, { target: "list" });
			}
		}
	});
</pre>

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

<p>Note on page 29 of 1801 impact2013 slides</p>




<a class="demoBtn demo" href="demo/contacts.php" target="_blank">View Demo</a>


<h3>Conclusion</h3>

<p>In this tutorial, we've learned about Dijit's powerful template system as implemented by the mixins
	<code>_TemplatedMixin</code> and <code>_WidgetsInTemplateMixin</code>, and how you can use this system to quickly
	create your own custom widgets for use in your applications. We've reviewed how the template system's <em>attach
	points</em> and <em>event attachments</em> allow you to quickly bind DOM elements to your code, and how to replace
	values in your template &mdash; as well as how to include other widgets in your widget template to create
	"uber-widgets".</p>

<p>Happy widget building!</p>
