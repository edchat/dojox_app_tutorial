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

<h3 id="buildAnApp">Building a Contacts Application</h3>

<p> The aim is to build a simple <strong>Contacts application</strong> based on <strong>Dojo Mobile & Application Framework 1.9</strong> with support to:</p>
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

<p>Note on page 20 of 1801 impact2013 slides</p>




<a class="demoBtn demo" href="demo/contacts.php" target="_blank">View Demo</a>


<h3>Conclusion</h3>

<p>In this tutorial, we've learned about Dijit's powerful template system as implemented by the mixins
	<code>_TemplatedMixin</code> and <code>_WidgetsInTemplateMixin</code>, and how you can use this system to quickly
	create your own custom widgets for use in your applications. We've reviewed how the template system's <em>attach
	points</em> and <em>event attachments</em> allow you to quickly bind DOM elements to your code, and how to replace
	values in your template &mdash; as well as how to include other widgets in your widget template to create
	"uber-widgets".</p>

<p>Happy widget building!</p>
