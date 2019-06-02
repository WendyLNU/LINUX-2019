<%@ page language="java" import="java.sql.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>快递查询</title>
</head>
<body bgcolor="33ccff">
<center>
<h1>查询结果</h1><br>
<hr> 
	 
	<table border=1 align="center">
		<tr>
			<th>快递编号</th>
			<th>姓名</th>
			<th>手机号</th>
			<th>出发地</th>
			<th>接收地</th>
		    <th>快递单位</th>
		    <th>现在位置</th>
		</tr>
 	<%
String driverName="com.mysql.jdbc.Driver";
String userName="root";
String userPasswd="123456";
String dbName="bishe";
String tableName="chaxun";
String url="jdbc:mysql://localhost:3306/"+dbName;
Connection con=null; Statement st=null; ResultSet rs=null;
try
{
	Class.forName(driverName).newInstance();
}catch(ClassNotFoundException e){
System.out.print("Error loading Driver,不能加载驱动程序");
}
try
{
con=DriverManager.getConnection(url, "root", "123456");
}catch(SQLException er)
{
System.out.print("Error getConnection,不能连接数据库");
}
 try{
	  String number=request.getParameter("text");
	  st=con.createStatement();
	  String sql="select * from "+tableName+" where number ="+number;
	  rs=st.executeQuery(sql);

		if(rs.next()){
				out.println("<tr>");
				out.println("<td>"+rs.getString("number")+"</td>");
				out.println("<td>"+rs.getString("xingming")+"</td>");
				out.println("<td>"+rs.getString("shoujihao")+"</td>");
				out.println("<td>"+rs.getString("cfd")+"</td>");
				out.println("<td>"+rs.getString("jsd")+"</td>");
				out.println("<td>"+rs.getString("kd")+"</td>");
				out.println("<td>"+rs.getString("xz")+"</td>");
				out.println("<tr>");
			 
		}else{
			out.print("<script language='javascript'>alert('没有该编号！');history.back();</script>"); 
		}
    
rs.close();
st.close();
con.close();	
 }
 catch(SQLException er)
 {System.out.println("Error executeQuery,不能执行查询！");}
%>
</center>
</body>
</html>