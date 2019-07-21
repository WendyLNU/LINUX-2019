<?php
include("config.php");
?>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>夏日读书</title>
<link rel="stylesheet" href="style.css" type="text/css">
</head>
<body>
<?php include("head.php");?>
<form  name="myform" method="post" onSubmit="return CheckPost()" action="" style="margin-bottom:5px;">
<table width="782" border="0" align="center" cellpadding="5" cellspacing="1" bgcolor="#CCCCCC">
  <tr>
    <td height="30" bgcolor="#FFFFFF" align="center"><a href="landing.php">用户登陆</a></td>
    </tr>
  <tr>
    <td height="30" bgcolor="#FFFFFF" align="center" ><a href="./admin/login.php">管理员登陆</a></div></td>
    </tr>
</table>
</form>
</body>
</html>
