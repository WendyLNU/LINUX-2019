<!-- �޸ĸ����ҳ�� -->
<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$template['title']='�����-�޸�';
$link=connect();
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){ //���idΪ�ջ�id��������
	skip('father_module.php', 'error', 'id��������');
}
$query="select * from father_module where id={$_GET['id']}";
$result=execute($link, $query);
if(!mysqli_num_rows($result)){//���������
	skip('father_module.php', 'error', '���������Ϣ�����ڣ�');
}
if(isset($_POST['submit'])){ //��������ύ
	//��֤�û���д����Ϣ
	$check_flag='update';//check_father_module.inc.php
	include 'inc/check_father_module.inc.php';
	$query="update father_module set module_name='{$_POST['module_name']}',sort={$_POST['sort']} where id!={$_GET['id']}";
	execute($link, $query);
	if(mysqli_affected_rows($link)==1){ //�����Ӱ��
		skip('father_module.php', 'ok', '�޸ĳɹ���');
	}else{
		skip('father_module.php', 'error', '�޸�ʧ�ܣ�');//ûӰ�죬��û���޸ģ��޸�ʧ��
	}
}

$data=mysqli_fetch_assoc($result);
?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">�޸ĸ����-<?php echo $data['module_name']?></div>
	<form method="post" >
		<table class="au">
			<tr>
				<td>�������</td>
				<td><input name="module_name" value="<?php echo $data['module_name']?>" type="text" /></td>
				<td>
					������Ʋ���Ϊ�գ���󲻵ó���66���ַ�
				</td>
			</tr>
			<tr>
				<td>����</td>
				<td><input name="sort" value="<?php echo $data['sort']?>" type="text" /></td>
				<td>
					��дһ�����ּ���
				</td>
			</tr>
			</table>
			<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="�޸�" />
		</form>
</div>
<?php include 'inc/footer.inc.php'?>
