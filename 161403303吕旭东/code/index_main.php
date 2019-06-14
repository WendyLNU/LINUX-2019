<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Zcode</title>
  <link type="text/css" rel="stylesheet" href="c_logo.css">
  <link type="text/css" rel="stylesheet" href="c_navigate.css">
  <link type="text/css" rel="stylesheet" href="c_main.css">
  <link type="text/css" rel="stylesheet" href="c_bottom.css">
</head>
<body>
<?php
  include "index_head.php";
  include "idx_register.php";
?>
  <div class="LeftNavigate" style="position: fixed;top: 0;z-index: 9">
    <div class="logo">
      <canvas id="myCanvas" width="200px" height="500px" ></canvas>
      <div class="logimg">
        <ul>
          <li><a href="idx_download.php" class="c1" target="_blank">下载搬码</a></li>
          <li><a href="#" class="c2">搬码市场</a></li>
          <li><a href="idx_serves.php" class="c3" target="_blank">联系专家</a></li>
          <li><a href="idx_serves.php" class="c4" target="_blank">私人订制</a></li>
        </ul>
      </div>
    </div>
    <div class="LeNav">
      <ul>
        <li class="s1"><p></p></li>

        <li><a id="L1">N</a><ul><li id="l1">最新消息</li></ul></li>
        <li><a id="L2">F</a><ul><li id="l2">强大功能</li></ul></li>
        <li><a id="L3">S</a><ul><li id="l3">企业共享</li></ul></li>

        <li class="s23"><p></p></li>

        <li><a id="L4">D</a><ul><li id="l4">自主协议</li></ul></li>
        <li><a id="L5">P</a><ul><li id="l5">私人订制</li></ul></li>
        <li><a id="L6">O</a><ul><li id="l6">工作机会</li></ul></li>

        <li class="s4"><p></p></li>
      </ul>
    </div>
  </div>
·
  <div class="main">
    <div id="m1">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>最新消息</h1></div>
      <img src="product_logo/Sketches%202.png" width="270" height="270" style="left:90px;top: 10px;position: absolute">
      <p style="position:relative;left: 400px;top: 40px;font-family:'c2';font-size: 30px">管理您的电子卡片<br><br>Zebra钱包：现已上市</p>
      <a href="idx_shopping_article.php?a=1" class="Download template" target="_blank">立即购买 ></a>
      <a href="#" class="ReadMore template">了解更多 ></a>
    </div>
    <div id="m2">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>强大功能</h1></div>
      <img class="img1" src="src/m21.png" />
      <h3 style="position: relative;left: 300px;font-size: 25px;top: 20px;font-family:'c2'">设备同步</h3>
      <p style="position: relative;left: 300px;font-size: 20px;top: 20px;font-family:'c2'">使用您的搬码账号，您的所有设备都可以使用购买的软件</p>
      <h3 style="position: relative;left: 300px;font-size: 25px;top: 20px;font-family:'c2'">开源</h3>
      <p style=" position: relative;left: 300px;font-size: 20px;top: 20px;font-family:'c2'">我们公开了代码，您可以根据喜好进行自定义设计</p>
      <h3 style=" position: relative;left: 300px;font-size: 25px;top: 20px;font-family:'c2' ">永不止步</h3>
      <p style=" position: relative;left: 300px;font-size: 20px;top: 20px;font-family:'c2'">我们会一直更新您购买的软件，直到您满意</p>
      <img class="img2" src="src/m2.png" />
      <a href="idx_download.php" class="Download template" target="_blank">立即下载</a>
      <a href="#" class="ReadMore template">更多功能</a>
    </div>
    <div id="m3">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>企业共享</h1></div>
      <p style=" position: relative;left: 100px;font-size: 25px;top: 20px;font-family:'c2'">一次购买，全企免费<br><br>连接您的企业账号，就可以免费试用企业所有软件<br><br>您的企业还没有注册账号？<a href="idx_login2.php" target="_blank">注册企业账户</a></p>
      <img class="img3" src="src/m3.png" />
    </div>
    <div id="m4">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>独立协议</h1></div>
      <h3 style="position: relative;left: 100px;font-size: 25px;top: 20px;font-family:'c2'">Feedback计划</h3><br>
      <p style="position: relative;left: 100px;font-size: 20px;top: 20px;font-family:'c2'">购买软件，并给我们提供使用反馈，您将得到一笔回报</p><br>
      <h3 style="position: relative;left: 100px;font-size: 25px;top: 20px;font-family:'c2'">Beta计划</h3><br>
      <p style="position: relative;left: 100px;font-size: 20px;top: 20px;font-family:'c2'">以更优惠的价格购买软件，并使用它的Beta版本,尝试最新功能</p><br>
    </div>
    <div id="m5">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>私人订制</h1></div>
      <p style="position: relative;left: 100px;font-size: 30px;top: 40px;font-family:'c2'">对我们市场提供的软件不满意？<br><br>现在定制，我们派一位专家为您服务</p>
      <a href="idx_serves.php" class="Start template" target="_blank">开始定制</a>
      <a href="idx_serves.php" class="Customer template" target="_blank">联系客服</a>
    </div>
    <div id="m6">
      <div style="width: 100%;text-align: center;font-family:'c1';margin-top: 10px"><h1>工作机会</h1></div>
      <p style="position: relative;left: 100px;font-size: 30px;top: 40px;font-family:'c2'">加入我们<br><br>动手开发你的软件</p>
      <a href="idx_join_main.php" class="ReadMore template" target="_blank">了解更多</a>
    </div>
    <div style="height: 100px"></div>
  </div>

  <div class="bottom_m">
      <pre>
        <a>关于搬码</a> <a>合作伙伴</a> <a> 营销中心</a> <a> 廉正举报</a> <a> 联系客服</a> <a> 开放平台</a> <a> 诚征英才</a> <a> 联系我们</a> 隐私权政策 法律声明知识产权 | © 2019-现在 Zcode.com 版权所有
        增值电信业务经营许可证：xxx-xxxxxxxx|增值电信业务经营许可证（跨地区）： xx-xxxxxxxx|网络文化经营许可证：x网文[xxxx]xxxxxxx号|
        互联网药品信息服务资格证书（x）-经营性-xxxx-xxxx|短消息类服务接入代码使用证书：号【xxxx】xxxxx-xxxx|信息网络传播视听许可证：xxxxxxx号|出版物网络交易平台服务经营备案号：新出发xx字第xxx号
        <a href="http://www.beian.gov.cn/portal/registerSystemInfo?spm=a2e15.8261149.1997523009.45.63d129b4mE53eY&recordcode=33010002000078">x公网安备 xxxxxxxxxxxxx号</a> |广播电视节目制作经营许可证（x）字第xxxxxxxx号|市场名称登记证：工商网市字xxxxxxxxxx号|
      </pre>
  </div>
</body>
</html>
<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_register.js"></script>
<script type="text/javascript" rel="script" src="j_navigate.js"></script>
<script type="text/javascript">
  var canvas = document.getElementById("myCanvas");
  var context = canvas.getContext("2d");
  context.strokeStyle = '#000';
  context.lineWidth = 1;
  context.moveTo(60,0);
  context.lineTo(60,150);
  context.stroke();
  context.save();
  var img = new Image();
  //img.src = "src/logo.jpg";
  img.onload = function(){
    context.restore();
    context.drawImage(img, 10, 190);
  }

</script>
