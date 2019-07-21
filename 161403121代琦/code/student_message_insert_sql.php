<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'">
<title>学生数据更新</title>
</head>
<body background="backgroud/7.jpg">
<?php
require('dbconnect.php');
ini_set("display_errors", "Off"); 
session_start();
//注册session变量
$tea_num=$_SESSION['access'];
$stu_number=$_SESSION['stu_number'];
$C_name=$_SESSION['C_name'];
ini_set('date.timezone','Asia/Shanghai');//这是为中国时间
$date=date("Y-m-d H:i:s");//取得当前时间



?>



<?php
//按ID序号逆序排列,只取出一页的留言数
	 
	$Content=$_POST['Content'];
	//$stu_number=$_POST['stu_number'];
//echo $name;
//echo $stu_number;
//0cho $Content;
//echo $idnum;
//echo $sex;
//echo $department;echo $edubg;echo $gry;echo $Content;
//echo $number;

$sqlinput="insert into  student_message values('$stu_number','$C_name','$tea_num','$Content','$date')";
//echo $sqlinput;
if(mysql_query($sqlinput,$conn))
	{
?>
<table  width="800"  height="80" border="1" cellpadding="0" cellspacing="0" align="center" >
  <tr>
	<td align="center" height="40" colspan="4" bgcolor="#FFFFCC" ><font color="#FF0000"></font><?php echo "留言成功" ?></td>
  </tr>
  
  <tr>
    <td bgcolor="#FFFFCC" align="center" bgcolor="#FF99CC"><font color="#FF0000"></font><?php echo "正在跳转到界面" ?></td>
  </tr>
  <tr>
</table>
	<?php
		echo "<script type='text/javascript'>";
		echo "function fun() {";
		echo "window.location.href='experimental_evidence.php'";//要跳转的页面
		echo "}";
		echo "window.setTimeout('fun()',1000)";
		echo "</script>";
	}
else


	echo "数据插入失败";
		
		



?>




</body>
</html>
	
