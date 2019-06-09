
<?php 

  $file=$_FILES['file'];
  
  if($file['error']==UPLOAD_ERR_OK)
  {
	//  $extName=strtolower(end(explode('.',$file['name'])));
	  $filename=date("Ymdhis").".xlsx"/*.$extName*/;
	  $dest="uploads/".$filename;
	  move_uploaded_file($file['tmp_name'],$dest);
	  $c=1;
   }
   else
   {
	  $c=0;
   }

  $link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign");
  mysql_query("set names 'utf8'");
  
  require_once("PHPExcel/PHPExcel.php");
  require_once("PHPExcel/PHPExcel/IOFactory.php");
  require_once("PHPExcel/PHPExcel/Reader/Excel2007.php");
	  
  $objReader = PHPExcel_IOFactory::createReader('excel2007'); //use Excel5 for 2003 format 
  $excelpath=$dest;
  $objPHPExcel = $objReader->load($excelpath); 
  $sheet = $objPHPExcel->getSheet(0); 
  $highestRow = $sheet->getHighestRow();           //取得总行数 
  $highestColumn = $sheet->getHighestColumn(); //取得总列数
  
  //逐行循环读取excel，并加入分隔符。
  for($j=2;$j<=$highestRow;$j++)                        //从第二行开始读取数据
  { 
      $str="";
      for($k='A';$k<=$highestColumn;$k++)            //从A列读取数据
         { 
             $str .=$objPHPExcel->getActiveSheet()->getCell("$k$j")->getValue().'|*|';//读取单元格
         } 
      $str=mb_convert_encoding($str,'utf8','auto');//根据自己编码修改
      $strs = explode("|*|",$str);// echo $str . "<br />";
	  $sql="insert into course (C_id,C_name,C_start_time,C_over_time,C_room,C_ip,C_department) values ('{$strs[0]}','{$strs[1]}','{$strs[2]}','{$strs[3]}','{$strs[4]}','{$strs[5]}','{$strs[6]}');";


      if(!mysqli_query($link,$sql))
      {
         $b=0;
      }
	  else
	  $b=1;
 
  }
fopen($dest,'a+');
  if(!unlink($dest))
     $a=0;
  else
  	 $a=1;
	 
	if($b==1&&$c==1)
	 {
		 echo "导入成功！";
		 echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	 }
	 else
	 {
		 echo "导入失败！";
		 echo '<p align=center> <br><a href="student_main.php">返回</a></p>';
	 }
		 
	
	 
?>


	
	     
   
   
   