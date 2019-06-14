<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link type="text/css" rel="stylesheet" href="c_header.css">
</head>
<body>
    <div class="header">
      <form action="idx_search.php" name="search" method="post">
        <label class="search">
          <input id="aa" type="text" value="" name="search"/>
          <input id="ab" value="搜索" type="submit" name="se"/>
        </label>
      </form>
    </div>

      <a href="index_main.php" style="position: absolute;left: 50%;margin-left: -10px;top: 0;color: white;display: block;height:35px;z-index: 10;text-decoration: none;font-size: 20px;padding: 8px">Zcode.com</a>

    <div id="dh" >
      <ul>
        <li><p>汉</p>
          <ul>
            <li><a href="#">中文</a></li>
            <li><a href="#">English</a></li>
          </ul>
        </li>
        <li><p>Z</p>
          <ul>
            <li><a href="#">新闻</a></li>
            <li><a href="idx_join_main.php" target="_blank">加入我们</a></li>
            <li><a href="#">关于我们</a></li>
          </ul>
        </li>
        <li><p>L</p>
          <ul>
            <li><a href="idx_login.php" style="border-bottom: 1px solid white" target="_blank">注册</a></li>
            <?php
            error_reporting(E_ALL^E_NOTICE^E_WARNING);
            include "iadx_connect.php";
            session_start();//  判断是否登陆
            if (isset($_SESSION["username"])){
              if($_SESSION["userway"] == 'zcode_customer') {
                $result = mysqli_query($mysqli,"SELECT * FROM zcode_customer where CusEmail = '".$_SESSION["username"]."'");
                $row = mysqli_fetch_array($result);
                echo "
                <li><a >" . $row['CusLName'] . $row['CusFName'] . "</a></li>
                <li><a href=\"iadx_output.php\">注销</a></li>
                <li><a href=\"idx_personal.php\" target='_blank'>个人信息</a></li>
                <li><a href=\"idx_shopping_cart.php\" target='_blank'>购物车</a></li>
                <li><a href=\"idx_shopping_logged.php\" target='_blank'>我的订单</a></li>";
              }
              elseif ($_SESSION["userway"] == 'zcode_enter'){
                $result = mysqli_query($mysqli,"SELECT * FROM zcode_enter where EntID = '".$_SESSION["username"]."'");
                $row = mysqli_fetch_array($result);
                echo "
                <li><a >" . $row['EntName'] ."</a></li>
                <li><a href=\"iadx_output.php\">注销</a></li>
                <li><a href=\"idx_personal.php\">企业信息</a></li>
                <li><a href=\"#\">购物车</a></li>
                <li><a href=\"#\">订单</a></li>";
              }
            }
            else{
              echo"<li><a class=\"head_Register\">登录</a></li>";
            }
            ?>
          </ul>
        </li>
      </ul>
    </div>
</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_register.js"></script>
