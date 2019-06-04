<?php
include("config.php");
?>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>夏日读书</title>
<link rel="stylesheet" href="style.css" type="text/css">
</head>
<body>
<?php include("head.php");?>
		<table width="782" border="0" align="center" cellpadding="0" cellspacing="0">
                <tr>
                  <td height="22">
	<?php
	$pagesize=15;
	if(!urldecode($_GET[proid])){
	$sql="select * from yx_books order by id desc";
	}else{
	$sql="select * from yx_books where type='".urldecode($_GET[proid])."'";
	}

	$rs=$mysqli->query($sql);

	$recordcount=mysqli_num_rows($rs);
	$pagecount=($recordcount-1)/$pagesize+1;
	$pagecount=(int)$pagecount;
	$pageno=$_GET["pageno"];
	if($pageno=="")
	{
		$pageno=1;
	}
	if($pageno<1)
	{
		$pageno=1;
	}
	if($pageno>$pagecount)
	{
		$pageno=$pagecount;
	}
	$startno=($pageno-1)*$pagesize;
	if(!urldecode($_GET[proid])){
	$sql="select * from yx_books order by id desc limit $startno,$pagesize";
	}else{
	$sql="select * from yx_books where type='".urldecode($_GET[proid])."' order by id desc limit $startno,$pagesize";
	}
	$rs=$mysqli->query($sql);
?>
  <table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC">
    <tr>
      <td width="88" height="30" align="center" bgcolor="#FFFFFF" class="line2">ID</td>
	    <td width="103" align="center" bgcolor="#FFFFFF" class="line2">书名</td>
	    <td width="77" align="center" bgcolor="#FFFFFF" class="line2">价格</td>
	    <td width="152" align="center" bgcolor="#FFFFFF" class="line2">入库时间</td>
	    <td width="107" align="center" bgcolor="#FFFFFF" class="line2">类别</td>
	    <td width="126" align="center" bgcolor="#FFFFFF" class="line2">现有数量(本)</td>
	    <td width="121" align="center" bgcolor="#FFFFFF" class="line2">操作</td>
	    </tr>
    <?php
	while($rows=mysqli_fetch_assoc($rs))
	{
	?>
	<tr>
	  <td height="30" align="center" bgcolor="#FFFFFF"><?php echo $rows["id"];?></td>
	  <td align="center" bgcolor="#FFFFFF"><?php echo $rows["name"];?></td>
	  <td align="center" bgcolor="#FFFFFF"><?php echo $rows["price"];?></td>
	  <td align="center" bgcolor="#FFFFFF"><?php echo $rows["uploadtime"];?></td>
	  <td align="center" bgcolor="#FFFFFF"><?php echo $rows["type"];?></td>
	  <td align="center" bgcolor="#FFFFFF"><?php echo $rows["leave_number"];?></td>
	  <td align="center" bgcolor="#FFFFFF" class="line2">
	  <?php 
	  $rs2=$mysqli->query("select * from lend where book_id='".$rows['id']."' and user_id='".$_SESSION['id']."'");
	  $rows2=mysqli_fetch_assoc($rs2);
	  if($rows2['book_id']){
	  echo "<font color='red'>您已借阅</font>&nbsp;&nbsp;<a href=huanshu.php?book_id=$rows[id]>我要还书</a>";
	  }else{
	  	if($rows["leave_number"]==0){
		echo "<font color='#cccc00'>该书已借完</font>";
		}else{
	  echo "<a href=jieshu.php?book_id=$rows[id]>我要借书</a>";
	  }
	  	}
	  ?>	  </td>
	</tr>
	<?php
	}
?>
</table>
<table width="100%" border="0" align="center" cellpadding="2" cellspacing="1" bgcolor="#CCCCCC">
  <tr>
  <td height="35" align="center" bgcolor="#FFFFFF">
  <?php
	if($pageno==1)
	{
	?>
    首页 | 上一页 | <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=<?php echo $pageno+1?>">下一页</a> | <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=<?php echo $pagecount?>">末页</a>
    <?php
	}
	else if($pageno==$pagecount)
	{
	?>
    <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=1">首页</a> | <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=<?php echo $pageno-1?>">上一页</a> | 下一页 | 末页
    <?php
	}
	else
	{
	?>
    <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=1">首页</a> | <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=<?php echo $pageno-1?>">上一页</a> | <a href="index.php?proid=<?php echo urlencode($_GET[proid]);?>&pageno=<?php echo $pageno+1?>" class="forumRowHighlight">下一页</a> | <a href="?pageno=<?php echo $pagecount?>">末页</a>
    <?php
	}
?>
    &nbsp;页次：<?php echo $pageno ?>/<?php echo $pagecount ?>页&nbsp;共有<?php echo $recordcount?>条信息</td>
  </tr>
