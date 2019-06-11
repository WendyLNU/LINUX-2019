<?php
include "iadx_connect.php";

  $phone = $_POST['phone'];
  $password = $_POST['number'];
  $result = mysqli_query($mysqli,"SELECT * FROM zcode_customer where CusPhone = '".$phone."'");
  while($row = mysqli_fetch_array($result))
  {
      if($row['Yanzhengma']==$password)
      {$flags=1;}
  }
  if($flags)
  {
    session_start();
    $_SESSION["username"] = $row['CusEmail'];
    $_SESSION["uid"] = $row['CusId'];
    $lifeTime = 24 * 3600;
    setcookie(session_name(), session_id(), time() + $lifeTime, "/");
      echo "<script>alert('登陆成功! ');window.location='index_main.php';</script>";
  }
  else
  {
      echo "<script>alert('密码或账号错误! ');window.location='index_main.php';</script>";
  }
  //关闭数据库链接
  mysqli_close($mysqli);
?>
