<!-- ��¼���ҳ -->
<?php 
if(empty($_POST['name'])){
	skip('login.php', 'error', '�û�������Ϊ�գ�');
}
if(mb_strlen($_POST['name'])>32){
	skip('register.php', 'error', '�û������Ȳ�Ҫ����32���ַ���');
}
if(empty($_POST['pw'])){
	skip('login.php', 'error', '���벻��Ϊ�գ�');
}
if(strtolower($_POST['vcode'])!=strtolower($_SESSION['vcode'])){ //strtolower��֤�벻���ִ�Сд
	skip('register.php', 'error', '��֤���������');
}
if(empty($_POST['time']) || is_numeric($_POST['time']) ||$_POST['time']>2592000){
	$_POST['time']=2592000;
}
?>