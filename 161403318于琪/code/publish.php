<!-- ǰ̨����ҳ�� -->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
if(!$member_id=is_login($link)){
	skip('login.php', 'error', '���¼���ٷ�����');
}
if(isset($_POST['submit'])){
	include 'inc/check_publish.inc.php';
	$_POST=escape($link,$_POST);
	$query="insert into content(module_id,title,content,time,member_id) values({$_POST['module_id']},'{$_POST['title']}','{$_POST['content']}',now(),{$member_id})";
	execute($link, $query);
	if(mysqli_affected_rows($link)==1){
		skip('publish.php', 'ok', '�����ɹ���');
	}else{
		skip('publish.php', 'error','����ʧ�ܣ������ԣ�');
	}
}
$template['title']='���ӷ���ҳ';
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<title></title>
<meta name="keywords" content="" />
<meta name="description" content="" />
<link rel="stylesheet" type="text/css" href="style/public.css" />
<link rel="stylesheet" type="text/css" href="style/publish.css" />
<?php include_once 'inc/header.inc.php';?>
	<div id="position" class="auto">
		 <a>��ҳ</a> &gt; ���ӷ���
	</div>
	<div id="publish">
		<form method="post">
			<select name="module_id">
				<?php 
				$query="select * from father_module order by sort desc";
				$result_father=execute($link, $query);
				while($data_father=mysqli_fetch_assoc($result_father)){
						echo "<optgroup label='{$data_father['module_name']} '>"; //����
						$query="select * from son_module where father_module_id={$data_father['id']} order by sort desc";
						$result_son=execute($link, $query);
						while($data_son=mysqli_fetch_assoc($result_son)){
							echo "<option value='{$data_son['id']}'>{$data_son['module_name']}</option>";
						}
						echo "</optgroup>";
				}
				?>
			</select>
			<input class="title" placeholder="���������" name="title" type="text" />
			<textarea name="content" class="content"></textarea>
			<input class="publish" type="submit" name="submit" value="" />
			<div style="clear:both;"></div>
		</form>	
	</div>
<?php include_once 'inc/footer.inc.php';?>