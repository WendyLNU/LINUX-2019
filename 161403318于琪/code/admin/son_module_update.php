<!-- �Ӱ���޸�ҳ -->
<?php 
include_once '../inc/config.inc.php';
include_once '../inc/mysql.inc.php';
include_once '../inc/tool.inc.php';
$template['title']='�Ӱ���޸�ҳ';
$link=connect();
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){ //���idΪ�ջ�id��������
	skip('son_module.php', 'error', 'id��������');
}
$query="select * from son_module where id={$_GET['id']}";
$result=execute($link, $query);
if(!mysqli_num_rows($result)){//���������
	skip('son_module.php', 'error', '�Ӱ����Ϣ�����ڣ�');
}
$data=mysqli_fetch_assoc($result);
if(isset($_POST['submit'])){
	//��֤�û���д����Ϣ
	$check_flag='update';//check_father_module.inc.php
	include 'inc/check_son_module.inc.php';
	$query="update son_module set father_module_id={$_POST['father_module_id']},module_name='{$_POST['module_name']}',info='{$_POST['info']}',member_id={$_POST['member_id']},sort={$_POST['sort']} where id={$_GET['id']}";
	execute($link, $query);
	if(mysqli_affected_rows($link)==1){ //�����Ӱ��
		skip('son_module.php', 'ok', '�޸ĳɹ���');
	}else{
		skip('son_module.php', 'error', '�޸�ʧ�ܣ�');//ûӰ�죬��û���޸ģ��޸�ʧ��
	}
}
?>
<?php include 'inc/header.inc.php'?>
<div id="main">
	<div class="title" style="margin-bottom:20px;">�޸��Ӱ��- <?php echo $data['module_name']?></div>
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
							if($data['father_module_id']==$data_father['id']){
								echo "<option selected='selected'  value='{$data_father['id']}'>{$data_father['module_name']}</option>";
							}else{
								echo "<option value='{$data_father['id']}'>{$data_father['module_name']}</option>";
							}
						}
						?>
					</select> 
				<td>
					����ѡ��һ�������ĸ����
				</td>
			</tr>
			<tr>
				<td>�������</td>
				<td><input name="module_name" value="<?php echo $data['module_name']?>" type="text" /></td>
				<td>
					������Ʋ���Ϊ�գ���󲻵ó���66���ַ�
				</td>
			</tr>
			<tr>
				<td>�����</td>
				<td>
					<TEXTAREA name="info"><?php echo $data['info']?></TEXTAREA>
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
				<td><input name="sort" value="<?php echo $data['sort']?>" type="text" /></td>
				<td>
					��дһ�����ּ���
				</td>
			</tr>
			</table>
			<input style="margin-top: 20px; cursor:pointer;" class="btn" type="submit" name="submit" value="���" />
		</form>
</div>
<?php include 'inc/footer.inc.php'?>