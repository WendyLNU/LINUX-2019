<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<style>
  .join_rul_m{
    width: 400px;
    height: 400px;
    position: relative;
    left: 50%;
    top: 100px;
    margin-left: -230px;
    text-align: center;
    line-height: 30px;
  }
  .join_rul_m h1{
    font-size: 40px;
  }
  .join_rul_m p{
    font-family: sans-serif;
    font-weight: bolder;
    font-size: 25px;
  }
  .join_rul_m a{
    font-family: sans-serif;
    font-weight: bolder;
    font-size: 15px;
    color: blue;
    text-decoration: none;
  }
</style>
<body>
<?php
  include "index_head.php";
    $j = $_POST['j'] ;
    $D = $_POST['A'];
    $email = $_POST['email'];
    if(!($sl1 = $_POST['sl1'])){$sl1 = 'sl1';}
    if(!($sl2 = $_POST['sl2'])){$sl1 = 'sl1';}
    if(!($sl3 = $_POST['sl3'])){$sl1 = 'sl1';}

    $selId = mysqli_query($mysqli, "SELECT ApplyId from zcode_apply where ApplyId = (SELECT MAX(ApplyId) from zcode_apply)");
    $row = mysqli_fetch_array($selId);
    $WorkId = $row['ApplyId'] + 1;
    $exec = "INSERT INTO zcode_apply(ApplyId,CusId,ApplyPos,ApplySalary,ApplyShape,DevelopId,Resume,workfile,CusWEmail,CusWAdd1,CusWAdd2,CusWAdd3) value('$WorkId',NULL,NULL,NULL,'$j','$D',NULL,NULL,'$email','$sl1','$sl2','$sl3')";

    if (!($mysqli->query($exec))) {
      echo "<script>alert('失败');window.location = 'idx_join_mess.php'</script>";
    }
?>
<div class="join_rul_m">
  <h1>感谢您关注搬码</h1><br>
  <p>如果我们对您也感兴趣<br>一段时间后会有人联系您</p><br>
  <a href="idx_personal.php">查看我的信息 ></a><br>
  <?php
    echo" <a href=\"idx_join_through.php?j=".$j."\">继续了解其他职位 ></a>";
  ?>
</div>
</body>
</html>
