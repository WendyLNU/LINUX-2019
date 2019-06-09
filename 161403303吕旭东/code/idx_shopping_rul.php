<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<style>
  body{
    overflow-x: hidden;
  }
  .sho_m{
    width: 100%;
    height: 100%;
    display: block;
  }
  .sho_m h1{
    text-align: center;
    display: block;
    margin: 10px;
  }
  .receipt{
    width: 350px;
    height: 500px;
    position: fixed;
    left: 80px;
    top: 80px;
    border: 1px solid #000000;
    background: white;
    overflow-x: hidden;
    overflow-y: scroll;
  }
  .sho_m p{
    position: relative;
    left: 500px;
    top: 50px;
    font-size: 25px;
    font-weight: bolder;
  }
  .sho_m a{
    position: relative;
    left: 500px;
    top: 50px;
    color: #0007e4;
    cursor: pointer;
    text-decoration: none;
    font-size: 15px;
  }
  .sho_m a:hover{
    color: #8fa6cb;
  }
  .sho_m .receipt p{
    font-size: 15px;
    font-weight: initial;
    font-family: sans-serif;
    position: relative;
    left: 20px;
  }
</style>
<?php
    include "index_head.php";
?>
<body>
<div class="sho_m">
  <h1>您已成功购买</h1>
  <div class="receipt">
    <p>购买详情：</p><br>
<?php
    if($test = $_POST['test']){
      if(!($radio1 = $_POST['radio1'])){$radio1 = '0';};
      if(!($radio2 = $_POST['radio2'])){$radio2 = 'null';};
      if(!($select = $_POST['select'])){$select = 'select';};
      $add = 0;
      $selId = mysqli_query($mysqli,"SELECT shoppingID from zcode_shopping where shoppingID = (SELECT MAX(shoppingID) from zcode_shopping)");
      if(!($sel = mysqli_fetch_array($selId))){$sel['shoppingID'] = 0;}
      $shoppingID = $sel['shoppingID']+1;
      $vlu = $sel['shoppingID'];
      $arr = date('Y-m-d H:i:s',time());
      for ($i=0;$test[$i];$i++) {
        $result = mysqli_query($mysqli, "SELECT * FROM (zcode_customer left join zcode_order on zcode_customer.CusId = zcode_order.CusId) left join zcode_product on zcode_order.ProductID = zcode_product.PudId where PudId = '".$test[$i]."'");
        $row = mysqli_fetch_array($result);
        $CusId = $row['CusId'];
        $PudId = $row['PudId'];
        $Cusemail = $row['CusEmail'];
        $vlu = $vlu + 1;
        if($row['PudShape'] == 1) {
          $exec = "insert into zcode_shopping(shovlu,shoppingID,CusId,PudID,CusEmail,SubDate) value ('$vlu','$shoppingID','$CusId','$PudId','$Cusemail','$arr')";
          $upt = "update zcode_order set Ordshape = 1 where ProductID = '".$test[$i]."'";
          if(!($mysqli->query($exec))||!($mysqli->query($upt))){
            echo "<script>alert('失败1')</script>";
          }
          else {
            echo "
        <p>" . $row['PudName'] . "(购买)  - - - - - - - ￥" . $row['PudPrice'] . "</p><br>
        ";
            $add = $add + $row['PudPrice'];
          }
        }
        if($row['PudShape'] == 0) {
          $exec2 = "insert into zcode_subscribe(subvlu,SubscribeID,CusID,ProductID,SubDate,Subshape,beta,feedback) value ('$vlu','$shoppingID','$CusId','$PudId','$arr','1','NULL','NULL')";
          $upt = "update zcode_order set Ordshape = 1 where ProductID = '".$test[$i]."'";
          if(!($mysqli->query($exec2))||!($mysqli->query($upt))){
            echo "<script>alert('失败2')</script>";
          }
          else {
            echo "
        <p>" . $row['PudName'] . "(订阅)  - - - - - - - ￥" . $row['PudPrice'] . "</p><br>
        ";
            $add = $add + $row['PudPrice'];
          }
        }

      }
      echo "<br><p>合计： ".$add."</p><br>";
      switch ($radio1){
        case 0:echo "<p>未参与任何计划</p>";break;
        case 1:echo "<p>参与Feedback计划</p>";break;
        case 2:echo "<p>参与Beta计划</p>";break;
        case 3:echo "<p>参与Feedback Beta计划</p>";break;
      }
      echo "<br><p>".gmdate('Y-m-d H:i:s',strtotime($arr))."</p>";
    }
    else{
      echo "<script>alert('啥也没选你买个球！');window.location='idx_shopping_cart.php';</script>";
    }
    ?>
  </div>
  <p>您可以在搬码app上下载这些软件</p>
  <a>->立即前往</a><br><br><br><br>
  <p>还没有搬码app?</p>
  <a href="idx_download.php" target="_blank">->现在下载</a><br><br><br><br>
  <p>您的电子收据已发送至您的email</p>
  <a>->开具电子发票</a><br>
  <a>->开具实体发票</a>
</div>
</body>
</html>
