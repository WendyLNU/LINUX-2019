<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="java.util.*" %>
<jsp:include   page="head.jsp" flush="true"/>
<div class="jumbotron" style="background-color: snow">
<div class="panel panel-default">
<div class="panel-heading">
    <div class="panel-title">
    	数据管理
    </div>
</div>
<table class="table table-striped">
<thead>
        <tr>
            <th width="25%"><center>Input</center></th>
            <th width="10%"><center>size</center></th>
            <th width="25%"><center>Output</center></th>
            <th width="10%"><center>size</center></th>
            <th width="30%"><center>Operation</center></th>
            
        </tr>
</thead>
<%
	if(request.getAttribute("fileMap")!=null){
	 Map<String,String> fileMap = (Map)request.getAttribute("fileMap");
	 for(String kv : fileMap.keySet()){
		 if(!kv.contains(".in")) continue;
		 String inFile = kv;
		 String inSize = fileMap.get(kv);
		 String outFile = kv.replaceAll(".in", ".out");
		 String outSize = fileMap.get(outFile);
		 String fileName = kv.replaceAll(".in", "");
%>
<tbody>
	<tr>
            <th width="25%"><center><%=inFile %></center></th>
            <th width="10%"><center><%=inSize %></center></th>
            <th width="25%"><center><%=outFile %></center></th>
            <th width="10%"><center><%=outSize %></center></th>
            <th width="30%"><center><a href="DeleteData?pid=<%=request.getParameter("pid") %>&fileName=<%=fileName%>">
            Delete</a>&nbsp;|&nbsp;<a href="DownLoadData?pid=<%=request.getParameter("pid") %>&fileName=<%=fileName%>">
            download</a></center></th>
            
        </tr>
</tbody>
<%
	 }
	}
%>
</table>

</div>
<div class="panel panel-default">
<div class="panel-heading">
    <div class="panel-title">
    	添加数据
    </div>
     <form class="form-inline" method="post" style="padding:15px" enctype="multipart/form-data" action="UpLoad?pid=<%=request.getParameter("pid") %>">
       <div class="form-group" >
      
      	<input type="file" name="file1" >
      	
   		</div>
   		<div class="form-group" >
      
      	
      	 <input type="submit" value="提交">
    
   		</div>

    </form>

</div>

</div>
</div>
<jsp:include   page="foot.jsp" flush="true"/>