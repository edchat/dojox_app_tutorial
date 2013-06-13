define(["dojo/dom","dojox/mobile/EdgeToEdgeStoreList", "dojox/mobile/FilteredListMixin"],
	function(dom){
	return {
		init: function(){
			this.contacts.on("click", function(e){
				dom.byId("selectionMade").innerHTML = e.target.innerHTML + ": was clicked.";
			});
		}
	};
});