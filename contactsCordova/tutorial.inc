<?php require("../../../resources/tutHead.inc"); ?>


<h3 id="buildApp">Building an Application</h3>

<p>Now that we have the Contacts Application we will show you how to <strong>build</strong> it,
	<a href="http://dojotoolkit.org/reference-guide/dojox/app.html#building-an-application" target="_blank">dojox/app</a> provides extensions
	to the Dojo build system to make it easy to build an application for production.
	The first step is to create a simple Dojo build system profile<strong>Dojo build system profile</strong> for the Contacts
	Application <strong>(build.profile.js)</strong> that will contain the key information of your build and import the dojox/app
	extensions into the build process as shown below (see require line in the profile):
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
			location: "{path-to-dojo}/dojo"
		},{
			name: "dijit",
			location: "{path-to-dijit}/dijit"
		},{
			name: "contactsApp",
			location: "./contactsApp"
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
			"contactsApp/contacts": {
				include: ["contactsApp/contacts"]
			}
		}
	};
</pre>
<p>The command you would run to <strong>build</strong> your application would look like this:</p>
<pre class="brush: js; html-script: true;">
	./build.sh --profile {pathToApp}contactsApp/build/build.profile.js
		--appConfigFile {pathToApp}contactsApp/contacts.json
		--appConfigLayer=contactsApp/contacts
</pre>

<p>By default the extension uses the only layer in the profile to bundle all the modules for the application.
	You can specify an alternate layer you want to target by passing <strong>-appConfigLayer=layer/name</strong> on the command line.</p>

<p>Alternatively, you can make sure a layer per-view is built instead of a single layer for the entire application by
	having the <strong>multipleAppConfigLayers</strong> property set to true in your profile.
	This is useful if you have a lot of views that won't get navigated to in a typical usage of your application.
	In that case you might not want to load everything upfront. In this case the controller file of each view will be
	used as the layer for the view.</p>


<h3 id="updatejsoncordova">We will update the Contacts Application to support
	<strong>Cordova/PhoneGap</strong> based access to the contacts on a device.</h3>

<p>Look here for details about <a href="http://docs.phonegap.com" target="_blank">Cordova/PhoneGap</a>.</p>

<p>The <strong>Contacts Application</strong> will have the following file structure:</p>

<pre>
	/contactsApp/
			contacts.css
			contacts.js
			contacts.json
			contacts.php
			contacts.profile.js
			package.json
			/build/
				build.profile.js
			/nls/  (the same as the previous Contacts Application)
			/views/  (the same as the previous Contacts Application)
</pre>

<p>The JSON configuration file <strong>contacts.json</strong> has to be updated in two sections to support
	<strong>Cordova/PhoneGap</strong>
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

<h3 id="updatemaincordova">Update the main module of your application for Cordova/PhoneGap.</h3>
<p>The main module (contacts.js) will be updated to add the code to check for and support <strong>Cordova/PhoneGap</strong>.</p>
<pre class="brush: js; html-script: true; highlight: [19, 21,22,26]">
	// we use 'define' and not 'require' to workaround Dojo build system limitation that prevents from making of this file
	// a layer if it using 'require'
	define(["dojo/sniff", "dojo/request", "dojo/json", "dojo/text!contactsApp/contacts.json", "dojox/app/main", "dojox/mobile/common"],
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


<h3 id="updateindexcordova">For Cordova/PhoneGap you will need to setup an index.html file, and build the app for Cordova/PhoneGap.</h3>
<p>This index.html file was setup to work with <strong>Cordova/PhoneGap</strong>.</p>
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
	    	&lt;script src="{path_to_dojox}/dojox/mobile/deviceTheme.js"&gt;&lt;/script&gt;
	        &lt;script src="cordova-2.7.0.js"&gt;&lt;/script&gt;
	        &lt;script src="{path_to_dojo}/dojo/dojo.js"
											data-dojo-config="app: {debugApp: 1}, async: true"&gt;&lt;/script&gt;
			&lt;script&gt
	            require(["contactsApp/contacts"]);
			&lt;/script&gt;
	    &lt;/head&gt;
	    &lt;body&gt;
	    &lt;/body&gt;
	&lt;/html&gt;
</pre>

<p>We can not run in Cordova/PhoneGap a part of this demo, you will need to install Cordova/PhoneGap and build the app to run on Cordova/PhoneGap.
	See the Getting Started Guides at the <a href="http://docs.phonegap.com/" target="_blank">The Cordova/PhoneGap Documentation</a> for more details.
	You can see how the <strong>has</strong> checking allows you to run the same code on a browser.</p>


<a class="demoBtn demo" href="demos/contactsApp/contacts.php" target="_blank">Run the Contacts Application Demo</a>
<a class="demoBtn demo" href="https://github.com/edchat/dojox_app_tutorial/tree/master/contactsCordova/demos/contactsApp" target="_blank">View the contactsApp source on github</a>



<h3 id="createAppTips">Tips for creating an Application using dojox/app</h3>

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

<p>In this tutorial we learned how to build the Contacts Application using the Dojo build extensions in dojox/app, and we
	learned how to setup the Contacts Application to work with Cordova/PhoneGap.  These tutorials have contained links to the code
used for the demos in a github project used for this tutorial, but if you want to run the code on from your own server, you will want to
get the Contacts Application from this github project:
<a href="https://github.com/cjolif/dojo-contacts-app">https://github.com/cjolif/dojo-contacts-app</a></p>

<?php include("../series.inc"); ?>

