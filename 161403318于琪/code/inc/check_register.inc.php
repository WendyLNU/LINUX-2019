<!-- ע����ҳ -->
<?php 
if(empty($_POST['name'])){
	skip('register.php', 'error', '�û�������Ϊ�գ�');
}
if(mb_strlen($_POST['name'])>32){
	skip('register.php', 'error', '�û������Ȳ�Ҫ����32���ַ���');
}
if(mb_strlen($_POST['pw'])<6){
	skip('register.php', 'error', '���벻������6λ��');
}
if($_POST['pw']!=$_POST['confirm_pw']){
	skip('register.php', 'error', '�����������벻һ�£�');
}
if(strtolower($_POST['vcode'])!=strtolower($_SESSION['vcode'])){ //strtolower��֤�벻���ִ�Сд
	skip('register.php', 'error', '��֤���������');
}
$_POST=escape($link, $_POST);
$query="select * from member where name='{$_POST['name']}'";
$result=execute($link, $query);
if(mysqli_num_rows($result)){ //�������
	skip('register.php', 'error', '����û����Ѿ�������ע���ˣ�');
}
?>