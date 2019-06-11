<!-- 前台注册页面 -->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
if(is_login($link)){ //如果已经登陆了
	skip('index.php', 'error', '你已经登录，请不要重复注册！');
}
if(isset($_POST['submit'])){ //如果点了提交
	include 'inc/check_register.inc.php';
	$query="insert into member(name,pw,register_time) values('{$_POST['name']}',md5('{$_POST['pw']}'), now())";//密码不能明文加进去，要用MD5加密
	$result=execute($link, $query);
	if(mysqli_affected_rows($link)==1){
		setcookie('sfk[name]',$_POST['name']); //保存注册状态
		setcookie('sfk[pw]',sha1(md5($_POST['pw'])));
		skip('index.php', 'ok', '注册成功！');
	}else{
		skip('register.php', 'error', '注册失败，请重试！');
	} 
}
$template['title']='会员注册页';
?> 
<?php include_once 'inc/header.inc.php';?>
	<div id="register" class="auto">
		<h2>欢迎注册成为 你的明星会员</h2>
		<form method="post">
			<label>用户名：<input type="text" name="name" /><span>*用户名不得为空，并且长度不得超过32个字符</span></label>
			<label>密码：<input type="password" name="pw" /><span>*密码不得少于6位</span></label>
			<label>确认密码：<input type="password" name="confirm_pw" /><span>*请输入与上面一致</span></label>
			<label>验证码：<input name="vcode" type="text"  /><span>*请输入下方验证码</span></label>
			<img class="vcode" src="show_code.php" /> 
			<div style="clear:both;"></div>
			<input class="btn" name="submit" type="submit" value="确定注册" />
		</form>
	</div>
	<div id="footer" class="auto">
		<div class="bottom">
			<a>你的明星</a>
		</div>
		<div class="copyright">Powered by stars 2019 stars.com</div>
	</div>
</body>
</html>