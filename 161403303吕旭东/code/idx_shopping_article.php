<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" href="c_shopping_article.css">
  <link type="text/css" rel="stylesheet" href="c_bottom.css">
</head>
<body>
<?php
  include "index_head.php";
  $a = $_GET['a'];
  $result = mysqli_query($mysqli, "SELECT * FROM zcode_product,zcode_developer where zcode_product.PudDev = zcode_developer.DeveloperId and zcode_product.PudId = '".$a."'");
  $result1 = mysqli_query($mysqli, "SELECT * FROM zcode_customer where CusEmail = '".$_SESSION["username"]."'");
  $row = mysqli_fetch_array($result);
  $row1 = mysqli_fetch_array($result1);
  echo "
  <div class=\"sho_article_m\">
  <div class=\"sho_art_logo\">
    <img src='product_logo/".$row['PudPicture']."' width='300' height='330'>
  </div>
  <form action='#' method='post'>
    <p>商品名</p><input type=\"text\" name=\"price\" value=\"".$row['PudName']."\"><br>
    <p>价格</p><input type=\"text\" name=\"price\" value=\"".$row['PudPrice']."\">
    <p>收货地址</p><input type=\"text\" name=\"add\" value=\"".$row1['CusAds']."\">
    <p>销售形态</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <input type=\"submit\" name=\"submit1\" value=\"立即购买\" style=\"left:44%;top: -235px;\">
    <a href=\"idx_order_add.php?a=".$a."\" style=\"left: 75%;top: -265px;position: relative;background: rgba(0,0,0,.3);border: 1px solid black;display: block;width: 130px;height: 23px;display: block;border-radius: 2px;color: white;text-decoration: none;text-align: center;font-weight: bolder;padding-top: 7px\">加入购物车</a>
    <p>支付方式</p>
    <select name=\"pay\">
      <option value=\"预设方式\">预设方式</option>
      <option value=\"支付宝\">支付宝</option>
      <option value=\"微信\">微信</option>
      <option value=\"信用卡\">信用卡</option>
    </select>
    <p style=\"top: -270px\">服务承诺&nbsp售后服务&nbsp极速退款&nbsp用户协议</p>
  </form>

  <section id=\"logged\">
    <div id=\"log_head\">
      <a href=\"#pc\" class=\"nav\" id=\"nav-pc\">商品详情</a>
      <a href=\"#pe\" class=\"nav\" id=\"nav-pe\">累计评价</a>
    </div>
    <div id=\"tad-content\">
      <article id=\"pc\" class=\"p_content\">
        <p>商品名：".$row['PudName']."</p>
        <p>开发商：".$row['DevelopName']."</p>
        <p>适用系统：".$row['Pudconfiguer']."</p>
        <p>版本号：".$row['PudVersion']."</p>
        <p>商品分类：".$row['PudClass']."</p>
        <p>商品描述：".$row['PudAppraise']."</p>
      </article>
      <article id=\"pe\" class=\"p_content\">
      </article>
    </div>
  </section>

</div>
  ";
?>

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

<script type="text/javascript" src="j_download.js"></script>
