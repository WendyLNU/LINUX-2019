<!-- ��������ҳ -->
<?php
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$template['title']='��������ҳ';

if(isset($_POST['submit'])){ //������ڣ�˵���û������ύ
	$link=connect();
	/*
	��֤�û���д����Ϣ
	*/
	$check_flag='add';
	include 'inc/check_father_module.inc.php';
	$query="insert into father_module(module_name,sort) values('{$_POST['module_name']}','{$_POST['sort']}')";
	execute($link, $query);
	if(mysqli_affected_rows($link))	{
		skip('father_module.php', 'ok', '��ϲ�㣬��ӳɹ���');
	}else{
		skip('father_module_add.php', 'error', '�Բ������ʧ�ܣ������ԣ�');
	}
}
	?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">��Ӹ����</div>
	<form method="post" >
		<table class="au">
			<tr>
				<td>�������</td>
				<td><input name="module_name" type="text" /></td>
				<td>
					������Ʋ���Ϊ�գ���󲻵ó���66���ַ�
				</td>
			</tr>
			<tr>
				<td>����</td>
				<td><input name="sort" value="0" type="text" /></td>
				<td>
					��дһ�����ּ���
				</td>
			</tr>
			</table>
			<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="���" />
		</form>
</div>
<?php include 'inc/footer.inc.php'?>