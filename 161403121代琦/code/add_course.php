
<?php 
	$depart=$_GET['depart'];
	
	$link=mysqli_connect("localhost","root","")or die("数据库连接失败！");
	
	mysqli_select_db($link,"sign")or die("数据链接失败！");
	mysqli_query($link,"set names 'utf-8'");
	$sql="select * from student where S_depart= '$depart'";
	$result=mysqli_query($link,$sql);
	while($row=mysqli_fetch_array($result)){
		for($i=0;$i<count($_POST["list"]);$i++){
			$sql1="insert into sign(Q_C_id,Q_S_id) values('{$_POST["list"][$i]}','{$row['S_id']}')";
			
			$result1=mysqli_query($link,$sql1);
		}
	}
	if($result1){
	?>
		<form action="teacherinsert.php" id="form1" name="form1" method="post"></form>
		<script language="javascript">
			alert("添加成功！");
			form1.submit();
		</script>
	<?php	
	}
	else{?>
		
		<script language="javascript">
			alert("添加失败！");
			history.back();
		</script>
	<?php 
	}
	?>
