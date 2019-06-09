<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<body>
<?php
$EntName = $_COOKIE['EntName'];
$EntNum = $_COOKIE['EntNum'];
$email = $_COOKIE['email'];
$area = $_COOKIE['area'];
$phone = $_COOKIE['phone'];
$pw1 = $_COOKIE['password'];

$address = $_COOKIE['address'];
$potalcode = $_COOKIE['potalcode'];
$pay = $_COOKIE['pay'];
$payid = $_COOKIE['payid'];
$paypwd = $_COOKIE['paypwd'];

include "iadx_connect.php";

$exec1 = "insert into zcode_enter(EntID,EntName,EntPwd,EntEmail,EntAds,potalcode,EntArea,EntPhone) values ('$EntNum','$EntName','$pw1','$email','$address','$potalcode','$area','$phone')";
$exec2 = "insert into zcode_ent_pay(EntID,EntPmth,EntPId,EntPPwd) values ('$EntNum','$pay','$payid','$paypwd')";

if(($mysqli->query($exec1))&&($mysqli->query($exec2))){
  echo "<script>alert('注册成功！');window.location='index_main.php';</script>";
}
else{
  echo "<script>alert('注册失败！');window.location='idx_login2.php</script>";
}
?>
</body>
</html>
