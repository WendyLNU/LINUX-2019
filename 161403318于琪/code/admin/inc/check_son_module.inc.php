<!-- ��ű༭������Ӱ��ʱ������Ϣ������ -->
<?php 
if(!is_numeric($_POST['father_module_id'])){
	skip('son_module_add.php', 'error', '��������鲻��Ϊ�գ�');
}
$query="select * from father_module where id={$_POST['father_module_id']}";
$result=execute($link, $query);
if(mysqli_num_rows($result)==0){ //���û�鵽
	skip('son_module_add.php', 'error', '��������鲻���ڣ�');
}
if(empty($_POST['module_name'])){ //�ж��ύ�İ�����ǲ��ǿ�
	skip('son_module_add.php', 'error', '�Ӱ�����Ʋ���Ϊ�գ�');
}
if(mb_strlen($_POST['module_name'])>66){ //���ַ������Ȳ�����66 mb_strlen��ȡ�ַ�������
	skip('son_module_add.php', 'error', '�Ӱ�����Ʋ��ö���66���ַ���');
}
$_POST=escape($link,$_POST); //�������"'�Ƚ���ת��
switch($check_flag){
	case 'add':
		$query="select * from son_module where module_name='{$_POST['module_name']}'";//�ж��Ƿ�������
		break;
	case 'update':
		$query="select * from son_module where module_name='{$_POST['module_name']}' and id!={$_GET['id']}";//�ж��Ƿ��������������Ѿ�����
		break;
	default:
		skip('son_module.php', 'error', '$check_flag��������');
}
$result=execute($link, $query);
if (mysqli_num_rows($result)) {//������ظ������Ϊ�㣬û���ظ����Ϊ��
	skip('son_module_add.php', 'error', '����Ӱ���Ѿ����ˣ�');
}
if(mb_strlen($_POST['info'])>255){ //��鳤�Ȳ�����255
	skip('son_module_add.php', 'error', '�Ӱ���鲻�ö���66���ַ���');
}
if(!is_numeric($_POST['sort'])){ //�ж��ύ�������ǲ�������
	skip('son_module_add.php', 'error', '����ֻ�������֣�');
}
?>