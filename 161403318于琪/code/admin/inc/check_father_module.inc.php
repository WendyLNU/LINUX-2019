<!-- ��ű༭����Ӹ����ʱ������Ϣ������ -->
<?php 
if(empty($_POST['module_name'])){ //�ж��ύ�İ�����ǲ��ǿ�
	skip('father_module_add.php', 'error', '������Ʋ���Ϊ�գ�');
}
if(mb_strlen($_POST['module_name'])>66){ //���ַ������Ȳ�����66 mb_strlen��ȡ�ַ�������
	skip('father_module_add.php', 'error', '������Ʋ��ö���66���ַ���');
}
if(!is_numeric($_POST['sort'])){ //�ж��ύ�������ǲ�������
	skip('father_module_add.php', 'error', '����ֻ�������֣�');
}
$_POST=escape($link,$_POST); //�������"'�Ƚ���ת��
switch($check_flag){
	case 'add':
		$query="select * from father_module where module_name='{$_POST['module_name']}'";//�ж��Ƿ�������
		break;
	case 'update':
		$query="select * from father_module where module_name='{$_POST['module_name']}' and id!={$_GET['id']}";//�ж��Ƿ��������������Ѿ�����
		break;
	default:
		skip('father_module_add.php', 'error', '$check_flag��������');
}
$result=execute($link, $query);
if (mysqli_num_rows($result)) {//������ظ������Ϊ�㣬û���ظ����Ϊ��
	skip('father_module_add.php', 'error', '�������Ѿ����ˣ�');
}
?>