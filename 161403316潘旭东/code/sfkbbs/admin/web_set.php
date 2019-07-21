<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';

$link=connect();
include_once 'inc/is_manage_login.inc.php';//验证管理员是否登录
$query="select * from sfk_info where id=1";
$result_info=execute($link, $query);
$data_info=mysqli_fetch_assoc($result_info);
if(isset($_POST['submit'])){
	$_POST=escape($link,$_POST);
	$query="update sfk_info set title='{$_POST['title']}',keywords='{$_POST['keywords']}',description='{$_POST['description']}' where id=1";
	execute($link, $query);
	if(mysqli_affected_rows($link)==1){
		skip('web_set.php','ok','修改成功！');
	}else{
		skip('web_set.php','error','修改失败,请重试！');
	}
}
$template['title']='站点设置';
$template['css']=array('style/public.css');
?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">网站设置</div>
	<form method="post">
		<table class="au">
			<tr>
				<td>网站标题</td>
				<td><input name="title" type="text" value="<?php echo $data_info['title']?>" /></td>
				<td>
					就是前台页面的标题
				</td>
			</tr>
			<tr>
				<td>关键字</td>
				<td><input name="keywords" type="text" value="<?php echo $data_info['keywords']?>" /></td>
				<td>
					关键字
				</td>
			</tr>
			<tr>
				<td>描述</td>
				<td>
					<textarea name="description"><?php echo $data_info['description']?></textarea>
				</td>
				<td>
					描述
				</td>
			</tr>
		</table>
		<input style="margin-top:20px;cursor:pointer;" class="btn" type="submit" name="submit" value="设置" />
	</form>
</div>
<?php include 'inc/footer.inc.php'?>