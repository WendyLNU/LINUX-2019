<!-- �����ҳ�� -->
<?php
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$link=connect();
if(isset($_POST['submit'])){
	foreach ($_POST['sort'] as $key=>$val){
		if(!is_numeric($val) || !is_numeric($key)){ //�����id��Ҫ������
			skip('father_module.php', 'error', '�����������');
		}
		$query[]="update father_module set sort={$val} where id={$key}";
		
	}
	if(execute_multi($link, $query, $error)){ //������䶼ִ�гɹ�
		skip('father_module.php', 'ok', '�����޸ĳɹ���');
	}else{
		skip('father_module.php', 'error', '$error��');
	}
}
$template['title']='������б�ҳ';
?>
<?php include 'inc/header.inc.php'?>
<?php include 'inc/footer.inc.php'?>
<div id="main">
	<div class="title">������б�</div>
	<form method="post">
	<table class="list">
		<tr>
			<th>����</th>	 	 	
			<th>�������</th>
			<th>����</th>
		</tr>
		<?php
		$query="select * from father_module";
		$result=execute($link,$query);
		while($data=mysqli_fetch_assoc($result)) {
			//var_dump($data);
			$url=urlencode("father_module_delete.php?id={$data['id']}");//��urlencode��ֹ�����������ʺŻ��� ,urlencode���з���ĸ�����ַ�����%�ź��16���������ո����Ϊ�Ӻš�����urldecode����
			$return_url=urlencode($_SERVER['REQUEST_URI']);//ȡ�õ�ǰurl��·����ַ
			$message="�����Ҫɾ�������{$data['module_name']}��?";
			$delete_url="confirm.php?url={$url}&return_url={$return_url}&message={$message}";//ɾ��ȷ�� ҳ��
$html=<<<YU
			<tr>
				<td><input class="sort" type="text" name="sort[{$data['id']}]" value="{$data['sort']}"/></td>
				<td>{$data['module_name']}[id:{$data['id']}]</td>
				<td><a href="#">[����]</a>&nbsp;&nbsp;<a href="father_module_update.php?id={$data['id']}">[�༭]</a>&nbsp;&nbsp;<a href="$delete_url">[ɾ��]</a></td>
			</tr>	
YU;
//��PHP������е��κ������ַ�������Ҫת��
			echo $html;
		}
		?>
	</table>
	<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="����" />
	</form>
</div>

    
