<?php
class Hash {
	public static function make($string, $salt = '') {
		return hash('sha256', $string . $salt);
	}

	public static function makeNoSalt($string) {
		return hash('sha256', $string);
	}

	public static function makeMD5($string, $salt = '') {
		$value = $string . $salt;
		$value = escapeshellarg($value);
		$value = escapeshellcmd($value);
		$output = array();
		$return_val = -1;
		exec('/var/www/html/md5src/md5.x ' . $value, $output, $return_val);
		sleep(2);
		return $output[0];
	}

	public static function makeMD5NoSalt($string) {
		$value = $string;
		$value = escapeshellarg($value);
		$value = escapeshellcmd($value);
		$output = array();
		$return_val = -1;
		exec('/var/www/html/md5src/md5.x ' . $value, $output, $return_val);
		sleep(2);
		return $output[0];
	}

	public static function salt($length) {
		return uniqid(mt_rand(), true);
	}

	public static function unique() {
		return self::make(uniqid());
	}
}
