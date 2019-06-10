<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <title>少女前线-建造模拟器 by 命运の乐章</title>
    <link href="../vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="../vendor/metisMenu/metisMenu.min.css" rel="stylesheet">
    <link href="../dist/css/sb-admin-2.css" rel="stylesheet">
    <link href="../vendor/morrisjs/morris.css" rel="stylesheet">
    <link href="../vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <script src="../js/IOPSimulate_main.js"></script>
</head>

<body>
    <div id="wrapper">
        <!-- Navigation -->
        <nav class="navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
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
                            <h1 class="page-header">建造模拟器 <button type="button" data-toggle="tooltip" data-placement="bottom" title="数据参考自IOP公司制造统计网站 格里芬魔术真实复刻" class="btn btn-outline btn-default">?</button></h1>
                        </div>
                    </div>
                </div>
                <!--Setting-->
                <div class="row">
                    <div class="col-lg-10">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                建造
                            </div>
                            <div class="panel-body" id="panelSetting" style="background:url(../img/Produce-tdoll-normal.png) no-repeat right 15px bottom 15px">
                                <!-- Nav tabs -->
                                <ul class="nav nav-tabs">
                                    <li class="active">
                                        <a href="#NormalProduce" data-toggle="tab" onclick="swapImage(1)">人形普建</a>
                                    </li>
                                    <li>
                                        <a href="#HeavyProduce" data-toggle="tab" onclick="swapImage(2)">人形重建</a>
                                    </li>
                                    <li>
                                        <a href="#NormalEquipment" data-toggle="tab" onclick="swapImage(3)">装备普建</a>
                                    </li>
                                    <li>
                                        <a href="#HeavyEquipment" data-toggle="tab" onclick="swapImage(4)">装备重建</a>
                                    </li>
                                    <li>
                                        <a href="#ResourceLimit" data-toggle="tab" onclick="swapImage(5)">资源限制</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <!--NORMAL TDOLL-->
                                    <div class="tab-pane fade in active" id="NormalProduce">
                                        <div class="col-lg-12">
                                            <p>&nbsp</p>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setWeight(1)">通用 4442</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(2)">HG 1111</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(3)">AR 1441</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(4)">RF 4142</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(5)">SMG 4412</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(6)">MG 7614</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(7)">MG-Plus 7644</button>
                                            </p>
                                        </div>
                                        <!--Resource-->
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=30 id="Mw" onblur="checkValueNormal()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=30 id="Rw" onblur="checkValueNormal()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=30 id="Aw" onblur="checkValueNormal()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=30 id="Pw" onblur="checkValueNormal()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <p><select class="form-control" id="NTimes">
                                                    <option value=1>单次建造</option>
                                                    <option value=10>十连建造</option>
                                                </select></p>
                                        </div>
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-success" id="buttonNormal" onclick="addListMulti()">普通建造</button>
                                            </p>
                                        </div>
                                    </div>
                                    <!--HEAVY TDOLL-->
                                    <div class="tab-pane fade" id="HeavyProduce">
                                        <!--Fast-->
                                        <div class="col-lg-12">
                                            <p>&nbsp</p>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setWeightH(1)">低耗 4163</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightH(2)">普通 6264</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightH(3)">高耗 6664</button>
                                            </p>
                                        </div>
                                        <!--Resource-->
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=1000 id="MwH" onblur="checkValueHeavy()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=1000 id="RwH" onblur="checkValueHeavy()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=1000 id="AwH" onblur="checkValueHeavy()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=1000 id="PwH" onblur="checkValueHeavy()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <p><select class="form-control" id="NTimesH">
                                                    <option value=1>单次建造</option>
                                                    <option value=10>十连建造</option>
                                                </select></p>
                                            <p>
                                                <select class="form-control" id="HClass">
                                                    <option value=1>一档：人形契约x1 / 核心x3</option>
                                                    <option value=2>二档：人形契约x20 / 核心x5</option>
                                                    <option value=3>三档：人形契约x50 / 核心x10</option>
                                                </select>
                                            </p>
                                        </div>
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-warning" id="buttonHeavy" onclick="addListHMulti()">重型建造</button></p>
                                        </div>
                                    </div>
                                    <!--NORMAL EQUIP-->
                                    <div class="tab-pane fade" id="NormalEquipment">
                                        <div class="col-lg-12">
                                            <p>&nbsp</p>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setWeightE(1)">通用 150x4</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightE(2)">无瞄具 151x4</button>
                                            </p>
                                        </div>
                                        <!--Resource-->
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10 id="MwE" onblur="checkValueNormalE()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10 id="RwE" onblur="checkValueNormalE()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10 id="AwE" onblur="checkValueNormalE()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10 id="PwE" onblur="checkValueNormalE()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <p><select class="form-control" id="NTimesE">
                                                    <option value=1>单次建造</option>
                                                    <option value=10>十连建造</option>
                                                </select></p>
                                        </div>
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-info" id="buttonNormalE" onclick="addListEMulti()">普通建造</button>
                                            </p>
                                        </div>
                                    </div>
                                    <!--HEAVY EQUIP-->
                                    <div class="tab-pane fade" id="HeavyEquipment">
                                        <!--Fast-->
                                        <div class="col-lg-12">
                                            <p>&nbsp</p>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setWeightEH(1)">零类 0000</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightEH(2)">一类 2021</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightEH(3)">二类 0221</button>
                                                <button type="button" class="btn btn-default" onclick="setWeightEH(4)">全类 2222</button>
                                            </p>
                                        </div>
                                        <!--Resource-->
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=500 id="MwEH" onblur="checkValueHeavyE()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=500 id="RwEH" onblur="checkValueHeavyE()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=500 id="AwEH" onblur="checkValueHeavyE()">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=500 id="PwEH" onblur="checkValueHeavyE()">
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <p><select class="form-control" id="NTimesEH">
                                                    <option value=1>单次建造</option>
                                                    <option value=10>十连建造</option>
                                                </select></p>
                                            <p>
                                                <select class="form-control" id="EHClass">
                                                    <option value=1>一档：装备契约x1 / 核心x2</option>
                                                    <option value=2>二档：装备契约x20 / 核心x4</option>
                                                    <option value=3>三档：装备契约x50 / 核心x6</option>
                                                </select>
                                            </p>
                                        </div>
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-danger" id="buttonHeavyE" onclick="addListEHMulti()">重型建造</button></p>
                                        </div>
                                    </div>
                                    <!--LIMITATION-->
                                    <div class="tab-pane fade" id="ResourceLimit">
                                        <!--Resource-->
                                        <div class="col-lg-12">
                                            <div class="checkbox">
                                                <label>
                                                    <input type="checkbox" id="unLimitReso" checked onclick="releaseResoLimit()">
                                                    无限资源
                                                </label>
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力余量</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10000 id="MwOwn" disabled>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮余量</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10000 id="RwOwn" disabled>
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药余量</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10000 id="AwOwn" disabled>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件余量</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=10000 id="PwOwn" disabled>
                                            </div>
                                        </div>
                                        <div class="col-lg-12">
                                            <div class="checkbox">
                                                <label>
                                                    <input type="checkbox" id="unLimitCoCo" checked onclick="releaseCoCoLimit()">
                                                    无限契约核心
                                                </label>
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人形契约</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=100 id="ConOwn" disabled>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">装备契约</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=100 id="ConOwnE" disabled>
                                            </div>
                                        </div>
                                        <div class="col-lg-3">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">核心</span>
                                                <input type="text" class="form-control" placeholder="输入整数" value=100 id="CoreOwn" disabled>
                                            </div>
                                        </div>
                                        <div class="col-lg-12">
                                            <p>
                                                <button type="button" class="btn btn-primary" onclick="resetResoLimit()">重置资源限制</button>
                                            </p>
                                        </div>
                                    </div>

                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <!--Resource -->
                <div class="row">
                    <div class="col-lg-10">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                资源消耗
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <div class="table-responsive" id="resoChart"></div>
                            </div>
                        </div>
                    </div>
                </div>
                <!--Result -->
                <div class="row">
                    <div class="col-lg-10">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                建造列表
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <!-- Nav tabs -->
                                <ul class="nav nav-tabs">
                                    <li id="panelT" class="active">
                                        <a href="#TdollResult" data-toggle="tab">人形</a>
                                    </li>
                                    <li id="panelE" class="">
                                        <a href="#EquipmentResult" data-toggle="tab">装备</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <!--TDOLL RESULTS-->
                                    <div class="tab-pane fade in active" id="TdollResult">
                                        <div class="panel-body">
                                            <div class="col-lg-12">
                                                <label>显示条目</label>
                                                <label class="radio-inline">
                                                    <input type="radio" name="ExpanSwitch" id="showAllSwitch" value="option1" onclick="showAll()" checked>
                                                    <b><span style="color:dodgerblue">全部</span></b>
                                                </label>
                                                <label class="radio-inline">
                                                    <input type="radio" name="ExpanSwitch" id="showFiveSwitch" value="option2" onclick="showFive()">
                                                    <b><span style="color:darkorange">★★★★★</span></b>
                                                </label>
                                            </div>
                                            <div class="col-lg-12">
                                                <div class="panel-body">
                                                    <div class="table-responsive" id="sumChart"></div>
                                                </div>
                                                <div class="panel-body">
                                                    <div class="table-responsive" id="rankingChart" style='height:400px; overflow-y:scroll'></div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                    <!--EQUIPMENT RESULTS-->
                                    <div class="tab-pane fade" id="EquipmentResult">
                                        <div class="panel-body">
                                            <div class="col-lg-12">
                                                <label>显示条目</label>
                                                <label class="radio-inline">
                                                    <input type="radio" name="ExpanSwitchE" id="showAllSwitchE" value="option1" onclick="showAllE()" checked>
                                                    <b><span style="color:dodgerblue">全部</span></b>
                                                </label>
                                                <label class="radio-inline">
                                                    <input type="radio" name="ExpanSwitchE" id="showFiveSwitchE" value="option2" onclick="showFiveE()">
                                                    <b><span style="color:darkorange">★★★★★</span></b>
                                                </label>
                                                <label class="radio-inline">
                                                    <input type="radio" name="ExpanSwitchE" id="showFairy" value="option3" onclick="showFairy()">
                                                    <b><span style="color:red">妖精</span></b>
                                                </label>
                                            </div>
                                            <div class="col-lg-12">
                                                <div class="panel-body">
                                                    <div class="table-responsive" id="sumChartE"></div>
                                                </div>
                                                <div class="panel-body">
                                                    <div class="table-responsive" id="rankingChartE" style='height:500px; overflow-y:scroll'></div>
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

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="../vendor/jquery/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../vendor/bootstrap/js/bootstrap.min.js"></script>

    <!-- Metis Menu Plugin JavaScript -->
    <script src="../vendor/metisMenu/metisMenu.min.js"></script>

    <!-- Custom Theme JavaScript -->
    <script src="../dist/js/sb-admin-2.js"></script>
    <!-- Page-Level Demo Scripts - Notifications - Use for reference -->
    <script>
        // tooltip demo
        $('.tooltip-demo').tooltip({
            selector: "[data-toggle=tooltip]",
            container: "body"
        })
        // popover demo
        $("[data-toggle=popover]")
            .popover()
    </script>
</body>

</html>
