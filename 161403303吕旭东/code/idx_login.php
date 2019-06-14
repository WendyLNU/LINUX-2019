<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="c_login.css">
</head>
<?php
include "index_head.php";
include "idx_register.php";
?>//表单
<body>
  <div id="login_mess">
  <div class="login_head">
    <div class="welcome_z">欢迎加入搬码</div>
    <div id="login_head_1" class="login_h login_h_color" style="left: 290px">基本信息</div>
    <div id="login_head_2" class="login_h" style="left: 570px">安全信息</div>
    <div id="login_head_3" class="login_h" style="left: 850px">支付信息</div>
  </div>

  <div class="login_main">
    <form method="post" action="idx_login_rul.php" name="login_form1">
    <div id="login_1" class="l_main show">
      <p class="l_head">基本信息</p>
      <a href="idx_login2.php" class="login_reserve">企业ID注册</a>
      <div class="l_main_m">
        <p>姓&nbsp&nbsp&nbsp：</p>
        <input type="text" name="fname" required/>
        <p>名&nbsp&nbsp&nbsp：</p>
        <input type="text" name="lname" required/>
        <p>性&nbsp&nbsp&nbsp别：</p>
        <select name="sex">
          <option value="M">男</option>
          <option value="F">女</option>
        </select>
        <p>生&nbsp&nbsp&nbsp日：</p>
        <input type="text" name="birthday" required/>
        <p>邮&nbsp&nbsp&nbsp箱：</p>
        <input type="email" name="email" value=" " required/>
        <p>手机号：</p>
        <select name="area">
          <option value="+86">+86</option>
          <option value="+852">+852</option>
          <option value="+853">+853</option>
          <option value="+886">+886</option>
        </select>
        <input type="text" name="phone" value=""/>
        <P>密&nbsp&nbsp&nbsp码：</P>
        <input type="password" name="pw1" id="pw1" value="" data-options="required:true"/>
        <P>确认密码：</P>
        <input type="password" name="pw2" id="pw2" value="" required="required" validType="equals['#pw1]"/><br>
        <input type="button" name="button" value="下一步" style="position: relative;top: 10px" class="login_button_1"/>
      </div>
    </div>
    <div id="login_2" class="l_main">
      <p class="l_head">安全信息</p>
      <div class="l_main_m">
        <p>备用邮箱：</p>
        <input type="email" name="email2" value=" " required/>
        <p>备用手机：</p>
        <select name="area2">
          <option value="+86">+86</option>
          <option value="+852">+852</option>
          <option value="+853">+853</option>
          <option value="+886">+886</option>
        </select>
        <input type="text" name="phone2" value=""/>
        <p>密保问题1：</p>
        <input type="text" name="question1" value=" " required/><br>
        <input type="text" name="answer1" value=" " required/>
        <p>密保问题2：</p>
        <input type="text" name="question2" value=" " required/><br>
        <input type="text" name="answer2" value=" " required/>
        <p>密保问题3：</p>
        <input type="text" name="question3" value=" " required/><br>
        <input type="text" name="answer3" value=" " required/><br>
        <input type="button" name="button" value="上一步" style="position: relative;top: 10px" class="login_button_1"/><br>
        <input type="button" name="button" value="下一步" style="position: relative;top: 10px" class="login_button_2"/>
      </div>
    </div>
    <div id="login_3" class="l_main">
      <p class="l_head">支付信息</p>
      <div class="l_main_m">
        <p>收件地址：</p>
        <input type="text" name="address" required/>
        <p>邮政编码：</p>
        <input type="text" name="potalcode" required/>
        <h2>支付方式(预留，可不填）：</h2><br>
        <select name="pay" style="width: 90px;left: 304px;top: -45px;">
          <option value="未填写">暂不填写</option>
          <option value="支付宝">支付宝</option>
          <option value="微信">微信</option>
          <option value="银联">银联</option>
          <option value="visc">visc</option>
          <option value="银行卡">银行卡</option>
        </select>
        <P>账&nbsp&nbsp&nbsp号：</P>
        <input type="text" name="payid" value="" data-options="required:true"/>
        <P>密&nbsp&nbsp&nbsp码：</P>
        <input type="password" name="paypwd" id="pw1" value="" data-options="required:true"/><br>
        <input type="button" name="button" value="上一步" style="position: relative;top: 10px" class="login_button_2"/><br>
        <input type="submit" name="button" value="提交" style="position: relative;top: 10px"/>
      </div>
    </form>
  </div>
  </div>


</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_login.js"></script>


