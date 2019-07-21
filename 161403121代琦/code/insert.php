<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>增加课程</title>
<script language="javascript">
    function check(){
		var a=document.getElementById("C_start_time").value;
		var b=document.getElementById("C_over_time").value;
		

		alert(a);

		if(a>=b){
			alert("实验开始时间大于结束时间，非法！");
			
			document.form1.C_over_time.focus();
			document.form1.C_start_time.focus();
		}
		else  {
				form1.submit();
			}
		}
</script>
</head>

<body>
<form  action="insert_course.php" method="post" name="form1" id="form1">
<table align="center" border="1"  cellpadding="0" ><tr><td>课程号</td><td><input type="text" name="C_id" /></td><td>课程名</td><td><input type="text" name="C_name" /></td></tr>
<tr><td>开始时间</td><td><input type="text" name="C_start_time" id="C_start_time"  /></td><td>结束时间</td><td><input type="text" name="C_over_time" id="C_over_time" /></td></tr>
<tr><td>实验教室</td><td><input type="text" name="C_room" /></td><td>IP</td><td><input type="text" name="C_ip" /><td></tr>
<tr><td >课程所属部门：</td><td ><select name="department" ><option value="信息学院">信息学院</option><option value="数学院">数学院</option></select></td><td colspan="2"></td></tr>
<tr><td colspan="4" align="center"><input type="button" onclick="check()" name="submit1" id="submit1"  value="提交"/></td>
</table>
</form>
</body>
</html>
