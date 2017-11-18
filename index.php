<?php
require_once('core/init.php');
$user = new User();
if(!$user->isLoggedIn()) {
	Redirect::to('login.php');
}
?>
<!doctype html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>CNT4406 - Index</title>
  </head>
  <body>
		<a href="logout.php">Logout</a><br />
    <p>table here</p>
  </body>
</html>
