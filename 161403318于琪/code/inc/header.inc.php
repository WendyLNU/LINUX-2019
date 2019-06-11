<!-- 存放前台页面的头部 -->
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
		<div class="logo">你的明星</div>
		<div class="nav">
			<a class="hover">首页</a>
		</div>
		<div class="serarch">
			<form>
				<input class="keyword" type="text" name="keyword" placeholder="搜索其实很简单" />
				<input class="submit" type="submit" name="submit" value="" />
			</form>
		</div>
		<div class="login">
       		<?php
       		if($member_id){ //如果有number_id,代表已经登录
       			$str=<<<Y
				<a>您好！{$_COOKIE['sfk']['name']}</a>
Y;
       			echo $str;
       		}else{
       			$str=<<<Y
				<a>登录</a>&nbsp;
				<a>注册</a>;
Y;
       			echo $str;
       		}		
			?>
		</div>
	</div>
</div>
<div style="margin-top:55px;"></div>