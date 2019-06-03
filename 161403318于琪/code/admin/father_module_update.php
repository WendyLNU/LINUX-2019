<!-- 修改父板块页面 -->
<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$template['title']='父板块-修改';
$link=connect();
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){ //如果id为空或id不是数字
	skip('father_module.php', 'error', 'id参数错误！');
}
$query="select * from father_module where id={$_GET['id']}";
$result=execute($link, $query);
if(!mysqli_num_rows($result)){//如果不存在
	skip('father_module.php', 'error', '这条板块信息不存在！');
}
if(isset($_POST['submit'])){ //如果点了提交
	//验证用户填写的信息
	$check_flag='update';//check_father_module.inc.php
	include 'inc/check_father_module.inc.php';
	$query="update father_module set module_name='{$_POST['module_name']}',sort={$_POST['sort']} where id!={$_GET['id']}";
	execute($link, $query);
	if(mysqli_affected_rows($link)==1){ //如果有影响
		skip('father_module.php', 'ok', '修改成功！');
	}else{
		skip('father_module.php', 'error', '修改失败！');//没影响，即没有修改，修改失败
	}
}

$data=mysqli_fetch_assoc($result);
?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">修改父板块-<?php echo $data['module_name']?></div>
	<form method="post" >
		<table class="au">
			<tr>
				<td>版块名称</td>
				<td><input name="module_name" value="<?php echo $data['module_name']?>" type="text" /></td>
				<td>
					板块名称不得为空，最大不得超过66个字符
				</td>
			</tr>
			<tr>
				<td>排序</td>
				<td><input name="sort" value="<?php echo $data['sort']?>" type="text" /></td>
				<td>
					填写一个数字即可
				</td>
			</tr>
			</table>
			<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="修改" />
		</form>
</div>
<?php include 'inc/footer.inc.php'?>
