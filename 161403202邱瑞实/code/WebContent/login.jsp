<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%
String path=request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<base href="<%=basePath%>">
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8"/>
    <title>幸运抽奖系统登录</title>
    <style>
        body{
            background: #ebebeb;
            font-family: "Helvetica Neue","Hiragino Sans GB","Microsoft YaHei","\9ED1\4F53",Arial,sans-serif;
            color: #222;
            font-size: 12px;
        }
        *{padding: 0px;margin: 0px;}
        .top_div{
            background: #008ead;
            width: 100%;
            height: 400px;
        }
        .ipt{
            border: 1px solid #d3d3d3;
            padding: 10px 10px;
            width: 290px;
            border-radius: 4px;
            padding-left: 35px;
            -webkit-box-shadow: inset 0 1px 1px rgba(0,0,0,.075);
            box-shadow: inset 0 1px 1px rgba(0,0,0,.075);
            -webkit-transition: border-color ease-in-out .15s,-webkit-box-shadow ease-in-out .15s;
            -o-transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;
            transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s
        }
        .ipt:focus{
            border-color: #66afe9;
            outline: 0;
            -webkit-box-shadow: inset 0 1px 1px rgba(0,0,0,.075),0 0 8px rgba(102,175,233,.6);
            box-shadow: inset 0 1px 1px rgba(0,0,0,.075),0 0 8px rgba(102,175,233,.6)
        }
        .u_logo{
            background: url("img/images-login/username.png") no-repeat;
            padding: 10px 10px;
            position: absolute;
            top: 43px;
            left: 40px;
        }
        .p_logo{
            background: url("img/images-login/password.png") no-repeat;
            padding: 10px 10px;
            position: absolute;
            top: 12px;
            left: 40px;
        }
        a{
            text-decoration: none;
        }
    </style>
    <script type="text/javascript">  
    function refresh() {  
        //IE存在缓存,需要new Date()实现更换路径的作用  
        document.getElementById("image").src="image.jsp?"+new Date();  
    }  
</script> 
</head>
<body>
<form action="UserLogin"method="post">
<div class="top_div"></div>
<div style="width: 400px;height: 200px;margin: auto auto;background: #ffffff;text-align: center;margin-top: -100px;border: 1px solid #e7e7e7">
    <p style="padding: 30px 0px 10px 0px;position: relative;">
        <input class="ipt" type="text" placeholder="请输入用户名或邮箱"name="username">
    </p>
    <p style="position: relative;">
        <span class="p_logo"></span>
        <input  class="ipt" type="password"  placeholder="请输入密码" name="pass">
    </p>
    <p style="position: relative;">
    <span class="p_logo"></span>
    <input  class ="ipt" type="text" name="code" maxlength="4"  placeholder="请输入验证码">  
        <img id="image" border="0"  onclick="refresh()" src="image.jsp" title="点击更换图片">
    </p>
    <div style="height: 50px;line-height: 50px;margin-top: 30px;border-top: 1px solid #e7e7e7;">
        <p style="margin: 0px 35px 20px 45px;">
           <span style="float: left"><a href="#" style="color:#ccc;">忘记密码?</a></span>
           <span style="float: right">
               <a href="register.jsp" style="color:#ccc;margin-right:10px;">注册</a>
               <input type="Submit"value="提交"style="background: #008ead;padding: 7px 10px;border-radius: 4px;border: 1px solid #1a7598;color: #FFF;font-weight: bold;">
              <!--  > <a href="manager.jsp" style="background: #008ead;padding: 7px 10px;border-radius: 4px;border: 1px solid #1a7598;color: #FFF;font-weight: bold;">Login</a><-->
           </span>
        </p>
    </div>
</div>
</form>
<div style="position: fixed;bottom: 0px;text-align: center;width: 100%;">
    Copyright ©2019。3.12
</div>
</body>
</html>