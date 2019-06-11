<!-- 存放发帖页-->
<?php 
include_once 'inc/config.inc.php';
include_once 'inc/mysql.inc.php';
include_once 'inc/tool.inc.php';
include_once 'inc/page.inc.php';
$template['title']='父板块列表页';
$link=connect();
if(!$member_id=is_login($link)){
	skip('login.php', 'error', '请登录后再发帖！');
}
if(!isset($_GET['id']) || !is_numeric($_GET['id'])){ //id=?不存在或不是一个数字
	skip('index.php', 'error', '父板块id参数不合法！');
}
$query="select * from father_module where id={$_GET['id']}";
$result_father=execute($link, $query);
if(mysqli_num_rows($result_father)==0){
	skip('index.php', 'error', '父板块不存在！');
}
$data_father=mysqli_fetch_assoc($result_father);

$query="select * from son_module where father_module_id={$_GET['id']}";
$result_son=execute($link, $query);
$id_son='';
$son_list='';
while ($data_son=mysqli_fetch_assoc($result_son)){ //一个父板块下的子版块可能不唯一
	$id_son.=$data_son['id'].','; //获取子版块id号
	$son_list.="<a>{$data_son['module_name']}</a> ";
}
// $id_son=trim($id_son,','); //去掉最左和最右的逗号
// echo $id_son;//以female父板块为例，子版块id号为6，9
// exit();
$id_son=trim($id_son,',');
if($id_son==''){
	$id_son=0;
}
$query="select count(*) from content where module_id in ({$id_son})"; 
$count_all=num($link, $query); //每个父板块下帖子的总数目
$query="select count(*) from content where module_id in ({$id_son}) and time>CURDATE()"; 
$count_today=num($link, $query); //今天发帖总数
?>
<link rel="stylesheet" type="text/css" href="style/public.css" />
<link rel="stylesheet" type="text/css" href="style/list.css" />
<?php include_once 'inc/header.inc.php';?>
<div id="position" class="auto">
	 <a href="index.php">首页</a> &gt; <a href="list_father.php?id=<?php echo $data_father['id']?>"><?php echo $data_father['module_name']?></a>
</div>
<div id="main" class="auto">
	<div id="left">
		<div class="box_wrap">
			<h3><?php echo $data_father['module_name']?></h3>
			<div class="num">
			    今日：<span><?php echo $count_today?></span>&nbsp;&nbsp;&nbsp;
			    总帖：<span><?php echo $count_all?></span>
			  <div class="moderator"> 子版块： <?php echo $son_list?></div>
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
						楼主：<?php echo $data_content['name']?>&nbsp;<?php echo $data_content['time']?>&nbsp;&nbsp;&nbsp;&nbsp;最后回复：2014-12-08
					</p>
				</div>
				<div class="count">
					<p>
						回复<br /><span>41</span>
					</p>
					<p>
						浏览<br /><span><?php echo $data_content['times']?></span>
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
			<div class="title">版块列表</div>
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