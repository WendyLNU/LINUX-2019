<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/12/25
  Time: 20:18
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>
<head>
    <title>编辑学生成绩</title>

    <link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>

    <script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="layer/layer.js"></script>
</head>
<body>
<div class="row">
    <div class="col-sm-3"></div>
    <div class="text-center col-sm-6 panel panel-primary">
        <div class="row">
            <hr>
            <div class="row">
                <div class="text-center col-sm-4 ">学号：</div>
                <input type="text" id="studentNumber" value="${studentScores.number}"
                          disabled="disabled" class="col-sm-7">
            </div>
            <hr>
            <div class="row">
                <div class="text-center col-sm-4 ">名字：</div>
                <input type="text" id="studentName" value="${studentScores.name}"
                          disabled="disabled" class="col-sm-7">
            </div>
            <hr>

            <div class="row">
                <div class="text-center col-sm-4 ">java成绩：</div>
                <input type="text" id="java" value="${studentScores.java}" class="col-sm-7">
            </div>
            <hr>

            <div class="row">
                <div class="text-center col-sm-4 ">kotlin成绩：</div>
                <input type="text" id="kotlin" value="${studentScores.kotlin}" class="col-sm-7">
            </div>
            <hr>

            <div class="row">
                <div class="text-center col-sm-4 ">python成绩：</div>
                <input type="text" id="python" value="${studentScores.python}" class="col-sm-7">
            </div>
            <hr>

            <div class="row">
                <div class="text-center col-sm-4 ">php成绩：</div>
                <input type="text" id="php" value="${studentScores.php}" class="col-sm-7">
            </div>
            <hr>

            <div class="row">
                <div class="col-sm-3"></div>
                <div class="col-sm-3">
                    <input type="submit" id="submit" value="提交" class="btn-primary form-control ">
                </div>
                <div class="col-sm-3">
                    <input type="reset" value="重置" class="btn-primary form-control col-sm-3">
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
       var java = $("#java").val();
       var kotlin = $("#kotlin").val();
       var python = $("#python").val();
       var php = $("#php").val();

        if(studentNumber == null || studentNumber == ""){
            layer.msg("学号不能为空！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#studentNumber").css("border","1px solid red");
            $("#studentNumber").focus();
            return false;
        }
        if(java == null || java == ""){
            layer.msg("请填写java成绩！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#java").css("border","1px solid red");
            $("#java").focus();
            return false;
        }else if( java < 0 || java > 100){
            layer.msg("成绩只能在0~100之间", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#java").css("border","1px solid red");
            $("#java").focus();
            return false;
        }
        if(kotlin == null || kotlin == ""){
            layer.msg("请填写kotlin成绩！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#kotlin").css("border","1px solid red");
            $("#kotlin").focus();
            return false;
        }else if( kotlin < 0 || kotlin > 100){
            layer.msg("成绩只能在0~100之间", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#kotlin").css("border","1px solid red");
            $("#kotlin").focus();
            return false;
        }
        if(python == null || python == ""){
            layer.msg("请填写python成绩！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#python").css("border","1px solid red");
            $("#python").focus();
            return false;
        }else if( python < 0 || python > 100){
            layer.msg("成绩只能在0~100之间", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#python").css("border","1px solid red");
            $("#python").focus();
            return false;
        }
        if(php == null || php == ""){
            layer.msg("请填写python成绩！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#php").css("border","1px solid red");
            $("#php").focus();
            return false;
        }else if( php < 0 || php > 100){
            layer.msg("成绩只能在0~100之间", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#php").css("border","1px solid red");
            $("#php").focus();
            return false;
        }
        $("#java").css("border","1px solid #66ccff");
        $("#kotlin").css("border","1px solid #66ccff");
        $("#python").css("border","1px solid #66ccff");
        $("#php").css("border","1px solid #66ccff");

        var data = {
           studentNumber : studentNumber,
           java : java,
           kotlin : kotlin,
           python : python,
           php : php
       }
       $.ajax({
           url:"${pgContext}/studentScoresSave",
           type:"post",
           data:data,
           dataType: "json",
           success: function (jsonObj) {
               var jsonData = eval(jsonObj);
               var res = jsonData.res;

               if(res == 1){
                   layer.msg('添加成功', {
                       icon: 1,
                       time: 2000 //2秒关闭（如果不配置，默认是3秒）
                   }, function () {
                       var index = parent.layer.getFrameIndex(window.name); //先得到当前iframe层的索引
                       parent.layer.close(index); //再执行关闭
                   });
               }else if( res == 0){
                   layer.msg("添加失败，学生不存在或已被删除！", {
                       icon: 2,
                       time: 3000 //3秒关闭（如果不配置，默认是3秒）
                   });
                   return false;
               }
           }
       });
    });

</script>
</html>
