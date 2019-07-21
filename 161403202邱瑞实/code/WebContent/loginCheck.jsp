<%@ page language="java" pageEncoding="UTF-8"%>
<%@ page import="bean.Login"%>
<body>
	<jsp:useBean id="login" class="bean.Login">
		<jsp:setProperty name="login" property="username" param="username" />
		<jsp:setProperty name="login" property="password" param="pass" />
	</jsp:useBean>
	<% %>
	<script language="JavaScript">
var out=<%=login.check()%>
alert(out);

</script>

</body>
