<table width="780" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC" >
  <tr>
    <td bgcolor="#FFFFFF"><img src="images/aa.jpg" width="780" height="150" /></td>
  </tr>
  <tr>
    <td bgcolor="#FFFFFF"><table width="780" height="30" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php" title="首页">首页</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php?proid=<?php echo urlencode('网页美工');?>" title="网页美工">网页美工</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php?proid=<?php echo urlencode('网络营销');?>" title="网络营销">网络营销</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php?proid=<?php echo urlencode('asp编程');?>" title="asp编程">asp编程</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php?proid=<?php echo urlencode('php编程');?>" title="php编程">php编程</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="index.php?proid=<?php echo urlencode('软件开发');?>" title="软件开发">软件开发</a></td>
        <td align="center" background="images/button1_bg.jpg"><a href="hh.php"  title="用户登陆">登陆</a>&nbsp;&nbsp;<?php 
		if ($_SESSION['id']){
			echo "<a href='landing.php?tj=out'  title='退出'>退出</a>";
		}
		?></td>
      </tr>
    </table></td>
  </tr>
</table>
