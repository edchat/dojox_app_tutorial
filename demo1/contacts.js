define(["dojo/json", "dojo/text!demo1/contacts.json", "dojox/app/main", "dojox/mobile/common"],
	function(json, config, Application, common){
		Application(json.parse(config));
});