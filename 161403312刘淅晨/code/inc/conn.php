<?php 



error_reporting(0);
header("content-Type: text/html; charset=utf-8");//输出编码GBK

//设置好以下3-8个参数（双引号内内容）
$tiaojian1="姓名";			//查询条件1列标题，跟excel列头一致，注意无空格回车;

$UpDir="shujukufangzheli";			//设置数据库所在目录(文件夹名称)请修改，修改后更名对应文件夹。
$title="某某中学成绩查询系统";			//设置查询标题,相信你懂的。
$copyr="某某中学";				//设置底部版权文字,相信你懂的。
$copyu="http://www.96448.cn/";			//设置底部版权连接,相信你懂的。

$ismas="0";				//设置是否使用验证码，1是0否。

//设置好以上3-8个参数（双引号内内容）




function webalert($Key){
 $html="<script>\r\n";
 $html.="alert('".$Key."');\r\n";
 $html.="history.go(-1);\r\n";
 $html.="</script>";
 exit($html);
}


function characet($data){
  if(!empty($data) ){    
    $fileType = mb_detect_encoding($data , array('UTF-8','GBK','LATIN1','BIG5')) ;   
    if( $fileType != 'UTF-8'){   
      $data = mb_convert_encoding($data ,'utf-8' , $fileType);   
    }   
  }   
  return $data;    
}

function charaget($data){
  if(!empty($data) ){    
    $fileType = mb_detect_encoding($data , array('UTF-8','GBK','LATIN1','BIG5')) ;   
    if( $fileType != 'GBK'){   
      $data = mb_convert_encoding($data ,'GBK' , $fileType);   
    }   
  }   
  return $data;    
}


//付费版可以选项时间排序
function traverse($dir_name = '.') {
$dir = opendir($dir_name); 
$basename = basename($dir_name); 
$fileArr = array(); 
while ($file_name = readdir($dir)) 
{ 
if (($file_name ==".") || ($file_name == "..")) { 
 } else if(is_dir($file_name)) {
 } else {
$filetp=substr($file_name,-4);
$filetp=strtolower($filetp);
$filesw=substr($file_name,0,-4);//注意后缀是4位数
if($filetp == ".xls"){
$file = $filesw;    //
echo '<option value="'.characet($file).'">' . characet($file) . '</option>';
} 
 } 
} 
closedir($dir); 
} 



?>