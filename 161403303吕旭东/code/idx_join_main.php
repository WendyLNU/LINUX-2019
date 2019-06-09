<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<?php
  include "index_head.php";
  include "idx_register.php";
?>
<style>
  .join_main{
    left: 50%;
    margin: -450px;
    width: 900px;
    height: 500px;
    overflow-x: hidden;
  }
  .jo_part1,.jo_part2{
    width: 380px;
    height: 350px;
    border: 2px solid #000;
    position: absolute;
    display: block;
    background: white;
  }
  .jo_part1{
    left: 250px;
    top: 220px;
  }
  .jo_part2{
    left: 680px;
    top: 90px;
  }
  .join_main h1{
    font-family: sans-serif;
    font-weight: bolder;
    font-size: 40px;
    text-align: center;
    position: relative;
  }
  .jo_part1 h1{top: -60px;}
  .jo_part2 h1{top: 360px;}
  .join_main p{
    text-align: center;
    font-family: sans-serif;
    font-size: 25px;
    position: relative;
    top: -20px;
    line-height: 35px;
  }
  .jo_part1 a,.jo_part2 a{
    position: relative;
    left: 140px;
    bottom: -75px;
    text-align: center;
    text-decoration: none;
    color: black;
    font-family: sans-serif;
    font-size: 17px;
    cursor: pointer;
    line-height: 30px;
  }
  .jo_part1 a:hover,.jo_part2 a:hover{
    color: #464aff;
  }
</style>
<body>
  <div class="join_main">
    <div class="jo_part1">
      <h1>全职工作</h1>
      <p>在这里<br>你将与满怀激情的同事一起<br>创造独一无二的搬码世界</p>
      <a href="idx_join_through.php?j=1">工作浏览 ></a><br>
      <a>工作环境 ></a><br>
      <a>搬码价值观 ></a><br>
    </div>
    <p style="position: absolute;top: 300px;left: 635px;font-size: 40px;font-weight: bolder">or</p>
    <div class="jo_part2">
      <h1>兼职工作</h1>
      <p>即使在家中<br>也可以完成搬码的兼职工作</p><br><br>
      <a href="idx_join_through.php?j=2">工作浏览 ></a><br>
      <a>工作环境 ></a><br>
      <a>搬码价值观 ></a><br>
    </div>
  </div>
</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript" src="j_register.js"></script>
