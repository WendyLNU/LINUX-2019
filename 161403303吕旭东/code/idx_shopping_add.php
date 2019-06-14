<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>

</head>
<style>
  .sho_article_m{
    width: 85%;
    position: relative;
    left: 50%;
    margin-left: -45%;
    top: 50px;
    overflow-x: hidden;
  }
  .sho_art_logo{
    width: 300px;
    height: 350px;
    border: 1px solid #000;
    left: 80px;
    position: relative;
  }
  .sho_article_m p{
    position: relative;
    left: 50%;
    top: -345px;
    font-family: sans-serif;
    font-size: 14px;
    opacity: .4;
  }
  .sho_article_m input,.sho_article_m select,.sho_article_m textarea{
    position: relative;
    font-size: 20px;
    left: 58%;
    top: -368px;
    border: 0 0 1 0;
    background: rgba(0,0,0,0);
  }
</style>
<body>
<?php
include "index_head.php";

echo "
  <div class=\"sho_article_m\">
  <div class=\"sho_art_logo\">

  </div>
  
  <form>
    <p>商品名：</p><input type=\"text\" name=\"name\" value=\"".$row['PudPrice']."\"><br>
    <p>价格：</p><input type=\"text\" name=\"price\" value=\"".$row['PudPrice']."\">
    <p>销售形态：</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>商品名：".$row['PudName']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>开发商：".$row['DevelopName']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>适用系统：".$row['Pudconfiguer']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>版本号：".$row['PudVersion']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>商品分类：".$row['PudClass']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>商品描述：".$row['PudAppraise']."</p><input type=\"text\" name=\"class\" value=\"".$row['PudShape']."\">
    <p>详细介绍：</p><textarea name='specifier' rows='5' cols='40'></textarea><br>
    <input type='file' style='left: 70px;top: -520px;'>
    <input type='submit'>
  </form>

</div>
  ";
?>
</body>
</html>

<script type="text/javascript" src="j_download.js"></script>
