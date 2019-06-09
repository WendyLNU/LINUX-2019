<?php
include './PHPExcel/PHPExcel.php';
//创建对象
$excel = new PHPExcel();
//Excel表格式,这里简略写了8列
$letter = array('A','B','C','D','E','F','G');
//表头数组
$tableheader = array('课程号','课程名','开始时间','结束时间','教室','IP','学院');
//填充表头信息
for($i = 0;$i < 7;$i++) {
$excel->getActiveSheet()->setCellValue("$letter[$i]1","$tableheader[$i]");
}

$link=mysqli_connect("localhost","root","");
  mysqli_select_db($link,"sign")or die("数据链接失败！");
	mysqli_query($link,"set names 'utf-8'");
	
	$sql="select  * from course  order by C_id ";
 $result=mysqli_query($link,$sql);
$rows=mysqli_num_rows($result);  
$i=2;


while($row=mysqli_fetch_array($result))
  {		
			//$row['name']=iconv('gb2312','utf-8',$row['name']);
			//$row['danr']=iconv('gb2312','utf-8',$row['danr']);
		$excel->getActiveSheet()->setCellValueExplicit("A".$i, $row['C_id'], PHPExcel_Cell_DataType::TYPE_STRING)
								->setCellValue("B".$i,$row['C_name'])
								->setCellValueExplicit("C".$i,$row['C_start_time'], PHPExcel_Cell_DataType::TYPE_STRING)
								->setCellValue("D".$i,$row['C_over_time'])
								->setCellValue("E".$i, $row['C_room'])
								->setCellValue("F".$i, $row['C_ip'])
								->setCellValue("G".$i, $row['C_department']);
								$i++;											
	}


$write = new PHPExcel_Writer_Excel5($excel);

header("Pragma: public");
header("Expires: 0");
ob_end_clean();
header("Content-Type: application/vnd.ms-excel; charset=UTF-8"); 
header("Cache-Control:must-revalidate, post-check=0, pre-check=0");
header("Content-Type:application/force-download");

header("Content-Type:application/octet-stream");
header("Content-Type:application/download");;
header('Content-Disposition:attachment;filename="课程信息.xls"');
header("Content-Transfer-Encoding:binary");
$write->save('php://output');

?>