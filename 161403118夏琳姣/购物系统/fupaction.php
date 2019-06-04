<?php
define("DESTINATION_FOLDER", $HTTP_POST_VARS['upUrl']);
$newfile = $HTTP_POST_FILES['file']['name'];
if(is_file(DESTINATION_FOLDER . "/" . $HTTP_POST_FILES['file']['name'])) { 
	$spildname = explode(".", $HTTP_POST_FILES['file']['name']);	
	for ($i=1;$i<100;$i++) {
		if ($i<10) {
			$newname = $spildname[0].'0'.$i;
		}else{
			$newname = $spildname[0].$i;
		}
		$newfile = $newname.".".$spildname[1];
		if(!is_file(DESTINATION_FOLDER . "/" . $newfile)) {
			$i = 100;
		}		
	}
}
if(@copy($HTTP_POST_FILES['file']['tmp_name'],DESTINATION_FOLDER . "/" . $newfile)){
	echo "ok";
} else {
	echo "no";
}
?>
<script language = "JavaScript">
window.opener.<?php echo $HTTP_POST_VARS['useForm']; ?>.<?php echo $HTTP_POST_VARS['prevImg']; ?>.src = '<?php echo $HTTP_POST_VARS['upUrl']; ?>'+'/'+'<?php echo $newfile; ?>';
window.opener.<?php echo $HTTP_POST_VARS['useForm']; ?>.<?php echo $HTTP_POST_VARS['reItem']; ?>.value = '<?php echo $newfile; ?>';
window.close();
</Script>