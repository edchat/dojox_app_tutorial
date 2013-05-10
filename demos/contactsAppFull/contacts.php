<!DOCTYPE HTML>
<html lang="en">
	<head>
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,minimum-scale=1,user-scalable=no"/>
		<meta name="apple-mobile-web-app-capable" content="yes" />

		<title>Full Contacts App Demo: Using dojox/app</title>
		<link rel="stylesheet" href="contacts.css">
	<!--
		<link rel="stylesheet" href="style.css" media="screen">
		<link rel="stylesheet" href="../../../resources/style/demo.css" media="screen">
	-->
		<?php
			include_once($_SERVER['DOCUMENT_ROOT'] . implode('/', array_slice(explode('/', dirname($_SERVER['PHP_SELF'])), 0, 4)) . '/Utils.php');
		?>
		<!-- TODO: should I add a Utils:printmobileTheme for this? -->
		<script type="text/javascript" src="/js/dojo/1.9/dojox/mobile/deviceTheme.js"></script>
	</head>
	<body>
		<script>
			// See the using Custom Modules with a CDN Tutorial for an explination of how
			// on how 
			var dojoConfig = {
				async: true,
				dojoBlankHtmlUrl: location.pathname.replace(/\/[^/]+$/, "") + "/blank.html",
				packages: [{
					name: "contactsAppFull",
					location: location.pathname.replace(/\/[^/]+$/, "") + "/"
				}]
			};
		</script>

		<?php
			Utils::printDojoScript();
		?>

		<script type="text/javascript">
			require(["contactsAppFull/contacts"]);
		</script>

	</body>
</html>
