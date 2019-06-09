<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
$member_id=is_login($link);
if(!$member_id){
	skip('index.php','error','你没有登录，不需要退出！');
}
setcookie('sfk[name]','',time()-3600);
setcookie('sfk[pw]','',time()-3600);
skip('index.php','ok','退出成功！');
?>