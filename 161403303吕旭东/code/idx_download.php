<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <link rel="stylesheet" type="text/css" href="c_download.css">
</head>
<body>
<?php
  include "index_head.php";
include "idx_register.php";
?>
  <div  id="tab-container">
    <section>
      <a href="#pc" class="nav" id="nav-pc">PC客户端</a>
      <a href="#pe" class="nav" id="nav-pe">移动客户端</a>

      <div id="tad-content">
        <article id="pc" class="p_content">
            <table border="1" cellpadding="0" cellspacing="0">
              <tr>
                <th align="left" width="50%"><a href="idx_down_confi.php?FileName=Win.txt">Win</a></th>
                <th align="right">V.1.0.0</th>
              </tr>
              <tr>
                <th align="left" width="50%"><a href="idx_down_confi.php?FileName=MacOS.txt">Mac OS</a></th>
                <th align="right">V.1.0.0</th>
              </tr>
            </table>
        </article>
        <article id="pe" class="p_content">
          <table border="1" cellpadding="0" cellspacing="0">
            <tr>
              <th align="left" width="50%"><a href="idx_down_confi.php?FileName=Android.txt">Android</a></th>
              <th align="right">V.1.0.0</th>
            </tr>
            <tr>
              <th align="left" width="50%"><a href="idx_down_confi.php?FileName=IOS.txt">IOS</a></th>
              <th align="right">V.1.0.0</th>
            </tr>
            <tr>
              <th align="left" width="50%"><a href="idx_down_confi.php?FileName=WinPhone.txt">Win Phone</a></th>
              <th align="right">V.1.0.0</th>
            </tr>
          </table>
        </article>
      </div>
    </section>
  </div>

  <div style="left: 90px;position: absolute">
    <p style="font-family: sans-serif"><a href="idx_configure.php" target="_blank">配置要求</a></p>
    <p style="font-family: sans-serif">对版本有疑问？-><a href="idx_serves.php" target="_blank">客服链接</a></p>
  </div>

  <div class="img">
    <img src="src/d1.png">
  </div>
</body>
</html>

<script type="text/javascript" rel="script" src="j_download.js"></script>
