<?php
include("../config.php");
require_once('ly_check.php');
$sql="delete from yx_books where id=".$_GET[id];
$arry=$mysqli->query($sql,$conn);
if($arry){
echo "<script> alert('删除成功');location='list.php';</script>";
}
else
echo "删除失败";
?>
