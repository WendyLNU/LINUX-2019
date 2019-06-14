<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="c_register.css">
</head>
<body>
<div class="Rmain">
  <div id="r1" class="r1 show">企业ID登录</div>
  <div id="r2" class="r1">账号登录</div>
  <div id="back"></div>
  <div class="sback">
  <div id="reg1" class="register show">
    <div class="close"></div>
    <form action="iadx_reg_conn1.php" method="post">
      <h1>登录你的ID</h1>
      <label>
        <p style="top: 80px">邮箱：</p>
        <input type="email" name="email" style="top: 78px">
        <p style="top: 150px">密码：</p>
        <input type="password" name="password" style="top: 148px">
        <input type="submit" name="submit1" value="" id="sub">
      </label>
    </form>
    <div>
      <a href="#" id="re1" style="left: 70px;bottom: 75px">手机号登录</a>
      <a href="#" style="right: 50px;bottom: 75px">无法登陆？</a>
      <a href="idx_login.php" style="bottom: 10px;left: 160px;" target="_blank">没有账号？现在注册</a>
    </div>
  </div>

  <div id="reg2" class="register">
    <div class="close"></div>
    <form action="iadx_reg_conn2.php" method="post">
      <h1>登录你的ID</h1>
      <label>
        <p style="top: 80px">手机号：</p>
        <input type="text" name="phone" style="top: 78px">
        <p style="top: 150px">验证码：</p>
        <input type="text" name="number" style="top: 148px">
        <input type="submit" name="submit2" value="" id="sub">
      </label>
    </form>
    <div>
      <a href="#" id="re2" style="left: 70px;bottom: 75px">手机号登录</a>
      <a href="#" style="right: 50px;bottom: 75px">无法登陆？</a>
      <a href="idx_login.php" style="bottom: 10px;left: 160px;" target="_blank">没有账号？现在注册</a>
    </div>
  </div>


  <div id="reg3" class="register">
    <div class="close"></div>
    <form action="iadx_reg_conn3.php" method="post" id="3">
      <h1>登录你的ID</h1>
      <label>
        <p style="top: 80px">企业ID：</p>
        <input type="name" name="name2" style="top: 78px">
        <p style="top: 150px">密码：</p>
        <input type="password" name="password2" style="top: 148px">
        <input type="submit" name="submit3  " value="" id="sub">
      </label>
    </form>
    <div>
      <a href="#" style="right: 50px;bottom: 75px">无法登陆？</a>
      <a href="idx_login2.php" style="bottom: 10px;left: 160px;" target="_blank">没有企业ID?</a>
    </div>
  </div>
  </div>
</div>
</body>
</html>


<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_register.js"></script>
