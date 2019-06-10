<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/12/27
  Time: 19:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>

<link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>

<script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
<script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
<script type="text/javascript" src="layer/layer.js"></script>
<html>
<head>
    <title>修改密码</title>
</head>
<body>
<div class="row">
    <input id="adminName" type="hidden" value="${admin.name}">
    <hr>
    <div class="col-sm-2"></div>
    <div class="text-center col-sm-8 panel panel-primary">
        <hr>
        <div class="row ">
            <div class="col-sm-10 text-center">
                <div class="col-sm-4 text-center">
                    请输入旧密码：
                </div>
                <input type="password" class="col-sm-7" id="oldPassword" placeholder="输入旧密码">
            </div>
            <div class="col-sm-2"></div>
        </div>
        <hr>
        <div class="row">
            <div class="col-sm-10 text-center">
                <div class="col-sm-4 text-center">
                请输入新密码：
                </div>
                <input type="password" class="col-sm-7" id="newPassword" placeholder="输入旧密码">
            </div>
            <div class="col-sm-2"></div>
        </div>
        <hr>

        <div class="row">
            <div class="col-sm-10 text-center">
                <div class="col-sm-4 text-center">
                请再次输入新密码：
                </div>
                <input type="password" class="col-sm-7" id="newPasswordAgain" placeholder="再次输入新密码">
            </div>
            <div class="col-sm-2"></div>
        </div>
        <hr>

        <div class="row">
            <div class="col-sm-3"></div>
            <div class="col-sm-3">
                <input type="submit" id="submit" value="提交" class="btn-primary form-control ">
            </div>
            <div class="col-sm-3">
                <input type="reset" id="reset" value="重置" class="btn-primary form-control col-sm-3">
            </div>
            <div class="col-sm-3"></div>
        </div>
    </div>
    <div class="col-sm-2"></div>
</div>
</body>

<script type="text/javascript">

    $("#submit").click(function () {
        var name = $("#adminName").val();
        var oldPassword = $("#oldPassword").val();
        var newPassword = $("#newPassword").val();
        var newPasswordAgain = $("#newPasswordAgain").val();

        if(name == null || name == ""){
            layer.msg("您尚未登录，请先登录！", {
                icon: 2,
                time: 3000 //3秒关闭（如果不配置，默认是3秒）
            });
            location.href = "${pgContext}/login.jsp";
            return false;
        }else {
            if(oldPassword == null || oldPassword == ""){
                layer.msg("请输入旧密码！", {
                    icon: 2,
                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                });
                $("#oldPassword").css("border","1px solid red");
                $("#oldPassword").focus();
                return false;
            }

            if(newPassword == null || newPassword == ""){
                layer.msg("请输入新密码！", {
                    icon: 2,
                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                });
                $("#newPassword").css("border","1px solid red");
                $("#newPassword").focus();
                return false;
            }
            if( newPasswordAgain == null || newPasswordAgain == ""){
                layer.msg("请再次输入新密码！", {
                    icon: 2,
                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                });
                $("#newPasswordAgain").css("border","1px solid red");
                $("#newPasswordAgain").focus();
                return false;
            }

            if( newPassword != newPasswordAgain){
                layer.msg("两次密码输入不一致！", {
                    icon: 2,
                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                });
                $("#newPasswordAgain").css("border","1px solid red");
                $("#newPasswordAgain").focus();
                return false;
            }

            $("#oldPassword").css("border","1px solid #00FF66");
            $("#newPassword").css("border","1px solid #00FF66");
            $("#newPasswordAgain").css("border","1px solid #00FF66");

            var data ={
                name : name,
                oldPassword : oldPassword,
                newPassword : newPassword,
            }
            $.ajax({
                url:"${pgContext}/adminEdit",
                type:"post",
                data:data,
                dataType:"json",
                success:function (jsonObj) {
                    var jsonData = eval(jsonObj);
                    var res = jsonData.res;

                    if(res == 1){
                        layer.msg('修改成功！', {
                            icon: 1,
                            time: 2000 //2秒关闭（如果不配置，默认是3秒）
                        });
                    }else if (res == 0){
                        layer.msg('修改失败，输入密码不正确！', {
                            icon: 2,
                            time: 3000 //2秒关闭（如果不配置，默认是3秒）
                        });
                    }else {
                        layer.msg('修改失败，用户名不存在', {
                            icon: 2,
                            time: 3000 //2秒关闭（如果不配置，默认是3秒）
                        });
                    }
                }
            });
        }
    });
    
    //重置
    $("#reset").click(function () {
        $("#oldPassword").val("");
        $("#newPassword").val("");
        $("#newPasswordAgain").val("");
    });

    
</script>
</html>
