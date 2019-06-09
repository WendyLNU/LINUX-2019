<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="c_personal.css">
  <script type="text/javascript" rel="script" src="j_personal.js"></script>
</head>
<body>
<?php
include "index_head.php";
include "iadx_connect.php";
//  判断是否登陆
if (isset($_SESSION["username"])){
  if($_SESSION["userway"] == 'zcode_customer') {
    $result = mysqli_query($mysqli,"SELECT * FROM (zcode_customer left join zcode_cus_safe on zcode_customer.CusId = zcode_cus_safe.CusId) left join zcode_cus_pay on zcode_customer.CusId = zcode_cus_pay.CusId where CusEmail = '".$_SESSION["username"]."'");
    $row = mysqli_fetch_array($result);
    echo "
    <div id=\"personal_left\">
    <a id=\"personal_v_per\" class=\"personal_v\">个人资料</a>
    <a id=\"personal_v_pay\" class=\"personal_v\">支付信息</a>
    <a id=\"personal_v_safe\" class=\"personal_v\">账户安全</a>
    <a id=\"personal_v_job\" class=\"personal_v\">商户信息</a>
  </div>

    <div id=\"personal_per\" class=\"personal_m\">
      <p>姓名： ".$row['CusLName'].$row['CusFName']."</p>
      <p>性别： ".$row['CusSex']."</p>
      <p>生日： ".$row['CusBirth']."</p>
      <p>邮箱： ".$row['CusEmail']."</p>
      <p>手机号：".$row['CusPhone']."</p>
      <p>账号余额：".$row['Price']."&nbsp<a style='font-size: 15px;text-decoration: none;color: #464aff;cursor: pointer'>提现</a></p>
    </div>
    <div id=\"personal_pay\" class=\"personal_m\">
      <p>支付方式：".$row['CusPmth']."</p>
      <p>支付账号：".$row['CusPId']."</p>
      <p>收件地址：  ".$row['CusAds']."</p>
      <p>联系方式（收件）：".$row['CusPhone']."</p>
      <p>邮政编码：".$row['potalcode']."</p>
    </div>
    <div id=\"personal_safe\" class=\"personal_m\">
      <p>备用邮箱： ".$row['CuEmail2']."</p>
      <p>备用手机号： ".$row['CuPhone2']."</p>
      <a href=\"#\" id=\"password_revise\" class=\"per_safe_divs\"><img src=\"src/pwd1.png\"><div class=\"per_safe_divs_t\">修改密码</div></a>
      <a href=\"#\" id=\"position_revise\" class=\"per_safe_divs\"><img src=\"src/qus1.png\"><div class=\"per_safe_divs_t\">安全问题</div></a>
      <a href=\"#\" id=\"email_revise\" class=\"per_safe_divs\"><img src=\"src/eml1.png\"><div class=\"per_safe_divs_t\">修改邮箱</div></a>
      <a href=\"#\" id=\"phone_revise\" class=\"per_safe_divs\"><img src=\"src/pho1.png\"><div class=\"per_safe_divs_t\">修改手机</div></a>
    </div>
    <div id=\"personal_job\" class=\"personal_m\">";
    $result1 = mysqli_query($mysqli,"SELECT * FROM zcode_work where CusId = '".$row['CusId']."' ");
    $result2 = mysqli_query($mysqli,"SELECT * FROM zcode_apply where CusId = '".$row['CusId']."' ");
    if($result1||$result2) {
      while ($row1 = mysqli_fetch_array($result1)) {
        $result3 = mysqli_query($mysqli, "SELECT * FROM zcode_developer where DeveloperId = '" . $row1['DevelopId'] . "' ");
        $row3 = mysqli_fetch_array($result3);
        echo "
        <p>商户信息：</p>
        <p>商户名：" . $row3['DevelopName'] . "</p>
        <p>商户ID： " . $row3['DeveloperId'] . "</p>
        <p>用户职位： " . $row1['WorkPos'] . "</p><br>
        <p><a href='idx_shopping_add.php' target='_blank'>上传商品</a></p>
         ";
      }
      while ($row2 = mysqli_fetch_array($result2)) {
        $result3 = mysqli_query($mysqli, "SELECT * FROM zcode_developer where DeveloperId = '" . $row1['DevelopId'] . "' ");
        $row3 = mysqli_fetch_array($result3);
        echo "
        <p>申请信息</p>
        <p>商户名：" . $row3['DevelopName'] . "</p>
        <p>商户ID： " . $row3['DeveloperId'] . "</p>
        <p>申请职位： " . $row1['WorkPos'] . "</p><br>
        <p><a href='idx_shopping_add.php' target='_blank'>撤销申请</a></p>
         ";
      }
    }
    else{
        echo "无";
     }
     echo "</div>";
    }
  }
  elseif ($_SESSION["userway"] == 'zcode_enter'){
    $result = mysqli_query($mysqli,"SELECT * FROM zcode_enter,zcode_ent_pay where zcode_enter.EntID = zcode_ent_pay.EntID and zcode_enter.EntID = '".$_SESSION["username"]."'");
    $row = mysqli_fetch_array($result);
    echo "
    <div id=\"personal_left\">
    <a id=\"personal_v_per\" class=\"personal_v\">企业资料</a>
    <a id=\"personal_v_pay\" class=\"personal_v\">支付信息</a>
    <a id=\"personal_v_safe\" class=\"personal_v\">账户安全</a>
    <a id=\"personal_v_job\" class=\"personal_v\">商户信息</a>
  </div>

  <div id=\"personal_main\">
    <div id=\"personal_per\" class=\"personal_m\">
      <p>企业名： ".$row['EntName']."</p>
      <p>企业编号： ".$row['EntID']."</p>
      <p>企业邮箱： ".$row['EntEmail']."</p>
      <p>企业电话：".$row['EntPhone']."</p>
    </div>
    <div id=\"personal_pay\" class=\"personal_m\">
      <p>支付方式：".$row['EntPmth']."</p>
      <p>支付账号：".$row['EntPId']."</p>
      <p>收件地址：  ".$row['EntAds']."</p>
      <p>联系方式（收件）：".$row['EntPhone']."</p>
      <p>邮政编码：".$row['potalcode']."</p>
    </div>
    <div id=\"personal_safe\" class=\"personal_m\">
      <a href=\"#\" id=\"password_revise\" class=\"per_safe_divs\"><img src=\"src/pwd1.png\"><div class=\"per_safe_divs_t\">修改密码</div></a>
      <a href=\"#\" id=\"position_revise\" class=\"per_safe_divs\"><img src=\"src/qus1.png\"><div class=\"per_safe_divs_t\">安全问题</div></a>
      <a href=\"#\" id=\"email_revise\" class=\"per_safe_divs\"><img src=\"src/eml1.png\"><div class=\"per_safe_divs_t\">修改邮箱</div></a>
      <a href=\"#\" id=\"phone_revise\" class=\"per_safe_divs\"><img src=\"src/pho1.png\"><div class=\"per_safe_divs_t\">修改手机</div></a>
    </div>
    <div id=\"personal_job\" class=\"personal_m\">
    </div>
  </div>";
  }

?>

</body>
</html>
<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" rel="script" src="j_personal.js"></script>
