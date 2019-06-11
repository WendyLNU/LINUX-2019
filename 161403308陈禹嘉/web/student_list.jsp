<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/12/26
  Time: 17:18
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ include file="WEB-INF/taglib.jsp"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <title>学生列表</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <link href="style/adminStyle.css" rel="stylesheet" type="text/css"/>

    <link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>

    <script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
    <script type="text/javascript" src="layer/layer.js"></script>
    <style>
        html,
        body {
            width: 100%;
            height: 100%;
        }
    </style>
    <script src="js/jquery.js"></script>
    <script src="js/public.js"></script>

</head>
<body>
<div class="wrap">
    <div class="page-title">
        <span class="modular fl"><i></i><em>学生列表</em></span>
        <span class="modular fr">
            <a href="javascript:void(0);" onclick="addStudent()" class="pt-link-btn">
                +添加学生</a>
        </span>
    </div>
    <div class="operate">
        <strong>选择排序：</strong>

        <select class="inline-select" id="order" disabled="disabled">
            <option value="s_number">按学号排</option>
        </select>
        <input id="searchContent" type="text" class="textBox length-long" placeholder="请输入学号/姓名/性别进行查询……"/>
        <input type="button" value="查询" class="tdBtn" id="searchBtn"/>
    </div>
    <table class="list-style Interlaced" id="tableDate">
        <tr>
            <th class="center">序号</th>
            <th class="center">学号</th>
            <th class="center">姓名</th>
            <th class="center">性别</th>
            <th class="center">操作</th>
        </tr>
    </table>
</div>
<!-- BatchOperation -->
<div style="overflow:hidden;">
    <!-- Operation -->
    <%--<div class="BatchOperation fl">--%>
    <%--<input type="checkbox" id="del"/>--%>
    <%--<label for="del" class="btnStyle middle">全选</label>--%>
    <%--<input type="button" value="批量删除" class="btnStyle"/>--%>
    <%--</div>--%>

    <!-- turn page -->
    <div class="text-center">
        <div id="dataCount"></div>
        <ul class="pagination" id="pagination">
        </ul>
    </div>
</div>
</body>

<script type="text/javascript">
    var thisPage = 1;   //默认当前页面为首页
    var pageSize = 10;   //设置页面显示数据条数
    var searchContent = ""; //搜索内容

    //    首页数据加载
    $(document).ready(function () {
        getPageData();
    });

    //获取页面数据
    function getPageData() {
        var data = {
            thisPage: thisPage,
            pageSize: pageSize,
            searchContent: searchContent,
        };
        $.ajax({
            type: "post",
            url: "${pgContext}/getStudents",
            data: data,
            dataType: "json",
            success: function (jsonObj) {
                var jsonData = eval(jsonObj);

                var studentList = jsonData.list;    //提取学生成绩数据
                getPagination(jsonData);    //处理分页
                getStudentScoreData(studentList);      //处理数据
            }
        });
    }

    //获取学生成绩
    function getStudentScoreData(jsonData) {
        var studentList = eval(jsonData);
        $.each(studentList, function (index, student) {
            var Nob = index + 1;     //序号

            var studentId = student.id;
            var number = student.number;
            var name = student.name;
            var gender = student.gender;

            $("#tableDate").append(
                "<tr>" +
                "   <th class= 'center'>" + Nob + "</th>" +
                "   <th class= 'center'>" + number + "</th>" +
                "   <th class= 'center'>" + name + "</th>" +
                "   <th class= 'center'>" + gender + "</th>" +
                "   <th class= 'center'>" +
                "       <a href= 'javascript:void(0);' title= '编辑'onclick= 'editStudentInfo(" + number + ")'>" +
                "           <img src= 'images/icon_edit.gif'/></a>" +
                "       <a href= 'javascript:void(0);' title='删除' onclick= 'deleteStudentInfo(" + number + ")'>" +
                "           <img src= 'images/icon_drop.gif'/></a>" +
                "   </th>" +
                " </tr>"
            );
        });
    }

    //    获取分页信息
    function getPagination(jsonData) {
        var dataTotal = jsonData.dataTotal;     //提取记录总条数
        var start = jsonData.start; //提取从第几页开始显示页码
        var pageTotal = jsonData.pageTotal;     //提取页面总数
        var end = jsonData.end;     //提取页码显示到第几页
        var thisPg = jsonData.thisPage;   //提取当前显示的页面

        if (dataTotal > pageSize) {
            $("#dataCount").html(
                "共：" + dataTotal + " 条记录，本页显示：" + pageSize + " 条"
            );
        } else {
            $("#dataCount").html(
                "共：" + dataTotal + " 条记录"
            );
        }

        if (thisPg > 1) {
            $("#pagination").html(
                "<li><a href='/index.jsp'>首页</a></li>"
            );
            $("#pagination").append(
                "<li><a href='javascript:void(0);' onclick= 'getPageValue(" + (thisPg - 1) + ")'>上一页</a></li>"
            );
        } else {
            $("#pagination").html("");
        }
        for (var i = start; i <= end; i++) {

            $("#pagination").append(
                "<li><a href='javascript:void(0);' onclick= 'getPageValue(" + i + ")'>" + i + "</a></li>"
            );
        }

        if (thisPg < pageTotal) {
            $("#pagination").append(
                "<li ><a href='javascript:void(0);' onclick= 'getPageValue(" + (thisPg + 1) + ")'>下一页</a></li>"
            );
            $("#pagination").append(
                "<li><a href='javascript:void(0);' onclick= 'getPageValue(" + pageTotal + ")'>尾页</a></li>"
            );
        }

//        $("#pagination li a").click(function () {
//            $(this).parent().addClass("active");
//        })
    }

    //某个页面按钮被点击时，获取它所代表页面的页面内容
    function getPageValue(index) {

        var thisPg = index;
        var data = {
            order: order,
            thisPage: thisPg,
            pageSize: pageSize,
        }

        if (thisPage != 1) {
            refreshPageData();
        } else {
            location.href = "student_list.jsp";
        }
    }

    //刷新页面数据
    function refreshPageData() {
        var data = {
            thisPage: thisPage,
            pageSize: pageSize,
            searchContent: searchContent,
        };
        $.ajax({
            type: "post",
            url: "${pgContext}/getStudents",
            data: data,
            dataType: "json",
            success: function (jsonObj) {
                var jsonData = eval(jsonObj);

                var studentList = jsonData.list;    //提取学生成绩数据
                getPagination(jsonData);    //处理分页
                refreshStudentData(studentList);      //刷新成绩数据
            }
        });
    }

    //刷新学生数据
    function refreshStudentData(jsonData) {
        var studentList = eval(jsonData);

        $("#tableDate").html(
            "<tr>" +
            "   <th class= 'center'>序号</th>" +
            "   <th class= 'center'>学号</th>" +
            "   <th class= 'center'>姓名</th>" +
            "   <th class= 'center'>性别</th>" +
            "   <th class= 'center'>操作</th>" +
            "</tr>"
        );

        $.each(studentList, function (index, student) {
            var Nob = index + 1;     //序号

            var studentId = student.id;
            var number = student.number;
            var name = student.name;
            var gender = student.gender;

            $("#tableDate").append(
                "<tr>" +
                "   <th class= 'center'>" + Nob + "</th>" +
                "   <th class= 'center'>" + number + "</th>" +
                "   <th class= 'center'>" + name + "</th>" +
                "   <th class= 'center'>" + gender + "</th>" +
                "   <th class= 'center'>" +
                "       <a href= 'javascript:void(0);' title= '编辑'onclick= 'editStudentInfo(" + number + ")'>" +
                "           <img src= 'images/icon_edit.gif'/></a>" +
                "       <a href= 'javascript:void(0);' title='删除' onclick= 'deleteStudentInfo(" + number + ")'>" +
                "           <img src= 'images/icon_drop.gif'/></a>" +
                "   </th>" +
                " </tr>"
            );
        });
    }

    //查询
    $("#searchBtn").click(function () {
        searchContent = $("#searchContent").val();

        refreshPageData();
    });

    //编辑学生信息
    function editStudentInfo(studentNumber) {
        layer.open({        //在当前页面弹窗
            title: '编辑学生信息',
            type: 2,
            area: ['800px', '400px'],
            fix: false, //不固定
            maxmin: true,
            content: '${pgContext}/editStudentInfo?studentNumber=' + studentNumber,
            success: function (layero, index) {
//                AddLayero = layero;
//				        alert(AddLayero);
            },
            end: function () {
                location.reload();
            }
        });
    }

    //添加学生
    function addStudent() {
        layer.open({
            title: '添加学生',
            type: 2,
            area: ['800px', '400px'],
            fix: false, //不固定
            maxmin: true,
            content: '${pgContext}/student_add.jsp',
            success: function (layero, index) {
//                AddLayero = layero;
//				        alert(AddLayero);
            },
            end: function () {
                location.reload();
            }
        });
    }

    //删除学生
    function deleteStudentInfo(studentNumber) {
        var data = {
            studentNumber : studentNumber,
        };
        layer.confirm("确认要删除吗，删除后不能恢复", {title: "删除确认"},
            function (index) {
                layer.close(index);
                $.ajax({
                    url: "${pgContext}/deleteStudent",
                    type: "post",
                    data: data,
                    dataType: "json",
                    success: function (jsonObj) {
                        var jsonData = eval(jsonObj);
                        var res = jsonData.res;

                        if (res == 1) {
                            layer.msg("删除成功！", {
                                icon: 1,
                                time: 3000 //3秒关闭（如果不配置，默认是3秒）
                            });
                            location.reload();  //更新页面
                        } else {
                            layer.msg("删除失败，学生不存在或已被删除！", {
                                icon: 2,
                                time: 3000 //3秒关闭（如果不配置，默认是3秒）
                            });
                        }
                    }
                });
            }
        );
    }
</script>
</html>
