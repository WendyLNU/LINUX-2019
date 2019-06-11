<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/11/17
  Time: 14:38
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>后台登录</title>

    <link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>

    <script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="layer/layer.js"></script>
</head>

<body>

<div class="row">

    <div class="col-lg-12 text-center v-center">

        <h1>后台管理系统</h1>
        <br>
        <p class="lead">请输入您的账号和密码来登录</p>

        <br>
        <br>
        <br>

        <div class="col-lg-12">
            <%--隐藏框--%>
            <input type="hidden" name="return_url" id="return_url" value="${return_url}">
            <input type="hidden" name="login_flag" id="login_flag" value="${login_flag}">
            <%--隐藏域结束--%>

            <div class="input-group" style="width: 340px; text-align: center; margin: 0 auto;">
                <input class="form-control input-lg" title="Confidential signup."
                       placeholder="请输入账号" type="text" id="userName" name="userName">
                <span id="userNameTips"></span>
            </div>
            <div class="input-group" style="width: 340px; text-align: center; margin: 0 auto;">
                <input class="form-control input-lg" title="Confidential signup."
                       placeholder="请输入密码" type="password" id="password" name="password">
                <span id="passwordTips"></span>
            </div>
            <div>
                <input class="btn btn-lg btn-primary" type="button" id="submit" value="登录"
                       style="margin: 10px;">
                <a class="btn btn-lg btn-warning" href="index.jsp">返回</a>
            </div>
        </div>
    </div>
</div>

</body>

<script>
    var errorMsg = "";
    $(document).ready(function () {

        $("#submit").click(function () {
            var return_url = $("#return_url").val();
            var userName = $("#userName").val();
            var password = $("#password").val();

            if (isLogin()) {
                layer.msg("您处于登录状态，请不要再登录了！", {
                    icon: 2,
                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                });
                return false;
            } else {
                if (userName == null || userName == "") {
                    return false;
                } else if (password == null || password == "") {
                    return false;
                } else {
                    var data = {
                        userName: userName,
                        password: password,
                        return_url: return_url
                    }
                    $.ajax({
                        type: "post",
                        url: "${pgContext}/loginServlet",
                        data: data,
                        dataType: "json",
                        success: function (jsonData) {
                            var data = eval(jsonData);
                            var res = data.login_flag;
                            var return_url = data.return_url;

                            if (res == 'success') {
                                layer.msg("主人，欢迎您的到来~", {
                                    icon: 1,
                                    time: 2000 //3秒关闭（如果不配置，默认是3秒）
                                });
                                if (return_url != null && return_url != '/login.jsp' && return_url != '') {
                                    location.href = return_url;
                                } else {
                                    location.href = "${pgContext}/index.jsp";
                                }
                            } else {
                                layer.msg("账号或密码错误，请重新输入~", {
                                    icon: 2,
                                    time: 3000 //3秒关闭（如果不配置，默认是3秒）
                                });
                                $("#userName").focus();
                                $("#userName").css("border","1px solid red");
                            }
                        }
                    })
                }
            }

        })
    });

    //    验证用户是否已经登录
    function isLogin() {
        var flag = $("#login_flag").val();
        if (flag == 'success') {
            return true;
        } else {
            return false;
        }
    }

    $("#userName").blur(function () {

        var userName = $("#userName").val();

        if (userName == null || userName == "") {
            errorMsg = "请输入账号！";
            $("#userNameTips").html("<span style='color: red'>" + errorMsg + "</span>");
            $("#userName").focus();
            $("#userName").css("border","1px solid red");
        } else {
            $("#userNameTips").html("");
        }
    })
    $("#password").blur(function () {
        var userName = $("#password").val();

        if (userName == null || userName == "") {
            errorMsg = "请输入密码！";
            $("#passwordTips").html("<span style='color: red'>" + errorMsg + "</span>");
            $("#password").focus();
            $("#password").css("border","1px solid red");
        } else {
            $("#passwordTips").html("");
        }
    })

</script>
</html>
