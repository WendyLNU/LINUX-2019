<?php 
if(!is_numeric($_POST['father_module_id'])){
	skip('son_module_add.php','error','所属父版块不得为空！');
}
$query="select * from sfk_father_module where id={$_POST['father_module_id']}";
$result=execute($link,$query);
if(mysqli_num_rows($result)==0){
	skip('son_module_add.php','error','所属父版块不存在！');
}
if(empty($_POST['module_name'])){
	skip('son_module_add.php','error','子版块名称不得为空！');
}
if(mb_strlen($_POST['module_name'])>66){
	skip('son_module_add.php','error','子版块名称不得多余66个字符！');
}
$_POST=escape($link,$_POST);
switch ($check_flag){
	case 'add':
		$query="select * from sfk_son_module where module_name='{$_POST['module_name']}'";
		break;
	case 'update':
		$query="select * from sfk_son_module where module_name='{$_POST['module_name']}' and id!={$_GET['id']}";
		break;
	default:
		skip('son_module','error','$check_flag参数错误！');
}
$result=execute($link,$query);
if(mysqli_num_rows($result)){
	skip('son_module_add.php','error','这个子版块已经有了！');
}
if(mb_strlen($_POST['info'])>255){
	skip('son_module_add.php','error','子版块简介不得多于255个字符！');
}
if(!is_numeric($_POST['sort'])){
	skip('son_module_add.php','error','排序只能是数字！');
}
?>