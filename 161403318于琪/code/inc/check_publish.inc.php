<!--�������ҳ -->
<?php 
if(empty($_POST['module_id']) || !is_numeric($_POST['module_id'])){
	skip('publish.php', 'error', '�������id���Ϸ���');
}
$query="select * from son_module where id={$_POST['module_id']}";
$result=execute($link, $query);
if(mysqli_num_rows($result)!=1){
	skip('publish.php', 'error', '������鲻���ڣ�');
}
if(empty($_POST['title'])){
	skip('publish.php', 'error', '���ⲻ��Ϊ�գ�');
}
if(mb_strlen($_POST['title'])>255){
	skip('publish.php', 'error', '���ⳤ�Ȳ�Ҫ����255���ַ���');
}
?>