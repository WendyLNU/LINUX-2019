<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="CHINA-Compatible" content="IE=edge">
<title></title>
<meta name="description" content="">
<meta name="viewport"
	content="width=device-width, initial-scale=1, shrink-to-fit=no">
<meta name="robots" content="all,follow">
<!-- Bootstrap CSS-->
<link rel="stylesheet" href="vendor/bootstrap/css/bootstrap.min.css">
<!-- Font Awesome CSS-->
<link rel="stylesheet"
	href="vendor/font-awesome/css/font-awesome.min.css">
<!-- Fontastic Custom icon font-->
<link rel="stylesheet" href="css/fontastic.css">
<!-- Google fonts - Poppins -->
<!-- theme stylesheet-->
<link rel="stylesheet" href="css/style.default.css"
	id="theme-stylesheet">
<!-- Custom stylesheet - for your changes-->
<link rel="stylesheet" href="css/custom.css">
<!-- Favicon-->
<link rel="shortcut icon" href="img/favicon.ico">
<!-- Tweaks for older IEs-->
<!--[if lt IE 9]>
  </head>
  <body>
    <div class="page login-page">
      <div class="container d-flex align-items-center">
        <div class="form-holder has-shadow">
          <div class="row">
            <!-- Logo & Information Panel-->
<div class="col-lg-6">
	<div class="info d-flex align-items-center">
		<div class="content">
			<div class="logo">
				<h1>幸运抽奖系统</h1>
			</div>
			<p>公司年会抽奖，商家抽奖活动，商家促销抽奖，LED屏显示抽奖</p>
		</div>
	</div>
</div>
<!-- Form Panel    -->
<div class="col-lg-6 bg-white">
	<div class="form d-flex align-items-center">
		<div class="content">
			<form class="form-validate" method="post" action="UserRegister">
				<div class="form-group">
					用户名 <input id="register-username" type="text"
						name="registerUsername" required data-msg="请输入用户名"
						class="input-material">

					<!--  > <label for="register-username" class="label-material">用户名      </label><-->
				</div>
				<div class="form-group">
					邮箱地址 <input id="register-email" type="email" name="registerEmail"
						required data-msg="请输入有效的邮箱地址" class="input-material">

					<!--  ><label for="register-email" class="label-material">邮箱地址       </label><-->
				</div>
				<div class="form-group">
					密码 <input id="register-password" type="password"
						name="registerPassword" required data-msg="请输入密码"
						class="input-material">

					<!--  > <label for="register-password" class="label-material">密码        </label><-->
				</div>
				<div class="form-group terms-conditions">
					<input id="register-agree" name="registerAgree" type="checkbox"
						required value="1" data-msg="Your agreement is required"
						class="checkbox-template"> <label for="register-agree">Agree
						the terms and policy</label>
				</div>
				<div class="form-group">
					<input type="submit" name="Submit" value="注册"
						class="btn btn-primary">
					<!--  ><button id="regidter" type="submit" name="registerSubmit" class="btn btn-primary">Register</button><-->
				</div>
			</form>
			<small>已经注册账户? </small><a href="login.jsp" class="signup">Login</a>
		</div>
	</div>
</div>
</div>
</div>
</div>
<div class="copyrights text-center">
	<p>Copyright &copy; 2019.Company name All rights reserved.</p>
</div>
</div>
<!-- JavaScript files-->
<script src="vendor/jquery/jquery.min.js"></script>
<script src="vendor/popper.js/umd/popper.min.js"> </script>
<script src="vendor/bootstrap/js/bootstrap.min.js"></script>
<script src="vendor/jquery.cookie/jquery.cookie.js"> </script>
<script src="vendor/chart.js/Chart.min.js"></script>
<script src="vendor/jquery-validation/jquery.validate.min.js"></script>
<!-- Main File-->
<script src="js/front.js"></script>
</body>
</html>