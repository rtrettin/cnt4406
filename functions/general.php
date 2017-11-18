<?php
function escape($string) {
	return htmlentities($string, ENT_QUOTES, 'UTF-8');
}

function getRandNum($min, $max) {
	return rand($min, $max);
}

function debug($val) {
	echo '<pre>';
	print_r($val);
	echo '</pre>';
}