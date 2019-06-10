<?php if(!defined('EMLOG_ROOT')) {exit('error!');}?>
<div class="containertitle"><b>评论管理</b>
<?php if(isset($_GET['active_del'])):?><span class="alert alert-success">删除评论成功</span><?php endif;?>
<?php if(isset($_GET['active_show'])):?><span class="alert alert-success">审核评论成功</span><?php endif;?>
<?php if(isset($_GET['active_hide'])):?><span class="alert alert-success">隐藏评论成功</span><?php endif;?>
<?php if(isset($_GET['active_edit'])):?><span class="alert alert-success">修改评论成功</span><?php endif;?>
<?php if(isset($_GET['active_rep'])):?><span class="alert alert-success">回复评论成功</span><?php endif;?>
<?php if(isset($_GET['error_a'])):?><span class="alert alert-danger">请选择要执行操作的评论</span><?php endif;?>
<?php if(isset($_GET['error_b'])):?><span class="alert alert-danger">请选择要执行的操作</span><?php endif;?>
<?php if(isset($_GET['error_c'])):?><span class="alert alert-danger">回复内容不能为空</span><?php endif;?>
<?php if(isset($_GET['error_d'])):?><span class="alert alert-danger">内容过长</span><?php endif;?>
<?php if(isset($_GET['error_e'])):?><span class="alert alert-danger">评论内容不能为空</span><?php endif;?>
</div>
<div class=line></div>
<?php if ($hideCommNum > 0) : 
$hide_ = $hide_y = $hide_n = '';
$a = "hide_$hide";
$$a = "class=\"filter\"";
?>
<div class="filters">
<span <?php echo $hide_; ?>><a href="./comment.php?<?php echo $addUrl_1 ?>">全部</a></span>
<span <?php echo $hide_y; ?>><a href="./comment.php?hide=y&<?php echo $addUrl_1 ?>">待审
<?php
$hidecmnum = ROLE == ROLE_ADMIN ? $sta_cache['hidecomnum'] : $sta_cache[UID]['hidecommentnum'];
if ($hidecmnum > 0) echo '('.$hidecmnum.')';
?>
</a></span>
<span <?php echo $hide_n; ?>><a href="comment.php?hide=n&<?php echo $addUrl_1 ?>">已审</a></span>
</div>
<?php endif; ?>
<form action="comment.php?action=admin_all_coms" method="post" name="form_com" id="form_com">
  <table class="table table-striped table-bordered table-hover dataTable no-footer">
    <thead>
      <tr>
        <th width="369" colspan="2"><b>内容</b></th>
        <th width="300"><b>评论者</b></th>
        <th width="250"><b>所属文章</b></th>
      </tr>
    </thead>
    <tbody>
    <?php
    if($comment):
    foreach($comment as $key=>$value):
    $ishide = $value['hide']=='y'?'<font color="red">[待审]</font>':'';
    $mail = !empty($value['mail']) ? "({$value['mail']})" : '';
    $ip = !empty($value['ip']) ? "<br />来自：{$value['ip']}" : '';
    $poster = !empty($value['url']) ? '<a href="'.$value['url'].'" target="_blank">'. $value['poster'].'</a>' : $value['poster'];
    $value['content'] = str_replace('<br>',' ',$value['content']);
    $sub_content = subString($value['content'], 0, 50);
    $value['title'] = subString($value['title'], 0, 42);
    doAction('adm_comment_display');
    ?>
     <tr>
        <td width="19"><input type="checkbox" value="<?php echo $value['cid']; ?>" name="com[]" class="ids" /></td>
        <td width="350"><a href="comment.php?action=reply_comment&amp;cid=<?php echo $value['cid']; ?>" title="<?php echo $value['content']; ?>"><?php echo $sub_content; ?></a> 	<?php echo $ishide; ?>
        <br /><?php echo $value['date']; ?>
        <span style="display:none; margin-left:8px;">    
            <a href="javascript: em_confirm(<?php echo $value['cid']; ?>, 'comment', '<?php echo LoginAuth::genToken(); ?>');" class="care">删除</a>
        <?php if($value['hide'] == 'y'):?>
        <a href="comment.php?action=show&amp;id=<?php echo $value['cid']; ?>">审核</a>
        <?php else: ?>
        <a href="comment.php?action=hide&amp;id=<?php echo $value['cid']; ?>">隐藏</a>
        <?php endif;?>
        <a href="comment.php?action=reply_comment&amp;cid=<?php echo $value['cid']; ?>">回复</a>
        <a href="comment.php?action=edit_comment&amp;cid=<?php echo $value['cid']; ?>">编辑</a>
        </span>
        </td>
        <td><?php echo $poster;?> <?php echo $mail;?> <?php echo $ip;?> 
            <?php if (ROLE == ROLE_ADMIN): ?><a href="javascript: em_confirm('<?php echo $value['ip']; ?>', 'commentbyip', '<?php echo LoginAuth::genToken(); ?>');" title="删除来自该IP的所有评论" class="care">(X)</a><?php endif;?></td>
        <td><a href="<?php echo Url::log($value['gid']); ?>" target="_blank" title="查看该文章"><?php echo $value['title']; ?></a></td>
     </tr>
    <?php endforeach;else:?>
      <tr><td class="tdcenter" colspan="4">还没有收到评论</td></tr>
    <?php endif;?>
    </tbody>
  </table>
    <div class="list_footer">
    <a href="javascript:void(0);" id="select_all">全选</a> 选中项：
    <a href="javascript:commentact('del');" class="care">删除</a>
    <a href="javascript:commentact('hide');">隐藏</a>
    <a href="javascript:commentact('pub');">审核</a>
    <input name="operate" id="operate" value="" type="hidden" />
    </div>
    <div class="page"><?php echo $pageurl; ?> (有<?php echo $cmnum; ?>条评论)</div> 
</form>
<script>
$(document).ready(function(){
    selectAllToggle();
    $("#adm_comment_list tbody tr:odd").addClass("tralt_b");
    $("#adm_comment_list tbody tr")
        .mouseover(function(){$(this).addClass("trover");$(this).find("span").show();})
        .mouseout(function(){$(this).removeClass("trover");$(this).find("span").hide();})
});
setTimeout(hideActived,2600);
function commentact(act){
    if (getChecked('ids') == false) {
        alert('请选择要操作的评论');
        return;
    }
    if(act == 'del' && !confirm('你确定要删除所选评论吗？')){return;}
    $("#operate").val(act);
    $("#form_com").submit();
}
$("#menu_cm").addClass('active');
</script>
