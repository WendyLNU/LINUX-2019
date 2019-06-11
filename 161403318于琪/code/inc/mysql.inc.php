<!--ר�Ŵ�ź�����MySQL���н���-->
<?php
//1.���ݿ�����
function connect($host=DB_HOST,$user=DB_USER,$password=DB_PASSWORD,$database=DB_DATABASE,$port=DB_PORT){
	$link=mysqli_connect($host,$user,$password,$database,$port);
	if(mysqli_connect_errno()){
		exit(mysqli_connect_error());
	}
	mysqli_set_charset($link,'utf-8');
	return $link;
}
//2.ִ��һ��sql��䣬���ؽ����������߷��ز���ֵ
function execute($link,$query){
	$result=mysqli_query($link,$query);
	if(mysqli_errno($link)){
		exit(mysqli_error($link));
	}
	return $result;
}
//3.ִ��һ��sql��䣬ֻ���ز���ֵ
function execute_bool($link,$query){
	$bool=mysqli_real_query($link,$query);
	if(mysqli_errno($link)){
		exit(mysqli_error($link));
	}
	return $bool;
}
//4.һ����ִ�ж���sql���
/*
 һ����ִ�ж���SQL���
$link������
$arr_sqls��������ʽ�Ķ���sql���
$error������һ�������������洢���ִ�еĴ�����Ϣ
ʹ�ð�����
$arr_sqls=array(
	'select * from sfk_father_module',
	'select * from sfk_father_module',
	'select * from sfk_father_module',
	'select * from sfk_father_module'
);
var_dump(execute_multi($link, $arr_sqls,$error));
echo $error;
*/
function execute_multi($link,$arr_sqls,&$error){
	$sqls=implode(';',$arr_sqls).';';
	if(mysqli_multi_query($link,$sqls)){
		$data=array();
		$i=0;//����
		do {
			if($result=mysqli_store_result($link)){
				$data[$i]=mysqli_fetch_all($result);
				mysqli_free_result($result);
			}else{
				$data[$i]=null;
			}
			$i++;
			if(!mysqli_more_results($link)) break;
		}while (mysqli_next_result($link));
		if($i==count($arr_sqls)){
			return $data;
		}else{
			$error="sql���ִ��ʧ�ܣ�<br />&nbsp;�����±�Ϊ{$i}�����:{$arr_sqls[$i]}ִ�д���<br />&nbsp;����ԭ��".mysqli_error($link);
			return false;
		}
	}else{
		$error='ִ��ʧ�ܣ�������������Ƿ���ȷ��<br />���ܵĴ���ԭ��'.mysqli_error($link);
		return false;
	}
}
//5.��ȡ��¼��
function num($link,$sql_count){
	$result=execute($link,$sql_count);//$sql_countΪ������Ŀ��sql���
	//var_dump(mysqli_num_rows($result));
	$count=mysqli_fetch_row($result);
	return $count[0];
}
//6.�������֮ǰ����ת�壬ȷ�������ܹ�˳�������
function escape($link,$data){//��Ҫת�������
	if(is_string($data)){
		return mysqli_real_escape_string($link,$data);
	}
	if(is_array($data)){
		foreach ($data as $key=>$val){
			$data[$key]=escape($link,$val);//��escape����mysqli_real_escape_string,�����Լ�������˶�ά���������
		}
	}
	return $data;
}
//7.�ر������ݿ������
function close($link){
	mysqli_close($link);
}
?>