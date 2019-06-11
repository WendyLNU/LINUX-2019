<!-- 删除确认页面 -->
<?php 
include_once '../inc/config.inc.php';
if(!isset($_GET['message']) || !isset($_GET['url']) || !isset($_GET['return_url'])){//判断变量是否存在,如果不存在
	exit();
}
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title>确认页</title>
<meta name="keywords" content="后台界面" />
<meta name="description" content="后台界面" />
<link rel="stylesheet" type="text/css" href="style/remind.css" />
</head>
<body>
<div class="notice"><span class="pic ask"></span><?php echo $_GET['message']?> <a style="color: red" href="<?php echo $_GET['url']?>">确定</a> <a href="<?php echo $_GET['return_url']?>">取消</a></div>
</body>
</html>