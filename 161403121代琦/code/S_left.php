
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>

<meta http-equiv="Content-Type" content="textml; charset=utf-8" />
<title>无标题文档</title>
<style type="text/css">
*{margin:0; padding:0}
#nav{ }
#nav h3{ cursor:pointer; line-height:30px;background-color:#223344; color:#aaaaaa}
#nav a{display:block;color:#8899FF;line-height:30px;left:450px}
#nav h3 a:hover{background-color:#000000; color:#234323;}
#nav div{display:none; border:1px solid #000; border-top:none}
a:link {
	text-decoration: none;
a:visited {
	text-decoration: none;
}
a:hover {
	text-decoration: none;
}
a:active {
	text-decoration: none;
}
</style>
<script type="text/javascript">
function $(id){return document.getElementById(id)}
window.onload = function(){
 $("nav").onclick = function(e){
  var src = e?e.target:event.srcElement;
  if(src.tagName == "H3"){
   var next = src.nextElementSibling || src.nextSibling;
   next.style.display = (next.style.display =="block")?"none":"block";
  }
 }
}
</script>
</head>

<body background="image/11.jpg">
 
<?php session_start(); 
error_reporting(E_ALL^E_NOTICE);?>
<table width=100% height="77"  bordercolor="#000066" >
  <tr>
    <td bgcolor="#0033CC"><font color="#6e7f39" ><strong><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;欢迎您:</b><?php echo $_SESSION['access'];?></strong></font></td>
  </tr>
  
</table>

<div  style="position:relative; margin:0" class="nav" id="nav">
 <h3 align="center">实验管理</h3>
 <div>
     <a href="student_qiandao.php" target="main"><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;学生签到</b></a>
<a href="chakanshiyan.php" target="main"><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;查看实验</b></a>
</div>
 <h3 align="center">教师留言</h3>
    <div>
     <a href="stu_tea_message.php" target="main"><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;教师回复</b></a>
       
    </div>
  <h3 align="center">版本V2019.5.13</h3>
</div>
</body>
<ml>