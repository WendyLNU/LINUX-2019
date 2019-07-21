<?php
	require_once("../config.php");
	if($_SESSION["admin"]=="")
	{
 	echo "<script language=javascript>alert('ÇëÖØÐÂµÇÂ½£¡');window.location='login.php'</script>";
	}
?>
