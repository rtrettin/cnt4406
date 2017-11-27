<?php
require_once('core/init.php');
$user = new User();
if(!$user->isLoggedIn()) {
  Redirect::to('login.php');
}else{
  $db = DB::getInstance();
  $newsalt = Hash::salt(32);
  $results = $db->get('users', array('id', '=', $user->data()->id));
  $data = $results->all();
  if(count($data) == 1) {
    $passwordplain = $data[0]->passwordplain;
  }else{
    die('Could not get plaintext password from DB.');
  }
  $newsha256 = Hash::make($passwordplain, $newsalt);
  $newmd5 = Hash::makeMD5($passwordplain, $newsalt);
  $results = $db->update('users', $user->data()->id, array(
    'salt' => $newsalt,
    'passwordsha256salt' => $newsha256,
    'passwordmd5salt' => $newmd5
  ));
  echo 'Salt changed...redirecting';
  sleep(5);
  Redirect::to('index.php');
}
?>
