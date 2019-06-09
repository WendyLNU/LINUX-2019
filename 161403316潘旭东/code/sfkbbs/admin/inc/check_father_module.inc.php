<?php 
if(empty($_POST['module_name'])){
	skip('father_module_add.php','error','版块名称不得为空！');
}
if(mb_strlen($_POST['module_name'])>66){
	skip('father_module_add.php','error','版块名称不得多余66个字符！');
}
if(!is_numeric($_POST['sort'])){
	skip('father_module_add.php','error','排序只能是数字！');
}
$_POST=escape($link,$_POST);
switch ($check_flag){
	case 'add':
		$query="select * from sfk_father_module where module_name='{$_POST['module_name']}'";
		break;
	case 'update':
		$query="select * from sfk_father_module where module_name='{$_POST['module_name']}' and id!={$_GET['id']}";
		break;
	default:
		skip('father_module_add.php','error','$check_flag参数错误！');
}
$result=execute($link,$query);
if(mysqli_num_rows($result)){
	skip('father_module_add.php','error','这个版块已经有了！');
}
?>