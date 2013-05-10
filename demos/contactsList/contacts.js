define(["dojo/json", "dojo/text!contactsList/contacts.json", "dojox/app/main", "dojox/mobile/common"],
	function(json, config, Application, common){
		Application(json.parse(config));
});