<%@ page language="java" import="java.sql.*" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>提交</title>
</head>
<body  bgcolor="33ccff">
<%
request.setCharacterEncoding("UTF-8");
String driverName="com.mysql.jdbc.Driver";
String userName="root";
String userPasswd="123456";
String dbName="bishe";
String tableName="liuyanban";
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
String name=request.getParameter("name"); 
String mail=request.getParameter("e-mail"); 
String title=request.getParameter("title"); 
String liuyan=request.getParameter("content"); 
String str="'"+name+"'"+","+"'"+mail+"'"+","+"'"+title+"'"+","+"'"+"liuyan"+"'";
String sql="insert into liuyanban values("+str+")";
st=con.createStatement();
 
  try{
	 /*if(name=="")
	  {
		  out.print("<script language='javascript'>alert('请填写完整的信息');history.back();</script>"); 
	  }
	  else{*/
	 st.execute(sql);
	 out.print("<script language='javascript'>alert('提交成功');history.back();</script>"); 
	//  }
 }catch(SQLException er)
	{
 	 System.err.println("Error executeInsert,不能添加数据！");
	} 
//rs.close(); 
st.close();
con.close();
%>
</body>
</html>