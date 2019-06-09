<?php
require('dbconnect.php');
//获取管理员将要修改的用户ID
$stu_number=$_GET['number'];
$C_name=$_GET['C_name'];

session_start();
//注册session变量
$_SESSION['stu_number']=$stu_number;
$_SESSION['C_name']=$C_name;
//echo $_SESSION['stu_number'];
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'">
<title>用户信息</title>
</head>
<body background="backgroud/6.jpg">
<?php

//构造SQL语句读取数据库函数
//$sql="select * from student_message where number='$number'";
//$re_page=mysql_query($sql,$conn)or die ("查询数据失败".mysql_error());
//$row=mysql_fetch_array($re_page);
?>


<form name="form1" action="student_message_insert_sql.php" target="main" method="POST">
<table  width="600"  height="160" border="1" cellpadding="0" cellspacing="0" align="center" >

<tr>
	<td   height="32" bgcolor="#FFFFCC" width="30%" bgcolor="#FF99CC"><font color="#FF0000">*</font>学号：</td>
    <td  height="32" bgcolor="#FFFFCC" width="70%"><?php echo $stu_number;?></td>
</tr> 

<tr>
	<td   height="80" bgcolor="#FFFFCC" width="20%" bgcolor="#FF99CC"><font color="#FF0000">*</font>教师留言：</td>
    <td  height="80" width="80%"><textarea name="Content" rows="8" cols="50"></textarea></td> 
</tr>

 
  <tr >
  	<td bgcolor="#FFFFCC" align="center" colspan="2" height="100">
	<input type="submit" stu_number=<?php echo $stu_number;?> value="留言">
	&nbsp;&nbsp;
	<input type="reset" value="重新填写"/>
	</td>
  </tr>
</table>
</form>


<?php
mysql_close($conn);
?>
</body>
</html>
	
