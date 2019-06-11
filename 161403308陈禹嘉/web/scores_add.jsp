<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/12/26
  Time: 0:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>

<html>
<head>
    <title>添加学生成绩</title>
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
            <div class="row" >
                <div class="text-center col-sm-4 ">学号：</div>
                <input type="text" id="studentNumber" class="col-sm-7" placeholder="请输入学生的学号">
            </div>
            <div id="studentNumberTip"></div>
            <hr>
            <div class="row">
                <div class="text-center col-sm-4 ">姓名：</div>
                <input type="text" id="studentName" disabled="disabled" class="col-sm-7">
            </div>
            <hr>
            <div class="row">
                <div class="col-sm-4">
                    选择科目:
                </div>
                <select class="col-sm-7" id="courseSelect">
                    <option value="">请选择科目</option>
                </select>
            </div>
            <hr>
            <div class="row">
                <div class="text-center col-sm-4 ">成绩：</div>
                <input type="text" id="studentScore" class="col-sm-7" placeholder="成绩只能是0~100">
            </div>
            <div id="studentScoreTip"></div>
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

    </div>
    <div class="col-sm-3"></div>
</div>

<script type="text/javascript">
    $(document).ready(function () {
        getCourses();
    });

    function getCourses() {
        $.ajax({
            url: "${pgContext}/getCourses",
            type: "post",
            dataType: "json",
            success: function (jsonObj) {
                var jsonData = eval(jsonObj);
                var courseList = jsonData.courseList;

                $.each(courseList, function (index, course) {
                    $("#courseSelect").append(
                        "<option value='"+course.number+"'>" + course.name + "</option>"
                    );
                })
            }
        })
    }

    $("#studentNumber").blur(function () {
        var studentNumber = $("#studentNumber").val();

        var data = {
            studentNumber: studentNumber
        }
        if (studentNumber == null || studentNumber == "") {
            $("#studentNumber").css("border","1px solid red");
            $("#studentNumberTip").html(
                "<div style='color: red'>学号不能为空！</div>"
            );
        }else {
            $.ajax({
                url: "${pgContext}/checkStudent",
                type: "post",
                data: data,
                dataType: "json",
                success: function (jsonObj) {
                    var jsonData = eval(jsonObj);
                    var isExist = jsonData.isExist;
                    var student = jsonData.student;

                    if(isExist == 1){
                        $("#studentNumber").css("border","1px solid #00FF66");

                        $("#studentNumberTip").html(
                            "<div style='color: #66ccff'>学号可用</div>"
                        );
                        $("#studentName").val(student.name);
                    }else {
                        $("#studentNumber").css("border","1px solid red");

                        $("#studentNumberTip").html(
                            "<div style='color: red'>此学生不存在！</div>"
                        );
                    }
                }
            })
        }
    });

    //提交数据
    $("#submit").click(function () {
        var studentNumber = $("#studentNumber").val();
        var courseNumber = $("#courseSelect").val();
        var grade = $("#studentScore").val();

        if(studentNumber == null || studentNumber == ""){
            layer.msg("学号不能为空！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#studentNumber").focus();
            return false;
        }
        if(courseNumber == null || courseNumber == ""){
            layer.msg("请选择课程！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });
            $("#courseNumber").focus();
            return false;
        }
        if(grade == null || grade == ""){
            layer.msg("请填写成绩！", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#studentScore").css("border","1px solid red");
            $("#studentScoreTip").html(
                "<div style='color: red'>请填写成绩！</div>"
            );

            $("#studentScore").focus();
            return false;
        }else if( grade < 0 || grade > 100){
            layer.msg("成绩只能在0~100之间", {
                icon: 2,
                time: 2000 //2秒关闭（如果不配置，默认是3秒）
            });

            $("#studentScore").css("border","1px solid red");
            $("#studentScoreTip").html(
                "<div style='color: red'>成绩只能是0到100之间！</div>"
            );
            $("#studentScore").focus();
            return false;
        }else {
            $("#studentScore").css("border","1px solid #00FF66");
            $("#studentScoreTip").html(
                "<div style='color: #66ccff'>成绩合理</div>"
            );
        }

        scoreSave( studentNumber, courseNumber, grade);

    });

    function scoreSave( studentNumber, courseNumber, grade) {

        var data = {
            studentNumber : studentNumber,
            courseNumber : courseNumber,
            grade : grade
        }
        $.ajax({
            url:"${pgContext}/scoreSave",
            type:"post",
            data:data,
            dataType:"json",
            success:function (jsonObj) {
                var jsonData = eval(jsonObj);

                var res = jsonData.res;

                if(res == 1){
                    layer.msg('添加成功', {
                        icon: 1,
                        time: 2000 //2秒关闭（如果不配置，默认是3秒）
                    }, function () {
//                        parent.reloadGrid();  //让父页面刷新显示数据
                        window.parent.location.reload(); //刷新父页面

                        var index = parent.layer.getFrameIndex(window.name); //先得到当前iframe层的索引
                        parent.layer.close(index); //再执行关闭
                    });
                }else if (res == 0){
                    layer.msg("添加失败，学生或是课程不存在！", {
                        icon: 2,
                        time: 3000 //3秒关闭（如果不配置，默认是3秒）
                    });
                    return false;
                }else if(res == -1){
                    layer.msg("添加失败，学号和课程号不能为空！", {
                        icon: 2,
                        time: 3000 //3秒关闭（如果不配置，默认是3秒）
                    });
                    return false;
                }
            }
        });
    }
    //重置
    $("#reset").click(function () {
        $("#studentNumber").val("");
        $("#studentName").val("");
        $("#courseSelect").val("");
        $("#studentScore").val("");
    });
</script>
</body>
</html>
