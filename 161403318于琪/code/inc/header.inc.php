<!-- ���ǰ̨ҳ���ͷ�� -->
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title><?php echo $template['title']?></title>
<meta name="keywords" content="" />
<meta name="description" content="" />
<link rel="stylesheet" type="text/css" href="style/public.css" />
<link rel="stylesheet" type="text/css" href="style/register.css" />
</head>
<body>
<div class="header_wrap">
	<div id="header" class="auto">
		<div class="logo">�������</div>
		<div class="nav">
			<a class="hover">��ҳ</a>
		</div>
		<div class="serarch">
			<form>
				<input class="keyword" type="text" name="keyword" placeholder="������ʵ�ܼ�" />
				<input class="submit" type="submit" name="submit" value="" />
			</form>
		</div>
		<div class="login">
       		<?php
       		if($member_id){ //�����number_id,�����Ѿ���¼
       			$str=<<<Y
				<a>���ã�{$_COOKIE['sfk']['name']}</a>
Y;
       			echo $str;
       		}else{
       			$str=<<<Y
				<a>��¼</a>&nbsp;
				<a>ע��</a>;
Y;
       			echo $str;
       		}		
			?>
		</div>
	</div>
</div>
<div style="margin-top:55px;"></div>