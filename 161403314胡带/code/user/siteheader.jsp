<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page language="java" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<!DOCTYPE html>
<html>
  <head>
   <title>商品交易首页</title>
   <link href="//cdn.bootcss.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
   <script src="//cdn.bootcss.com/jquery/2.1.1/jquery.min.js"></script>
   <script src="//cdn.bootcss.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
   
   
  </head>
<body>
<nav class="navbar navbar-default" role="navigation">
   <div class="navbar-header">
      <a class="navbar-brand" href="#">商品交易</a>
   </div>
   <div>
    <ul class="nav navbar-nav">
         <li class="active"><a href="siteheader.jsp">首页</a></li>
         <li><a href="book.jsp">书籍</a></li>
         <li><a href="lifegoods.jsp">生活用品</a></li>
         <li><a href="clothing.jsp">衣服鞋包</a></li>
         <li><a href="electronic.jsp">电子设备</a></li>
         
      </ul>
       <div>
      <form class="navbar-form navbar-left" role="search" length="100">
         <div class="form-group">
            <input type="text" class="form-control" placeholder="Search">
         </div>
         <button type="submit" class="btn btn-default">查询</button>
      </form>    
   </div>
     
<div class="profile navbar-nav">
<ul class="nav navbar-nav">
<li><a href="login.jsp">登录</a></li>
   <li><a href="register.jsp">注册</a></li>
    <li><a href="personal.jsp">个人中心</a></li>
</ul>
</div>
   </div>
   </nav>
   
   <div id="myCarousel" class="carousel slide">
   <!-- 轮播（Carousel）指标 -->
   <ol class="carousel-indicators">
      <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
      <li data-target="#myCarousel" data-slide-to="1"></li>
      <li data-target="#myCarousel" data-slide-to="2"></li>
   </ol>   
   <!-- 轮播（Carousel）项目 -->
   <div class="carousel-inner" >
      <div class="item active" >
         <img src="../images/1.jpg" alt="First slide" style="width:100%;height:320px">
      </div>
      <div class="item">
         <img src="../images/2.jpg" alt="Second slide" style="width:100%;height:320px" >
      </div>
      <div class="item">
         <img src="../images/3.jpg" alt="Third slide" style="width:100%;height:320px">
      </div>
   </div>
   <!-- 轮播（Carousel）导航 -->
   <a class="carousel-control left" href="#myCarousel" 
      data-slide="prev">&lsaquo;</a>
   <a class="carousel-control right" href="#myCarousel" 
      data-slide="next">&rsaquo;</a></div> </body></html>
      
     <div class="container">
        <div class="row jx">
            <img src="../images/8.jpg">
            <span style="font-size:20px">书籍</span>
        </div>
        <div>
        <HR  width="100%" SIZE=3>
        </div>

      <div class="row paddtop">
           <div class="col-md-3">
                <div class="thumbnail">
                    <img src="../images/4.jpg" alt="">
                    <p>人生海海</p>
                     <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
             购买            </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
          加入购物车         </a>
         </p>
                    <font color="red">&yen; 58</font>
                </div>
           </div>
           <div class="col-md-3">
               <div class="thumbnail">
                   <img src="../images/5.jpg" alt="">
                   <p>作家榜经典:月亮与六便士</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买          </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 46</font>
               </div>

           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/6.jpg" alt="">
                   <p>局外人</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
              购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 60</font>
               </div>
           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/7.jpg" alt="">
                   <p>人间失格</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
              加入购物车            </a>
         </p>
                   <font color="red">&yen; 88</font>
               </div>
           </div>


       <div class="row jx">
            <img src="../images/8.jpg">
            <span style="font-size:20px">生活用品</span>
        </div>
        <div>
        <HR  width="100%" SIZE=3>
        </div>

      <div class="row paddtop">
           <div class="col-md-3">
                <div class="thumbnail">
                    <img src="../images/9.jpg" alt="">
                    <p>真空不锈钢食物罐</p>
                     <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
             购买            </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
          加入购物车         </a>
         </p>
                    <font color="red">&yen; 299</font>
                </div>
           </div>
           <div class="col-md-3">
               <div class="thumbnail">
                   <img src="../images/10.jpg" alt="">
                   <p>简约办公室喝水杯子男</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买          </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 28.8</font>
               </div>

           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/11.jpg" alt="">
                   <p>茶具套装中式功夫茶具带茶盘 </p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
              购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 1118</font>
               </div>
           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/12.jpg" alt="">
                   <p> 快客杯 一壶一杯套装女性茶具</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
              加入购物车            </a>
         </p>
                   <font color="red">&yen; 258</font>
               </div>
           </div>
       
       
       <div class="row jx">
            <img src="../images/8.jpg">
            <span style="font-size:20px">衣服鞋帽</span>
        </div>
        <div>
        <HR  width="100%" SIZE=3>
        </div>

      <div class="row paddtop">
           <div class="col-md-3">
                <div class="thumbnail">
                    <img src="../images/13.jpg" alt="">
                    <p>休闲校园简约学院风背包</p>
                     <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
             购买            </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
          加入购物车         </a>
         </p>
                    <font color="red">&yen; 78</font>
                </div>
           </div>
           <div class="col-md-3">
               <div class="thumbnail">
                   <img src="../images/14.jpg" alt="">
                   <p>休闲鞋男跑步鞋</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买          </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 105</font>
               </div>

           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/15.jpg" alt="">
                   <p>月半晴连衣裙2019春夏季新品</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
              购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 128</font>
               </div>
           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/16.jpg" alt="">
                   <p>超媛男士翻领短袖T恤</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
              加入购物车            </a>
         </p>
                   <font color="red">&yen; 102</font>
               </div>
           </div>
       
       
       <div class="row jx">
            <img src="../images/8.jpg">
            <span style="font-size:20px">电子设备</span>
        </div>
        <div>
        <HR  width="100%" SIZE=3>
        </div>

      <div class="row paddtop">
           <div class="col-md-3">
                <div class="thumbnail">
                    <img src="../images/17.jpg" alt="">
                    <p>小天才儿童电话手表</p>
                     <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
             购买            </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
          加入购物车         </a>
         </p>
                    <font color="red">&yen; 1399</font>
                </div>
           </div>
           <div class="col-md-3">
               <div class="thumbnail">
                   <img src="../images/18.jpg" alt="">
                   <p>华为WS520增强版双千兆路由器 </p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买          </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 299</font>
               </div>

           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/19.jpg" alt="">
                   <p>便携式平板电脑</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
              购买           </a> 
            <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车           </a>
         </p>
                   <font color="red">&yen; 4990</font>
               </div>
           </div>
           <div class="col-md-3">

               <div class="thumbnail">
                   <img src="../images/20.jpg" alt="">
                   <p>黑色耳麦耳机</p>
                    <p>
            <a href="paysite.jsp" class="btn btn-primary" role="button">
               购买           </a> 
               <a href="shopcar0.jsp" class="btn btn-default" role="button">
               加入购物车          </a> 
                  
         </p>
                   <font color="red">&yen; 118</font>
               </div>
           </div>
           
             <nav style="text-align: center">
      <ul class="pagination">
    <li><a href="#">&laquo;</a></li>
    <li><a href="#">1</a></li>
    <li><a href="#">2</a></li>
    <li><a href="#">3</a></li>
    <li><a href="#">4</a></li>
    <li><a href="#">5</a></li>
    <li><a href="#">&raquo;</a></li>
</ul>
          </nav>
          </div>
       </div>
   </body>
   </html>