<!-- ��ҳ���� -->
<!-- 
$page=page(100,10,5);
����ֵ:array('limit','html')
��ҳ��������������������
1.�����������select����limit����
  select limit 0,2
2.Ӧ�ð������� ���ú�ҳ���б��html���벿��
     ���ݴ��뺯����$sum_btn��������ʾ��ť��Ŀ
  1��Ҫ��ʾ�İ�ť��Ŀ$sum_btn������ҳ����Ŀ$page_num_all
  2)$sum_btnС����ҳ�� 
  	��������£�����������һ����ʾ�����ǣ���ǰҳ����߰�ť��ĿӦ�ú��ұ߰�ť��Ŀ��ȣ������ұ߶�һ����ť
  	����״̬������֪����ǰҳ��ҳ��ţ���Ҫ֪������߰�ť��ҳ��ţ�������ߵİ�ť��Ŀ���԰�����ߵİ�ťҳ��ż������
  	�������״̬����ߵ�һ����ť���Ѿ���С��1��
  			   �ұ����һ����ť�Ѿ��������ҳ����$page_num_all
  ����ť��Ŀ>=3��ʱ����ʡ�Ժ�Ч����
  	����һ����ť��ҳ�벻��1��ʱ�����ǾͰѵ�һ����ť�滻��1...
  	����һ����ť��ҳ�벻��$page_num_all��ʱ�����ǾͰ����һ����ť�滻��...$page_num_all
-->
<?php 
function page($count,$page_size,$num_btn=10,$page='page'){//���ݿ�ļ�¼������ÿһҳ��ʾ������,�ڼ�ҳ��ť������,�ڼ�ҳ
	if(!isset($_GET[$page]) || !is_numeric($_GET[$page]) || $_GET[$page]<1){ //���û��д?page=���ٻ��߲������ֻ��߲���С��1���򰴵�һҳ����
		$_GET[$page]=1;
	}
	$page_num_all=ceil($count/$page_size);//����ȡ��,��ҳ��
	if($_GET[$page]>$page_num_all){ //���û��д?page=���ٻ��߲������ֻ��߲���С��1���򰴵�һҳ����
		$_GET[$page]=$page_num_all;
	}
	$start=($_GET[$page]-1)*$page_size;
	$limit="limit {$start},{$page_size}";
	
	$current_url=$_SERVER['REQUEST_URI']; //���浱ǰurl��ַ
	$arr_current=parse_url($current_url); //path+query ����ǰurl��ֵ���������
	$current_path=$arr_current['path'];//���ļ�·�����ֱ�������
	$url='';
	if(isset($arr_current['query'])){
		parse_str($arr_current['query'],$arr_query);
		unset($arr_query[$page]);//ɾ��page����
		if(empty($arr_query)){
			$url="{$current_path}?{$page}=";
		}else{
			$other=http_build_query($arr_query);
			$url="{$current_path}?{$other}&{$page}=";
		}
	}else{
		$url="{$current_path}?{$page}=";
	}
	$html=array();
	if($num_btn>=$page_num_all){//�������İ�ť��������ҳ��
		//�����е�ҳ�밴ťȫ����ʾ
		for($i=1;$i<=$page_num_all;$i++){ //��ߵı���$page_num_all��������ѭ�������Կ�����ʾ��ť��Ŀ�ı�����$i��ҳ���
			if($_GET[$page]==$i){ //���ҳ����ڵ�ǰҳ�����ܵ�
				$html[$i]="<span>{$i}</span> ";
			}else{
				$html[$i]="<a href='{$url}{$i}'>{$i}</a> ";	
			}
		}
	}else{ //��ť��Ŀ��ȥ���м�ĵ�ǰҳ���Ա����Ҹ�����ҳ�������ż�����ұ�+1������ȡ��
		$num_left=floor(($num_btn-1)/2); //���߰�ť��
		$start=$_GET[$page]-$num_left;//��ǰҳ���-���߰�ť��=��ʼҳ���
		$end=$start+($num_btn-1); //������ҳ���
		if($start<1){
			$start=1; //�����һ��ҳ��С��1������һ��ҳ������Ϊ1
		}
		if($end>$page_num_all){
			$start=$page_num_all-($num_btn-1); //������һ��ҳ�������ҳ���������һ��ҳ����Ϊ��ǰҳ
		}
		for($i=0;$i<$num_btn;$i++){
			if($_GET[$page]==$start){
				$html[$start]="<span>{$start}</span> ";
			}else{
				$html[$start]="<a href='{$url}{$start}'>{$start}</a> ";
			}
			$start++;
		}
		//�����ť��Ŀ���ڵ���3��ʱ����ʡ�Ժ�Ч��
		if(count($html)>=3){
			reset($html);
			$key_first=key($html);//��ʼָ����뵽�����еĵ�һ����Ԫ
			end($html);
			$key_end=key($html); //ָ�����һ����Ԫ	
			if($key_first!=1){ //��ʼҳ��Ϊ1������Ϊ1...
				array_shift($html);
				array_unshift($html,"<a href='{$url}1'>1...</a>");
			}
			if($key_end!=$page_num_all){ //βҳ��Ϊ���ҳ������Ϊ...���ҳ
				array_pop($html);
				array_push($html,"<a href='{$url}$page_num_all'>...$page_num_all</a>");
			}
				
		}
	}
	if($_GET[$page]!=1){ //��һҳ����һҳ
		$prev=$_GET[$page]-1;
		array_unshift($html,"<a href='{$url}{$prev}'><< ��һҳ</a>");
	}
	if($_GET[$page]!=$page_num_all){
		$next=$_GET[$page]+1;
		array_push($html,"<a href='{$url}$next}'>��һҳ>> </a>");
	}
	$html=implode(' ', $html); //������Ԫ������һ��
	$data=array(
		'limit'=>$limit,
		'html'=>$html
	);
	return $data;
}
?>
<!-- 
0
1
2
----
3
4
5
----
6
7
8
----
9
10
ÿҳ��ʾ3��
limit 0,3 //��һҳ ���ӵڼ�����ʼ��ʾ����ʾ������
limit 3,3 //�ڶ�ҳ limit ($_GET[$page]-1)*$page_size,$page_size
-->

