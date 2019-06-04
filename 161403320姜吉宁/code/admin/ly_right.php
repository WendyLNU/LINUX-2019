<?php
//require_once('config.php');
require_once('ly_check.php');
 ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>夏日读书</title>
<style type="text/css">
<!--
body {
	margin-left: 3px;
	margin-top: 0px;
	margin-right: 3px;
	margin-bottom: 0px;
}
.STYLE1 {
	color: #e1e2e3;
	font-size: 12px;
}
.STYLE6 {color: #000000; font-size: 12; }
.STYLE10 {color: #000000; font-size: 12px; }
.STYLE19 {
	color: #344b50;
	font-size: 12px;
}
.STYLE21 {
	font-size: 12px;
	color: #3b6375;
}
.STYLE22 {
	font-size: 12px;
	color: #295568;
}
a:link { font-size: 9pt; color: #344b50; text-decoration: none} 
a:visited { font-size: 9pt; color: #344b50; text-decoration: none} 
a:hover { font-size: 9pt; color: #344b50; text-decoration: none} 
a:active { font-size: 9pt; color: #344b50; text-decoration: none} 
-->
</style>
</head>
<?php
date_default_timezone_set("Etc/GMT-8");
?>
<body>
<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="30"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="24" bgcolor="#353c44"><table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="6%" height="19" valign="bottom"><div align="center"><img src="images/tb.gif" width="14" height="14" /></div></td>
                <td width="94%" valign="bottom"><span class="STYLE1">parameter about server</span></td>
              </tr>
            </table></td>
            <td><div align="right"><span class="STYLE1">&nbsp;</span><span class="STYLE1"> &nbsp;</span></div></td>
          </tr>
        </table></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td><table width="100%" border="0" cellpadding="0" cellspacing="1" bgcolor="#a8c7ce">
      
      <tr>
        <td height="20" colspan="2" align="center" bgcolor="#FFFFFF" class="STYLE6"><div align="center"><span class="STYLE19">software version</span></div></td>
        <td height="20" align="center" bgcolor="#FFFFFF" class="STYLE19"><!--删除后将无法获得最新版本--><script type="text/javascript" src="http://www.04ie.com/net/phpbook0_3.js"></script></td>
      </tr>
      <tr>
        <td width="23%" height="20" align="left" bgcolor="#FFFFFF" class="STYLE6"><div align="center"><span class="STYLE19">php version</span></div></td>
        <td width="77%" height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo "PHP".PHP_VERSION; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">MYSQL version</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo("5.7.11-0ubuntu6"); ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">server name:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo $_SERVER['SERVER_NAME']; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">server IP:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo $_SERVER["HTTP_HOST"]; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">server interface:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo $_SERVER["SERVER_PORT"]; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">server time:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo $showtime=date("Y-m-d H:i:s");?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">server operate system:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo PHP_OS; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">station physics path:</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><?php echo $_SERVER["DOCUMENT_ROOT"]; ?></div></td>
        </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">admin</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center">system administor</div></td>
      </tr>
      <tr>
        <td height="20" align="left" bgcolor="#FFFFFF" class="STYLE19"><div align="center">help online</div></td>
        <td height="20" bgcolor="#FFFFFF" class="STYLE19"><div align="center"><a href="http://www.04ie.com/codes/700.html" target="_blank">see help file</a></div></td>
      </tr>
    </table></td>
  </tr>
</table>
</body>
</html>
