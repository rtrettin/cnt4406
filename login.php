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
                'min' => 5
            ),
            'password' => array(
                'required' => true
            )
        ));
        if($validation->passed()) {
            $login = $user->login(strtolower(Input::get('username')), Input::get('password'), false);
            if($login) {
                Redirect::to('index');
            }else{
                $errors = 'An error occurred while attempting to process your login request. An incorrect username or password was entered.';
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
    <title>CNT4406 - Login</title>
</head>
<body>
    <form role="form" action="" method="POST">
        <?php
        if(!empty($errors)) {
            echo '<div><strong>Errors: </strong>' . $errors . '</div>';
        }
        ?>
        <input type="text" name="username" id="username">
        <input type="password" name="password" id="password">
        <input type="submit" value="Login">
        <input type="hidden" name="token" value="<?php echo Token::generate(); ?>" />
    </form>
</body>
</html>
