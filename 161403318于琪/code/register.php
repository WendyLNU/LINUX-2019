<!-- ǰ̨ע��ҳ�� -->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
if(is_login($link)){ //����Ѿ���½��
	skip('index.php', 'error', '���Ѿ���¼���벻Ҫ�ظ�ע�ᣡ');
}
if(isset($_POST['submit'])){ //��������ύ
	include 'inc/check_register.inc.php';
	$query="insert into member(name,pw,register_time) values('{$_POST['name']}',md5('{$_POST['pw']}'), now())";//���벻�����ļӽ�ȥ��Ҫ��MD5����
	$result=execute($link, $query);
	if(mysqli_affected_rows($link)==1){
		setcookie('sfk[name]',$_POST['name']); //����ע��״̬
		setcookie('sfk[pw]',sha1(md5($_POST['pw'])));
		skip('index.php', 'ok', 'ע��ɹ���');
	}else{
		skip('register.php', 'error', 'ע��ʧ�ܣ������ԣ�');
	} 
}
$template['title']='��Աע��ҳ';
?> 
<?php include_once 'inc/header.inc.php';?>
	<div id="register" class="auto">
		<h2>��ӭע���Ϊ ������ǻ�Ա</h2>
		<form method="post">
			<label>�û�����<input type="text" name="name" /><span>*�û�������Ϊ�գ����ҳ��Ȳ��ó���32���ַ�</span></label>
			<label>���룺<input type="password" name="pw" /><span>*���벻������6λ</span></label>
			<label>ȷ�����룺<input type="password" name="confirm_pw" /><span>*������������һ��</span></label>
			<label>��֤�룺<input name="vcode" type="text"  /><span>*�������·���֤��</span></label>
			<img class="vcode" src="show_code.php" /> 
			<div style="clear:both;"></div>
			<input class="btn" name="submit" type="submit" value="ȷ��ע��" />
		</form>
	</div>
	<div id="footer" class="auto">
		<div class="bottom">
			<a>�������</a>
		</div>
		<div class="copyright">Powered by stars 2019 stars.com</div>
	</div>
</body>
</html>