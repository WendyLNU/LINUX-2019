
<?php
  $admin_id=$_GET['admin_id'];
  $admin_name=$_GET['admin_name'];
  $admin_passwd=$_GET['admin_passwd'];
  $admin_passwd1=$_GET['admin_passwd1'];
  $admin_sex=$_GET['admin_sex'];
  $admin_bumen=$_GET['admin_bumen'];
  if ($admin_id==""||$admin_passwd==""||$admin_passwd1=="")  
  {
     echo "内容不得为空";
	 	echo '<p align=center> <br><a href="student_insert.html">返回</a></p>';
     die();
  }
  
  if ($admin_passwd!=$admin_passwd1)  
  {
     echo "两次输入密码不一致";
	 	echo '<p align=center> <br><a href="studeny_insert.html">返回</a></p>';
     die();
  }
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  
  $sql="select admin_id from student where S_id='$admin_id'";
  $result=mysqli_query($link,$sql);
  $row=mysqli_fetch_array($link,$result);
  if ($row)   
  {
     echo "此学号已经存在!\n";
	 echo '<p align=center> <br><a href="admin_insert.php">返回</a></p>';
     die();
  }
  $sql="insert into student (S_id,S_name,S_passwd,S_sex,S_depart)";
  $sql=$sql." values('$admin_id','$admin_name','$admin_passwd','$admin_sex','$admin_bumen')";
  if (mysqli_query($link,$sql))
  {
    echo "增加成功!";
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';

  }
  else
  {
    echo '增加失败!';	
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	}
  mysqli_close($link);
  ?>
