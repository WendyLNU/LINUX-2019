<!-- 验证码 -->
<?php 
function vcode($width=120,$height=40,$fontSize=30,$countElement=5,$countPixel=100,$countLine=4){ //验证码默认值
	ob_clean();
	header('Content-type:image/jpeg');
	$element=array('a','b','c','d','e','f','g','h','i','j','k','m','n','o','p','q','r','s','t','u','v','w','x','y','z');
	$string='';
	for ($i=0;$i<$countElement;$i++){ //随机字母的数目
		$string.=$element[rand(0,count($element)-1)];
	}
	$img=imagecreatetruecolor($width, $height);
	$colorBg=imagecolorallocate($img,rand(200,255),rand(200,255),rand(200,255));
	$colorBorder=imagecolorallocate($img,rand(200,255),rand(200,255),rand(200,255));
	$colorString=imagecolorallocate($img,rand(10,100),rand(10,100),rand(10,100));
	imagefill($img,0,0,$colorBg);
	for($i=0;$i<$countPixel;$i++){ //点的数目
		imagesetpixel($img,rand(0,$width-1),rand(0,$height-1),imagecolorallocate($img,rand(100,200),rand(100,200),rand(100,200)));
	}
	for($i=0;$i<$countLine;$i++){ //线的数目
		imageline($img,rand(0,$width/2),rand(0,$height),rand($width/2,$width),rand(0,$height),imagecolorallocate($img,rand(100,200),rand(100,200),rand(100,200)));
	}
	//imagestring($img,5,0,0,'abcd',$colorString);
	imagettftext($img,$fontSize,rand(-5,5),rand(5,15),rand(30,35),$colorString,'font/ManyGifts.ttf',$string);
	imagejpeg($img);
	imagedestroy($img);
	return $string;
}
?>