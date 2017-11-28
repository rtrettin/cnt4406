<?php
require_once('core/init.php');

$user = new User();
if($user->isLoggedIn()) {
    Redirect::to('index');
}
if(Input::exists()) {
    if(Token::check(Input::get('token'))) {
        $validate = new Validate();
        $validation = $validate->check($_POST, array(
            'username' => array(
                'required' => true,
                'max' => 100,
                'min' => 5,
                'unique' => true
            ),
            'password' => array(
                'required' => true,
                'max' => 100
            )
        ));
        if($validation->passed()) {
            $salt = Hash::salt(32);
            $register = $user->create(array(
              'username' => escape(Input::get('username')),
              'passwordsha256salt' => Hash::make(escape(Input::get('password')), $salt),
              'passwordsha256' => Hash::makeNoSalt(escape(Input::get('password'))),
              'passwordmd5salt' => Hash::makeMD5(escape(Input::get('password')), $salt),
              'passwordmd5' => Hash::makeMD5NoSalt(escape(Input::get('password'))),
              'passwordplain' => escape(Input::get('password')),
              'salt' => $salt
            ));
            Redirect::to('login');
        }else{
            $errors = '';
            foreach($validation->errors() as $error) {
                $errors .= $error . '<br />';
            }
        }
    }
}
?>
<!doctype html>
<html>
<head>
    <meta charset="utf-8" />
    <title>CNT4406 - Register</title>
</head>
<body>
  <a href="login">Login</a><br />
    <h1>Register</h1>
    <form role="form" action="" method="POST">
        <?php
        if(!empty($errors)) {
            echo '<div><strong>Errors: </strong>' . $errors . '</div>';
        }
        ?>
        Username: <input type="text" name="username" id="username"><br /><br />
        Password: <input type="password" name="password" id="password"><br /><br />
        <input type="submit" value="Register">
        <input type="hidden" name="token" value="<?php echo Token::generate(); ?>" />
    </form>
</body>
</html>
