<?php
	require_once("../config.php");
	if($_SESSION["admin"]=="")
	{
 	echo "<script language=javascript>alert('�����µ�½��');window.location='login.php'</script>";
	}
?>
