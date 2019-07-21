<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page language="java" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>注册-商品交易网站</title>
<link href="http://apps.bdimg.com/libs/bootstrap/3.3.0/css/bootstrap.min.css" rel="stylesheet">
<link href="//cdn.bootcss.com/font-awesome/4.3.0/css/font-awesome.min.css" rel="stylesheet">
<script src="http://apps.bdimg.com/libs/jquery/2.0.0/jquery.min.js"></script>
<script src="http://apps.bdimg.com/libs/bootstrap/3.3.0/js/bootstrap.min.js"></script>
<script type="text/javascript" src="js/jquery.validate.min.js" ></script>
<script type="text/javascript" src="js/message.js" ></script>
<script type="text/javascript" src="jquery2/jquery.min.js"></script>
<script type="text/javascript">
$(document).ready(function(){ 
    $("#form1").submit(function(){
    	
    	 var id=$("#id").val();
    	    if(id.length==0){
    	        $("#idError").html("ID不能为空");
    	          return false;
    	         }    
    	
    var name=$("#name").val();
    if(name.length==0){
        $("#nameError").html("账号不能为空");
          return false;
         }    
             
         var password=$("#password").val();
         if(password.length==0){
            $("#passwordError").html("密码不能为空");
            return false;
             }           
             
       
       
         });
     
     });
 </script>

	</head>
	<body>
<div class="container">
		<div class="form row">
			<form class="form-horizontal col-sm-offset-3 col-md-offset-3"  method="post" action="../registerservlet" id="form1">
				<h3 class="form-title">注册账号</h3>
				<div class="col-sm-9 col-md-9">
				
				<div class="form-group">
						<i class="fa fa-user fa-lg"></i>
						<input class="form-control required" type="text" placeholder="ID" name="id" id="id"/>
						 <div id="idError" style="display:inline;color:red;"></div>
					</div>
				
					<div class="form-group">
						<i class="fa fa-user fa-lg"></i>
						<input class="form-control required" type="text" placeholder="用户名" name="name" id="name"/>
						 <div id="nameError" style="display:inline;color:red;"></div>
					</div>
					<div class="form-group">
							<i class="fa fa-lock fa-lg"></i>
							<input class="form-control required" type="password" placeholder="密码" id="password" name="password"/>
							<div id="passwordError" style="display:inline;color:red;"></div>
					</div>
					
					
					<div class="form-group">
						<input type="submit" class="btn btn-success pull-right" value="注册"/>
						<input type="submit" class="btn btn-info pull-left" id="back_btn" value="返回"  onclick="javascript:history.go(-1);"/>
					</div>
				</div>
			</form>
		</div>
		</div>
	
	</body>
</html>
		



