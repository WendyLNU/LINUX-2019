<?php 

?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<title><?php echo $template['title'] ?></title>
<meta name="keywords" content="后台界面" />
<meta name="description" content="后台界面" />
<?php 
foreach ($template['css'] as $val){
	echo "<link rel='stylesheet' type='text/css' href='{$val}' />";
}
?>
</head>
<body>
<div id="top">
	<div class="logo">
		管理中心
	</div>
	<ul class="nav">
		<li><a href="http://www.sifangku.com" target="_blank">私房库</a></li>
		<li><a href="http://www.sifangku.com" target="_blank">私房库</a></li>
	</ul>
	<div class="login_info">
		<a target="_blank" href="../index.php" style="color:#fff;">网站首页</a>&nbsp;|&nbsp;
		管理员：<?php echo $_SESSION['manage']['name']?> <a href="logout.php">[注销]</a>
	</div>
</div>
<div id="sidebar">
	<ul>
		<li>
			<div class="small_title">系统</div>
			<ul class="child">
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='index.php'){echo 'class="current"';}?> href="index.php">系统信息</a></li>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='manage.php'){echo 'class="current"';}?> href="manage.php">管理员</a></li>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='manage_add.php'){echo 'class="current"';}?> href="manage_add.php">添加管理员</a></li>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='web_set.php'){echo 'class="current"';}?> href="web_set.php">站点设置</a></li>
			</ul>
		</li>
		<li><!--  class="current" -->
			<div class="small_title">内容管理</div>
			<ul class="child">
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module.php'){echo 'class="current"';}?> href="father_module.php">父板块列表</a></li>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module_add.php'){echo 'class="current"';}?> href="father_module_add.php">添加父板块</a></li>
				<?php 
				if(basename($_SERVER['SCRIPT_NAME'])=='father_module_update.php'){
					echo '<li><a class="current">编辑父版块</a></li>';
				}
				?>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module.php'){echo 'class="current"';}?> href="son_module.php">子板块列表</a></li>
				<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module_add.php'){echo 'class="current"';}?> href="son_module_add.php">添加子板块</a></li>
				<?php 
				if(basename($_SERVER['SCRIPT_NAME'])=='son_module_update.php'){
					echo '<li><a class="current">编辑子版块</a></li>';
				}
				?>
				<li><a target="_blank" href="../index.php">帖子管理</a></li>
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