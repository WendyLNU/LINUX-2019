<?php
include "iadx_connect.php";

  $name = $_POST['name2'];
  $password = $_POST['password2'];
  $result = mysqli_query($mysqli,"SELECT * FROM zcode_enter where EntID = '".$name."'");
  while($row = mysqli_fetch_array($result))
  {
      if($row['EntPwd']==$password)
      {$flags=1;}
  }
  if($flags)
  {
    session_start();
    $_SESSION["userway"] = 'zcode_enter';
    $_SESSION["username"] = $name;
    $_SESSION["uid"] = $name;
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
