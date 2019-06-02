<%@ page language="java" import="java.sql.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>编辑</title>
<body bgcolor="33ccff">
<center>
<h1>编辑结果</h1><br>
<hr> 
<table border=1 align="center">
		<tr>
			<th>出发地</th>
			<th>接收地</th>
			<th>时间</th>
			<th>重量</th>
			<th>价格</th>
		</tr>
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
	 String cfd=request.getParameter("cfd");
	 String jsd=request.getParameter("jsd");
	 String sj=request.getParameter("sj");
	 String jg=request.getParameter("jg");
    st=con.createStatement();
    if(sj!="")
    {
    String sql="update wangdian"+" set sj = '"+sj+ "' where cfd = '"+cfd + "' and jsd = '"+jsd+"'";
	st.executeUpdate(sql);
    }
    else if(jg!=""){
        String sql="update wangdian"+" set jg = '"+jg+ "' where cfd = '"+cfd + "' and jsd = '"+jsd+"'";
    	st.executeUpdate(sql);
    }
  
	 out.println("快递详细信息");
	 out.println("<br>");
	 rs=st.executeQuery("select * from wangdian");
	 while(rs.next()){
		 out.println("<tr>");
			out.println("<td>"+rs.getString("cfd")+"</td>");
			out.println("<td>"+rs.getString("jsd")+"</td>");
			out.println("<td>"+rs.getString("sj")+"</td>");
			out.println("<td>"+rs.getString("zl")+"</td>");
			out.println("<td>"+rs.getString("jg")+"</td>");
			out.println("<tr>"); 
		} 
    
rs.close();
st.close();
con.close();	
 }
 catch(SQLException er)
 {
	 er.printStackTrace();
	 System.out.println("Error executeQuery,不能执行编辑！");}
%>
</table>
</center>
</body>
</html>