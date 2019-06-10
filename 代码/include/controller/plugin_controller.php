<?php
/**
 * 前台加载插件页面
 *
 * @copyright (c) Emlog All Rights Reserved
 */

class Plugin_Controller {
	function loadPluginShow($params) {
		$plugin = isset($params[1]) && $params[1] == 'plugin' ? addslashes($params[2]) : '' ;
		if (preg_match("/^[\w\-]+$/", $plugin) && file_exists(EMLOG_ROOT."/content/plugins/{$plugin}/{$plugin}_show.php")) {
			include_once("./content/plugins/{$plugin}/{$plugin}_show.php");
		}
	}
}
