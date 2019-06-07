<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="com.domain.*"%>
<jsp:include   page="head.jsp" flush="true"/>
<%
	Problem problem = (Problem)request.getAttribute("problem");
%>
<!-- 提交代码模态框（Modal） -->
<div class="modal fade" id="SubmitCodeModal" tabindex="-1" role="dialog" 
    aria-labelledby="myModalLabel" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
              <div class="modal-header">
                 <button type="button" class="close" 
                    data-dismiss="modal" aria-hidden="true">
                       &times;            </button>
                 <h4 class="modal-title" id="myModalLabel">
                    Welcome!           </h4>
              </div>
              <form class="form-horizontal" role="form" method="POST" id="SubmitCodeform" action="Status?pid=<%=problem.getProblem_id()%>">
              <div class="modal-body">
                <div class="form-group" style="padding:15px;">
    <label for="name">Only C++ code</label>
    <textarea class="form-control" rows="20" name="code"></textarea>
  </div>     
                    
              </div>
              <div class="modal-footer">
                 <input type="button" class="btn btn-default" 
                    data-dismiss="modal" value="关闭"></input>
                 <input type="submit" class="btn btn-primary" value="提交"></input>
              </div>
              </form> 
        </div>
           <!-- /.modal-content -->
    </div>
    <!-- /.modal -->
</div>
<div class="jumbotron" style="padding-top: 10px">

 <h3><span><%=problem.getProblem_id() %></span> - <span><%=problem.getTitle() %></span></h3>

 <div class="row">

     <div class="col-xs-9" style="padding: 15px;padding-left: 18px;">
        <font color="#7CA9ED" size="5px">Problem Description</font>
        <div  class="page_content" style="padding:5px">
        <%=problem.getDescription() %>
        </div>
        <font color="#7CA9ED" size="5px">Input</font>
        <div  class="page_content" style="padding:5px"><%=problem.getInput() %></div>
        <font color="#7CA9ED" size="5px">Output</font>
        <div  class="page_content" style="padding:5px"><%=problem.getOutput() %></div>
        <font color="#7CA9ED" size="5px">Sample</font>
        <div class="page_content" style="padding:5px">
        输入样例
        <pre><%=problem.getSample_input() %></pre>
        输出样例
        <pre><%=problem.getSample_output() %></pre>
        <div style="margin-top: 15px;">
        <a href="#">编辑题目</a> &nbsp;|&nbsp; <a href="ManData?pid=<%=problem.getProblem_id() %>">数据管理</a>
        </div>
    </div>
     </div>
     
     <div class="col-xs-3" style="padding: 15px;">
       <center> <a href="#SubmitCodeModal" data-toggle="modal"><button type="button" class="btn btn-primary">提交代码</button></a></center>
       <div style="padding: 5px;padding-left: 15px; border: 1px solid;margin: 30px">
        Time limit : <%=problem.getTimelimit() %> ms<br>
        Memory limit : <%=problem.getSpacelimit()/1000.0 %> MB<br>
        Submitted : <%=problem.getSubmit() %><br>
        Accepted : <%=problem.getAccept() %><br>
       </div>
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