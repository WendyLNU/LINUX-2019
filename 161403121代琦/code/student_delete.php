
<?php
	$admin_account=$_GET['admin_id'];
	$link=mysqli_connect("localhost","root","");
	mysqli_select_db($link,"sign");
	mysqli_query($link,"set names 'utf8'");
	$sql="delete from student where S_id='$admin_account'";
	$result=mysqli_query($link,$sql);
	$rows=mysqli_num_rows($result);
	$a=mysqli_query($link,$sql);
	
	$sql="delete from sign where Q_S_id='$admin_account'";
	$result=mysqli_query($link,$sql);
	$rows=mysqli_num_rows($result);
  	$b=mysqli_query($link,$sql);
	
  if ($a&&$b)
  {
    echo "删除成功!";
	echo '<a href="student_main.php">返回</a></p>';
  }
  else
  {
    echo '删除失败!';
	echo '<p align=center> <br><a href=" href="student_main.php">返回</a></p>';
  }
  mysqli_close($link);
?>
