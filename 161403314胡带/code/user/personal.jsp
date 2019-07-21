<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
    <%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<%
	//判断pn参数
	int pn = 1;
	
	int ceta = 0;
	String tmpString = request.getParameter("pn");
	//获取pn参数
	if (tmpString != null && tmpString.length() != 0) {
		if (Integer.parseInt(tmpString) > 0) {
			pn = Integer.parseInt(tmpString);
		}
	}
	//获取ceta参数
	tmpString = request.getParameter("ceta");
	if (tmpString != null && tmpString.length() != 0) {
		if (Integer.parseInt(tmpString) > 0) {
			ceta = Integer.parseInt(tmpString);
		}
	}
	
	
%>
<!DOCTYPE html>
<html>
  <head>
   <title>商品交易首页</title>
   <link href="//cdn.bootcss.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
   <script src="//cdn.bootcss.com/jquery/2.1.1/jquery.min.js"></script>
   <script src="//cdn.bootcss.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
   
   
  </head>
<body>
<nav class="navbar navbar-default" role="navigation">
   <div class="navbar-header">
      <a class="navbar-brand" href="#">商品交易</a>
   </div>
   <div>
    <ul class="nav navbar-nav">
         <li class="active"><a href="siteheader.jsp">首页</a></li>
         <li><a href="book.jsp">书籍</a></li>
         <li><a href="lifegoods.jsp">生活用品</a></li>
         <li><a href="clothing.jsp">衣服鞋包</a></li>
         <li><a href="electronic.jsp">电子设备</a></li>
         
      </ul>
       <div>
      <form class="navbar-form navbar-left" role="search" length="100">
         <div class="form-group">
            <input type="text" class="form-control" placeholder="Search">
         </div>
         <button type="submit" class="btn btn-default">查询</button>
      </form>    
   </div>
     
<div class="profile navbar-nav">
<ul class="nav navbar-nav">
<li><a href="login.jsp">登录</a></li>
   <li><a href="register.jsp">注册</a></li>
   <li><a href="personal.jsp">个人中心</a></li>
</ul>
</div>
   </div>
   </nav>
   
 
   <div class="container">
		<div class="row">
			<div class="col-md-3">
				<div class="row">
					<div class="col-md-12">
						<div class="list-group">
							<span class="list-group-item list-group-item-info">个人中心</span> 
							
							 <a href="personal.jsp?ceta=0"
								class="list-group-item <%=ceta == 0 ? "active" : ""%>"><span
								class="badge"></span>个人信息</a> <a href="personal.jsp?ceta=1"
								class="list-group-item <%=ceta == 1 ? "active" : ""%>"><span
								class="badge"></span>购物车</a> <a href="personal.jsp?ceta=2"
								class="list-group-item <%=ceta == 2 ? "active" : ""%>"><span
								class="badge"></span>购买记录</a> 
						</div>
					</div>
				</div>
			</div>
			
			<div class="col-md-8">
				<div class="list-group">
					<%
						switch (ceta) {
						case 0:
							out.println("<span class=\"list-group-item list-group-item-info\">个人中心-个人信息</span>");
						
							break;
						case 1:
							out.println("<span class=\"list-group-item list-group-item-info\">个人中心-购物车</span>");
							
							break;
						case 2:
							out.println("<span class=\"list-group-item list-group-item-info\">个人中心-购买记录</span>");
						
							break;
							}
					%>
					
					<div class="list-group-item">没有个人信息，请前往注册！</div>
			
			</body>
			</html>