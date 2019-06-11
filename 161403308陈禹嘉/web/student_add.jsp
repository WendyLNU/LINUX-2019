<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/12/26
  Time: 18:04
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>
<html>
<head>
    <title>编辑学生信息</title>
    <link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>

    <script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="layer/layer.js"></script>
</head>
<div class="row">
    <div class="col-sm-3"></div>
    <div class="text-center col-sm-6 panel panel-primary">

        <div class="row">
            <hr>
            <c:if test="${not empty student.number}">
                <div class="row">
                    <div class="text-center col-sm-4 ">学号：</div>
                    <input type="text" id="studentNumber" value="${student.number}"
                           disabled="disabled" class="col-sm-7">
                </div>

                <hr>
                <div class="row">
                    <div class="text-center col-sm-4 ">名字：</div>
                    <input type="text" id="studentName" value="${student.name}" class="col-sm-7">
                </div>
                <hr>
                <div class="row">
                    <div class="text-center col-sm-4 ">性别：</div>
                    <input type="text" id="genderSelect" value="${student.gender}" class="col-sm-7">
                </div>
                <hr>
            </c:if>
            <c:if test="${empty student.number}">
                <div class="row">
                    <div class="text-center col-sm-4 ">学号：</div>
                    <input type="text" id="studentNumber"  class="col-sm-7">
                </div>

                <hr>
                <div class="row">
                    <div class="text-center col-sm-4 ">名字：</div>
                    <input type="text" id="studentName"  class="col-sm-7">
                </div>
                <hr>
                <div class="row">
                    <div class="text-center col-sm-4 ">性别：</div>
                    <select id="genderSelect" class="col-sm-7">
                        <option value="男">男</option>
                        <option value="女">女</option>
                    </select>
                </div>
                <hr>
            </c:if>
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

    </div>
    <div class="col-sm-3"></div>
</div>
</body>

<script type="text/javascript">
    $(document).ready(function () {

    });

    $("#submit").click(function () {
        var studentNumber = $("#studentNumber").val();
        var studentName = $("#studentName").val();
        var gender = $("#genderSelect").val();

        if (studentNumber == null || studentNumber == "") {
            layer.msg("学号不能为空！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#studentNumber").css("border", "1px solid red");
            $("#studentNumber").focus();
            return false;
        }
        if (studentName == null || studentName == "") {
            layer.msg("请填写学生姓名！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#studentName").css("border", "1px solid red");
            $("#studentName").focus();
            return false;
        }

        if (gender != "男" && gender != "女") {
            layer.msg("性别只能是男或女！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#genderSelect").css("border", "1px solid red");
            $("#genderSelect").focus();
            return false;
        }

        $("#studentName").css("border", "1px solid #66ccff");

        var data = {
            studentNumber: studentNumber,
            studentName: studentName,
            gender : gender
        }
        $.ajax({
            url: "${pgContext}/studentAdd",
            type: "post",
            data: data,
            dataType: "json",
            success: function (jsonObj) {
                var jsonData = eval(jsonObj);
                var res = jsonData.res;

                if (res == 1) {
                    layer.msg('添加成功！', {
                        icon: 1,
                        time: 2000 //2秒关闭（如果不配置，默认是3秒）
                    }, function () {
                        var index = parent.layer.getFrameIndex(window.name); //先得到当前iframe层的索引
                        parent.layer.close(index); //再执行关闭
                    });
                } else if (res == 0) {
                    layer.msg('学生信息已更新！', {
                        icon: 1,
                        time: 2000 //2秒关闭（如果不配置，默认是3秒）
                    }, function () {
                        var index = parent.layer.getFrameIndex(window.name); //先得到当前iframe层的索引
                        parent.layer.close(index); //再执行关闭
                    });
                }else {
                    layer.msg("添加失败，学号或姓名或性别为空！", {
                        icon: 2,
                        time: 3000 //3秒关闭（如果不配置，默认是3秒）
                    });
                    return false;
                }
            }
        });
    });
    //重置
    $("#reset").click(function () {
        $("#studentNumber").val("");
        $("#studentName").val("");
        $("#genderSelect").val("男");
    });
</script>
</html>
