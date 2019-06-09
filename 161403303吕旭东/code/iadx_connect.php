<?php
$mysql_conf = array(
    'host'    => '127.0.0.1',
    'db'      => 'zcode',
    'db_user' => 'root',
    'db_pwd'  => 'root',
);
$mysqli = new mysqli($mysql_conf['host'], $mysql_conf['db_user'], $mysql_conf['db_pwd']);
if ($mysqli->connect_errno) {
  die("could not connect to the database:\n" . $mysqli->connect_error);//诊断连接错误
}
$mysqli->query("set names 'utf8';");//编码转化
$select_db = $mysqli->select_db($mysql_conf['db']);
if (!$select_db) {
  die("could not connect to the db:\n" . $mysqli->error);
}

?>//数据库连接
