<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<style type="text/css"> 
a:link,a:visited{ 
 text-decoration:none;  /*超链接无下划线*/ 
} 
a:hover{ 
 text-decoration:underline;  /*鼠标放上去有下划线*/ 
} 
button{background-color:#FFFFFF;
border:hidden;
border-bottom-color:#FFFFFF;
color:#FFFFFF;
}
</style> 
<title>无标题文档</title>
</head>
<?php
session_start();
  $admin_id=$_SESSION['access'];
 ?>
<body background="image/1.jpg">
<div align="right">
<a href="S_index.html" target="_top"><font color="#FF0000"><input type="button" value="首页"></font></a>&nbsp;  <input type="button" value="刷新" onclick="window.parent.main.location.reload();"  border="0" /> &nbsp;<a href="student_update_edit.php?admin_id=<?php echo $admin_id; ?>" target="main"><font color="#FF0000"><input type="button"value="个人资料修改"></font></a>&nbsp; <a href="quite.php" target="_parent"  ><font color="#FF0000"><input type="button" value="退出" ></font></a>



</div>
</body>
</html>
