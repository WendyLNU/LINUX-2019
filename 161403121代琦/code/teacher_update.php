
<?php
  $admin_account=$_GET['admin_account'];
  $admin_account0=$_GET['admin_account0'];
  $admin_name=$_GET['admin_name'];
  $admin_passwd=$_GET['admin_passwd'];
  $admin_passwd1=$_GET['admin_passwd1'];
  $admin_profession=$_GET['admin_profession'];
  $admin_bumen=$_GET['admin_bumen'];
  $admin_email=$_GET['admin_email'];
  
  if ($admin_account==""||$admin_passwd==""||$admin_passwd1=="")  
  {
     echo "内容不得为空";
	 echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
     die();
  }
  
  if ($admin_passwd!=$admin_passwd1)  
  {
     echo "两次输入密码不一致";
	 echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
     die();
  }
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  
  if ($admin_account<>$admin_account0)  {
    $sql="select T_id from teacher where T_id='$admin_account'";
    $result=mysql_query($sql,$link);
    $row = mysql_fetch_array($result);
    if ($row)  {
       echo "此职工号已经存在!";
	   echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
       die();
     }
   }
  
  $sql="update teacher set T_id='$admin_account',T_name='$admin_name',T_passwd='$admin_passwd',T_depart='$admin_bumen',T_profession='$admin_profession',T_email='$admin_email' where T_id='$admin_account0'";

  if (mysqli_query($link,$sql))
  {
    echo "修改成功!";
	echo '<a href="student_main.php">返回</a></p>';
  }
  else
  {
    echo '修改失败!';
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
  }
  mysqli_close($link);
?>
