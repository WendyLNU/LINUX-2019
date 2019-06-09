<?php
require('dbconnect.php');
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<link href="css/style.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'" />
<title>ZoneBoard</title>
</head>
<body>
<div ><p><b>您当前的位置：</b>[教师留言]-[教师回复]</p></div>
<br>
<?php 
include('head.php');

?>

<!--主体部分-->
<div class="main">

<div class="left_body">
<?php

//获取管理员将要修改的用户ID



session_start();
//注册session变量
$access=$_SESSION['access'];

//echo $_SESSION['stu_number'];
?>
<?php
//PHP与HEML 混编模式

//构造SQL语句读取数据库函数,用来计算留言总数和分页所用
$sql="select T_name,datetime,Content from student_message,teacher where stu_number like '$access' and teacher.T_id=student_message.tea_num;";
//echo $sql;
$result=mysqli_query($conn,$sql);
$num=mysqli_num_rows($result);//取得结果集中的行数

//定义每页显示留言数
$page_size=5;

//计算页数
//如果总留言数小于分页数，则页数为1
if($num<=$page_size)
{
	$page_count=1;
}
//如果总留言数大于每页数，则计算总页数
if($num % $page_size)
{
	$page_count=(int)($num/$page_size)+1;
} 
else
{
	$page_count=$num/$page_size;
}
//获取当前显示页数
if(isset($_GET['page']))
{
	$page=intval($_GET['page']);//intval函数是将变量转换为10进制
}
else
{
	$page=1;
}

?>

<!--留言内容循环-->
<div class="content">
<?php
//从数据库中取出每条留言，按datetime序号逆序排列,只取出一页的留言数
$sqlpage="select T_name,datetime,Content,T_email  from student_message,teacher where stu_number like '$access' and teacher.T_id=student_message.tea_num order by datetime desc limit ".($page-1)*$page_size.",$page_size"; //limit后面第一个是,起始datetime，第二个是取出数量
//echo $sqlpage;
$re_page=mysqli_query($conn,$sqlpage)or die ("查询数据库失败".mysqli_error());
while($row=mysqli_fetch_array($re_page))
{
?>
<table width="800" border="1px" cellpadding="0" cellspacing="0" style="border-collapse:collapse; border-style:solid">
<tr>
<td width="200" align="center"><font color="#0000FF">老师</font>:<font color="#CC0000"><?php echo $row['T_name']; ?></font></td>
<td width="600">
<font size="-1" color="#CC0000"><?php echo $row['datetime']; ?></font>
&nbsp;
<font color="#CC0000">E-mail</font>:<a href="mailto:"><?php echo $row['T_email']; ?>
<img src="images/email.gif" style="width:16px; height:16px;"  border="0"/>
</a>
</td>
</tr>

<tr>
<td height="105" rowspan="3" align="center">内容</td>
<td style="margin:0" >
<?php echo $row['Content']; ?>
</td>
</tr>
</table>
</br>
<?php
}
?>
</div>

<div style="float:right">
<?php
//如果总页数大于1，则显示所有页数
echo "<h3>";
if($page_count>1)
{
	echo "页数:";
	for($i=1;$i<=$page_count;$i++)
	{
		if($i==$page)
		{
			echo "$i  ";
		}
		else
		{
			echo "<a href=?page=$i>$i</a>";
		}
	}
}
echo "</h3>";
?>
</div>

</div>



</div>

</body>
</html>
