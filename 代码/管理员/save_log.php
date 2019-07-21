<?php
/**
 * 保存文章（增加、修改）
 * @copyright (c) Emlog All Rights Reserved
 */

require_once 'globals.php';

$Log_Model = new Log_Model();
$Tag_Model = new Tag_Model();

$title = isset($_POST['title']) ? addslashes(trim($_POST['title'])) : '';
$postDate = isset($_POST['postdate']) ? trim($_POST['postdate']) : '';
$date = isset($_POST['date']) ? addslashes($_POST['date']) : '';//修改前的文章时间
$sort = isset($_POST['sort']) ? intval($_POST['sort']) : -1;
$tagstring = isset($_POST['tag']) ? addslashes(trim($_POST['tag'])) : '';
$content = isset($_POST['content']) ? addslashes(trim($_POST['content'])) : '';
$excerpt = isset($_POST['excerpt']) ? addslashes(trim($_POST['excerpt'])) : '';
$author = isset($_POST['author']) && ROLE == ROLE_ADMIN ? intval(trim($_POST['author'])) : UID;
$blogid = isset($_POST['as_logid']) ? intval(trim($_POST['as_logid'])) : -1;//如被自动保存为草稿则有blog id号
$alias = isset($_POST['alias']) ? addslashes(trim($_POST['alias'])) : '';
$top = isset($_POST['top']) ? addslashes(trim($_POST['top'])) : 'n';
$sortop = isset($_POST['sortop']) ? addslashes(trim($_POST['sortop'])) : 'n';
$allow_remark = isset($_POST['allow_remark']) ? addslashes(trim($_POST['allow_remark'])) : 'n';
$ishide = isset($_POST['ishide']) && !empty($_POST['ishide']) && !isset($_POST['pubdf']) ? addslashes($_POST['ishide']) : 'n';
$password = isset($_POST['password']) ? addslashes(trim($_POST['password'])) : '';

$postTime = strtotime($postDate);

LoginAuth::checkToken();

//check alias
if (!empty($alias)) {
    $logalias_cache = $CACHE->readCache('logalias');
    $alias = $Log_Model->checkAlias($alias, $logalias_cache, $blogid);
}

$logData = array(
    'title' => $title,
    'alias' => $alias,
    'content' => $content,
    'excerpt' => $excerpt,
    'author' => $author,
    'sortid' => $sort,
    'date' => $postTime,
    'top '=> $top,
    'sortop '=> $sortop,
    'allow_remark' => $allow_remark,
    'hide' => $ishide,
    'checked' => $user_cache[UID]['ischeck'] == 'y' ? 'n' : 'y',
    'password' => $password
);

if ($blogid > 0) {//自动保存草稿后,添加变为更新
    $Log_Model->updateLog($logData, $blogid);
    $Tag_Model->updateTag($tagstring, $blogid);
    $dftnum = '';
} else{
    if (!$blogid = $Log_Model->isRepeatPost($title, $postTime)) {
        $blogid = $Log_Model->addlog($logData);
        $Tag_Model->addTag($tagstring, $blogid);
    }
    $dftnum = $Log_Model->getLogNum('y', '', 'blog', 1);
}

$CACHE->updateCache();

doAction('save_log', $blogid);

switch ($action) {
    case 'autosave':
        echo "autosave_gid:{$blogid}_df:{$dftnum}_";
        break;
    case 'add':
    case 'edit':
        $tbmsg = '';
        if ($ishide == 'y') {
            emDirect("./admin_log.php?pid=draft&active_savedraft=1");
        } else {
            if ($action == 'add' || isset($_POST['pubdf'])) {
                emDirect("./admin_log.php?active_post=1");//文章发布成功
            } else {
                emDirect("./admin_log.php?active_savelog=1");//文章保存成功
            }
        }
        break;
}
