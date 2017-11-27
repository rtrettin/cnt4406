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
		<style type="text/css">
			table,th,td {
				border: 1px solid black;
			}
			th,td {
				padding: 15px;
			}
		</style>
  </head>
  <body>
		<a href="logout.php">Logout</a><br /><br /><br />
		<h3>Hello <?php echo $user->data()->username; ?>!</h3>
		<p>Your session ID is: <?php echo $_COOKIE['PHPSESSID']; ?></p>
		<br /><br />
		<p>Here are your stored password values:</p>
		<?php
		$db = DB::getInstance();
		$results = $db->get('users', array('id', '=', $user->data()->id));
		$data = $results->all();
		if(count($data) == 1) {
			for($i = 0; $i < count($data); $i++) {
				$passwordplain = $data[$i]->passwordplain;
				$salt = $data[$i]->salt;
				$passwordsha256salt = $data[$i]->passwordsha256salt;
				$passwordsha256 = $data[$i]->passwordsha256;
				$passwordmd5salt = $data[$i]->passwordmd5salt;
				$passwordmd5 = $data[$i]->passwordmd5;
			}
		}
		?>
		<p><strong>Plaintext Password:</strong> <?php echo $passwordplain; ?></p>
		<p><strong>Salt Value:</strong> <?php echo $salt; ?> <a href="changesalt.php">Change Salt</a></p>
		<p><strong>SHA256+Salt Password*:</strong> <?php echo $passwordsha256salt; ?></p>
		<p><strong>SHA256 Password:</strong> <?php echo $passwordsha256; ?></p>
		<p><strong>MD5+Salt Password:</strong> <?php echo $passwordmd5salt; ?></p>
		<p><strong>MD5 Password:</strong> <?php echo $passwordmd5; ?></p>
  </body>
</html>
