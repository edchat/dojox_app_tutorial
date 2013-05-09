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