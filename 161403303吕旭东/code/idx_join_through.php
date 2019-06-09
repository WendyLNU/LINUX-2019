<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" href="c_join_through.css">
</head>
<body>
<?php
  include "index_head.php";

  $j = $_GET['j'];
  setcookie('j',$j)
?>
<div class="thr_m">
    <form action="idx_join_confirm.php" method="post">
      <p>工作方式</p>
      <select name="meth">
        <option value="0">全职</option>
        <option value="1">兼职</option>
      </select>
      <p>工作地点</p>
      <select name="add">
        <option value="null">未填写</option>
        <option value='上海'>上海</option>
        <option value='北京'>北京</option>
        <option value='武汉'>武汉</option>
        <option value='大连'>大连</option>
        <option value='广州'>广州</option>
        <option value='杭州'>杭州</option>
      </select>
    </form>
  <div id="slideshow">
    <ul>
      <li>
        <div>
          <p>CoreOS 开发<br>2019年1月1日</p>
          <p>上海<br></p>
          <?php
           echo "<a href=\"idx_join_mess.php?D=1\">申请 ></a>";
          ?>
        </div>
        <p>工作介绍：<br>搬码CoreOS开发团队正在寻找一群软件工程师来帮助开发和排除故障，需要熟练使用C/C++/C#等开发</p>
      </li>
      <li><div></div></li>
      <li><div></div></li>
      <li><div></div></li>
    </ul>
    <div id="slideshow-nav"></div>
  </div>
</div>
</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_slideshow.js"></script>
