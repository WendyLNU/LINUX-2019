<?php 
require ('config.php');
	//如果没有登录，退出
	if ($_SESSION['id']==""){
			echo "<script language=javascript>alert('您还没有登陆');window.location='landing.php'</script>";
			exit();
		}
	$book_id=$_GET[book_id];	
	//构建sql语句还书
	//在lend表中删除该借书记录
	$returnsql="delete from lend where book_id='$book_id' and user_id=".$_SESSION['id'];
	$mysqli->query($returnsql,$conn) or die ("删除借书记录失败：".mysqli_error());
	//在book表中增加一本现存书数量
	$booksql="update yx_books set leave_number=leave_number+1 where id='$book_id'";
	$mysqli->query($booksql,$conn) or die ("增加剩余书数量失败：".mysqli_error());
	echo "<script language=javascript>alert('还书成功');window.location='index.php'</script>";
?>
