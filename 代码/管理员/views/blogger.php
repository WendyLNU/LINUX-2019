<?php if(!defined('EMLOG_ROOT')) {exit('error!');}?>
<div class="panel-heading">
<?php if (ROLE == ROLE_ADMIN):?>
<ul class="nav nav-tabs" role="tablist">
    <li role="presentation"><a href="./configure.php">基本设置</a></li>
    <li role="presentation"><a href="./seo.php">SEO设置</a></li>
    <li role="presentation" class="active"><a href="./blogger.php">个人设置</a></li>
    <?php if(isset($_GET['active_edit'])):?><span class="alert alert-success">个人资料修改成功</span><?php endif;?>
    <?php if(isset($_GET['active_del'])):?><span class="alert alert-success">头像删除成功</span><?php endif;?>
    <?php if(isset($_GET['error_a'])):?><span class="alert alert-danger">昵称不能太长</span><?php endif;?>
    <?php if(isset($_GET['error_b'])):?><span class="alert alert-danger">电子邮件格式错误</span><?php endif;?>
    <?php if(isset($_GET['error_c'])):?><span class="alert alert-danger">密码长度不得小于6位</span><?php endif;?>
    <?php if(isset($_GET['error_d'])):?><span class="alert alert-danger">两次输入的密码不一致</span><?php endif;?>
    <?php if(isset($_GET['error_e'])):?><span class="alert alert-danger">该登录名已存在</span><?php endif;?>
    <?php if(isset($_GET['error_f'])):?><span class="alert alert-danger">该昵称已存在</span><?php endif;?>
</ul>
<?php else:?>
<ul class="nav nav-tabs" role="tablist">
  <li role="presentation" class="active"><a href="./blogger.php">个人设置</a></li>
</ul>
<?php endif;?>
</div>
<form action="blogger.php?action=update" method="post" name="blooger" id="blooger" enctype="multipart/form-data">
<div class="form-group" style="margin-left:30px;">
    <li><?php echo $icon; ?><input type="hidden" name="photo" value="<?php echo $photo; ?>"/></li>
    <li>
    <label>头像(支持JPG、PNG格式图片)</label>
    <input name="photo" type="file" />
    </li>
    <li><label>昵称</label><input maxlength="50" style="width:200px;" class="form-control" value="<?php echo $nickname; ?>" name="name" /> </li>
    <li><label>邮箱</label><input name="email" class="form-control" value="<?php echo $email; ?>" style="width:200px;" maxlength="200" /></li>
    <li><label>个人描述</label><textarea name="description" class="form-control" style="width:300px; height:65px;" type="text" maxlength="500"><?php echo $description; ?></textarea></li>
    <li><label>登陆名</label><input maxlength="200" style="width:200px;" class="form-control" value="<?php echo $username; ?>" name="username" /></li>
    <li><label>新密码（不小于6位，不修改请留空）</label><input type="password" maxlength="200" class="form-control" style="width:200px;" value="" name="newpass" /></li>
    <li><label>再输入一次新密码</label><input type="password" maxlength="200" class="form-control" style="width:200px;" value="" name="repeatpass" /></li>
    <li>
        <input name="token" id="token" value="<?php echo LoginAuth::genToken(); ?>" type="hidden" />
        <input type="submit" value="保存资料" class="btn btn-primary" />
    </li>
</div>
</form>
<script>
$("#chpwd").css('display', $.cookie('em_chpwd') ? $.cookie('em_chpwd') : 'none');
setTimeout(hideActived, 2600);
$("#menu_category_sys").addClass('active');
$("#menu_sys").addClass('in');
$("#menu_setting").addClass('active');
</script>
