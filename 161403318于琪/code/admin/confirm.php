<!-- ɾ��ȷ��ҳ�� -->
<?php 
include_once '../inc/config.inc.php';
if(!isset($_GET['message']) || !isset($_GET['url']) || !isset($_GET['return_url'])){//�жϱ����Ƿ����,���������
	exit();
}
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title>ȷ��ҳ</title>
<meta name="keywords" content="��̨����" />
<meta name="description" content="��̨����" />
<link rel="stylesheet" type="text/css" href="style/remind.css" />
</head>
<body>
<div class="notice"><span class="pic ask"></span><?php echo $_GET['message']?> <a style="color: red" href="<?php echo $_GET['url']?>">ȷ��</a> <a href="<?php echo $_GET['return_url']?>">ȡ��</a></div>
</body>
</html>