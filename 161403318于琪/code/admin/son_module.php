<!-- 子版块展示页 -->
<?php
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$link=connect();
if(isset($_POST['submit'])){
	foreach ($_POST['sort'] as $key=>$val){
		if(!is_numeric($val) || !is_numeric($key)){ //排序和id都要是数字
			skip('son_module.php', 'error', '排序参数错误！');
		}
		$query[]="update son_module set sort={$val} where id={$key}";

	}
	if(execute_multi($link, $query, $error)){ //所有语句都执行成功
		skip('son_module.php', 'ok', '排序修改成功！');
	}else{
		skip('son_module.php', 'error', '$error！');
	}
}
$template['title']='子板块列表页';
?>
<?php include 'inc/header.inc.php'?>
<?php include 'inc/footer.inc.php'?>
<div id="main">
	<div class="title">子板块列表</div>
	<form method="post">
	<table class="list">
		<tr>
			<th>排序</th>	 	 	
			<th>版块名称</th>
			<th>所属父板块</th>
			<th>版主</th>
			<th>操作</th>
		</tr>
		<?php
		$query="select ssm.id,ssm.sort,ssm.module_name,sfm.module_name father_module_name,ssm.member_id from son_module ssm,father_module sfm where ssm.father_module_id=sfm.id order by sfm.id";
		$result=execute($link,$query);
		while($data=mysqli_fetch_assoc($result)) {
			//var_dump($data);
			$url=urlencode("son_module_delete.php?id={$data['id']}");//用urlencode防止参数中两个问号混淆 ,urlencode所有非字母数字字符换成%号后跟16进制数，空格编码为加号。可用urldecode解码
			$return_url=urlencode($_SERVER['REQUEST_URI']);//取得当前url的路径地址
			$message="你真的要删除子板块{$data['module_name']}吗?";
			$delete_url="confirm.php?url={$url}&return_url={$return_url}&message={$message}";//删除确认 页面
$html=<<<YU
			<tr>
				<td><input class="sort" type="text" name="sort[{$data['id']}]" value="{$data['sort']}"/></td>
				<td>{$data['module_name']}[id:{$data['id']}]</td>
				<td>{$data['father_module_name']}</td>
				<td>{$data['member_id']}</td>
				<td><a href="#">[访问]</a>&nbsp;&nbsp;<a href="son_module_update.php?id={$data['id']}">[编辑]</a>&nbsp;&nbsp;<a href="$delete_url">[删除]</a></td>
			</tr>	
YU;
//在PHP定界符中的任何特殊字符都不需要转义
			echo $html;
		}
		?>
	</table>
	<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="排序" />
	</form>
</div>

    

