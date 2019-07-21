<?php
error_reporting(0);
session_start();
getCode(4,50,20);

function getCode($num,$w,$h) {
	$code = "";
	for ($i = 0; $i < $num; $i++) {
		$code .= rand(0, 9);
	}
	//4位验证码也可以用rand(1000,9999)直接生成
	//将生成的验证码写入session，备验证页面使用
	$_SESSION['PHP_M2T'] = $code;
	setcookie("mimi", md5($code), time()+1200);
	//创建图片，定义颜色值
	Header("Content-type: image/PNG");
	$im = imagecreate($w, $h);
	$black = imagecolorallocate($im, 255, 0, 63);
	$gray = imagecolorallocate($im, 200, 200, 200);
	$bgcolor = imagecolorallocate($im, 255, 255, 255);

	imagefill($im, 0, 0, $bgcolor);

	//画边框
	//imagerectangle($im, 0, 0, $w-1, $h-1, $black);

	//在画布上随机生成大量黑点，起干扰作用;
	for ($i = 0; $i < 10; $i++) {
		imagesetpixel($im, rand(0, $w), rand(0, $h), $black);
	}
	//将数字随机显示在画布上,字符的水平间距和位置都按一定波动范围随机生成
	$strx = rand(1,3);
	for ($i = 0; $i < $num; $i++) {
		$strpos = rand(2, 6);
		imagestring($im, 5, $strx, $strpos, substr($code, $i, 1), $black);
		$strx += rand(8, 12);
	}
	imagepng($im);
	imagedestroy($im);
}
?>
