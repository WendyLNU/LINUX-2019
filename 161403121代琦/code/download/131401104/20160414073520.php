<?php
/*
* ����:��ʾ�ļ����ļ��в��ṩ����
* ����:������Ҷ   http://www.itdhz.com
* Ч��:http://soft.itdhz.com
* ��Ȩ:��Ȩ����,�����ת����ע������!�и����Ż����ջ�!
*
* �÷�:1.�����ļ�����Ϊindex.php�ŵ���վ�ĸ�Ŀ¼
*      2.�ڸ�Ŀ¼���½�download�ļ���
*      3.������Ҫ���ص��ļ��ŵ�download�ļ�����
*      4.��$basedir�������ó����½�download�ļ��е�ȫ·��
*
* �ر�˵��:���ļ��ڴ���������·��Ȩ������.
*          ��������ļ��޸���webshell��Ŀ¼��.
*          ���ļ����������κη���������ԭ�����޹�.
*/
  
error_reporting(0);
$basedir = "./download";
if(!is_dir($basedir)) $basedir = dirname(__FILE__);
$file_name = $_GET['downfile'];
if(!empty($file_name)){
	$file_dir = $basedir . "/" . $file_name;
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
header("Content-type: text/html; charset=utf-8");
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
			<td class="title">PHPFileList�ļ������б�</td>
			<td align="right" valign="bottom"><font color="#FF0000"><?php echo "����������ϵͳ: ".PHP_OS."<br>";?>
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
			if($dir > $basedir) echo "<a href=\"?dir=". $predir ."\">�ϼ�Ŀ¼</a>";
			?>
			</td>
		</tr>
		<?php
		$dirs=@opendir($dir);
		$count = 0;
		while($file=@readdir($dirs)) {
			$b="$dir/$file";
			$a=@is_dir($b);
			if($a=="1"){
				if($file!=".."&&$file!=".") {
					if($count < 1){
						$count ++;
						echo "<tr>\n";
						echo "<td><b>��Ŀ¼</b></td>\n";
						echo "</tr>\n";
					}
					echo "<tr>\n";
					echo "<td>�� <a href=\"?dir=" . ($dir > $basedir ? str_replace($basedir . "/",'',$dir . "/") : '') . urlencode($file)."\">$file</a></td>\n";
					echo "</tr>\n";
				}
			}
		}
		@closedir($dirs);
		?>
	</table>
	<hr width="100%" style="border:1px dashed black; height:1px">
	<table width="100%" border="0" cellpadding="3" cellspacing="1">
		<tr>
			<td><b>�ļ���</b></td>
			<td><b>����</b></td>
			<td><b>��С</b></td>
			<td><b>����</b></td>
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
				echo "<td>�� $file</td>\n";
				echo "<td>$lastsave</td>\n";
				echo "<td>$size KB</td>\n";
				echo "<td><a href=\"?downfile=".($dir > $basedir ? str_replace($basedir . "/",'',$dir . "/") : '').urlencode($file)."\">����</a></td>\n";
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