<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="utf-8">
    <title>少女前线工具 by 刘照林</title>
    <style>
        .table_mid {
            text-align: center;
        }

        .table_supporter {
            width: auto;
            text-align: center;
            margin: 10px;
            border: "0";
        }

        .td_supporter {
            width: 20%;
        }
    </style>
</head>

<body>
    <div id="wrapper">
        <!-- Navigation -->
       
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="index.html"><span style="color:#FF0066">少女前线工具</span> by 命运の乐章 (GF tools)</a>
            </div>
            <div class="navbar-default sidebar" role="navigation">
                <div class="sidebar-nav navbar-collapse">
                    <ul class="nav" id="side-menu">
                        <li class="sidebar-search">
                            <div class="input-group custom-search-form">
                                <input type="text" class="form-control" placeholder="Search...">
                                <span class="input-group-btn">
                                    <button class="btn btn-default" type="button">
                                        <i class="fa fa-search"></i>
                                    </button>
                                </span>
                            </div>
                        </li>
                        <li><a href="index.html"><i class="fa fa-home fa-fw"></i> 主页</a></li>
                        <li><a href="GFT_Database.html"><i class="fa fa-book fa-fw"></i> 资料库</a></li>
                        <li><a href="GFT_LogiRank.html"><i class="fa fa-briefcase fa-fw"></i> 后勤排序器</a></li>
                        <li><a href="GFT_LevelCal.html"><i class="fa fa-upload fa-fw"></i> 练级计算器</a></li>
                        <li><a href="GFT_IOPSimulate.html"><i class="fa fa-gears fa-fw"></i> 建造模拟器</a></li>
                        <li><a href="GFT_ChipCal.html"><i class="fa fa-delicious fa-fw"></i> 芯片计算器</a></li>
                        <li><a href="GFT_Echelon.html"><i class="glyphicon glyphicon-screenshot"></i> &nbsp阵形模拟器</a></li>
                        <li><a href="GFT_Stat.html"><i class="glyphicon glyphicon-stats"></i> &nbsp掉落统计</a></li>
                    </ul>
                </div>
            </div>
        </nav>
        <!-- Main Pages -->
        <div id="page-wrapper">
            <div class="container-fluid">
                <div class="row">
                    <div class="col-lg-12">
                        <div class="tooltip-demo">
                            <h1 class="page-header">掉落统计 <button type="button" class="btn btn-warning" id="btn_alert" onclick="showAlert()">本页须知</button></h1>
                        </div>
                    </div>
                    <div class="col-lg-12" id="info_alert" style="background:url(../img/GK-small.png) no-repeat right 50% center;"></div>
                    <div class="col-lg-6">
                        <div class="panel panel-default">
                            <div class="panel-heading">核心统计</div>
                            <div class="panel-body">
                                <h5>核心掉率(百分比取整)，显示战斗数多于<span style="color:darkorange" id="text_validnum"></span>的结果，单位：个数 / <b><span style="color:blue">战斗</span></b></h5>
                                <div id="placeholder" style="height:300px"></div>
                                <ul class="nav nav-tabs">
                                    <li class="active">
                                        <a href="#116" data-toggle="tab">11-6</a>
                                    </li>
                                    <li>
                                        <a href="#115" data-toggle="tab">11-5</a>
                                    </li>
                                    <li>
                                        <a href="#104e" data-toggle="tab">10-4E</a>
                                    </li>
                                    <li>
                                        <a href="#02" data-toggle="tab">0-2</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <div class="tab-pane fade in active" id="116">
                                        <h4></h4>
                                        <ul class="nav nav-pills">
                                            <li class="active">
                                                <a href="#116true" data-toggle="tab">搜救</a>
                                            </li>
                                            <li>
                                                <a href="#116false" data-toggle="tab">无搜救</a>
                                            </li>
                                        </ul>
                                        <h4></h4>
                                        <div class="tab-content">
                                            <div class="tab-pane fade in active" id="116true">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_116"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_116true"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_116true"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="116false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_116_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_116false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_116false"></tbody>
                                                </table>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="tab-pane fade" id="115">
                                        <h4></h4>
                                        <ul class="nav nav-pills">
                                            <li class="active">
                                                <a href="#115true" data-toggle="tab">搜救</a>
                                            </li>
                                            <li>
                                                <a href="#115false" data-toggle="tab">无搜救</a>
                                            </li>
                                        </ul>
                                        <h4></h4>
                                        <div class="tab-content">
                                            <div class="tab-pane fade in active" id="115true">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_115"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_115true"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_115true"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="115false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_115_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_115false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_115false"></tbody>
                                                </table>
                                            </div>
                                        </div>

                                    </div>
                                    <div class="tab-pane fade" id="104e">
                                        <h4></h4>
                                        <ul class="nav nav-pills">
                                            <li class="active">
                                                <a href="#104e7true" data-toggle="tab">7战+搜救</a>
                                            </li>
                                            <li>
                                                <a href="#104e7false" data-toggle="tab">7战</a>
                                            </li>
                                            <li>
                                                <a href="#104e6false" data-toggle="tab">6战</a>
                                            </li>
                                            <li>
                                                <a href="#104e5true" data-toggle="tab">5战+搜救</a>
                                            </li>
                                            <li>
                                                <a href="#104e5false" data-toggle="tab">5战</a>
                                            </li>
                                            <li>
                                                <a href="#104e4true" data-toggle="tab">4战+搜救</a>
                                            </li>
                                            <li>
                                                <a href="#104e4false" data-toggle="tab">4战</a>
                                            </li>
                                        </ul>
                                        <h4></h4>
                                        <div class="tab-content">
                                            <div class="tab-pane fade in active" id="104e7true">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e7"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e7true"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e7true"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e7false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e7_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e7false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e7false"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e6false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e6_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e6false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e6false"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e5true">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e5"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e5true"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e5true"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e5false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e5_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e5false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e5false"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e4true">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e4"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e4true"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e4true"></tbody>
                                                </table>
                                            </div>
                                            <div class="tab-pane fade" id="104e4false">
                                                <table class="table table_mid table-bordered table-hover">
                                                    <tbody>
                                                        <tr>
                                                            <td style="width:50%">战斗信息</td>
                                                            <td id="card_104e4_2"></td>
                                                        </tr>
                                                        <tr>
                                                            <td style="width:50%">掉落信息</td>
                                                            <td id="stat_104e4false"></td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                                <table class="table table_mid table-bordered table-hover table-striped">
                                                    <thead>
                                                        <th style="width:50%;text-align:center">核心人形</th>
                                                        <th style="width:50%;text-align:center">数量</th>
                                                    </thead>
                                                    <tbody id="table_104e4false"></tbody>
                                                </table>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="tab-pane fade" id="02">
                                        <h4>该部分不需要贡献数据</h4>
                                        <div class="tab-content">
                                            <table class="table table_mid table-bordered table-hover">
                                                <tbody>
                                                    <tr>
                                                        <td style="width:50%">战斗信息</td>
                                                        <td id="card_02"></td>
                                                    </tr>
                                                    <tr>
                                                        <td style="width:50%">掉落信息</td>
                                                        <td><span style="color:dodgerblue">8%</span> (精确数据) 搜救:无搜救</td>
                                                    </tr>
                                                </tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                                <div class="panel panel-default">
                                    <div class="panel-heading">
                                        <h4 class="panel-title">
                                            <a data-toggle="collapse" data-parent="#accordion" href="#supporter_panel_core">贡献者列表</a>
                                        </h4>
                                    </div>
                                    <div id="supporter_panel_core" class="panel-collapse collapse">
                                        <div class="panel-body">
                                            <table class="table_supporter">
                                                <tbody id="spt_1"></tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                            </div>

                        </div>
                    </div>
                    <div class="col-lg-6">
                        <div class="panel panel-default">
                            <div class="panel-heading">打捞统计</div>
                            <div class="panel-body">
                                <h5>单位：个数 / <b><span style="color:red">判定</span></b></h5>
                                <ul class="nav nav-tabs">
                                    <li class="active">
                                        <a href="#drag1" data-toggle="tab">2019/5/4打捞</a>
                                    </li>
                                    <li>
                                        <a href="#drag2" data-toggle="tab">主线战役</a>
                                    </li>
                                    <li>
                                        <a href="#drag3" data-toggle="tab">常驻活动</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <h4></h4>
                                    <div class="tab-pane fade in active" id="drag1">
                                        <h5></h5>
                                        <table class="table table_mid table-bordered table-hover">
                                            <thead>
                                                <th style="width:30%;text-align:center">打捞人形</th>
                                                <th style="width:20%;text-align:center">地点</th>
                                                <th style="width:25%;text-align:center">搜救Lv.10</th>
                                                <th style="width:25%;text-align:center">无搜救</th>
                                            </thead>
                                            <tbody id="table_drag1">
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:rgb(50, 250, 0)">★★★★ UMP40</span></td>
                                                    <td>1-6</td>
                                                    <td id="drag1_1_1"></td>
                                                    <td id="drag1_1_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>1-4E</td>
                                                    <td id="drag1_1_3"></td>
                                                    <td id="drag1_1_4"></td>
                                                </tr>
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:rgb(50, 250, 0)">★★★★ KLIN</span></td>
                                                    <td>2-6</td>
                                                    <td id="drag1_2_1"></td>
                                                    <td id="drag1_2_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>2-4E</td>
                                                    <td id="drag1_2_3"></td>
                                                    <td id="drag1_2_4"></td>
                                                </tr>
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:darkorange">★★★★★ DSR-50</span></td>
                                                    <td>3-6</td>
                                                    <td id="drag1_3_1"></td>
                                                    <td id="drag1_3_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>3-4E</td>
                                                    <td id="drag1_3_3"></td>
                                                    <td id="drag1_3_4"></td>
                                                </tr>
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:darkorange">★★★★★ MP7</span></td>
                                                    <td>4-6</td>
                                                    <td id="drag1_4_1"></td>
                                                    <td id="drag1_4_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>4-4E</td>
                                                    <td id="drag1_4_3"></td>
                                                    <td id="drag1_4_4"></td>
                                                </tr>
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:darkorange">★★★★★ TAC-50</span></td>
                                                    <td>5-6</td>
                                                    <td id="drag1_5_1"></td>
                                                    <td id="drag1_5_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>5-4E</td>
                                                    <td id="drag1_5_3"></td>
                                                    <td id="drag1_5_4"></td>
                                                </tr>
                                                <tr>
                                                    <td style="vertical-align:middle;"><span style="color:darkorange">★★★★★ M1887</span></td>
                                                    <td>6-6</td>
                                                    <td id="drag1_6_1"></td>
                                                    <td id="drag1_6_2"></td>
                                                </tr>
                                                <tr>
                                                    <td></td>
                                                    <td>6-4E</td>
                                                    <td id="drag1_6_3"></td>
                                                    <td id="drag1_6_4"></td>
                                                </tr>
                                            </tbody>
                                        </table>
                                    </div>
                                    <div class="tab-pane fade" id="drag2">
                                        <h5></h5>
                                        <table class="table table_mid table-bordered table-hover">
                                            <thead>
                                                <th style="width:20%;text-align:center">地点</th>
                                                <th style="width:30%;text-align:center">人形</th>
                                                <th style="width:25%;text-align:center">搜救Lv.10</th>
                                                <th style="width:25%;text-align:center">无搜救</th>
                                            </thead>
                                            <tbody id="table_drag_normal"></tbody>
                                        </table>
                                    </div>
                                    <div class="tab-pane fade" id="drag3">
                                        <h5></h5>
                                        <table class="table table_mid table-bordered table-hover">
                                            <thead>
                                                <th style="width:20%;text-align:center">地点</th>
                                                <th style="width:30%;text-align:center">人形</th>
                                                <th style="width:25%;text-align:center">搜救Lv.10</th>
                                                <th style="width:25%;text-align:center">无搜救</th>
                                            </thead>
                                            <tbody id="table_drag_resident"></tbody>
                                        </table>
                                    </div>
                                    <!-- supporter -->
                                    <div class="panel panel-default">
                                        <div class="panel-heading">
                                            <h4 class="panel-title">
                                                <a data-toggle="collapse" data-parent="#accordion" href="#supporter_panel">贡献者列表</a>
                                            </h4>
                                        </div>
                                        <div id="supporter_panel" class="panel-collapse collapse">
                                            <div class="panel-body">
                                                <table class="table_supporter">
                                                    <tbody id="spt_2"></tbody>
                                                </table>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>

                        </div>
                    </div>

                </div>

            </div>
        </div>
    </div>
   
</body>

</html>
