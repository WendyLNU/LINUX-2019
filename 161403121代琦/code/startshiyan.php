<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'" />
<title>开始实验</title>
<script language="javascript">
   <!-- Begin

function check(o) {
	var ch=document.getElementsByName(o);
	if (window.document.getElementById("checkbox1").checked ) {
		for (var i = 0; i < ch.length; i++) 
			ch[i].checked =true;
 	}
	else {
		for (i = 0; i <ch.length; i++) 
				ch[i].checked =false;
	}
}


//  End -->
</script>
</head>

<body>
<div ><h3>您当前的位置-[签到控制]</h3></div>
<div ><b>请老师在每次手动控制，实验课开始和即将开始的为第几次实验</b></div>
<hr />
<?php 
	
	$link=mysqli_connect("localhost","root","")or die("数据库连接失败！");
	
	mysqli_select_db($link,"sign")or die("数据链接失败！");
	mysqli_query($link,"set names 'utf-8'");
	
	$sql="select  * from course where C_id in(select Q_C_id from sign) order by C_id";
	
	$result=mysqli_query($link,$sql);
	$rows=mysqli_num_rows($result);
	$pagesize=3;
	$pagecount=ceil($rows/$pagesize);
	if(isset($_GET["pageno"]))
		$pageno=$_GET["pageno"];
	if(!isset($pageno)||$pageno<1)
		$pageno=1;
	if($pageno>$pagecount)
		$pageno=$pagecount;
		
	$offset=($pageno-1)*$pagesize;
	mysqli_data_seek($result,$offset);
	
	?>
	<form action="startshiyan1.php" method="post" name="form1" id="form1">
	<table width="100%" border="0" cellpadding="2" cellspacing="2" bgcolor="#cccccc">
<tr bgcolor="#999999" align="center">
<td><div align="center"><input type="checkbox" name="checkbox1" id="checkbox1" onClick="check('list[]')" ></div></td>
<td><b>课程ID</b></td>
<td><b>课程名称</b></td>
<td><b>开始时间</b></td>
<td><b>结束时间</b></td>
<td><b>实验学院</b></td>
<td><b>实验教室</b></td>
<td><b>实验室IP</b></td>
<td><b>实验次数</b></td>
</tr>
<?php
	$i=0;
	while($row=mysqli_fetch_array($result)){
	?>
	
<tr bgcolor="#ffffff">
 <td><div align="center"><input type="checkbox" name="list[]" value="<?php echo $row['C_id'];?>" ></div></td>
<td><div align="center"><?php echo $row['C_id'];?></div></td>
<td><div align="center"><?php echo $row['C_name'];?></div></td>
<td><div align="center"><?php echo $row['C_start_time'];?></div></td>
<td><div align="center"><?php echo $row['C_over_time'];?></div></td>
<td><div align="center"><?php echo $row['C_department'];?></div></td>

<td><div align="center"><?php echo $row['C_room'];?></div></td>
<td><div align="center"><?php echo $row['C_ip'];?></div></td>
<td><div align="center"><select name="s[]"><option value="1">第1次实验</option><option value="2">第2次实验</option><option value="3">第3次实验</option><option value="4">第4次实验</option></select></div></td>
</tr>
<?php
	$i=$i+1;
	if($i==$pagesize)
	break;
	}
	mysqli_free_result($result);
	mysqli_close($link);
	?>
<tr><td colspan="9">&nbsp;</td></tr>
</table>

<div align="center">
[第<?php echo $pageno;?>页/共<?php echo $pagecount;?>页]
<?php // $href=$_SERVER['PHP_SELF']."?subit=".urlencode($subit);
if($pageno<>1){
?>
<a href="<?php echo "startshiyan.php"?>?pageno=1">首页</a>
<a href="<?php echo "startshiyan.php"?>?pageno=<?php echo $pageno-1; ?>">上一页</a>
<?php
}
if($pageno<>$pagecount){
?>
<a href="<?php echo "startshiyan.php"?>?pageno=<?php echo $pageno+1;?>">下一页</a>
<a href="<?php echo "startshiyan.php"?>?pageno=<?php  echo $pagecount;?>">尾页</a>
<?php 
}
?>
[共找到<?php echo $rows;?>个课程]

</div>
</td>
</tr>
</table>
<table align="center"><tr><td><input type="submit"  name="submit1" id="submit1" value="开始实验" /></td></tr></table>
</form>

</body>
</html>