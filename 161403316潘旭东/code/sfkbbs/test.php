<?php 
//5.4.0
echo PHP_VERSION;

if(version_compare(PHP_VERSION,'5.4.0')<0){
	exit('您的PHP版本为'.PHP_VERSION.'！我们的程序要求是PHP版本不低于5.4.0!');
}
?>