<!-- 分页函数 -->
<!-- 
$page=page(100,10,5);
返回值:array('limit','html')
分页函数帮助我们两个工作
1.帮助我们完成select语句的limit部分
  select limit 0,2
2.应该帮助我们 设置好页码列表的html代码部分
     根据传入函数的$sum_btn参数来显示按钮数目
  1）要显示的按钮数目$sum_btn大于总页码数目$page_num_all
  2)$sum_btn小于总页数 
  	这种情况下，我们有这样一种显示策略是，当前页的左边按钮数目应该和右边按钮数目相等，或者右边多一个按钮
  	理想状态：我们知道当前页的页码号，需要知道最左边按钮的页码号（根据左边的按钮数目可以把最左边的按钮页码号计算出来
  	不理想的状态：左边第一个按钮号已经是小于1了
  			   右边最后一个按钮已经大于最大页码数$page_num_all
  当按钮数目>=3的时候做省略号效果：
  	当第一个按钮的页码不是1的时候，我们就把第一个按钮替换成1...
  	当第一个按钮的页码不是$page_num_all的时候，我们就把最后一个按钮替换成...$page_num_all
-->
<?php 
function page($count,$page_size,$num_btn=10,$page='page'){//数据库的记录总数，每一页显示的数量,第几页按钮的数量,第几页
	if(!isset($_GET[$page]) || !is_numeric($_GET[$page]) || $_GET[$page]<1){ //如果没有写?page=多少或者不是数字或者参数小于1，则按第一页处理
		$_GET[$page]=1;
	}
	$page_num_all=ceil($count/$page_size);//向上取整,总页数
	if($_GET[$page]>$page_num_all){ //如果没有写?page=多少或者不是数字或者参数小于1，则按第一页处理
		$_GET[$page]=$page_num_all;
	}
	$start=($_GET[$page]-1)*$page_size;
	$limit="limit {$start},{$page_size}";
	
	$current_url=$_SERVER['REQUEST_URI']; //保存当前url地址
	$arr_current=parse_url($current_url); //path+query 将当前url拆分到数组里面
	$current_path=$arr_current['path'];//将文件路径部分保存起来
	$url='';
	if(isset($arr_current['query'])){
		parse_str($arr_current['query'],$arr_query);
		unset($arr_query[$page]);//删掉page部分
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
	if($num_btn>=$page_num_all){//如果传入的按钮数大于总页码
		//把所有的页码按钮全部显示
		for($i=1;$i<=$page_num_all;$i++){ //这边的变量$page_num_all既是限制循环次数以控制显示按钮数目的变量，$i是页码号
			if($_GET[$page]==$i){ //如果页码等于当前页，不能点
				$html[$i]="<span>{$i}</span> ";
			}else{
				$html[$i]="<a href='{$url}{$i}'>{$i}</a> ";	
			}
		}
	}else{ //按钮数目减去最中间的当前页，旁边左右各多少页，如果是偶数，右边+1，向下取整
		$num_left=floor(($num_btn-1)/2); //左半边按钮数
		$start=$_GET[$page]-$num_left;//当前页码号-左半边按钮数=起始页码号
		$end=$start+($num_btn-1); //结束的页码号
		if($start<1){
			$start=1; //如果第一个页码小于1，将第一个页码设置为1
		}
		if($end>$page_num_all){
			$start=$page_num_all-($num_btn-1); //如果最后一个页码大于总页码数，最后一个页码设为当前页
		}
		for($i=0;$i<$num_btn;$i++){
			if($_GET[$page]==$start){
				$html[$start]="<span>{$start}</span> ";
			}else{
				$html[$start]="<a href='{$url}{$start}'>{$start}</a> ";
			}
			$start++;
		}
		//如果按钮数目大于等于3的时候做省略号效果
		if(count($html)>=3){
			reset($html);
			$key_first=key($html);//初始指向插入到数组中的第一个单元
			end($html);
			$key_end=key($html); //指向最后一个单元	
			if($key_first!=1){ //开始页不为1，设置为1...
				array_shift($html);
				array_unshift($html,"<a href='{$url}1'>1...</a>");
			}
			if($key_end!=$page_num_all){ //尾页不为最大页，设置为...最大页
				array_pop($html);
				array_push($html,"<a href='{$url}$page_num_all'>...$page_num_all</a>");
			}
				
		}
	}
	if($_GET[$page]!=1){ //上一页和下一页
		$prev=$_GET[$page]-1;
		array_unshift($html,"<a href='{$url}{$prev}'><< 上一页</a>");
	}
	if($_GET[$page]!=$page_num_all){
		$next=$_GET[$page]+1;
		array_push($html,"<a href='{$url}$next}'>下一页>> </a>");
	}
	$html=implode(' ', $html); //将数组元素连在一起
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
每页显示3条
limit 0,3 //第一页 （从第几条开始显示，显示几条）
limit 3,3 //第二页 limit ($_GET[$page]-1)*$page_size,$page_size
-->

