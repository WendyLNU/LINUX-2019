<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
<jsp:include   page="head.jsp" flush="true"/>

<div class="jumbotron" style="background-color: snow">
    <div class="row">
        <div class="col-xs-5" style="padding: 15px;">
        <div id="myCarousel" class="carousel slide">
                <!-- 轮播（Carousel）指标 -->
                <ol class="carousel-indicators">
                   <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
                   <li data-target="#myCarousel" data-slide-to="1"></li>
                   <li data-target="#myCarousel" data-slide-to="2"></li>
                </ol>   
                <!-- 轮播（Carousel）项目 -->
                <div class="carousel-inner">
                   <div class="item active">
                      <img src="img/1.jpg" alt="First slide">
                     
                   </div>
                   <div class="item">
                      <img src="img/2.png" alt="Second slide">
                      
                   </div>
                   <div class="item">
                      <img src="img/3.jpg" alt="Third slide">
                      
                   </div>
                </div>
                <!-- 轮播（Carousel）导航 -->
                <a class="carousel-control left" href="#myCarousel" 
                   data-slide="prev">&lsaquo;</a>
                <a class="carousel-control right" href="#myCarousel" 
                   data-slide="next">&rsaquo;</a>
        </div>
        </div>
        <div class="col-xs-7" style="padding: 15px;">
            <h3>在线评测平台 houzena-Online Judge <small>第一版</small></h3>
        </div>
    </div>
</div>
<center>

<jsp:include   page="foot.jsp" flush="true"/>
