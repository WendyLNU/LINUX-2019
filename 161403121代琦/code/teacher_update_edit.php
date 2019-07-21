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
	echo "职工号不能为空！";
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	die();
  }
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select * from teacher where T_id='$admin_account'";
  $result=mysqli_query($link,$sql);
  $rows=mysqli_num_rows($result);  
 
  $row=mysqli_fetch_array($result);
  
  $admin_name=$row['T_name'];
  $admin_passwd=$row['T_passwd'];
  $admin_bumen=$row['T_depart'];
  $admin_email=$row['T_email'];
  $admin_profession=$row['T_profession'];

?>
    <form action="teacher_update.php"  method="GET" >
    <table border="1" align="center">
    <tr>
      <td>职工号</td>
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
     <td>职称</td>
      <td><input type="text" name="admin_profession" value="<?php echo $admin_profession; ?>"></td>
      <td>学院：</td>
      <td><select name="admin_bumen"><option value="信息学院">信息学院</option><option value="数学院">数学院</option></td>
    </tr>
    
    <tr>
      <td>电子邮件</td>
      <td><input type="text" name="admin_email" value="<?php echo $admin_email; ?>"></td>
    </tr>
    
    
</table>
<input name="admin_account0" type="hidden" value="<?php echo $admin_account; ?>">
<p align="center"><input name="submit" type="submit" value="保存">
<input name="reset" type="reset" value="重置"></p>
</form>

</body>
</html>
