<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>

<head>
<title>hoj</title>
<meta charset="utf-8">
<link href="css/bootstrap.min.css" rel="stylesheet">
<script src="jquery-2.1.1/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
<script src="js/check.js"></script>
</head>

<body style="background-color:wheat">
<div class="container">
<!-- 登录模态框（Modal） -->
<div class="modal fade" id="LoginModal" tabindex="-1" role="dialog" 
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
              <form class="form-horizontal" role="form" method="POST" id="loginform" action="index.jsp" onsubmit="return loginsubmit();">
              <div class="modal-body">
                    <div class="form-group">
                            <label class="col-sm-2 control-label">用户名</label>
                            <div class="col-sm-6">
                               <input type="text" class="form-control" name="user_id" id="login_name" maxlength="20">
                            </div>
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label">密码</label>
                            <div class="col-sm-6">
                               <input type="password" class="form-control" name="password" id="passwd0" maxlength="20">
                            </div>
                    </div>
                    <div class="form-group">
                            <div class="col-sm-offset-2 col-sm-6">
                               <div class="checkbox">
                                  <label>
                                     <input type="checkbox"> 请记住我  </label>
                               </div>
                            </div>
                    </div>
                    <div class="col-sm-offset-2 "  id="div_login_check"></div>
                    
              </div>
              <div class="modal-footer">
                 <input type="button" class="btn btn-default" 
                    data-dismiss="modal" value="关闭"></input>
                 <input type="submit" class="btn btn-primary" value="登录"></input>
              </div>
              </form> 
        </div>
           <!-- /.modal-content -->
    </div>
    <!-- /.modal -->
</div>

<!-- 注册模态框（Modal） -->
<div class="modal fade" id="SignModal" tabindex="-1" role="dialog" 
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
              <form class="form-horizontal" role="form" method="POST" id="signform" action="index.jsp"  onsubmit="return signsubmit();">
              <div class="modal-body">
                    <div class="form-group">
                            <label class="col-sm-2 control-label">用户名</label>
                            <div class="col-sm-6">
                               <input type="text" class="form-control" name="user_id" placeholder="*" id="sign_name"maxlength="20">
                            </div>
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label" >昵称</label>
                            <div class="col-sm-6">
                               <input type="text" class="form-control" name="nick"  placeholder="*" id="sign_nickname"maxlength="20">
                            </div>
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label">密码</label>
                            <div class="col-sm-6">
                               <input type="password" class="form-control" name="password" id="passwd1" maxlength="20">
                            </div>
                            
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label">再次输入</label>
                            <div class="col-sm-6">
                               <input type="password" class="form-control" name="password2" id="passwd2" onblur="checkRePasswd()" maxlength="20">
                            </div>
                            <span  id="span_repasswd"></span>
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label">学校</label>
                            <div class="col-sm-6">
                               <input type="text" class="form-control" name="school" id="school">
                            </div>
                    </div>
                    <div class="form-group">
                            <label class="col-sm-2 control-label">邮箱</label>
                            <div class="col-sm-6">
                               <input type="text" class="form-control" name="email" id="email" placeholder="*">
                            </div>
                    </div>
                    <div class="col-sm-offset-2 "  id="div_sign_check"></div>             
              </div>
              <div class="modal-footer">
                 <input type="button" class="btn btn-default" 
                    data-dismiss="modal" value="关闭"></input>
                 <input type="submit" class="btn btn-primary" value="注册"></input>
              </div>
              </form> 
        </div>
           <!-- /.modal-content -->
    </div>
    <!-- /.modal -->
</div>

<nav class="navbar navbar-default" role="navigation">
    <div class="navbar-header">
        <a class="navbar-brand" >在线评测</a>
    </div>
    <div>
        <ul class="nav navbar-nav">
            <li><a href="index.jsp"><span class="glyphicon glyphicon-home"></span>首页</a></li>
            <li><a href="ProblemSet"><span class="glyphicon glyphicon-th-list"></span>题集</a></li>
            <li><a href="#"><span class="glyphicon glyphicon-signal"></span>总榜</a></li>
            <li><a href="contestlist.html"><span class="glyphicon glyphicon-flag"></span>比赛</a></li>
            <li><a href="StatusList"><span class="glyphicon glyphicon-ok-circle"></span>判题队列</a></li>
        </ul>
        <ul class="nav navbar-nav navbar-right">
        <% 
        	if(request.getParameter("user_id")!=null&&request.getMethod()!="GET")
        	{
        		session.setAttribute("user_id", request.getParameter("user_id"));
        		out.write("<li><a href=\"#\"><span class=\"glyphicon glyphicon-user\"></span>&nbsp");
        		out.write("<font color=\"orange\"> "+session.getAttribute("user_id")+"</font></a></li>");
        	}
        	else if(session.getAttribute("user_id")!=null)
        	{	out.write("<li><a href=\"#\"><span class=\"glyphicon glyphicon-user\"></span>&nbsp");
        		out.write("<font color=\"orange\"> "+session.getAttribute("user_id")+"</font></a></li>");
        	}
        	else
           {
        		out.write("<li><a href=\"#LoginModal\" data-toggle=\"modal\">登录</a></li>");
        		out.write("<li><a href=\"#SignModal\" data-toggle=\"modal\">注册</a></li>");
           }
       	   
		 %>
            &nbsp;&nbsp;&nbsp;
        </ul>
    </div>

</nav>