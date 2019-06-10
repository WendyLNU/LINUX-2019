<?php
include "iadx_connect.php";

  $email = $_POST['email'];
  $password = $_POST['password'];
  $result = mysqli_query($mysqli,"SELECT * FROM zcode_customer where CusEmail = '".$email."'");
  while($row = mysqli_fetch_array($result))
  {
      if($row['CusPwd']==$password)
      {$flags=1;}
  }
  if($flags)
  {
    session_start();
    $_SESSION["userway"] = 'zcode_customer';
    $_SESSION["username"] = $email;
    $_SESSION["id"] = $row['CusId'];
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
?>//登陆
