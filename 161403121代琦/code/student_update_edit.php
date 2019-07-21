<!doctype html>
<html>
<head>
<meta charset="utf-8">
	<title>update_edit.php</title>
</head>
    
<body>
<?php 
  $admin_account=$_GET['admin_id'];
   if ($admin_account=="")  {
	echo "学号不能为空！";
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	die();
  }
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select * from student where S_id='$admin_account'";
  $result=mysqli_query($link,$sql);
  $rows=mysqli_num_rows($result);  
 
  $row=mysqli_fetch_array($result);
  
  $admin_name=$row['S_name'];
  $admin_passwd=$row['S_passwd'];
  $admin_bumen=$row['S_depart'];
  $admin_sex=$row['admin_sex'];

?>
    <p align="left"><b>您当前的位置：</b>[学生管理]-[账号管理]-[编辑用户]</p>
    <form action="student_update.php"  method="GET" >
    <table border="1" align="center">
    <tr>
      <td>学号</td>
      <td><input type="text" name="admin_account" value="<?php echo $admin_account; ?>"></td>
      <td>姓名</td>
      <td><input type="text" name="admin_name" value="<?php echo $admin_name; ?>"></td>
    </tr>

    <tr>
      <td>密码</td>
      <td><input type="password" name="admin_passwd" value=""></td>
      <td>确认密码</td>
      <td><input type="password" name="admin_passwd1" value=""></td>
    </tr>
    
    <tr>
     <td>性别</td>
      <td><input type="radio" name="admin_sex" value="男">男
      <input type="radio" name="admin_sex" value="女">女</td>
      <td>学院：</td>
      <td><select name="admin_bumen"><option value="信息学院">信息学院</option><option value="数学院">数学院</option></td>
    </tr>
    
</table>
<input name="admin_account0" type="hidden" value="<?php echo $admin_account; ?>">
<p align="center"><input name="submit" type="submit" value="保存">
<input name="reset" type="reset" value="重置"></p>
</form>

</body>
</html>
