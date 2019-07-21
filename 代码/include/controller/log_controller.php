<?php
/**
 * 显示首页、内容
 *
 * @copyright (c) Emlog All Rights Reserved
 */

class Log_Controller {
    function display($params) {
        $Log_Model = new Log_Model();
        $CACHE = Cache::getInstance();

        $options_cache = Option::getAll();
        extract($options_cache);

        $page = isset($params[1]) && $params[1] == 'page' ? abs(intval($params[2])) : 1;
        
        $pageurl = '';
        $sqlSegment ='ORDER BY top DESC ,date DESC';
        $sta_cache = $CACHE->readCache('sta');
        $lognum = $sta_cache['lognum'];
        $pageurl .= Url::logPage();
        $total_pages = ceil($lognum / $index_lognum);
        if ($page > $total_pages) {
            $page = $total_pages;
        }
        $logs = $Log_Model->getLogsForHome($sqlSegment, $page, $index_lognum);
        $page_url = pagination($lognum, $index_lognum, $page, $pageurl);

        include View::getView('header');
        include View::getView('log_list');
    }

    function displayContent($params) {
        $comment_page = isset($params[4]) && $params[4] == 'comment-page' ? intval($params[5]) : 1;

        $Log_Model = new Log_Model();
        $CACHE = Cache::getInstance();

        $options_cache = $CACHE->readCache('options');
        extract($options_cache);

        $logid = 0 ;
        if (isset($params[1])) {
            if ($params[1] == 'post') {
                $logid = isset($params[2]) ? intval($params[2]) : 0;
            } elseif (is_numeric($params[1])) {
                $logid = intval($params[1]);
            } else {
                $logalias_cache = $CACHE->readCache('logalias');
                if (!empty($logalias_cache)) {
                    $alias = addslashes(urldecode(trim($params[1])));
                    $logid = array_search($alias, $logalias_cache);
                    if (!$logid) {
                        show_404_page();
                    }
                }
            }
        }

        $Comment_Model = new Comment_Model();

        $logData = $Log_Model->getOneLogForHome($logid);
        if ($logData === false) {
            show_404_page();
        }
        extract($logData);

        if (!empty($password)) {
            $postpwd = isset($_POST['logpwd']) ? addslashes(trim($_POST['logpwd'])) : '';
            $cookiepwd = isset($_COOKIE['em_logpwd_'.$logid]) ? addslashes(trim($_COOKIE['em_logpwd_'.$logid])) : '';
            $Log_Model->AuthPassword($postpwd, $cookiepwd, $password, $logid);
        }
        //meta
        switch ($log_title_style) {
            case '0':
                $site_title = $log_title;
                break;
            case '1':
                $site_title = $log_title . ' - ' . $blogname;
                break;
            case '2':
                $site_title = $log_title . ' - ' . $site_title;
                break;
        }
        $site_description = extractHtmlData($log_content, 90);
        $log_cache_tags = $CACHE->readCache('logtags');
        if (!empty($log_cache_tags[$logid])) {
            foreach ($log_cache_tags[$logid] as $value) {
                $site_key .= ','.$value['tagname'];
            }
        }
        //comments
        $verifyCode = ISLOGIN == false && $comment_code == 'y' ? "<img src=\"".BLOG_URL."include/lib/checkcode.php\" align=\"absmiddle\" /><input name=\"imgcode\" type=\"text\" class=\"input\" size=\"5\" tabindex=\"5\" />" : '';
        $ckname = isset($_COOKIE['commentposter']) ? htmlspecialchars(stripslashes($_COOKIE['commentposter'])) : '';
        $ckmail = isset($_COOKIE['postermail']) ? htmlspecialchars($_COOKIE['postermail']) : '';
        $ckurl = isset($_COOKIE['posterurl']) ? htmlspecialchars($_COOKIE['posterurl']) : '';
        $comments = $Comment_Model->getComments(0, $logid, 'n', $comment_page);

        include View::getView('header');
        if ($type == 'blog') {
            $Log_Model->updateViewCount($logid);
            $neighborLog = $Log_Model->neighborLog($timestamp);
            $tb = array();$tb_url = '';//兼容未删除引用模板
            include View::getView('echo_log');
        }elseif ($type == 'page') {
            $template = !empty($template) && file_exists(TEMPLATE_PATH . $template . '.php') ? $template : 'page';
            include View::getView($template);
        }
    }
}
