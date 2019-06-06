<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html><html><head>
   <title>支付页面</title>
   <link rel="stylesheet" href="//apps.bdimg.com/libs/bootstrap/3.3.0/css/bootstrap.min.css">
   <script src="//apps.bdimg.com/libs/jquery/2.1.1/jquery.min.js"></script>
   <script src="//apps.bdimg.com/libs/bootstrap/3.3.0/js/bootstrap.min.js"></script>
   </head>
   <body>
   
   <div class="container">
   
        <div class="form row">
            <div class="form-horizontal col-md-offset-3" id="login_form">
                <h3 class="form-title">请支付！</h3>
<div class="col-md-9">
   
   <form class="form-horizontal" role="form">
   <div class="form-group">
      <label for="number" class="col-sm-2 control-label">银行账号</label>
      <div class="col-sm-10">
         <input type="text" class="form-control" id="number" 
            placeholder="请输入账号">
      </div>
   </div>
   <div class="form-group">
      <label for="password" class="col-sm-2 control-label">密码</label>
      <div class="col-sm-10">
         <input class="form-control required" type="password" placeholder="密码" id="inputPassword" name="inputPassword" >
      </div>
   </div>
   
   <div class="form-group">
      <div class="col-sm-offset-2 col-sm-10">
         <button type="submit" class="btn btn-default">购买</button>
      </div>
   </div>
   
    </div>
            </div>
        </div>
    </div>
   
   </form>
   </body>
   </html>