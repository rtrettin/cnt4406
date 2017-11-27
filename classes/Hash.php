<?php
class Hash {
	public static function make($string, $salt = '') {
		return hash('sha256', $string . $salt);
	}

	public static function makeNoSalt($string) {
		return hash('sha256', $string);
	}

	public static function makeMD5($string, $salt = '') {
		return '';
		// exec('binary ' . $string . $salt, $output, $return_val);
	}

	public static function makeMD5NoSalt($string) {
		return '';
		// exec('binary ' . $string, $output, $return_val);
	}

	public static function salt($length) {
		return uniqid(mt_rand(), true);
	}

	public static function unique() {
		return self::make(uniqid());
	}
}
