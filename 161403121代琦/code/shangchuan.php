<?php
  session_start();
  $admin_account=$_SESSION['access'];
  $date=date('Y-m-d');
  $title=$_POST['title'];
  $content=$_POST['content'];
  
  $file=$_FILES['file'];
  
  header("Content-type:text/html;charset=utf-8");
	//要创建的多级目录
	$path="./download/".$admin_account."/";
	//判断目录存在否，存在给出提示，不存在则创建目录
	if (!is_dir($path)){  
		//第三个参数是“true”表示能创建多级目录，iconv防止中文目录乱码
		$res=mkdir(iconv("UTF-8", "GBK", $path),0777,true); 
		if ($res){
			echo "目录 $path 创建成功";
		}else{
			echo "目录 $path 创建失败";
		}
	}
  
  
  if($file['error']==UPLOAD_ERR_OK)
  {
	  $extName=strtolower(end(explode('.',$file['name'])));
	  $filename=date("Ymdhis").".".$extName;
	  $dest=$path.$filename;
	  move_uploaded_file($file['tmp_name'],$dest);
	  $a=1;
   }
   else
   {
	   $a=0;
   }
 
  
  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysql_query("set names 'utf8'");
  
  $sql="update student set path='$path' where S_id='$admin_account' ";
  
  if (mysqli_query($link,$sql)&&$a=="1")
  {
    echo "增加成功!";
	 echo '<p align=center> <br><a href="chakanshiyan.php">返回</a></p>';
  }
  else
  {
    echo '增加失败!';	
	 echo '<p align=center> <br><a href="chakanshiyan.php">返回</a></p>';
	}
  mysqli_close($link);
?>
