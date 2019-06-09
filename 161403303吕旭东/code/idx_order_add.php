<?php
include "index_head.php";
$a = $_GET['a'];
$selId = mysqli_query($mysqli,"SELECT OrderID from zcode_order where OrderID = (SELECT MAX(OrderID) from zcode_order)");
$row = mysqli_fetch_array($selId);
$OrderID = $row['OrderID']+1;
$CusId = $_SESSION['username'];
$selId1 = mysqli_query($mysqli,"SELECT CusId from zcode_customer where CusId = '".$CusId."' ");
$row1 = mysqli_fetch_array($selId1);
$CusId = $row['CusId'];
$exec = "insert into zcode_order(OrderID,CusId,ProductID,beta,feedback,Ordshape) value ('$OrderID','$CusId','$a',null,null,0)";
if($mysqli->query($exec)){
  echo "<script>alert('添加成功');window.location='index_main.php';</script>";
}
?>
