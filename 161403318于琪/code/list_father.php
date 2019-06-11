<!-- ��ŷ���ҳ-->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
include_once 'inc/page.inc.php';
$template['title']='������б�ҳ';
$link=connect();
if(!$member_id=is_login($link)){
	skip('login.php', 'error', '���¼���ٷ�����');
}
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){ //id=?�����ڻ���һ������
	skip('index.php', 'error', '�����id�������Ϸ���');
}
$query="select * from father_module where id={$_GET['id']}";
$result_father=execute($link, $query);
if(mysqli_num_rows($result_father)==0){
	skip('index.php', 'error', '����鲻���ڣ�');
}
$data_father=mysqli_fetch_assoc($result_father);

$query="select * from son_module where father_module_id={$_GET['id']}";
$result_son=execute($link, $query);
$id_son='';
$son_list='';
while ($data_son=mysqli_fetch_assoc($result_son)){ //һ��������µ��Ӱ����ܲ�Ψһ
	$id_son.=$data_son['id'].','; //��ȡ�Ӱ��id��
	$son_list.="<a>{$data_son['module_name']}</a> ";
}
// $id_son=trim($id_son,','); //ȥ����������ҵĶ���
// echo $id_son;//��female�����Ϊ�����Ӱ��id��Ϊ6��9
// exit();
$id_son=trim($id_son,',');
if($id_son==''){
	$id_son=0;
}
$query="select count(*) from content where module_id in ({$id_son})"; 
$count_all=num($link, $query); //ÿ������������ӵ�����Ŀ
$query="select count(*) from content where module_id in ({$id_son}) and time>CURDATE()"; 
$count_today=num($link, $query); //���췢������
?>
<link rel="stylesheet" type="text/css" href="style/public.css" />
<link rel="stylesheet" type="text/css" href="style/list.css" />
<?php include_once 'inc/header.inc.php';?>
<div id="position" class="auto">
	 <a href="index.php">��ҳ</a> &gt; <a href="list_father.php?id=<?php echo $data_father['id']?>"><?php echo $data_father['module_name']?></a>
</div>
<div id="main" class="auto">
	<div id="left">
		<div class="box_wrap">
			<h3><?php echo $data_father['module_name']?></h3>
			<div class="num">
			    ���գ�<span><?php echo $count_today?></span>&nbsp;&nbsp;&nbsp;
			    ������<span><?php echo $count_all?></span>
			  <div class="moderator"> �Ӱ�飺 <?php echo $son_list?></div>
			</div>
			<div class="pages_wrap">
				<a class="btn publish" href=""></a>
				<div class="pages">
					<?php 
					$page=page($count_all,1);
					echo $page['html'];
					?>
				</div>
				<div style="clear:both;"></div>
			</div>
		</div>
		<div style="clear:both;"></div>
		<ul class="postsList">
			<?php 
			$query="select content.title,content.id,content.time,content.times,member.name,member.photo,son_module.module_name from content,member,son_module where content.module_id in ({$id_son}) and content.member_id=member.id and content.module_id=son_module.id {$page['limit']}";
			$result_content=execute($link, $query);
		    while($data_content=mysqli_fetch_assoc($result_content)){
			?>
			<li>
				<div class="smallPic">
					<a href="#">
						<img width="45" height="45"src="<?php if($data_content['photo']!=''){echo $data_content['photo'];}else{echo 'style/photo.jpg';}?>">
					</a>
				</div>
				<div class="subject">
					<div class="titleWrap"><a href="#">[<?php echo $data_content['module_name']?>]</a>&nbsp;&nbsp;<h2><a href="#"><?php echo $data_content['title']?></a></h2></div>
					<p>
						¥����<?php echo $data_content['name']?>&nbsp;<?php echo $data_content['time']?>&nbsp;&nbsp;&nbsp;&nbsp;���ظ���2014-12-08
					</p>
				</div>
				<div class="count">
					<p>
						�ظ�<br /><span>41</span>
					</p>
					<p>
						���<br /><span><?php echo $data_content['times']?></span>
					</p>
				</div>
				<div style="clear:both;"></div>
			</li>
		<?php 
		}
		?>
		</ul>
		<div class="pages_wrap">
			<a class="btn publish" href=""></a>
			<div class="pages">
				<?php echo $page['html'];?>
			</div>
			<div style="clear:both;"></div>
		</div>
	</div>
	<div id="right">
		<div class="classList">
			<div class="title">����б�</div>
			<ul class="listWrap">
			<?php 
			$query="select * from father_module";
			$result_father=execute($link, $query);
			while($data_father=mysqli_fetch_assoc($result_father)){
			?>
				<li>
					<h2><a href="list_father.php?id=<?php echo $data_father['id'];?>"><?php echo $data_father['module_name']?></a></h2>
					<ul>
						<?php 
						$query="select * from son_module where father_module_id={$data_father['id']}";
						$result_son=execute($link, $query);
						while($data_son=mysqli_fetch_assoc($result_son)){
						?>
						<li><h3><a href="#"><?php echo $data_son['module_name']?></a></h3></li>
						<?php 
						}
						?>
					</ul>
				</li>
				<?php 
				}
				?>
			</ul>
		</div>
	</div>
	<div style="clear:both;"></div>
</div>
<?php include_once 'inc/footer.inc.php';?>