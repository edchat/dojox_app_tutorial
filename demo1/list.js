define(["dojox/mobile/EdgeToEdgeStoreList"],
	function(){
	return {
		init: function(){
			this.contacts.on("click", function(e){
				console.log(e.target.innerHTML + ": was clicked.");
			});
		}
	};
});