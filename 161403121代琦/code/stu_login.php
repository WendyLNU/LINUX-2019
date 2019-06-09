

<?php 

ini_set("display_errors", "Off");	
error_reporting(E_ALL^E_NOTICE);
$access=$_POST['access'];
//初始化session
session_start();
//注册session变量
$_SESSION['access']=$access;
 
?>



<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'">
<title>用户登入检查</title>
</head>
<body background="backgroud/7.jpg">
<?php
//PHP与HEML 混编模式
require('dbconnect.php');
//echo 111;

?>



<?php
//从数据库中取出每条留言，按ID序号逆序排列,只取出一页的留言数

	$pswd=$_POST["pswd"];
//echo $pswd;
//echo $access;
	$sql="select * from student where S_id='$access' and S_passwd='$pswd'";
	//echo $sql;
$result=mysqli_query($conn,$sql);
$num=mysqli_num_rows($result);//取得结果集中的行数
	?>
    
    <?php    
//echo 111;
if ($num>"0") 
	{
?>

<table  width="800"  height="80" border="1" cellpadding="0" cellspacing="0" align="center" >
  <tr>
	<td align="center" height="40" colspan="4" bgcolor="#FFFFCC" ><font color="#FF0000"></font><?php echo "登入成功" ?></td>
  </tr>
  
  <tr>
    <td bgcolor="#FFFFCC" align="center" bgcolor="#FF99CC"><font color="#FF0000"></font><?php echo "正在跳转到界面" ?></td>
  </tr>
  <tr>
</table>
<?php
		echo "<script type='text/javascript' target='_parent'>";
		echo "function fun() {";
		echo " window.location.href='S_index.html'";//要跳转的页面
		echo "}";
		echo "window.setTimeout('fun()',1000)";
		echo "</script>";
	}

		else
	{
?>
<table  width="800"  height="160" border="1" cellpadding="0" cellspacing="0" align="center" >
  <tr>
	<td align="center" height="30" colspan="4" bgcolor="#FFFFCC" ><font color="#FF0000">*</font><?php echo "登入失败" ?></td>
  </tr>
  
  <tr>
    <td align="center" bgcolor="#FFFFCC"  bgcolor="#FF99CC"><font color="#FF0000">*</font><?php echo "请重新登入" ?></td>
  </tr>
  <tr>
</table>
		<?php
		echo "<script type='text/javascript'>";
		echo "function fun() {";
		echo "window.location.href='index.html'";//要跳转的页面
		echo "}";
		echo "window.setTimeout('fun()',1000)";
		echo "</script>";
		
		
	}
?>





</body>
</html>
	
