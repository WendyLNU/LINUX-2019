<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
</head>
<style>
  @font-face {
    font-family: 'c3';
    src: url('src/c3.ttf');
  }
  @font-face {
    font-family: 'league';
    src: url('src/league Script.ttf');
  }
  .ser_main{
    width: 100%;
    height: 100%;
    position: relative;
    display: block;
  }
  .main_part{
    width: 200px;
    height: 440px;
    position: relative;
    display: block;
    border: 2px solid #000000;
    float: left;
    top:10px;
    left: 10%;
    margin: 10px 5%;
    text-align: center;
    padding-top: 100px;
    cursor: pointer;
    background: #a1a4cb;
  }
  .main_part:hover{background: #b3d4fc}
  .en_part{
    font-size: 27px;
    font-weight: bolder;
    font-family: league;
  }
  .ch_part{
    padding-top: 40px;
    margin: 0 auto;
    font-size: 45px;
    width: 45px;
    font-weight: bolder;
    font-family: c3;
  }
</style>
<body>
<?php
  include "index_head.php";
  include "idx_register.php";
?>
  <div class="ser_main">
    <div id="Advice" class="main_part"><p class="en_part">Advice</p><p class="ch_part">我有建议</p></div>
    <div id="Consultant" class="main_part"><p class="en_part">Consultant</p><p class="ch_part">我要咨询</p></div>
    <div id="Custom_tailor" class="main_part"><p class="en_part">Custom-tailor</p><p class="ch_part">我要定制</p></div>
    <div id="Feedback" class="main_part"><p class="en_part">Feedback</p><p class="ch_part">我要反馈</p></div>
  </div>
</body>
</html>
