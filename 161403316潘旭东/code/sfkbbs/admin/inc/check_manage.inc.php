<?php 
if(empty($_POST['name'])){
	skip('manage_add.php','error','管理员名称不得为空！');
}
if(mb_strlen($_POST['name'])>32){
	skip('manage_add.php','error','管理员名称不得多余32个字符！');
}
if(mb_strlen($_POST['pw'])<6){
	skip('manage_add.php','error','密码不得少于6位！');
}
$_POST=escape($link,$_POST);
$query="select * from sfk_manage where name='{$_POST['name']}'";
$result=execute($link,$query);
if(mysqli_num_rows($result)){
	skip('manage_add.php','error','这个名称已经有了！');
}
if(!isset($_POST['level'])){
	$_POST['level']=1;
}elseif ($_POST['level']=='0'){
	$_POST['level']=0;
}elseif ($_POST['level']=='1'){
	$_POST['level']=1;
}else{
	$_POST['level']=1;
}
?>