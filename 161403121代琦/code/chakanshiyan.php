<html>
<head>
<meta charset="utf-8">
<title>admin_search_all.php</title>
<body>
<?php 
  //$pageno=$_GET['pageno'];
  session_start();
  $admin_account=$_SESSION['access'];
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select path from student where S_id = '$admin_account';";
  $result=mysqli_query($link,$sql);
  $row=mysqli_fetch_array($result);
  $path=$row['path'];
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select * from course where C_id in (select Q_C_id from sign where Q_S_id='$admin_account');";
 
  $result=mysqli_query($link,$sql);
  $rows=mysqli_num_rows($result);  
  if ($rows==0)  {
    echo "没有满足条件的记录！";
  }
  $pagesize=5;  
  $pagecount=ceil($rows/$pagesize);  
  
  if (!isset($pageno)||$pageno<1)
      $pageno=1;
  if ($pageno>$pagecount)
      $pageno=$pagecount;
  $offset=($pageno-1)*$pagesize;
  mysqli_data_seek($result,$offset);
?>
<div ><p><b>您当前的位置：</b>[实验管理]-[查看实验]</p></div>
<br>
<table width="1000" border="1" align="center">
    <tr>
      <td align=center>课程号</td>
      <td align=center>课程名</td>
      <td align=center>实验1</td>
      <td align=center>实验2</td>
      <td align=center>实验3</td>
      <td align=center>实验4</td>
    </tr>
<?php
  $i=0;	
  while($row=mysqli_fetch_array($result))
  {
?>
  <tr> 
    <td><div align="center"><?php echo $row['C_id']; ?></div></td>
    <td><div align="center"><?php echo $row['C_name']; ?></div></td>
    <td><div align="center">
	<a href="shangchuan.html" target="main">上传报告</a> 
    <a href="download/1.php" target="main">查看报告</a> 
	</div></td>
    <td><div align="center">
	<a href="shangchuan.html" target="main">上传报告</a> 
    <a href="download/1.php" target="main">查看报告</a> 
	</div></td>
    <td><div align="center">
	<a href="shangchuan.html" target="main">上传报告</a> 
    <a href="download/1.php" target="main">查看报告</a> 
	</div></td>
    <td><div align="center">
	<a href="shangchuan.html" target="main">上传报告</a> 
    <a href="download/1.php" target="main">查看报告</a> 
	</div></td>
  </tr>
<?php
  $i=$i+1;
  if ($i==$pagesize)
    break; 
  }
  mysqli_free_result($result);
  mysqli_close($link); 
?>
</table>
<div align="center">
[第<?php echo $pageno; ?>页/共<?php echo $pagecount; ?>页]
<?php 
//$href=urlencode($C_id);
if ($pageno<>1){
?>
  <a href="<?php echo $href; ?>&pageno=1">首页</a>
  <a href="<?php echo $href; ?>&pageno=<?php echo $pageno-1; ?>">上一页</a>
<?php
}
if ($pageno<>$pagecount){
?>
<a href="<?php echo $href; ?>&pageno=<?php echo $pageno+1; ?>">下一页</a>
<a href="<?php echo $href; ?>&pageno=<?php echo $pagecount; ?>">尾页</a>
<?php 
}
?>
[共找到<?php echo $rows; ?>个记录]
</div>
</body>
</html>

