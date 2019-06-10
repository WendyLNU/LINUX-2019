<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="c_login.css">
</head>
<?php
include "index_head.php";
?>
<body>
<div class="login_result">
  <div class="l_head">确认你的信息</div>
  <?php
  error_reporting(E_ALL^E_NOTICE^E_WARNING);

  if(!($fname = $_POST['fname'])){$fname = 'fname';};//表单传入的地方
  if(!($lname = $_POST['lname'])){$lname = 'lname';};
  if(!($sex = $_POST['sex'])){$sex = 'M';};
  if(!($email = $_POST['email'])){$email = 'email';};
  if(!($area = $_POST['area'])){$area = '86';};
  if(!($phone = $_POST['phone'])){$phone = 'phone';};
  if(!($birthday = $_POST['birthday'])){$birthday = '未填写';};
  if(!($pw1 = $_POST['pw1'])){$pw1 = 'password';};

  if(!($email2 = $_POST['email2'])){$email2 = '未填写';};
  if(!($area2 = $_POST['area2'])){$area2 = '86';};
  if(!($phone2 = $_POST['phone2'])){$phone2 = '未填写';};
  if(!($question1 = $_POST['question1'])){$question1 = '未填写';};
  if(!($answer1 = $_POST['answer1'])){$answer1 = '未填写';};
  if(!($question2 = $_POST['question2'])){$question2 = '未填写';};
  if(!($answer2 = $_POST['answer2'])){$answer2 = '未填写';};
  if(!($question3 = $_POST['question3'])){$question3 = '未填写';};
  if(!($answer3 = $_POST['answer3'])){$answer3 = '未填写';};

  if(!($address = $_POST['address'])){$address = '000000';};
  if(!($potalcode = $_POST['potalcode'])){$potalcode = '未填写';};
  if(!($pay = $_POST['pay'])){$pay = '未填写';};
  if(!($payid = $_POST['payid'])){$payid = '未填写';};
  if(!($paypwd = $_POST['paypwd'])){$paypwd = '未填写';};

  setcookie('fname',$fname);
  setcookie('lname',$lname);
  setcookie('sex',$sex);
  setcookie('email',$email);
  setcookie('area',$area);
  setcookie('phone',$phone);
  setcookie('birthday',$birthday);
  setcookie('password',$pw1);
  setcookie('email2',$email2);
  setcookie('area2',$area2);
  setcookie('phone2',$phone2);
  setcookie('question1',$question1);
  setcookie('answer1',$answer1);
  setcookie('question2',$question2);
  setcookie('answer2',$answer2);
  setcookie('question3',$question3);
  setcookie('answer3',$answer3);
  setcookie('address',$address);
  setcookie('potalcode',$potalcode);
  setcookie('pay',$pay);
  setcookie('payid',$payid);
  setcookie('paypwd',$paypwd);



  echo "
<h5>姓&nbsp&nbsp名：</h5><p>$fname $lname</p>
  <h5>性&nbsp&nbsp别：</h5><p>$sex</p>
  <h5>生&nbsp&nbsp日：</h5><p>$birthday</p>
  <h5>手&nbsp&nbsp机：</h5><p>$area $phone</p>
  <h5>邮&nbsp&nbsp箱：</h5><p>$email</p>
  <h5>备用手机：</h5><p>$area2 $phone2</p>
  <h5>备用邮箱：</h5><p>$email2</p>
  <h5>地&nbsp&nbsp址：</h5><p>$address</p>
  <h5>邮政编码：</h5><p>$potalcode</p>";

  ?>
  <div id="p_agreement">
    <input type="checkbox" name="checkbox">
    接受<a id="p_agreement_p">《搬码软件许可及服务协议》</a></div>
  <div id="bottons">
    <a href="idx_login.php"><button>修改</button></a>
    <a href="idx_login_ins.php"><button>提交</button></a>
  </div>
</div>

<div id="agreement" class="hidden">
  <div id="agreement_main">
    <div id="agreement_text">
      <pre>
        搬码软件许可及服务协议
【首部及导言】
欢迎您使用搬码软件及服务！
为使用搬码软件（以下统称“本软件”）及服务（以下统称“本服务”），您应当阅读并遵守《搬码软件许可及服务协议》（以下简称“本协议”）。请您务必审慎阅读、充分理解各条款内容，特别是免除或者限制搬码责任的条款、对用户权利进行限制的条款、约定争议解决方式和司法管辖的条款（如第十五条相关约定）等，以及开通或使用某项服务的单独协议。限制、免责条款或者其他涉及您重大权益的条款可能以加粗、加下划线等形式提示您重点注意。
除非您已充分阅读、完全理解并接受本协议所有条款，否则您无权下载、安装或使用本软件和/或相关服务。您点击“同意”、“下一步”或您的下载、安装、使用、登录等行为或者您以其他任何明示或者默示方式表示接受本协议的，即视为您已阅读并同意本协议的约束。本协议即在您与搬码之间产生法律效力，成为对双方均具有约束力的法律文件。
如果您因年龄、智力等因素而不具有完全民事行为能力，请在法定监护人（以下简称"监护人"）的陪同下阅读和判断是否同意本协议。
如果您是非中国大陆地区的用户，您订立或履行本协议以及使用本服务的行为还需要同时遵守您所属和/或所处国家或地区的法律。
一、【协议的范围】
1.1 本协议是您与搬码之间关于您下载、安装、使用、登录本软件，以及使用本服务所订立的协议。
1.2 本协议的内容，包括但不限于以下与本软件和/或本服务相关的协议、规则、规范以及搬码可能不断发布的关于本软件和/或本服务的相关协议、规则、规范等内容，前述内容一经正式发布，即为本协议不可分割的组成部分，与其构成统一整体，您同样应当遵守本协议。
二、【关于本软件和本服务】
2.1 本软件是指搬码开发并按照本协议之约定授权用户下载、安装、使用的搬码软件。
2.2 您知晓并同意，搬码可能会根据需要更新或调整本软件和/或本服务的内容。
2.3 您可能可以通过电脑、手机等终端以客户端等形式使用本服务，具体以搬码提供的为准。同时，搬码会不断丰富您使用本服务的终端、形式等。当您使用本服务时，您应选择与您的终端、系统等相匹配的本软件版本，否则，您可能无法正常使用本服务。
2.4 搬码给予您一项个人的、不可转让及非排他性的许可，以按照本协议及搬码其他协议、规则限定的范围和方式使用本软件。
2.4.1 您可以为非商业目的在单一台终端设备上下载、安装、使用、登录本软件。
2.4.2 您可以制作本软件的一个副本，仅用作备份。备份副本必须包含原软件中含有的所有著作权信息。
2.4.3 本条及本协议其他条款未明示授权的其他一切权利仍由搬码保留，您在行使这些权利时须另外取得搬码的书面许可。搬码如果未行使前述任何权利，并不构成对该权利的放弃。
      </pre>
    </div>
    <div id="agreement_close">关闭</div>
  </div>
  <div id="agreement_back"></div>
</div>
</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript">
  $(document).ready(function () {
    $('#p_agreement_p,#agreement_close').click(function (e) {
      e.preventDefault();
      $('#agreement').toggleClass('show');
      $('#agreement').toggleClass('hidden');
    });
  });
</script>
