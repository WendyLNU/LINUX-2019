<%@ page language="java" import="java.sql.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>查询结果</title>
</head>
<body bgcolor="33ccff">
<center>
<h1>查询结果</h1>
<br>
<hr>
<br>
<%
	request.setCharacterEncoding("UTF-8");
String driverName="com.mysql.jdbc.Driver";
String userName="root";
String userPasswd="123456";
String dbName="bishe";
String tableName="wangdian";
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
	 String n = request.getParameter("text1");
		String m = request.getParameter("text2");
		String zl = request.getParameter("zl");
		st = con.createStatement();
		 String sql="select * from "+tableName+" where cfd = '"+n + "' and jsd = '"+m+"'"+ " and zl = '"+zl+"'";
		rs = st.executeQuery(sql);
		if (rs.next()) {
			out.println("从"+n+"到"+m+"邮寄 "+zl+"斤快递的价格为："+rs.getString("jg"));
			 
		} else {
			out.println("<script language='javascript'>alert('请检查接收地或出发地！');</script>");
		}

		rs.close();
		st.close();
		con.close();
	} catch (SQLException er) {
		er.printStackTrace();
		System.out.println("Error executeQuery,不能执行查询！");
	}
%>
 



</body>
</html>