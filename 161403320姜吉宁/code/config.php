<?php
 define('DB_NAME','bookinfo'); 

    $mysqli = new mysqli('localhost','root','123456',DB_NAME);
	error_reporting(0);
	ob_start();
	session_start(); //开启缓存

	if($mysqli->connect_error)
	{
		echo "数据库打开失败";
		exit; //数据库打开失败，退出
	}
	 $mysqli->query('set names utf8'); //设置数据库编码
    
?>

