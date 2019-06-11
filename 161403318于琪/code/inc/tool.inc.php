<!-- 跳转函数 + 判断用户是否登录函数-->
<?php 
function skip($url,$pic,$message){
$html=<<<YU
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<meta http-equiv="refresh" content="3;URL={$url}" />
<title>正在跳转中</title>
<meta name="keywords" content="后台界面" />
<meta name="description" content="后台界面" />
<link rel="stylesheet" type="text/css" href="style/remind.css" />
</head>
<body>
<div class="notice"><span class="pic {$pic}"></span>{$message} <a href="{$url}">3秒后自动跳转!</a></div>
</body>
</html>
YU;
echo $html;
exit;
}
function is_login($link){ //看register的setcookie,验证用户是否登录
	if(isset($_COOKIE['sfk']['name']) && isset($_COOKIE['sfk']['pw'] )){
		$query="select * from member where name='{$_COOKIE['sfk']['name']}' and sha1(pw)='{$_COOKIE['sfk']['pw']}'";
		$result=execute($link, $query);
		if(mysqli_num_rows($result)==1){
			$data=mysqli_fetch_assoc($result);
			return $data['id']; //如果登陆了则返回id号
		}else{
			return false;
		}
		
	}else{
		return false;
	}
}
?>