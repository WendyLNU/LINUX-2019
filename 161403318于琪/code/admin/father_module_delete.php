<!-- �����ɾ��ҳ�� -->
<?php
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){
	skip('father_module.php', 'error', 'id��������');
}
$link=connect();
$query="select * from son_module where father_module_id={$_GET['id']}";//����������������Ӱ�飬����ֱ��ɾ�������
$result=execute($link,$query);
if (mysqli_num_rows($result)) {//������ظ������Ϊ�㣬û���ظ����Ϊ��
	skip('father_module.php', 'error', '�ø������������Ӱ�飬���Ƚ���Ӧ���Ӱ����ɾ����');
}
$query="delete from father_module where id={$_GET['id']}";
execute($link,$query);
if(mysqli_affected_rows($link)==1){
	skip('father_module.php', 'ok', '��ϲ��ɾ���ɹ���');
}
else{
	skip('father_module.php', 'error', 'ɾ��ʧ�ܣ�������');
}
?>