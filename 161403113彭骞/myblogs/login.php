<?php
session_start();

//注销登录
if($_GET['action'] == "logout"){
    unset($_SESSION['username']);
    echo '注销登录成功！点击此处 <a href="login.html">登录</a>';
    exit;
}

//登录
if(!isset($_POST['submit'])){
    exit('非法访问!');
}
$username = htmlspecialchars($_POST['username']);
$password = MD5($_POST['pw']);

//包含数据库连接文件
$conn = @mysql_connect("localhost","debian-sys-maint","clwKlOWnhyqrM5Zf");
if (!$conn){
    die("连接数据库失败：" . mysql_error());
}
mysql_select_db("taka", $conn);

//字符转换，读库
mysql_query("set character set 'gbk'");

//写库
mysql_query("set names 'gbk'");

//检测用户名及密码是否正确
$check_query = mysql_query("select uid from user where username='$username' and password='$password' 
limit 1");
if($result = mysql_fetch_array($check_query)){
    //登录成功
    $_SESSION['username'] = $username;
    echo $username,' 欢迎你！进入 <a href="index.html">用户中心</a><br />';
    echo '点击此处 <a href="login.php?action=logout">注销</a> 登录！<br />';
    exit;
} else {
    exit('登录失败！点击此处 <a href="javascript:history.back(-1);">返回</a> 重试');
}
?>