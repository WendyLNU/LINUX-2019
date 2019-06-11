<!-- 父板块删除页面 -->
<?php
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){
	skip('father_module.php', 'error', 'id参数错误！');
}
$link=connect();
$query="select * from son_module where father_module_id={$_GET['id']}";//如果父板块下面存在子版块，不能直接删除父板块
$result=execute($link,$query);
if (mysqli_num_rows($result)) {//如果有重复结果不为零，没有重复结果为零
	skip('father_module.php', 'error', '该父板块下面存在子版块，请先将对应的子版块先删掉！');
}
$query="delete from father_module where id={$_GET['id']}";
execute($link,$query);
if(mysqli_affected_rows($link)==1){
	skip('father_module.php', 'ok', '恭喜你删除成功！');
}
else{
	skip('father_module.php', 'error', '删除失败，请重试');
}
?>