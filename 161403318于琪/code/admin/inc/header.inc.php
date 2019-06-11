<!-- 存放后台需要访问的一些文件 -->
<?php 
	basename($_SERVER['SCRIPT_NAME'])  //basename返回路径中的文件名部分
	                                   //SCRIPT_NAME返回当前页面地址，被谁包含地址为谁
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title><?php echo $template['title']?></title>
<meta name="keywords" content="后台界面" />
<meta name="description" content="后台界面" />
<link rel="stylesheet" type="text/css" href="style/public.css" />
</head>
<body>
<div id="top">
		<div class="logo">
			管理中心
		</div>
		<ul class="nav">
			<li><a href="#" target="_blank">明星</a></li>
			<li><a href="#" target="_blank">stars</a></li>
		</ul>
		<div class="login_info">
			<a href="#" style="color:#fff;">网站首页</a>&nbsp;|&nbsp;
			管理员： admin <a href="#">[注销]</a>
		</div>
</div>
<div id="sidebar">
		<ul>
			<li>
				<div class="small_title">系统</div>
				<ul class="child">
					<li><a href="#">系统信息</a></li>
					<li><a href="#">管理员</a></li>
					<li><a href="#">添加管理员</a></li>
					<li><a href="#">站点设置</a></li>
				</ul>
			</li>
			<li><!--  class="current" -->
				<div class="small_title">内容管理</div>
				<ul class="child">
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module.php'){echo 'class="current"';} ?> href="father_module.php">父板块列表</a></li>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module_add.php'){echo 'class="current"';} ?> href="father_module_add.php">添加父板块</a></li>
					<?php 
					if(basename($_SERVER['SCRIPT_NAME'])=='father_module_update.php'){
						echo '<li><a class="current">编辑父板块</a></li>';
					}
					?>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module.php'){echo 'class="current"';} ?> href="son_module.php">子板块列表</a></li>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module_add.php'){echo 'class="current"';} ?> href="son_module_add.php">添加子板块</a></li>
					<?php 
					if(basename($_SERVER['SCRIPT_NAME'])=='son_module_update.php'){
						echo '<li><a class="current">编辑子板块</a></li>';
					}
					?>
					<li><a href="#">帖子管理</a></li>
				</ul>
			</li>
			<li>
				<div class="small_title">用户管理</div>
				<ul class="child">
					<li><a href="#">用户列表</a></li>
				</ul>
			</li>
		</ul>
</div>