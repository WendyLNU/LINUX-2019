<!-- ����Ӱ�� -->
<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$template['title']='�Ӱ�����ҳ';
$link=connect();
if(isset($_POST['submit'])){
	/*
	 ��֤�û���д����Ϣ
	*/
	$check_flag='add';
	include 'inc/check_son_module.inc.php';
	$query="insert into son_module(father_module_id,module_name,info,member_id,sort) values({$_POST['father_module_id']},'{$_POST['module_name']}','{$_POST['info']}',{$_POST['member_id']},{$_POST['sort']})";
	execute($link, $query);
	if(mysqli_affected_rows($link))	{
		skip('son_module.php', 'ok', '��ϲ�㣬��ӳɹ���');
	}else{
		skip('son_module_add.php', 'error', '�Բ������ʧ�ܣ������ԣ�');
	}
}
?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">����Ӱ��</div>
	<form method="post" >
		<table class="au">
			<tr>
				<td>���������</td>
				<td>
					<select name="father_module_id"> 
						<option value="0">======��ѡ��һ�������======</option> 
						<?php 
						$query="select * from father_module";
						$result_father=execute($link, $query);
						while($data_father=mysqli_fetch_assoc($result_father)){
							echo "<option value='{$data_father['id']}'>{$data_father['module_name']}</option>";
						}
						?>
					</select> 
				<td>
					����ѡ��һ�������ĸ����
				</td>
			</tr>
			<tr>
				<td>�������</td>
				<td><input name="module_name" type="text" /></td>
				<td>
					������Ʋ���Ϊ�գ���󲻵ó���66���ַ�
				</td>
			</tr>
			<tr>
				<td>�����</td>
				<td>
					<TEXTAREA name="info"></TEXTAREA>
				</td>
				<td>
					��鲻�ö���255���ַ�
				</td>
			</tr>
			<tr>
				<td>����</td>
				<td>
					<select name="member_id"> 
						<option value="0">======��ѡ��һ����Ա��Ϊ����======</option> 
					</select> 
				<td>
					����������ѡ��һ����Ա��Ϊ����
				</td>
			</tr>
			<tr>
				<td>����</td>
				<td><input name="sort" value="0" type="text" /></td>
				<td>
					��дһ�����ּ���
				</td>
			</tr>
			</table>
			<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="���" />
		</form>
</div>
<?php include 'inc/footer.inc.php'?>