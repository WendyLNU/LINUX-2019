<?php
define ('MYSQL_HOST','localhost');
define ('MYSQL_USER','root');
define ('MYSQL_PASSWORD','12345678');
define ('MYSQL_DB','gfnews');
$db=mysql_connect(MYSQL_HOST,MYSQL_USER,MYSQL_PASSWORD);//连接mysql服务器
mysql_query("set names 'gb2312'");//选择编码
mysql_select_db(MYSQL_DB,$db);//选择数据库
?>
