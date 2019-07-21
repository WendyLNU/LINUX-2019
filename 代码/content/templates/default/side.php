<?php
/**
 * 侧边栏
 */
if (!defined('EMLOG_ROOT')) {
    exit('error!');
}
?>
<div class="col-md-4 col-md-push-1 sidebar">
    <ul class="well">
        <?php
        $widgets = !empty($options_cache['widgets1']) ? unserialize($options_cache['widgets1']) : array();
        doAction('diff_side');
        foreach ($widgets as $val) {
            $widget_title = @unserialize($options_cache['widget_title']);
            $custom_widget = @unserialize($options_cache['custom_widget']);
            if (strpos($val, 'custom_wg_') === 0) {
                $callback = 'widget_custom_text';
                if (function_exists($callback)) {
                    call_user_func($callback, htmlspecialchars($custom_widget[$val]['title']), $custom_widget[$val]['content']);
                }
            } else {
                $callback = 'widget_' . $val;
                if (function_exists($callback)) {
                    preg_match("/^.*\s\((.*)\)/", $widget_title[$val], $matchs);
                    $wgTitle = isset($matchs[1]) ? $matchs[1] : $widget_title[$val];
                    call_user_func($callback, htmlspecialchars($wgTitle));
                }
            }
        }
        ?>
    </ul>
</div>
