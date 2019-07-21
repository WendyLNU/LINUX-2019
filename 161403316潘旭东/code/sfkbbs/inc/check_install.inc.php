<?php 
if(empty($_POST['db_host'])){
	exit('数据库地址不得为空！<a href="install.php">点击返回</a>');
}
if(empty($_POST['db_port'])){
	exit('数据库服务端口不得为空！<a href="install.php">点击返回</a>');
}
if(empty($_POST['db_user'])){
	exit('数据库用户名不得为空！<a href="install.php">点击返回</a>');
}
if(!isset($_POST['db_pw'])){
	exit('数据库密码不存在！<a href="install.php">点击返回</a>');
}
if(empty($_POST['db_database'])){
	exit('数据库名称不得为空！<a href="install.php">点击返回</a>');
}
$_POST['manage_name']='admin';
if(empty($_POST['manage_pw']) || mb_strlen($_POST['manage_pw'])<6){
	exit('后台管理员密码不得少于6位！<a href="install.php">点击返回</a>');
}
if(empty($_POST['manage_pw_confirm']) || $_POST['manage_pw']!=$_POST['manage_pw_confirm']){
	exit('两次密码输入不一致！<a href="install.php">点击返回</a>');
}
$link=@mysqli_connect($_POST['db_host'],$_POST['db_user'],$_POST['db_pw'],'',$_POST['port']);
if(mysqli_connect_errno()){
	exit('数据库连接失败，请填写正确的数据库连接信息！<a href="install.php">点击返回</a>');
}
mysqli_set_charset($link,'utf8');
if(!mysqli_select_db($link,$_POST['db_database'])){
	$query="CREATE DATABASE IF NOT EXISTS `{$_POST['db_database']}` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci";
	mysqli_query($link,$query);
	if(mysqli_errno($link)){
		exit('数据库创建失败，请检查数据库账户权限！<a href="install.php">点击返回</a>');
	}
	mysqli_select_db($link,$_POST['db_database']);
}
?>