<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>插入</title>
</head>

<body>
<?php $C_id=$_POST["C_id"];
		$C_name=$_POST["C_name"];
		$C_start_time=$_POST["C_start_time"];
		$C_over_time=$_POST["C_over_time"];
		$C_room=$_POST["C_room"];
		$C_ip=$_POST["C_ip"];
		$C_department=$_POST["department"];
		$link=mysqli_connect("localhost","root","");
		mysqli_select_db($link,"sign") or die("ʧ��!");
		mysqli_query($link,"set names 'utf-8'");
		$sql="insert into course(C_id,C_name,C_department,C_start_time,C_over_time,C_room,C_ip) 									values('$C_id','$C_name','$C_department','$C_start_time','$C_over_time','$C_room','$C_ip')";
	$result=mysqli_query($link,$sql);
	if($result){
			
			?>
		 	<form name="name0" id="name0" method="post" action="insert.php"></form>
		 <script language="javascript">
		 	alert("插入成功");
		 	name0.submit();
			</script>
		<?php }
		 else {
		 echo "添加失败，请重新添加";
		 ?>
		 <form name="name1" id="name1" method="post" action="insert_course.php"></form>
		 <script language="javascript">
		 	name1.submit();
			</script><br />
<?php 
}
?>

</body>
</html>
