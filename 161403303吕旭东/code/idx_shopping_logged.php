<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link type="text/css" rel="stylesheet" href="c_bottom.css">
</head>
<style>
  a{
    color: #a016ff;
    text-decoration: none;
  }
  #logged{
    width: 90%;
    height: 500px;
    display: block;
    top: 50px;
    left: 50px;
    position: relative;
    overflow-y: auto;
    overflow-x: hidden;
    min-width: 500px;
  }
  #logged #log_head{
    width: 100%;
    height: 42px;
    position: relative;
    box-shadow: 2px 2px 2px 2px #999999 inset;
  }
  #logged .nav{
    width: 90px;
    height: 22px;
    padding: 10px;
    margin-right: 3px;
    position: relative;
    display: block;
    cursor: pointer;
    float: left;
    text-decoration: none;
    text-align: center;
    box-shadow: 2px 2px 2px 2px #999999 inset;
    color: black;
    opacity: .7;
  }
  #logged #nav-pc{
    background: #a967f0;
    color: white;
  }
 .log_part{
   width: 100%;
   height: 60px;
   padding: 5px 0 5px 10px;
   background: linear-gradient(#f4f4f4,#e6e6e6);
   border-radius: 5px;
   cursor: pointer;
   margin-bottom: 10px;
   border: 1px solid rgba(0,0,0,.4);
  }
 .log_part:hover{
   background: linear-gradient(white,#f4f4f4);
 }
  .log_part p{
    position: relative;
    display: block;
    width: 100px;
    margin-right: 10%;
    float: left;
    font-family: sans-serif;
    font-size: 18px;
  }
</style>
<body>
<?php
  include "index_head.php";

  $result = mysqli_query($mysqli,"SELECT * FROM zcode_customer where CusEmail = '".$_SESSION["username"]."'");
  $row = mysqli_fetch_array($result);
?>
<section id="logged">
  <h1>订单一览：</h1><br>
  <div id="log_head">
    <a href="#pc" class="nav" id="nav-pc">已购买</a>
    <a href="#pe" class="nav" id="nav-pe">已订阅</a>
  </div>
  <div id="tad-content">
    <article id="pc" class="p_content">
      <?php
        $r1 = mysqli_query($mysqli,"SELECT * FROM zcode_shopping,zcode_product where zcode_shopping.PudID = zcode_product.PudId and zcode_shopping.CusId = '".$row['CusId']."'");
        while ($row1 = mysqli_fetch_array($r1)){
        echo "
          <div class=\"log_part\">
            <p>商品名：<br><a href='idx_shopping_article.php?a=".$row1['PudId']."' target='_blank'>".$row1['PudName']."</a></p>
            <p>商品类型：<br>".$row1['PudClass']."</p>
            <p>价格：<br>".$row1['PudPrice']."</p>
            <p>购买时间：<br>".$row1['SubDate']."</p>
          </div>
        ";}
      ?>
    </article>
    <article id="pe" class="p_content">
      <?php
      $r2 = mysqli_query($mysqli,"SELECT * FROM zcode_Subscribe,zcode_product where zcode_Subscribe.ProductID = zcode_product.PudId and zcode_Subscribe.CusId = '".$row['CusId']."'");
      while ($row2 = mysqli_fetch_array($r2)){
      echo "
          <div class=\"log_part\">
            <p>商品名：<br><a href='idx_shopping_article.php?a=".$row2['PudId']."' target='_blank'>".$row2['PudName']."</a></p>
            <p>商品类型：<br>".$row2['PudClass']."</p>
            <p>价格：<br>".$row2['PudPrice']."/月</p>
            <p>订阅时间：<br>".$row2['SubDate']."</p>
          </div>
        ";}
      ?>
    </article>
  </div>
</section>

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
