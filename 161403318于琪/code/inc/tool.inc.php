<!-- ��ת���� + �ж��û��Ƿ��¼����-->
<?php 
function skip($url,$pic,$message){
$html=<<<YU
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="gb2312" />
<meta http-equiv="refresh" content="3;URL={$url}" />
<title>������ת��</title>
<meta name="keywords" content="��̨����" />
<meta name="description" content="��̨����" />
<link rel="stylesheet" type="text/css" href="style/remind.css" />
</head>
<body>
<div class="notice"><span class="pic {$pic}"></span>{$message} <a href="{$url}">3����Զ���ת!</a></div>
</body>
</html>
YU;
echo $html;
exit;
}
function is_login($link){ //��register��setcookie,��֤�û��Ƿ��¼
	if(isset($_COOKIE['sfk']['name']) && isset($_COOKIE['sfk']['pw'] )){
		$query="select * from member where name='{$_COOKIE['sfk']['name']}' and sha1(pw)='{$_COOKIE['sfk']['pw']}'";
		$result=execute($link, $query);
		if(mysqli_num_rows($result)==1){
			$data=mysqli_fetch_assoc($result);
			return $data['id']; //�����½���򷵻�id��
		}else{
			return false;
		}
		
	}else{
		return false;
	}
}
?>