<!-- ǰ̨��ҳ -->
<?php
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
$link=connect();
if(!$member_id=is_login($link)){
	skip('login.php', 'error', '���¼���ٷ�����');
}
$template['title']='��ҳ';
?>
<link rel="stylesheet" type="text/css" href="style/public.css" />
<link rel="stylesheet" type="text/css" href="style/index.css" />
<?php include_once 'inc/header.inc.php';?>
<div id="hot" class="auto">
	<div class="title">���Ŷ�̬</div>
	<ul class="newlist">
		<!-- 20�� -->
		<li><a href="#">[stars]</a> <a href="#">����֪����ta��������...</a></li>
		
	</ul>
	<div style="clear:both;"></div>
</div>
<?php 
$query="select * from father_module order by sort desc";
$result_father=execute($link, $query);
while($data_father=mysqli_fetch_assoc($result_father)){
?>
	<div class="box auto">
	<div class="title">
		<a href="list_father.php?id=<?php echo $data_father['id']?>" style="color:#105cb6"><?php echo $data_father['module_name']?></a> <!-- ���ӵ�����ҳ -->
	</div>
	<div class="classList">
	<?php 
	$query="select * from son_module where father_module_id={$data_father['id']}";
	$result_son=execute($link, $query);
	if(mysqli_num_rows($result_son)){ //�ж��ж����Ӱ��
		while($data_son=mysqli_fetch_assoc($result_son)){
			$query="select count(*) from content where module_id={$data_son['id']} and time>CURDATE()";//CURDATA()������2019-5-21�����ݿ�ʱ�����������ڣ���:2019-5-21 16:40:50)
			$count_today=num($link, $query);
			$query="select count(*) from content where module_id={$data_son['id']}";
			$count_all=num($link, $query);
			$html=<<<YU
				<div class="childBox new">
					<h2><a href="list_son.php?id={$data_son['id']}">{$data_son['module_name']}</a> <span>(����{$count_today})</span></h2>
					���ӣ�{$count_all}<br />
				</div>
YU;
				echo $html;
		}
	}else{ //���û�У�����ʾ�����Ӱ��
		echo '<div style="padding:10px 0;">�����Ӱ��...</div>'; //ע������
	}
	?>
	<div style="clear:both;"></div>
</div>
<?php }?>
<?php include_once 'inc/footer.inc.php';?>