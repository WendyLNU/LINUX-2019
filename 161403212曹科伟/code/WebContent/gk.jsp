<%@ page language="java" import="java.sql.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>管理</title>
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
}catch(ClassNotFoundException e)
{
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
     st=con.createStatement();
	 String sql="select * from "+tableName;
	 rs=st.executeQuery(sql);
	 out.println("快递详细信息");
	 out.println("<br>");
	 while(rs.next()){
		  
			out.println("<tr>");
			out.println("<td>"+rs.getString("number")+"</td>");
			out.println("<td>"+rs.getString("xingming")+"</td>");
			out.println("<td>"+rs.getString("shoujihao")+"</td>");
			out.println("<td>"+rs.getString("cfd")+"</td>");
			out.println("<td>"+rs.getString("jsd")+"</td>");
			out.println("<td>"+rs.getString("kd")+"</td>");
			out.println("<td>"+rs.getString("xz")+"</td>");
			out.println("<tr>");
		 
	 }
	 
	 
	 String sql4="select * from wangdian";
	 rs=st.executeQuery(sql4);
	 
	 out.println("<table border=1 >");
	    out.println("<tr>");
		out.println("<td>"+"出发地"+"</td>");
		out.println("<td>"+"接收地"+"</td>");
		out.println("<td>"+"时间"+"</td>");
		out.println("<td>"+"重量"+"</td>");
		out.println("<td>"+"价格"+"</td>");
		out.println("<tr>");
		 while(rs.next()){
				out.println("<tr>");
				out.println("<td>"+rs.getString("cfd")+"</td>");
				out.println("<td>"+rs.getString("jsd")+"</td>");
				out.println("<td>"+rs.getString("sj")+"</td>");
				out.println("<td>"+rs.getString("zl")+"</td>");
				out.println("<td>"+rs.getString("jg")+"</td>");
				out.println("<tr>");
			 
		}
	 out.println("快递信息");
	 out.println("<br>");
	 
	 
	 String sql1="select * from denglu";
	 rs=st.executeQuery(sql1);
	 
	 out.println("<table border=1 >");
	    out.println("<tr>");
		out.println("<td>"+"账号"+"</td>");
		out.println("<td>"+"密码"+"</td>");
		out.println("<tr>");
	 while(rs.next())
	 {
		   
		    out.println("<tr>");
			out.println("<td>"+rs.getString("name")+"</td>");
			out.println("<td>"+rs.getString("password")+"</td>");
			out.println("<tr>");
	 }
	 out.println("会员信息");
	 out.println("<br>");
	 
	 String sql2="select * from hezuohuoban";
	 rs=st.executeQuery(sql2);
	 
	 out.println("<table border=1 >");
	    out.println("<tr>");
		out.println("<td>"+"姓名"+"</td>");
		out.println("<td>"+"快递公司"+"</td>");
		out.println("<td>"+"联系方式"+"</td>");
		out.println("<td>"+"性别"+"</td>");
		out.println("<tr>");
	 while(rs.next())
	 {
		   
		    out.println("<tr>");
			out.println("<td>"+rs.getString("xingming")+"</td>");
			out.println("<td>"+rs.getString("kd")+"</td>");
			out.println("<td>"+rs.getString("dh")+"</td>");
			out.println("<td>"+rs.getString("xb")+"</td>");
			out.println("<tr>");
	 }
	 out.println("快递公司信息");
	 out.println("<br>");
	 
	 String sql3="select * from liuyanban";
	 rs=st.executeQuery(sql3);
	 
	 out.println("<table border=1 >");
	    out.println("<tr>");
		out.println("<td>"+"姓名"+"</td>");
		out.println("<td>"+"E-mail"+"</td>");
		out.println("<td>"+"主题"+"</td>");
		out.println("<td>"+"留言"+"</td>");
		out.println("<tr>");
	 while(rs.next())
	 {
		   
		    out.println("<tr>");
			out.println("<td>"+rs.getString("name")+"</td>");
			out.println("<td>"+rs.getString("E-mail")+"</td>");
			out.println("<td>"+rs.getString("title")+"</td>");
			out.println("<td>"+rs.getString("liuyan")+"</td>");
			out.println("<tr>");
	 }
	 out.println("留言信息");
	 out.println("<br>");
	 
	 
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