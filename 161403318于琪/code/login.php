<!-- ǰ̨��¼ҳ�� -->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
if(is_login($link)){ //����Ѿ���½��
	skip('index.php', 'error', '���Ѿ���¼���벻Ҫ�ظ���¼��');
}
if(isset($_POST['submit'])){
	include 'inc/check_login.inc.php';
	escape($link, $_POST);
	$query="select * from member where name='{$_POST['name']}' and pw=md5('{$_POST['pw']}')";
	$result=execute($link, $query);
	if(mysqli_num_rows($result)==1){
		setcookie('sfk[name]',$_POST['name'],time()+$_POST['time']); //�����¼״̬
		                                                             //����timeΪ��ǰʱ��+����д��ʱ��ֵ
		setcookie('sfk[pw]',sha1(md5($_POST['pw'])),time()+$_POST['time']);
		skip('index.php', 'ok', '��¼�ɹ���');
	}else
	{
		skip('login.php', 'error', '�û�����������д����');
	}
}
$template['title']='��ӭ��¼';
?>
<?php include_once 'inc/header.inc.php';?>
<div id="register" class="auto">
	<h2>���¼</h2>
	<form method="post">
		<label>�û�����<input type="text" name="name" /><span></span></label>
		<label>���룺<input type="password" name="pw" /><span></span></label>
		<label>��֤�룺<input name="vcode" type="text"  /><span>*�������·���֤��</span></label>
		<img class="vcode" src="show_code.php" />
		<label>�Զ���¼��
			<select style="width:236px;height:25px;" name="time">
				<option value="3600">1Сʱ��</option>
				<option value="86400">1����</option>
				<option value="259200">3����</option>
				<option value="2592000">30����</option>
			</select>
			<span>*�����������������Զ���¼</span>
		</label>
		<div style="clear:both;"></div>
		<input class="btn" type="submit" name="submit" value="��¼" />
	</form>
</div>
<?php include_once 'inc/footer.inc.php';?>
	