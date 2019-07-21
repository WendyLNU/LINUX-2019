<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=‘utf-8’">
<title>学生数据数据</title>
</head>
<body background="backgroud/6.jpg">
<?php
//PHP与HEML 混编模式
require('dbconnect.php');
session_start();
//注册session变量
$access=$_SESSION['access'];


//构造SQL语句读取数据库函数,
//$sql="select * from sign and student where Q_S_id like '$access' and sign.Q_S_id like student.S_id ";
$sql="select C_name, Q_S_id,S_name from sign,course,student where sign.Q_C_id=course.C_id and sign.Q_S_id=student.S_id";

//echo $sql;
$result=mysql_query($sql,$conn);
$num=mysql_num_rows($result);//取得结果集中的行数

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
	//echo $page;
}
else
{
	$page=1;
}

?>

<div ><H3><b>您当前的位置：</b>[教师管理]-[实验检查]</H3></div>


<br>
<!--留言内容循环-->
<div class="content">

<form name="form1" action="tea_student_course_ifo_query.php" target="main" method="POST">
<table  width="860"  height="80" border="1" cellpadding="0" cellspacing="0" align="center" >
  <tr  align="center">
  	<td align="center" colspan="6" height="30">
	信息查询
	</td>
  </tr> 

<tr>
<td  width="100" height="30"   align="center"><font color="#FF0000"></font>实验课名:</td>
<td width="150"><input  type="text"  name="course_name" id="course_name" "width: 150px;" ></span>

<td  width="100" height="30"   align="center"><font color="#FF0000"></font>姓名:</td>
<td width="150"><input  type="text"  name="S_name" id="S_name" "width: 150px;" ></span>

<td  width="100" height="30" align="center" ><font color="#FF0000"></font>学号:</td>
<td width="150"><input  type="text"  name="S_num" id="S_num" "width: 150px;" ></td>
 <tr >
  	<td align="center" colspan="6" height="30">
	<input type="submit" onClick="return check(document.getElementById('email_address').value);" value="查询">
	&nbsp;&nbsp;
	<input type="reset" value="重填"/>
	</td>
  </tr>
</table>

</form>

<table width="860"  border="1px" align="center">
<tr>
<td bgcolor="#c6e7f1" width="125" height="30" align="center"><font color="#0000FF">课程名</font></td>
<td bgcolor="#c6e7f1" width="109" align="center"><font color="#0000FF">学号</font></td>
<td bgcolor="#c6e7f1" width="101" align="center"><font color="#0000FF">学生姓名</font></td>
<td bgcolor="#c6e7f1" width="102" align="center"><font color="#0000FF">实验课1</font></td>
<td bgcolor="#c6e7f1" width="117" align="center"><font color="#0000FF">实验课2</font></td>
<td bgcolor="#c6e7f1" width="103" align="center"><font color="#0000FF">实验课3</font></td>

<td bgcolor="#c6e7f1" width="114" align="center" ><font color="#0000FF">实验课4</font></td>
<td bgcolor="#c6e7f1" width="37" align="center" ><font color="#0000FF">留言</font></td>

</tr>
</table>
<?php
//从数据库中取出每条留言，按ID序号逆序排列,只取出一页的留言数
$sqlpage="select C_name, Q_S_id,S_name,Q_sign1,Q_sign2,Q_sign3,Q_sign4 from sign,course,student where sign.Q_C_id=course.C_id and sign.Q_S_id=student.S_id order  by C_name desc limit ".($page-1)*$page_size.",$page_size"; //limit后面第一个是,起始ID，第二个是取出数量
//echo $sqlpage;
$re_page=mysql_query($sqlpage,$conn)or die ("查询数据失败".mysql_error());
while($row=mysql_fetch_array($re_page))
{
?>
<table width="860"  border="1px" align="center">
<tr>
<td   style="word-break:break-all" bgcolor="#c6e7f1" width="126" height="30" align="center"><font color="#0000FF"><?php echo $row['C_name']; ?></font></td>
<td   style="word-break:break-all" bgcolor="#c6e7f1" width="112" height="30" align="center"><font color="#0000FF"><?php echo $row['Q_S_id' ]; ?></font></td>
<td   style="word-break:break-all" bgcolor="#c6e7f1" width="105" height="30" align="center"><font color="#0000FF"><?php echo $row['S_name']; ?></font></td>
<td  style="word-break:break-all" bgcolor="#c6e7f1" width="106" align="center"><font color="#0000FF">
<img src="images/<?php echo $row['Q_sign1'];?>.png" style="width:16px; height:16px;"  border="0"/>

</font></td>

<td  style="word-break:break-all" bgcolor="#c6e7f1" width="120" align="center"><font color="#0000FF">
<img src="images/<?php echo $row['Q_sign2'];?>.png" style="width:16px; height:16px;"  border="0"/>
</font></td>

<td  style="word-break:break-all" bgcolor="#c6e7f1" width="107" align="center"><font color="#0000FF">
<img src="images/<?php echo $row['Q_sign3'];?>.png" style="width:16px; height:16px;"  border="0"/>
</font></td>

<td  style="word-break:break-all" bgcolor="#c6e7f1" width="116" align="center"><font color="#0000FF">
<img src="images/<?php echo $row['Q_sign4'];?>.png" style="width:16px; height:16px;"  border="0"/>
</font></td>



<td width="33"  bgcolor="#c6e7f1">
<font color="#CC0000"></font>
<a href="tea_student_message_pad_modify.php?number=<?php echo $row['Q_S_id'];?>&C_name=<?php echo $row['C_name'];?>">
<img src="images/modify.png" style="width:16px; height:16px;"  border="0"/>
</a>

</td>
</tr></table>

<?php
}
?>
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


</body>
</html>
	
