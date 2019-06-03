<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title>Home</title>
<meta name="description" content="">
<meta name="viewport"
	content="width=device-width, initial-scale=1, shrink-to-fit=no">
<meta name="robots" content="all,follow">
<!-- Bootstrap CSS-->
<link rel="stylesheet" href="vendor/bootstrap/css/bootstrap.min.css">
<!-- Font Awesome CSS-->
<link rel="stylesheet"
	href="vendor/font-awesome/css/font-awesome.min.css">
<!-- Fontastic Custom icon font-->
<link rel="stylesheet" href="css/fontastic.css">
<!-- theme stylesheet-->
<link rel="stylesheet" href="css/style.default.css"
	id="theme-stylesheet">
<!---mdui-->
<link rel="stylesheet" href="mdui-v0.4.2/css/mdui.min.css">
</head>
<body>
	<div class="page">
		<header class="header">
			<nav class="navbar">
				<div class="container-fluid">
					<div
						class="navbar-holder d-flex align-items-center justify-content-between">
						<div class="navbar-header">
							<a href="manager.jsp"
								class="navbar-brand d-none d-sm-inline-block">
								<div class="brand-text d-none d-lg-inline-block">
									<span>抽奖系统</span><strong>后台管理</strong>
								</div>
								<div class="brand-text d-none d-sm-inline-block d-lg-none">
									<strong>AM</strong>
								</div>
							</a>
							<!---隐藏标签-->
							<a id="toggle-btn" href="#" clascs="menu-btn active"><span></span><span></span></a>
						</div>
						<ul
							class="nav-menu list-unstyled d-flex flex-md-row align-items-md-center">
							<!--Search-->
							<li class="nav-item d-flex align-items-center"><a
								id="search" href="#"><i class="mdui-icon material-icons">&#xe8b6;</i></a>
							</li>
							<!--notifications-->
							<li class="nan -item dropdown"><a id="notifications"
								rel="nofollow" data-target="#" href="#" data-toggle="dropdown"
								aria-haspopup="true" aria-expanded="false" class="nav-link">
									<i class="fa fa-bell-o"> <span
										class="badge bg-red badge-corner">12</span>
								</i>
							</a></li>
							<li class="nav-item dropdown"><a id="messages"
								rel="nofollow" data-target="#" href="#" data-toggle="dropdown"
								aria-haspopup="true" aria-expanded="false" class="nav-link">
									<i class="fa fa-envelope-o"></i> <span
									class="badge bg-orange badge-corner">1</span>
							</a></li>
							<li class="nav-item"><a href="login.jsp"
								class="nav-link logout"> <span class="d-none d-sm-inline">Logout</span><i
									class="fa fa-sign-out"></i></a></li>
						</ul>
					</div>
				</div>
			</nav>
		</header>
		<div class="page-content d-flex align-items-stretch">
			<!-- Side Navbar -->
			<nav class="side-navbar">
				<!---用户图像-->
				<div class="sidebar-header d-flex align-items-center">
					<div class="avatar">
						<img src="img/favicon.ico" alt="X"
							class="img-fluid rounded-circle">
					</div>
					<div>
						<h1 class="h4">测试用户</h1>
					</div>
				</div>
				<!---menu-->
				<span class="heading">主菜单</span>
				<ul class="list-unstyled">
					<li class="active"><a href="manager.jsp"><i
							class="mdui-icon material-icons">&#xe8d2;</i>主界面</a></li>
					<li><a href="view.jsp"><i class="mdui-icon material-icons">&#xe8f0;</i>查看</a></li>
					<li><a href="history.jsp"><i
							class="mdui-icon material-icons">&#xe8f3;</i>历史记录</a></li>
					<li><a href="award.jsp"><i
							class="mdui-icon material-icons">&#xe42c;</i>抽奖网页编译</a></li>
				</ul>
			</nav>
			<div class="content-inner">
				<div class="mdui-container">
					<div class="mdui-row">
						<div class="mdui-col-xs-9">
							<header>
								<div class="mdui-container">
									<div class="mdui-typo">
										<center>
											<h1>编辑你的抽奖规则</h1>
										</center>
									</div>
								</div>
							</header>
							<div class="mdui-container">
								<div class="mdui-typo-title-opacity">开始编辑抽奖活动：</div>
							</div>
							<div class="mdui-divider"></div>
							<div class="mdui-col-xs-9">
								<div class="mdui-textfield mdui-textfield-floating-label">
									<label id="avticity_name" class="mdui-textfield-label">抽奖活动名称</label>
									<input class="mdui-textfield-input" type="text" />
								</div>
							</div>
							<div class="mdui-divider"></div>
							<div class="mdui-col-xs-9">
								<div class="mdui-textfield mdui-textfield-floating-label">
									<label id="total" class="mdui-textfield-label">请输入总人数</label> <input
										class="mdui-textfield-input" type="text" />
								</div>
							</div>
							<div class="mdui-divider"></div>
							<div class="mdui-divider"></div>
							<div class="mdui-divider"></div>
							<div id="award_list" class="mdui-container">
								<div id='award_row' class="mdui-row">
									<div class="mdui-col-xs-8 mdui-col-sm-6">
										<label id="awardname" class="mdui-textfield-label">请输入奖项名称</label>
										<input class="mdui-textfield-input" type="text" />
									</div>
									<div class="mdui-col-xs-4 mdui-col-sm-6">
										<label id="awardnum" class="mdui-textfield-label">请输入该奖项中奖人数</label>
										<input class="mdui-textfield-input" type="text" />
									</div>
								</div>
							</div>
							<div class="mdui-divider"></div>
							<div class="mdui-container">
								<div class="mdui-row-xs-2">
									<div class="mdui-col">
										<button
											class="mdui-btn mdui-btn-block mdui-color-theme-accent mdui-ripple"
											onclick="add()">添加</button>
									</div>
									<div class="mdui-col">
										<button
											class="mdui-btn mdui-btn-block mdui-color-theme-accent mdui-ripple"
											onclick="del()">删除</button>
									</div>
								</div>
							</div>
							<div class="mdui-divider-inset"></div>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
	<!-- Main File-->
	<script src="mdui-v0.4.2/js/mdui.min.js"></script>
	<script src="js/tianjia.js"></script>
</body>
</html>