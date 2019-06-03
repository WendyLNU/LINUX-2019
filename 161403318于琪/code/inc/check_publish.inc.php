<!--发帖检测页 -->
<?php 
if(empty($_POST['module_id']) || !is_numeric($_POST['module_id'])){
	skip('publish.php', 'error', '所属板块id不合法！');
}
$query="select * from son_module where id={$_POST['module_id']}";
$result=execute($link, $query);
if(mysqli_num_rows($result)!=1){
	skip('publish.php', 'error', '所属板块不存在！');
}
if(empty($_POST['title'])){
	skip('publish.php', 'error', '标题不得为空！');
}
if(mb_strlen($_POST['title'])>255){
	skip('publish.php', 'error', '标题长度不要超过255个字符！');
}
?>