<?php
ini_set("display_errors", "Off"); 

error_reporting(E_ALL | E_STRICT); 
$conn=mysqli_connect("localhost","root","")or die("不能连接数据库:".mysql_error());//连接数据库
mysqli_query("SET NAMES 'utf-8'");
mysqli_select_db($conn,"sign")or die("不能选择数据库:".mysql_error());//连接数据库

?>
