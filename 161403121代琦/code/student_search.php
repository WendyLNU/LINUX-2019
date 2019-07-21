<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>无标题文档</title>
</head>

<body>
<?php 
  $admin_id=$_GET['admin_id'];
  $admin_name=$_GET['admin_name'];
  $admin_bumen=$_GET['admin_bumen'];
  $admin_sex=$_GET['admin_sex'];
  //$pageno=$_GET['pageno'];

  
  $admin_id0="%".$admin_id."%";
  $admin_name0="%".$admin_name."%";
  $admin_bumen0="%".$admin_bumen."%";
  
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
 
 $ConditionsNumber=5;
 $ConditionsArray=array("$admin_id","$admin_name","$admin_bumen","$admin_sex");
 $SearchSQLArray=array(" where S_id like '$admin_id0'"," where S_name like '$admin_name0'"," where S_depart like '$admin_bumen0'"," where S_sex='$admin_sex'");

 for($i=0;$i<$ConditionsNumber;$i++)
 {
	 if($ConditionsArray[$i]=="")
	 	$SearchSQLArray[$i]="";
		$haveWhere=false;

	for($j=0;$j<$i;$j++)
{
$wherePosition=strpos($SearchSQLArray[$j],"where");

if(($wherePosition=="1")&&($haveWhere==false))
{
$SearchSQLArray[$i]=str_replace("where","and",$SearchSQLArray[$i]);
$haveWhere=true; 
}
}
};

for($i=0;$i<$ConditionsNumber;$i++)
$sql=$sql.$SearchSQLArray[$i];
$sql="select * from student".$sql.";";

  $result=mysqli_query($link,$sql);
  $rows=mysqli_num_rows($result);  
  if ($rows==0)  {
    echo "没有满足条件的记录！";
	echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	die();

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
</div>
<div align="center"><a href="student_insert.html" target="main">增加</a>  
   <a href="student_daoru.html" target="main">导入</a></div>
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
	<a href="student_update_edit.php?admin_id=<?php echo $row['admin_id']; ?>" target="main">编辑</a> 
	<a href="student_delete.php?admin_id=<?php echo $row['admin_id']; ?>" target="main">删除</a> 
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
$href=$PHP_SELF."?admin_account=".urlencode($admin_id);
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
</body>
</html>
