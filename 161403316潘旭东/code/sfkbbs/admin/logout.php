<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$link=connect();
if(!is_manage_login($link)){
	header('Location:login.php');
}
session_unset();//Free all session variables
session_destroy();//销毁一个会话中的全部数据
setcookie(session_name(),'',time()-3600,'/');//销毁保存在客户端的卡号（session id）
header('Location:login.php');
?>