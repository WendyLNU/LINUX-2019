<!-- ��ź�̨��Ҫ���ʵ�һЩ�ļ� -->
<?php 
	basename($_SERVER['SCRIPT_NAME'])  //basename����·���е��ļ�������
	                                   //SCRIPT_NAME���ص�ǰҳ���ַ����˭������ַΪ˭
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title><?php echo $template['title']?></title>
<meta name="keywords" content="��̨����" />
<meta name="description" content="��̨����" />
<link rel="stylesheet" type="text/css" href="style/public.css" />
</head>
<body>
<div id="top">
		<div class="logo">
			��������
		</div>
		<ul class="nav">
			<li><a href="#" target="_blank">����</a></li>
			<li><a href="#" target="_blank">stars</a></li>
		</ul>
		<div class="login_info">
			<a href="#" style="color:#fff;">��վ��ҳ</a>&nbsp;|&nbsp;
			����Ա�� admin <a href="#">[ע��]</a>
		</div>
</div>
<div id="sidebar">
		<ul>
			<li>
				<div class="small_title">ϵͳ</div>
				<ul class="child">
					<li><a href="#">ϵͳ��Ϣ</a></li>
					<li><a href="#">����Ա</a></li>
					<li><a href="#">��ӹ���Ա</a></li>
					<li><a href="#">վ������</a></li>
				</ul>
			</li>
			<li><!--  class="current" -->
				<div class="small_title">���ݹ���</div>
				<ul class="child">
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module.php'){echo 'class="current"';} ?> href="father_module.php">������б�</a></li>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='father_module_add.php'){echo 'class="current"';} ?> href="father_module_add.php">��Ӹ����</a></li>
					<?php 
					if(basename($_SERVER['SCRIPT_NAME'])=='father_module_update.php'){
						echo '<li><a class="current">�༭�����</a></li>';
					}
					?>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module.php'){echo 'class="current"';} ?> href="son_module.php">�Ӱ���б�</a></li>
					<li><a <?php if(basename($_SERVER['SCRIPT_NAME'])=='son_module_add.php'){echo 'class="current"';} ?> href="son_module_add.php">����Ӱ��</a></li>
					<?php 
					if(basename($_SERVER['SCRIPT_NAME'])=='son_module_update.php'){
						echo '<li><a class="current">�༭�Ӱ��</a></li>';
					}
					?>
					<li><a href="#">���ӹ���</a></li>
				</ul>
			</li>
			<li>
				<div class="small_title">�û�����</div>
				<ul class="child">
					<li><a href="#">�û��б�</a></li>
				</ul>
			</li>
		</ul>
</div>