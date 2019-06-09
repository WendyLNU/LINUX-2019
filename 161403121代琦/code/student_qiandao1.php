<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title></title>
</head>

<body>

<?php
date_default_timezone_set(PRC);
  session_start();
  $admin_account=$_SESSION['access'];
  $Q_C_id=$_GET['Q_C_id'];
  $count=$_GET['count'];
  $time=date("H:i:s");
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysqli_query($link,"set names 'utf8'");
  $sql="select C_start_time,C_over_time from course where C_id='$Q_C_id'";
  $result=mysqli_query($link,$sql);
  $rows=mysqli_fetch_array($result);  

  if(strtotime($time)>=strtotime($rows['C_start_time'])&&strtotime($time)<=strtotime($rows['C_over_time']))
  	$a=1;
  else
  	$a=0;
	
	if($count==0||$a==0)
  {?>
	 <script language="javascript">
	 	alert ("非法签到时间，确定返回！");
	 	history.go(-1);
		
	 </script>
  <?php
  die();
  }
	
	
	$sql0="select Q_count from sign where Q_C_id='$Q_C_id' and Q_S_id='$admin_account' ";
	$result0=mysqli_query($link,$sql0);
	$row=mysqli_fetch_array($result0);
	if($row['Q_count']==1)
		$b=1;
	else
		$b=0;
	
	
	
		
   $sql1="update sign set Q_sign".$count." ='1',Q_count='0' where Q_C_id='$Q_C_id' and Q_S_id='$admin_account' and Q_count='1'";


   
  if($b&&mysqli_query($link,$sql1))
  {?>
	 <script language="javascript">
	 	alert ("签到成功，确定返回！");
	 	history.go(-1);
		
		
	 </script>  
  <?php 
  die();
  }
  else 
  {
?>
     <script language="javascript">
	 	alert ("您已签到过一次，确定返回！");
	 	history.go(-1);
		
		
	 </script>
	 
  <?php
  die();
  }
  
  
  ?>
 </body>
</html>

  
  
