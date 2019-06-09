<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';

$link=connect();
if(is_manage_login($link)){
	skip('index.php','ok','您已经登录，请不要重复登录！');
}
if(isset($_POST['submit'])){
	include_once 'inc/check_login.inc.php';
	$_POST=escape($link,$_POST);
	$query="select * from sfk_manage where name='{$_POST['name']}' and pw=md5('{$_POST['pw']}')";
	$result=execute($link, $query);
	if(mysqli_num_rows($result)==1){
		$data=mysqli_fetch_assoc($result);
		$_SESSION['manage']['name']=$data['name'];
		$_SESSION['manage']['pw']=sha1($data['pw']);
		$_SESSION['manage']['id']=$data['id'];
		$_SESSION['manage']['level']=$data['level'];
		skip('index.php','ok','登录成功！');
	}else{
		skip('login.php','error','用户名或者密码错误，请重试！');
	}
}
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<title>后台登录</title>
<meta name="keywords" content="后台登录" />
<meta name="description" content="后台登录" />
<style type="text/css">
body {
	background:#f7f7f7;
	font-size:14px;
}
#main {
	width:360px;
	height:320px;
	background:#fff;
	border:1px solid #ddd;
	position:absolute;
	top:50%;
	left:50%;
	margin-left:-180px;
	margin-top:-160px;
}
#main .title {
	height: 48px;
	line-height: 48px;
	color:#333;
	font-size:16px;
	font-weight:bold;
	text-indent:30px;
	border-bottom:1px dashed #eee;
}
#main form {
	width:300px;
	margin:20px 0 0 40px;
}
#main form label {
	margin:10px 0 0 0;
	display:block;
}
#main form label input.text {
	width:200px;
	height:25px;
}
#main form label .vcode {
	display:block;
	margin:0 0 0 56px;
}
#main form label input.submit {
	width:200px;
	display:block;
	height:35px;
	cursor:pointer;
	margin:0 0 0 56px;
}
</style>
</head>
<body>
	<div id="main">
		<div class="title">管理登录</div>
		<form method="post">
			<label>用户名：<input class="text" type="text" name="name" /></label>
			<label>密　码：<input class="text" type="password" name="pw" /></label>
			<label>验证码：<input class="text" type="text" name="vcode" /></label>
			<label><img class="vcode" src="../show_code.php" /></label>
			<label><input class="submit" type="submit" name="submit" value="登录" /></label>
		</form>
	</div>
</body>
</html>