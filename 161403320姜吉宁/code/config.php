<?php
 define('DB_NAME','bookinfo'); 

    $mysqli = new mysqli('localhost','root','123456',DB_NAME);
	error_reporting(0);
	ob_start();
	session_start(); //��������

	if($mysqli->connect_error)
	{
		echo "���ݿ��ʧ��";
		exit; //���ݿ��ʧ�ܣ��˳�
	}
	 $mysqli->query('set names utf8'); //�������ݿ����
    
?>

