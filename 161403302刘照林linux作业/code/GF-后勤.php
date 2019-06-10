<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    
    
    <title>少女前线-后勤排序器</title>

    <script type="text/javascript">
        window.onload = function () {
            var chart = document.getElementById("rankingChart");
            var tab = '点击 <span style="color:deepskyblue">按条件排序</span> 按钮，排序前十的结果将在这里显示';
            chart.innerHTML = tab;
        }
        function creatLogiData(ilevel, impw, iamm, irat, iprt, iitm1, iitm2, itime) {
            var logiData = new Object;
            logiData.level = ilevel;
            logiData.mpw = impw;
            logiData.amm = iamm;
            logiData.rat = irat;
            logiData.prt = iprt;
            logiData.itm1 = iitm1;
            logiData.itm2 = iitm2;
            logiData.time = itime;
            return logiData;
        }
        function setWeight(weightInfo) {
            var Mw = document.getElementById('Mw');
            var Aw = document.getElementById('Aw');
            var Rw = document.getElementById('Rw');
            var Pw = document.getElementById('Pw');
            switch (weightInfo) {
                case 1:
                    Mw.value = 1; Aw.value = 1; Rw.value = 1; Pw.value = 1; break;
                case 2:
                    Mw.value = 1; Aw.value = 1; Rw.value = 1; Pw.value = 3; break;
                case 3:
                    Mw.value = 4; Aw.value = 4; Rw.value = 4; Pw.value = 2; break;
                case 4:
                    Mw.value = 1; Aw.value = 0; Rw.value = 0; Pw.value = 0; break;
                case 5:
                    Mw.value = 0; Aw.value = 1; Rw.value = 0; Pw.value = 0; break;
                case 6:
                    Mw.value = 0; Aw.value = 0; Rw.value = 1; Pw.value = 0; break;
                case 7:
                    Mw.value = 0; Aw.value = 0; Rw.value = 0; Pw.value = 1; break;
            }
        }
        function setTime(timeInfo) {
            var Tr = document.getElementById('Tr');
            var Tm = document.getElementById('Tm');
            switch (timeInfo) {
                case 1:
                    Tr.value = 6; Tm.value = 12; break;
                case 2:
                    Tr.value = 4; Tm.value = 6; break;
                case 3:
                    Tr.value = 1; Tm.value = 3; break;
                case 4:
                    Tr.value = 0; Tm.value = 1.7; break;
                case 5:
                    Tr.value = 0; Tm.value = 24; break;
            }
        }
        function obeyLimit(Tr, Tm, logiDataEntry) {
            var MapLimit = parseFloat(document.getElementById('MapLimit').value);
            var s1 = parseFloat((logiDataEntry.level).substr(0, 1));
            var s2 = (logiDataEntry.level).substr(1, 1);
            var mplmt = false;
            if (s1 === 0) {
                if (MapLimit >= 4.5) mplmt = true;
            } else if (s1 === 1) {
                if (s2 === '-') mplmt = true;
                else {
                    s1 = 10 + parseInt(s2);
                    if (MapLimit >= s1) mplmt = true;
                }
            } else {
                if (MapLimit >= s1) mplmt = true;
            }
            if (logiDataEntry.time >= Tr && logiDataEntry.time <= Tm && mplmt) {
                return true;
            } else {
                return false;
            }
        }
        function haveItem(it1, it2, logiDataEntry) {
            var validNum = 0;
            if (it1 === it2) {
                if (it1 === 0) {
                    validNum += 2;
                } else {
                    if ((logiDataEntry.itm1 === "人形契约" || logiDataEntry.itm2 === "人形契约") && it1 === 1) {
                        validNum += 2;
                    } else if ((logiDataEntry.itm1 === "装备契约" || logiDataEntry.itm2 === "装备契约") && it1 === 2) {
                        validNum += 2;
                    } else if ((logiDataEntry.itm1 === "快速建造" || logiDataEntry.itm2 === "快速建造") && it1 === 3) {
                        validNum += 2;
                    } else if ((logiDataEntry.itm1 === "快速修复" || logiDataEntry.itm2 === "快速修复") && it1 === 4) {
                        validNum += 2;
                    } else if ((logiDataEntry.itm1 === "采购币" || logiDataEntry.itm2 === "采购币") && it1 === 5) {
                        validNum += 2;
                    }
                }
            } else {
                if (it1 === 0 || it2 === 0) {
                    validNum++;
                }
                if ((logiDataEntry.itm1 === "人形契约") && (it1 === 1 || it2 === 1)) {
                    validNum++;
                } else if ((logiDataEntry.itm1 === "装备契约") && (it1 === 2 || it2 === 2)) {
                    validNum++;
                } else if ((logiDataEntry.itm1 === "快速建造") && (it1 === 3 || it2 === 3)) {
                    validNum++;
                } else if ((logiDataEntry.itm1 === "快速修复") && (it1 === 4 || it2 === 4)) {
                    validNum++;
                } else if ((logiDataEntry.itm1 === "采购币") && (it1 === 5 || it2 === 5)) {
                    validNum++;
                }
                if ((logiDataEntry.itm2 === "人形契约") && (it1 === 1 || it2 === 1)) {
                    validNum++;
                } else if ((logiDataEntry.itm2 === "装备契约") && (it1 === 2 || it2 === 2)) {
                    validNum++;
                } else if ((logiDataEntry.itm2 === "快速建造") && (it1 === 3 || it2 === 3)) {
                    validNum++;
                } else if ((logiDataEntry.itm2 === "快速修复") && (it1 === 4 || it2 === 4)) {
                    validNum++;
                } else if ((logiDataEntry.itm2 === "采购币") && (it1 === 5 || it2 === 5)) {
                    validNum++;
                }
            }
            if (validNum === 2) return true;
            else return false;
        }

        function getChart(logiList, it1, it2, it1_text, it2_text, Tr, Tm) {
            var allEntry = 0;
            var listNum = 48;
            var chart = document.getElementById("rankingChart");
            var tab = '<table class="table table-striped table-bordered table-hover"><thead><tr><th>排行</th><th>关卡</th><th>人力/h</th><th>弹药/h</th><th>口粮/h</th><th>零件/h</th><th>道具1</th><th>道具2</th><th>时间(h)</th></tr></thead>';
            tab += '<tbody>';
            for (var i = 0; i < listNum && allEntry < 10; i++) {
                if (haveItem(it1, it2, logiList[i]) && obeyLimit(Tr, Tm, logiList[i])) {
                    tab += "<tr>"; tab += "<td>";
                    tab += ((allEntry + 1) + "");
                    tab += "</td>"; tab += "<td>";
                    tab += logiList[i].level;
                    tab += "</td>"; tab += "<td>";
                    tab += (logiList[i].mpw + "");
                    tab += "</td>"; tab += "<td>";
                    tab += (logiList[i].amm + "");
                    tab += "</td>"; tab += "<td>";
                    tab += (logiList[i].rat + "");
                    tab += "</td>"; tab += "<td>";
                    tab += (logiList[i].prt + "");
                    tab += "</td>"; tab += "<td>";
                    tab += logiList[i].itm1;
                    tab += "</td>"; tab += "<td>";
                    tab += logiList[i].itm2;
                    tab += "</td>"; tab += "<td>";
                    tab += (logiList[i].time + "");
                    tab += "</td>"; tab += "</tr>";
                    allEntry++;
                }
            }
            tab += '</tbody></table>';
            if (allEntry === 0) {
                tab = "";
                if (it1_text != '无' && it2_text != '无') {
                    if (it1_text != it2_text) {
                        tab += '没有既包含 <span style="color:#FF0066">';
                        tab += it1_text;
                        tab += '</span> 又包含<span style="color:#FF0066"> ';
                        tab += it2_text;
                        tab += ' </span>并且时间在 <span style="color:#FF0066">';
                        tab += Tr; tab += " ~ "; tab += Tm;
                        tab += '</span> 小时的后勤条目';
                    } else {
                        tab += '没有包含 <span style="color:#FF0066">';
                        tab += it1_text;
                        tab += ' </span>并且时间在 <span style="color:#FF0066">';
                        tab += Tr; tab += " ~ "; tab += Tm;
                        tab += '</span> 小时的后勤条目';
                    }
                } else if (it1_text === '无' && it2_text === '无') {
                    tab += '没有时间长于 <span style="color:#FF0066">';
                    tab += Tr; tab += " ~ "; tab += Tm;
                    tab += '</span> 小时的后勤条目';
                } else {
                    if (it1_text === '无') {
                        tab += '没有包含 <span style="color:#FF0066">';
                        tab += it2_text;
                        tab += ' </span>并且时间在 <span style="color:#FF0066">';
                        tab += Tr; tab += " ~ "; tab += Tm;
                        tab += '</span> 小时的后勤条目';
                    } else {
                        tab += '没有包含 <span style="color:#FF0066">';
                        tab += it1_text;
                        tab += ' </span>并且时间在 <span style="color:#FF0066">';
                        tab += Tr; tab += " ~ "; tab += Tm;
                        tab += '</span> 小时的后勤条目';
                    }
                }
            }
            chart.innerHTML = tab;
        }

        function getRanking() {
            var Mw = document.getElementById('Mw');
            var Aw = document.getElementById('Aw');
            var Rw = document.getElementById('Rw');
            var Pw = document.getElementById('Pw');
            var Tr = document.getElementById('Tr'); var Tm = document.getElementById('Tm');
            var Tr = parseFloat(Tr.value); var Tm = parseFloat(Tm.value);
            var Itm1 = document.getElementById('ItemNeed1');
            var idx1 = Itm1.selectedIndex;
            var it1 = parseInt(Itm1[idx1].value);
            var it1_text = Itm1[idx1].text;
            var Itm2 = document.getElementById('ItemNeed2');
            var idx2 = Itm2.selectedIndex;
            var it2 = parseInt(Itm2[idx2].value);
            var it2_text = Itm2[idx2].text;
            var logiList = [];
            logiList.push(creatLogiData("0-1", 0, 174, 174, 0, "快速修复", "快速建造", 0.83));
            logiList.push(creatLogiData("0-2", 183.3, 0, 0, 116.7, "人形契约", "—", 3));
            logiList.push(creatLogiData("0-3", 75, 75, 75, 20.8, "装备契约", "快速修复", 12));
            logiList.push(creatLogiData("0-4", 0, 50, 33.3, 31.3, "采购币", "—", 24));
            logiList.push(creatLogiData("1-1", 40, 120, 60, 0, "—", "—", 0.25));
            logiList.push(creatLogiData("1-2", 0, 80, 120, 0, "—", "—", 0.5));
            logiList.push(creatLogiData("1-3", 30, 0, 30, 10, "快速修复", "—", 1));
            logiList.push(creatLogiData("1-4", 80, 80, 0, 0, "人形契约", "—", 2));
            logiList.push(creatLogiData("2-1", 150, 0, 0, 45, "—", "—", 0.67));
            logiList.push(creatLogiData("2-2", 40, 133.3, 53.3, 0, "快速修复", "—", 1.5));
            logiList.push(creatLogiData("2-3", 2.5, 2.5, 2.5, 57.5, "快速修复", "快速建造", 4));
            logiList.push(creatLogiData("2-4", 0, 41.7, 100, 10, "人形契约", "—", 6));
            logiList.push(creatLogiData("3-1", 150, 0, 225, 0, "—", "—", 0.33));
            logiList.push(creatLogiData("3-2", 0, 160, 93.3, 40, "—", "—", 0.75));
            logiList.push(creatLogiData("3-3", 0, 200, 0, 0, "快速修复", "快速建造", 1.5));
            logiList.push(creatLogiData("3-4", 0, 0, 60, 60, "人形契约", "装备契约", 5));
            logiList.push(creatLogiData("4-1", 0, 185, 185, 0, "装备契约", "—", 1));
            logiList.push(creatLogiData("4-2", 0, 0, 0, 105, "快速建造", "—", 2));
            logiList.push(creatLogiData("4-3", 133.3, 91.7, 0, 0, "人形契约", "快速修复", 6));
            logiList.push(creatLogiData("4-4", 50, 50, 50, 18.8, "快速建造", "—", 8));
            logiList.push(creatLogiData("5-1", 0, 0, 200, 90, "—", "—", 0.5));
            logiList.push(creatLogiData("5-2", 0, 240, 120, 0, "快速修复", "—", 2.5));
            logiList.push(creatLogiData("5-3", 200, 100, 100, 0, "装备契约", "—", 4));
            logiList.push(creatLogiData("5-4", 14.3, 0, 0, 100, "人形契约", "—", 7));
            logiList.push(creatLogiData("6-1", 150, 150, 0, 50, "—", "—", 2));
            logiList.push(creatLogiData("6-2", 0, 66.7, 183.3, 33.3, "快速修复", "快速建造", 3));
            logiList.push(creatLogiData("6-3", 0, 0, 40, 100, "装备契约", "—", 5));
            logiList.push(creatLogiData("6-4", 66.7, 66.7, 66.7, 0, "采购币", "—", 12));
            logiList.push(creatLogiData("7-1", 260, 0, 260, 0, "—", "—", 2.5));
            logiList.push(creatLogiData("7-2", 0, 162.5, 0, 75, "人形契约", "快速修复", 4));
            logiList.push(creatLogiData("7-3", 163.6, 109.1, 109.1, 0, "装备契约", "—", 5.5));
            logiList.push(creatLogiData("7-4", 31.3, 31.3, 31.3, 75, "快速建造", "—", 8));
            logiList.push(creatLogiData("8-1", 150, 150, 150, 0, "装备契约", "—", 1));
            logiList.push(creatLogiData("8-2", 0, 0, 0, 150, "快速修复", "—", 3));
            logiList.push(creatLogiData("8-3", 66.7, 133.3, 133.3, 0, "快速修复", "快速建造", 6));
            logiList.push(creatLogiData("8-4", 166.7, 44.4, 44.4, 11.1, "人形契约", "—", 9));
            logiList.push(creatLogiData("9-1", 0, 0, 200, 100, "—", "—", 0.5));
            logiList.push(creatLogiData("9-2", 120, 0, 120, 66.7, "快速建造", "—", 1.5));
            logiList.push(creatLogiData("9-3", 166.7, 166.7, 0, 0, "人形契约", "—", 4.5));
            logiList.push(creatLogiData("9-4", 71.4, 128.6, 128.6, 0, "装备契约", "—", 7));
            logiList.push(creatLogiData("10-1", 210, 300, 0, 0, "—", "—", 0.67));
            logiList.push(creatLogiData("10-2", 0, 144, 108, 0, "人形契约", "快速建造", 1.67));
            logiList.push(creatLogiData("10-3", 0, 90, 90, 56.3, "快速修复", "快速建造", 5.33));
            logiList.push(creatLogiData("10-4", 66, 66, 66, 33, "装备契约", "—", 10));
            logiList.push(creatLogiData("11-1", 87.5, 262.5, 0, 0, "人形契约", "装备契约", 4));
            logiList.push(creatLogiData("11-2", 90, 135, 135, 0, "人形契约", "—", 4));
            logiList.push(creatLogiData("11-3", 0, 93.8, 187.5, 31.3, "快速修复", "—", 8));
            logiList.push(creatLogiData("11-4", 0, 165, 0, 90, "快速建造", "—", 10));
            logiList.sort(function (a, b) {
                var weight1 = a.mpw * parseInt(Mw.value) + a.amm * parseInt(Aw.value) + a.rat * parseInt(Rw.value) + a.prt * parseInt(Pw.value);
                var weight2 = b.mpw * parseInt(Mw.value) + b.amm * parseInt(Aw.value) + b.rat * parseInt(Rw.value) + b.prt * parseInt(Pw.value);
                if (weight1 > weight2) {
                    return -1;
                } else if (weight1 === weight2) {
                    return 0;
                } else return 1;
            });
            getChart(logiList, it1, it2, it1_text, it2_text, Tr, Tm);
        }
        
    </script>
</head>

<body>
    <div id="wrapper">
        <!-- Navigation -->
        
                
                <a href="01.php" style="font-size:30px"><span style="color:#FF0066">少女前线工具</span> (GF tools)</a>
            </div>
            
                        
                        <a href="GF.php" style="font-size:20px">返回主页</a>
                        
                 
        </nav>

        <!-- Main Pages -->
        <div id="page-wrapper">
            <div class="container-fluid">
                <div class="">
                    <div class="col-lg-12">
                        <div class="tooltip-demo">
                            <h1 class="page-header">后勤排序器 <button type="button" data-toggle="tooltip" data-placement="bottom" title="English language" class="btn btn-outline btn-default" onclick="Language('English')">English</button> <button type="button" data-toggle="tooltip" data-placement="bottom" title="各资源获取速率乘其权重求和排序 所缺的资源可将权重调大" class="btn btn-outline btn-default">?</button></h1>
                        </div>
                    </div>
                </div>
                <div class="row">
                    <!--Setting-->
                    <div class="col-lg-8">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                设置
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <!-- Nav tabs -->
                                <ul class="nav nav-tabs">
                                    <li class="active">
                                        <a href="#Ratio" data-toggle="tab">配比</a>
                                    </li>
                                    <li>
                                        <a href="#Limitation" data-toggle="tab">限制</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <!--RATIO-->
                                    <div class="tab-pane fade in active" id="Ratio">
                                        <div class="col-lg-6" style="background:url(../img/Logi-token.png) no-repeat right 15px top 15px">
                                            <h4>常用</h4>
                                            <p>
                                                <button type="button" class="btn btn-outline btn-primary" onclick="setWeight(2)">零件x3</button>
                                                <button type="button" class="btn btn-outline btn-danger" onclick="setWeight(1)">等比</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(3)">赌枪</button>
                                            </p>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setWeight(4)">人力</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(5)">弹药</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(6)">口粮</button>
                                                <button type="button" class="btn btn-default" onclick="setWeight(7)">零件</button>
                                            </p>
                                            <h4>包含道具</h4>
                                            <p>
                                                <select class="form-control" id="ItemNeed1">
                                                    <option value=0>无要求</option>
                                                    <option value=1>人形契约</option>
                                                    <option value=2>装备契约</option>
                                                    <option value=3>快速建造</option>
                                                    <option value=4>快速修复</option>
                                                    <option value=5>采购币</option>
                                                </select>
                                            </p>
                                            <p>
                                                <select class="form-control" id="ItemNeed2">
                                                    <option value=0>无要求</option>
                                                    <option value=1>人形契约</option>
                                                    <option value=2>装备契约</option>
                                                    <option value=3>快速建造</option>
                                                    <option value=4>快速修复</option>
                                                    <option value=5>采购币</option>
                                                </select>
                                            </p>
                                        </div>
                                        <div class="col-lg-6">
                                            <h4>权重</h4>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">人力权重</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="Mw" value=1>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">弹药权重</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="Aw" value=1>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">口粮权重</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="Rw" value=1>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">零件权重</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="Pw" value=3>
                                            </div>
                                        </div>
                                    </div>
                                    <!--LIMITATION-->
                                    <div class="tab-pane fade" id="Limitation">
                                        <div class="col-lg-12">
                                            <h4>时间区间</h4>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setTime(5)">全部</button>
                                                <button type="button" class="btn btn-outline btn-primary" onclick="setTime(1)">6~12h</button>
                                                <button type="button" class="btn btn-default" onclick="setTime(2)">4~6h</button>
                                                <button type="button" class="btn btn-default" onclick="setTime(3)">1~3h</button>
                                                <button type="button" class="btn btn-outline btn-danger" onclick="setTime(4)">0~1.7h</button>
                                            </p>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">最短</span>
                                                <input type="text" class="form-control" value="0" placeholder="输入数字" id="Tr">
                                                <span class="input-group-addon">小时</span>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">最长</span>
                                                <input type="text" class="form-control" value="24" placeholder="输入数字" id="Tm">
                                                <span class="input-group-addon">小时</span>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <h4>关卡解锁</h4>
                                            <p>
                                                <select class="form-control" id="MapLimit">
                                                    <option value=1>第一战役</option>
                                                    <option value=2>第二战役</option>
                                                    <option value=3>第三战役</option>
                                                    <option value=4>第四战役</option>
                                                    <option value=4.5>第零战役 (通关4-4E)</option>
                                                    <option value=5>第五战役</option>
                                                    <option value=6>第六战役</option>
                                                    <option value=7>第七战役</option>
                                                    <option value=8>第八战役</option>
                                                    <option value=9>第九战役</option>
                                                    <option value=10>第十战役</option>
                                                    <option value=11 selected>第十一战役</option>
                                                </select>
                                            </p>
                                        </div>
                                    </div>
                                    <div class="col-lg-12">
                                        <p><button type="button" class="btn btn-info" onclick="getRanking()">按条件排序</button></p>
                                    </div>
                                </div>

                            </div>
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="col-lg-8">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                排序结果
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <div class="table-responsive" id="rankingChart"></div>
                                <!-- /.table-responsive -->
                            </div>
                            <!-- /.panel-body -->
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
