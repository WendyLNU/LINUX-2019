<?php
/*
* 作用:显示文件及文件夹并提供下载
* 作者:寒枫欣叶   http://www.itdhz.com
* 效果:http://soft.itdhz.com
* 版权:版权所有,发表或转载请注明出处!有付出才会有收获!
*
* 用法:1.将此文件命令为index.php放到网站的根目录
*      2.在根目录下新建download文件夹
*      3.将所有要下载的文件放到download文件夹内
*      4.将$basedir变量设置成你新建download文件夹的全路径
*
* 特别说明:此文件在代码中已做路径权限限制.
*          请勿请此文件修改做webshell跨目录用.
*          此文件所产生的任何法律问题与原作者无关.
*/
  
error_reporting(0);
session_start();
  $admin_account=$_SESSION['access'];
$basedir = "./".$admin_account."/";
if(!is_dir($basedir)) 
{
	$res=mkdir(iconv("UTF-8", "GBK", $basedir),0777,true); 
/*$basedir = dirname(__FILE__);*/

}
$file_name = $_GET['downfile'];
if(!empty($file_name)){
	$file_dir = $basedir . "\\" . $file_name;
	echo $file_name;
	if(dirname(realpath($file_dir)) < $basedir){
		echo "Permission Denied!";
		exit;
	}
	if (!file_exists($file_dir)) {
		echo "File Not Found!";
		exit;
	} else {
		$file = fopen($file_dir,"r");
		Header("Content-type: application/octet-stream");
		Header("Accept-Ranges: bytes");
		Header("Accept-Length: ".filesize($file_dir));
		Header("Content-Disposition: attachment; filename=" . $file_name);
		echo fread($file,filesize($file_dir));
		fclose($file);
		exit;
	}
}
header("Content-type: text/html; charset='utf-8'");
$requestDir = $_GET['dir'];
if(empty($requestDir)){
	$dir = $basedir;
}else{
	$dir = $basedir . "/" . $requestDir;
}
$dir = realpath($dir);
if($dir < $basedir) $dir = $basedir;
?>

<html>
<head>
<title>download</title>
<meta http-equiv="Content-Type" content="text/html; charset='utf-8'" />
<STYLE type="text/css">
body {
	font-family: "Courier New", "Verdana", "Tahoma";
	font-size: 12px;
}

td {
	font-family: "Courier New", "Verdana", "Tahoma";
	font-size: 12px;
}

input {
	font-family: "Courier New", "Verdana", "Tahoma";
	font-size: 12px;
}

.title {
	font-family: "Verdana", "Tahoma";
	font-size: 22px;
	font-weight: bold;
}
</STYLE>
</head>
<body>
	<table width="100%" border="0" cellspacing="1" cellpadding="3">
		<tr>
			<td class="title">实验文件下载列表</td>
			<td align="right" valign="bottom"><font color="#FF0000"><?php echo "服务器操作系统: ".PHP_OS."<br>";?>
			</font>
			</td>
		</tr>
	</table>
	<hr width="100%" style="border:1px dashed black; height:1px">
	<table width="100%" border="0" cellpadding="3" cellspacing="1">
		<tr>
			<td><?php 
			$predir = realpath($dir . "/../");
			if($predir > $basedir) $predir = str_replace($basedir . "/","",$predir);
			if($predir == $basedir) $predir = ".";
			
			?>
			</td>
		</tr>
		
	</table>
	<hr width="100%" style="border:1px dashed black; height:1px">
	<table width="100%" border="0" cellpadding="3" cellspacing="1">
		<tr>
			<td><b>文件名</b></td>
			<td><b>日期</b></td>
			<td><b>大小</b></td>
			<td><b>操作</b></td>
		</tr>
		<?php
		$dirs=@opendir($dir);
		while ($file=@readdir($dirs)) {
			$b="$dir/$file";
			$a=@is_dir($b);
			if($a=="0"){
				$size=@filesize("$dir/$file");
				$size=$size/1024 ;
				$size= @number_format($size,3);
				$lastsave=@date("Y-n-d H:i:s",filectime("$dir/$file"));
				echo "<tr>\n";
				echo "<td>□ $file</td>\n";
				echo "<td>$lastsave</td>\n";
				echo "<td>$size KB</td>\n";
				echo "<td><a href=\"?downfile=".urlencode($file)."\">下载</a></td>\n";
				echo "</tr>\n";
			}
		}
		@closedir($dirs);
		?>
	</table>
<hr width="100%" style="border:1px dashed black; height:1px">
<?php include View::getView('side'); include View::getView('footer');?>
</body>
</html>