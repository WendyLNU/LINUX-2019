<?php include "inc/conn.php";?><?php include "inc/excel.php";?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="viewport" content="width=device-width,minimum-scale=1.0,maximum-scale=1.0"/>
<meta name="apple-mobile-web-app-capable" content="yes" />
<title><?php echo $title;?></title>
<meta property="qc:admins" content="2c9a085366c30b3b0b61af9f57cf8915" />
<meta name="baidu-site-verification" content="533066cc044c77518994dc7d3a0d7279" />
<meta property="qc:admins" content="2c9a085366c30b3b0b61af9f57cf8915" />
<meta name="baidu-site-verification" content="533066cc044c77518994dc7d3a0d7279" />
<meta name="author" content="yujianyue, admin@ewuyi.net">
<meta name="copyright" content="www.12391.net">
<script type="text/javascript" src="inc/js/ajax_wap.js"></script>
<link href="inc/css/wap.css" rel="stylesheet" type="text/css" />
<body onLoad="inst();">
<div class="sub_bod"></div>
<div class="sub_top">
	<div class="title"><?php echo $title;?></div>
	<!---<div class="back" id="pageback"><a href="?b=back" class="d">返回</a></div> ---> 
	<!---<div class="menu" id="topmenus"><a href="http://test.96448.cn" class="d">推荐信息</a></div>--->
</div><div class="main">
<?php 

/**
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d======================================================================
' * 版权所有 (C) XueLiKai.Com，并保留所有权利。
' * 官方网址: http://Www.dbcha.com （请保留版权信息）
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * $Author: yujianyue <admin@ewuyi.net> $
' * $LastEdit: 2016-09-24 $
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * 代码不加密；你可以二次开发以便更适合你的需求 ，但不得：公开发布、公开销售。
' * 代码无域名、时间限制，非常通用；你可以安装多份，单位主体请购买本软件。
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d:index.php=============================================================
*/

$stime=microtime(true); 
$codes = trim($_POST['code']);
$shujus = trim($_POST['time']);
$shuru1 = trim($_POST['name']);
if(!$shujus){
?>
<form name="queryForm" method="post" class="" action="?t=<?php echo time();?>" onsubmit="return startRequest(0);">
<div class="select" id="10">
<select name="time" id="time" onBlur="startRequest(1)" />
<?php traverse($UpDir."/");?></select>
</div>
<div class="so_box" id="11">
<input name="name" type="text" class="txts" id="name" value="" placeholder="请输入<?php echo $tiaojian1;?>" onfocus="st('name',1)" onBlur="startRequest(2)" />
</div>
<?php 
if($ismas=="1"){
?>
<div class="so_box" id="33">
<input name="code" type="text" class="txts" id="code" placeholder="请输入验证码" onfocus="this.value=''" onBlur="startRequest(3)" />
<div class="more" id="clearkey">
<img src="inc/code.php?t=<?php echo date("Y-m-d-H-i-s",time());?>" id="Codes" onClick="this.src='inc/code.php?t='+new Date();"/>
</div></div>
<?php }?><div class="so_boxes">
<input type="submit" name="button" class="buts" id="sub" value="立即查询" />
</div>
<div class="so_boxex" id="tishi">说明:【<?php echo $tiaojian1;?><?php 
if($ismas=="1"){
?>+验证码<?php }?>】都输入正确才显示相应结果。
<!---你的其他说明在这里添加：开始--->



<!---你的其他说明在这里添加：结束--->
</div>
<div id="tishi1" style="display:none;">请认真输入<?php echo $tiaojian1;?></div>
<div id="tishi4" style="display:none;">认真输入4数字验证码</div>
</form>
<?php 

/**
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d======================================================================
' * 版权所有 (C) XueLiKai.Com，并保留所有权利。
' * 官方网址: http://Www.dbcha.com （请保留版权信息）
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * $Author: yujianyue <admin@ewuyi.net> $
' * $LastEdit: 2016-09-24 $
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * 代码不加密；你可以二次开发以便更适合你的需求 ，但不得：公开发布、公开销售。
' * 代码无域名、时间限制，非常通用；你可以安装多份，单位主体请购买本软件。
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d:index.php=============================================================
*/

}else{
if($ismas=="1"){
session_start();
if($codes!=$_SESSION['PHP_M2T']){
 webalert("请正确输入验证码！");
}
}
if(!$shuru1){
 webalert("请输入$tiaojian1!");
}
$files = $UpDir."/".$shujus.".xls";


$files = charaget($files);

if(!file_exists($files)){
$files = characet($files);
}

if(!file_exists($files)){
 webalert('请检查数据库文件');
}else{
 echo '<p align="center"> ';
 echo $shujus; 
 echo '</p>';
}
echo '<!--startprint-->';
echo '<table cellspacing="0">';
echo "<caption align='center'>查询结果 $iae</caption>";
$data = new Spreadsheet_Excel_Reader(); 
$data->setOutputEncoding('UTF-8'); 
$data->read($files); 

for ($i = 1; $i <= $data->sheets[0]['numRows']; $i++) { 
 if($i=="1"){
 $iaa=0;
 $iab=0;
 echo '<tr class="tt">';
for ($j = 1; $j <= $data->sheets[0]['numCols']; $j++) { 
$taba = ''.$data->sheets[0]['cells'][$i][$j].'';
//$taba = iconv('UTF-8', 'GB2312', $taba); 
 echo '<td>'.$taba.'</td>';
      $io++; 
    if($taba==$tiaojian1){
      $iaa=$io; 
    }
} 
 echo '</tr>';
    if(strlen($iaa)<1){   //if($iaa){
 webalert('请检查Excel数据第1行是否存在【'.$tiaojian1.'】字段!');
    }else{
echo "<!--'.$tiaojian1.'='.$iaa.'-->\r\n";
    }
echo "\r\n";
 }else{
 $Excelx=$data->sheets[0]['cells'][$i][$iaa];
// $Excelx=iconv('UTF-8', 'GB2312', $Excelx); 
if("_".$shuru1=="_".$Excelx){
echo "<!-- $shuru1 == $Excelx -->\r\n";
 $iae++; 
 echo '<tr>';
for ($j = 1; $j <= $data->sheets[0]['numCols']; $j++) { 
 $tabe = ''.$data->sheets[0]['cells']['1'][$j].'';
// $tabe = iconv('UTF-8', 'GB2312', $tabe); 
$tabu = ''.$data->sheets[0]['cells'][$i][$j].'';
// $tabu = iconv('UTF-8', 'GB2312', $tabu); 
 //echo '<td class="r">'.$tabe.'</td>';
 echo '<td >'.$tabu.'</td>';
 } 
 echo "</tr>\r\n";
} 
}
}
if($iae<1){
    echo '<tr>';
        echo "<td colspan=$j>没有查询到$tiaojian1=$shuru1 相关信息哦</td>";
    echo "</tr>\r\n";
}
 echo "</table>\r\n";
echo '<!--endprint-->';
fclose($filer);
?><div class="so_boxesd">
<input type="button" name="print" value="预览并打印" onclick="preview()" class="buts">
<input type="button" value="返 回" class="buts" onclick="location.href='?t=back';" id="reset"></div>
<?php 

/**
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d======================================================================
' * 版权所有 (C) XueLiKai.Com，并保留所有权利。
' * 官方网址: http://Www.dbcha.com （请保留版权信息）
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * $Author: yujianyue <admin@ewuyi.net> $
' * $LastEdit: 2016-09-24 $
' * ------61c537ca4404f419a3f8b6d0b7ddfb9d----------------------------------------------------------------------
' * 代码不加密；你可以二次开发以便更适合你的需求 ，但不得：公开发布、公开销售。
' * 代码无域名、时间限制，非常通用；你可以安装多份，单位主体请购买本软件。
' * ======61c537ca4404f419a3f8b6d0b7ddfb9d:index.php=============================================================
*/

}
$etime=microtime(true);//获取程序执行结束的时间
$total=$etime-$stime;   //计算差值
echo "<!----页面执行时间：{$total} ]秒--->";
?></div>
<div class="foot">
  <div class="title"> <!---更多版本请看:http://test.96448.cn/--->
    <span>&copy;<?php echo date('Y');?>&nbsp; <a href="<?php echo $copyu;?>" target="_blank"><?php echo $copyr;?></a></span>
  </div> <!---更多版本请看:http://test.96448.cn/--->
</div>
</body>
</html><script type="text/javascript" src="../index_cha.js?v=ADA_A1T"></script>