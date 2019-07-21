<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'" />
<title>无标题文档</title>
</head>

<body>
<?php session_start();
		session_destroy();
		?>
		<form action="index.html" method="post"  id="form1"></form>
		<script language="javascript">
		alert("退出成功！");
		form1.submit();
		</script>
</body>
</html>
