<?php
require_once('core/init.php');

$user = new User();
if($user->isLoggedIn()) {
    Redirect::to('index.php');
}
if(Input::exists()) {
    if(Token::check(Input::get('token'))) {
        $validate = new Validate();
        $validation = $validate->check($_POST, array(
            'username' => array(
                'required' => true,
                'max' => 100,
                'min' => 5
            ),
            'password' => array(
                'required' => true
            )
        ));
        if($validation->passed()) {
            $salt = Hash::salt(32);
            $register = $user->create(array(
              'username' => escape(Input::get('username')),
              'password' => Hash::make(escape(Input::get('password')), $salt),
              'salt' => $salt
            ));
            if($register) {
              Redirect::to('login.php');
            }else{
              $errors = 'An error occurred while attempting to process your register request.';
            }
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
  <a href="login.php">Login</a><br />
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
