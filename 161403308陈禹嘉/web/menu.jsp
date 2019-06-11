<%--
  Created by IntelliJ IDEA.
  User: YangYi
  Date: 2017/11/17
  Time: 11:40
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>左侧导航</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="style/adminStyle.css" rel="stylesheet" type="text/css" />

    <link rel="stylesheet" type="text/css" href="bootstrap/css/bootstrap.min.css"/>
    <script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="bootstrap/js/bootstrap.min.js"></script>
    <script src="js/public.js"></script>
</head>
<body style="background:#313131">
<div class="menu-list">
    <a href="main.jsp" target="mainCont" class="block menu-list-title center" style="border:none;margin-bottom:8px;color:#fff;">起始页</a>
    <ul>

        <li class="menu-list-title">
            <span>成绩管理</span>
            <i>◢</i>
        </li>
        <li>
            <ul class="menu-children">
                <li><a href="score_list.jsp" title="学生成绩列表" target="mainCont">学生成绩列表</a></li>
            </ul>
        </li>

        <li class="menu-list-title">
            <span>学生管理</span>
            <i>◢</i>
        </li>
        <li>
            <ul class="menu-children">
                <li><a href="student_list.jsp" title="学生列表" target="mainCont">学生列表</a></li>
            </ul>
        </li>
    </ul>
</div>
</body>
</html>
