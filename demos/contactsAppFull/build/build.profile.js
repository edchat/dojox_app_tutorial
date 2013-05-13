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
		location: "/Users/edchat/Documents/htdocsDevelopment/aptanaWorkSpace/dojo19WS4/dojo"
	},{
		name: "dijit",
		location: "/Users/edchat/Documents/htdocsDevelopment/aptanaWorkSpace/dojo19WS4/dijit"
	},{
		name: "contactsAppFull",
		location: "./contactsAppFull"
	},{
		name: "dojox",
		location: "/Users/edchat/Documents/htdocsDevelopment/aptanaWorkSpace/dojo19WS4/dojox"
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



