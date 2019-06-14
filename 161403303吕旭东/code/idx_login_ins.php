<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<body>
<?php
$fname = $_COOKIE['fname'];
$lname = $_COOKIE['lname'];
$sex = $_COOKIE['sex'];
$email = $_COOKIE['email'];
$area = $_COOKIE['area'];
$phone = $_COOKIE['phone'];
$birthday = $_COOKIE['birthday'];
$pw1 = $_COOKIE['password'];

$email2 = $_COOKIE['email2'];
$area2 = $_COOKIE['area2'];
$phone2 = $_COOKIE['phone2'];
$question1 = $_COOKIE['question1'];
$answer1 = $_COOKIE['answer1'];
$question2 = $_COOKIE['question2'];
$answer2 = $_COOKIE['answer2'];
$question3 = $_COOKIE['question3'];
$answer3 = $_COOKIE['answer3'];

$address = $_COOKIE['address'];
$potalcode = $_COOKIE['potalcode'];
$pay = $_COOKIE['pay'];
$payid = $_COOKIE['payid'];
$paypwd = $_COOKIE['paypwd'];

include "iadx_connect.php";//把表单传入数据库

$selId = mysqli_query($mysqli,"SELECT CusId from zcode_customer where CusId = (SELECT MAX(CusId) from zcode_customer)");
$row = mysqli_fetch_array($selId);
$CusId = $row['CusId']+1;

$exec1 = "insert into zcode_customer(CusId,CusLName,CusFName,CusPwd,CusBirth,CusSex,CusArea,CusPhone,CusEmail,CusAds,CusEnt,potalcode,yanzhengma,Price) values ('$CusId','$fname','$lname','$pw1','$birthday','$sex','$area','$phone','$email','$address',NULL,'$potalcode',NULL,NULL )";
$exec2 = "insert into zcode_cus_safe(CusId,CuArea2,CuPhone2,CuEmail2,CusQus1,CusAws1,CusQus2,CusAws2,CusQus3,CusAws3) value ('$CusId','$area2','$phone2','$email2','$question1','$answer1','$question2','$answer2','$question3','$answer3')";
$exec3 = "insert into zcode_cus_pay(CusId,CusPmth,CusPId,CusPPwd) value ('$CusId','$pay','$payid','$paypwd')";

if(($mysqli->query($exec1))&&($mysqli->query($exec3))&&($mysqli->query($exec2))){
  echo "<script>alert('注册成功！');window.location='index_main.php';</script>";
}
else{
  echo "<script>alert('注册失败！');window.location='idx_login.php';</script>";
}
?>
</body>
</html>
