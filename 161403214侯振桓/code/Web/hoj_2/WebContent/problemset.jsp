<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="java.util.*" import="com.domain.*"%>
    
<jsp:include   page="head.jsp" flush="true"/>

<div class="row" >
<div class="col-xs-9" style="padding: 15px;">

<div class="panel panel-default">
<div class="panel-heading">
    <div class="panel-title">
    	题库
    <a href="addproblem.html" ><span class="label label-primary">+ problem</span></a>
    </div>
</div>
<table class="table table-striped">

    <thead>
        <tr>
            <th width="80">ID</th>
            <th class="header">Name</th>
            <th width="100">正确</th>
            <th width="100">提交</th>
        </tr>
    </thead>
    <tbody>
    <%
    if(request.getAttribute("problemList")!=null){
		List problemList = (List) request.getAttribute("problemList");
		List ac = (List) request.getAttribute("ac");
		List submited = (List) request.getAttribute("submited");
    	for(int i=0;i<problemList.size();i++)
    	{
    		Problem problem = (Problem)problemList.get(i);
    	
    %>
        <tr>
            <td><%=problem.getProblem_id() %></td>
            <% String temp = "ProblemPage?pid="+ problem.getProblem_id();%>
            <td><a href="<%=temp%>"><%=problem.getTitle() %></a></td>
            <td><%=ac.get(i) %></td>
            <td><%=submited.get(i) %></td>
        </tr>
      <%
    	}
	}
      %>
    </tbody>
</table>
</div>
<center>
<ul class="pagination">
    <li><a href="#">&laquo;</a></li>
    <li><a href="#">1</a></li>
    <li><a href="#">2</a></li>
    <li><a href="#">3</a></li>
    <li><a href="#">4</a></li>
    <li><a href="#">5</a></li>
    <li><a href="#">&raquo;</a></li>
</ul>
</center>
</div>

<div class="col-xs-3" style="padding: 15px;">
<div class="panel panel-default">
    <div class="panel-heading">
        <h2 class="panel-title">分类</h2>
    </div>
    <ul class="nav nav-pills nav-stacked">
        <li><a href="#">数据结构</a></li>
        <li><a href="#">动态规划</a></li>
        <li><a href="#">数论</a></li>
        <li><a href="#">图论</a></li>
        <li><a href="#">搜索</a></li>
    </ul>
</div>
</div>
</div>
<center>
<div id="footer" class="center">
    CopyRight by <a href="#">houzena</a> 2018
</div>
</center>
</div>
</body>
</html>