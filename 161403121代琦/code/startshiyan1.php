<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8' />
<title>无标题文档</title>
</head>

<body>
<?php 
	$s=$_POST["s"];
	$link=mysqli_connect("localhost","root","")or die("数据库连接失败！");
	$count=0;
	mysqli_select_db($link,"sign")or die("数据链接失败！");
	mysqli_query($link,"set names 'utf-8'");
	for($i=0;$i<count($_POST["list"]);$i++){
		$sql="update sign set Q_count='1',Q_a='$s[$i]' where Q_C_id='{$_POST["list"][$i]}'";
		$result=mysqli_query($link,$sql);
		$count++;
	}
	
	if($count>0){
	?>
    
		<form action="student_main.php"  id="form1" name="form1" method="post"></form>
		<script language="javascript">
			alert("实验设置成功！");
			history.go(-1);
		</script>
	<?php	
	}
	else{?>
		
		<script language="javascript">
			alert("实验设置失败！");
			history.go(-1);
		</script>
	<?php 
	}
	?>
	</body>
	</html>
