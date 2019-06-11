<!-- 存放编辑或添加子板块时输入信息的限制 -->
<?php 
if(!is_numeric($_POST['father_module_id'])){
	skip('son_module_add.php', 'error', '所属父板块不得为空！');
}
$query="select * from father_module where id={$_POST['father_module_id']}";
$result=execute($link, $query);
if(mysqli_num_rows($result)==0){ //如果没查到
	skip('son_module_add.php', 'error', '所属父板块不存在！');
}
if(empty($_POST['module_name'])){ //判断提交的板块名是不是空
	skip('son_module_add.php', 'error', '子板块名称不得为空！');
}
if(mb_strlen($_POST['module_name'])>66){ //且字符串长度不超过66 mb_strlen获取字符串长度
	skip('son_module_add.php', 'error', '子板块名称不得多于66个字符！');
}
$_POST=escape($link,$_POST); //对输入的"'等进行转义
switch($check_flag){
	case 'add':
		$query="select * from son_module where module_name='{$_POST['module_name']}'";//判断是否有重名
		break;
	case 'update':
		$query="select * from son_module where module_name='{$_POST['module_name']}' and id!={$_GET['id']}";//判断是否有重名且排序已经存在
		break;
	default:
		skip('son_module.php', 'error', '$check_flag参数错误！');
}
$result=execute($link, $query);
if (mysqli_num_rows($result)) {//如果有重复结果不为零，没有重复结果为零
	skip('son_module_add.php', 'error', '这个子板块已经有了！');
}
if(mb_strlen($_POST['info'])>255){ //简介长度不超过255
	skip('son_module_add.php', 'error', '子板块简介不得多于66个字符！');
}
if(!is_numeric($_POST['sort'])){ //判断提交的排序是不是数字
	skip('son_module_add.php', 'error', '排序只能是数字！');
}
?>