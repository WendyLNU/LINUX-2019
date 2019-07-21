<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>学生管理</title>
</head>
<div>
<H3 align="left"><b>您当前的位置：</b>[学生管理]-[账号管理]</h3>
<h3 align="center">【查询】</h3>
<form method="get" align="center" name="form1" id="form1" action="student_search.php" target="main">
     <table border="1" align="center">
  <tbody>
    <tr>
      <td>学号：</td>
      <td><input type="text" name="admin_id"></td>
      <td>姓名：</td>
      <td><input type="text" name="admin_name"></td>
      </td>
      <td>学院：</td>
      <td><select name="admin_bumen"><option value="信息学院">信息学院</option><option value="数学院">数学院</option></td>
    </tr>
    <tr>
    	<td>性别：</td>
      <td><input type="radio" name="admin_sex" value="男" checked>男
      <input type="radio" name="admin_sex" value="女">女</td>
      <td colspan="8"><p align="main"><input name="submit" type="submit" value="确定">
<input name="reset" type="reset" value="重置"></p></td>

  </tbody>
  </table>

  </div>
  
  <br>
  <br>
  
  <div>
  	<?php 
  //$pageno=$_GET['pageno'];

  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select * from student order by S_id asc";

 
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
<div align="center"><a href="student_insert.html" target="main"><input type="button" value="增加"></a>  
   <a href="student_daoru.html" target="main"><input type="button" value="导入"></a> <a href="student_daochu.php" target="main"><input type="button" value="导出"></a></div>
   </div>
   <br>
<table width="1000" border="1" align="center">
    <tr>
      <td align=center>学号</td>
      <td align=center>姓名</td>
      <td align=center>学院</td>
      <td align=center>性别</td>
      <td align=center>操作</td>
    </tr>
<?php
  $i=0;	
  while($row=mysqli_fetch_array($result))
  {
?>
  <tr> 
    <td><div align="center"><?php echo $row['S_id']; ?></div></td>
    <td><div align="center"><?php echo $row['S_name']; ?></div></td>
    <td><div align="center"><?php echo $row['S_depart']; ?></div></td>
    <td><div align="center"><?php echo $row['S_sex']; ?></div></td>
    <td><div align="center">
	<a href="student_update_edit.php?admin_id=<?php echo $row['S_id']; ?>" target="main">编辑</a> 
	<a href="student_delete.php?admin_id=<?php echo $row['S_id']; ?>" target="main">删除</a> 
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
$href=$PHP_SELF."?".urlencode($admin_id);
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
   
  
  
<body>
</body>
</html>
