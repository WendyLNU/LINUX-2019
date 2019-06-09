<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" href="c_shopping_cart.css">
</head>
<body>
<?php
include "index_head.php";
include "idx_register.php";
include "iadx_connect.php";
if (isset($_SESSION["username"])){
?>
<div class="shopping_left">
  <img src="src/sho1.png" width="350" height="500">
</div>
<div class="shopping_main">
  <h1>查看你的购物车</h1>
  <p>购物清单</p>
  <p>- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -</p>
  <p>购买</p>
  <form action="idx_shopping_rul.php" method="post">
  <table>
  <?php
  $result = mysqli_query($mysqli, "SELECT * FROM (zcode_customer left join zcode_order on zcode_customer.CusId = zcode_order.CusId) left join zcode_product on zcode_order.ProductID = zcode_product.PudId where zcode_order.Ordshape = 0 and CusEmail = '".$_SESSION["username"]."'");
  while($row = mysqli_fetch_array($result)) {
    if ($row['PudShape'] == 1) {
      echo "
          <tr>
            <td><input type='checkbox' name='test[]' value='".$row['PudId']."'></td>
            <td class=\"sel_1\"><a target='_blank' href='idx_shopping_article.php?a=".$row['PudId']."'>" . $row['PudName'] . "</a></td>
            <td>￥</td>
            <td align='right'>" . $row['PudPrice'] ."</td>
          </tr>
        ";
    }
  }
  ?>
  </table>
  <p>- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -</p>
  <p>订阅</p>
  <table>
   <?php
   $result1 = mysqli_query($mysqli, "SELECT * FROM (zcode_customer left join zcode_order on zcode_customer.CusId = zcode_order.CusId) left join zcode_product on zcode_order.ProductID = zcode_product.PudId where zcode_order.Ordshape = 0 and CusEmail = '".$_SESSION["username"]."'");
   while($row1 = mysqli_fetch_array($result1)) {
      if ($row1['PudShape'] == 0) {
        echo " 
          <tr>
            <td><input type='checkbox'  name='test[]' value='".$row1['PudId']." '></td>
            <td class=\"sel_1\"><a target='_blank' href='idx_shopping_article.php?a=".$row1['PudId']."'>" . $row1['PudName'] . "</a></td>
            <td>￥</td>
            <td>" . $row1['PudPrice'] . "/月</td>
          </tr>
         ";
      }
   }
   ?>
  </table>
    <br><br>
    <p>= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =</p>
    <p>FeedBack计划</p><br>
    <input type="radio" name="radio1" value="0"><p class="sel_2">不参与任何计划</p>
    <input type="radio" name="radio1" value="1"><p class="sel_2">参与Feedback计划</p>
    <input type="radio" name="radio1" value="2"><p class="sel_2">参与Beta计划</p>
    <input type="radio" name="radio1" value="3"><p class="sel_2">参与Feedback Bate计划</p>
    <br>
    <p>= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =</p>
    <p>支付方式</p>
    <input type="radio" name="radio2" value="sub"><p class="sel_2">预设方式</p>
    <input type="radio" name="radio2" value="other"><p class="sel_2">其他</p>
    <select name="select">
      <option value="支付宝">支付宝</option>
      <option value="微信">微信</option>
      <option value="银行卡">银行卡</option>
      <option value="银联">银联</option>
      <option value="信用卡">信用卡</option>
    </select>
    <input type="submit" class="button" value="立即购买">
  </form>
  <div style="height: 200px"></div>
   <?php
}
  else{
    echo "<script>alert('未登录！点击确定返回');window.location='index_main.php';</script>";
  }
  ?>
</div>
</body>
</html>
