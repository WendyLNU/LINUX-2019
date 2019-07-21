<!DOCTYPE html>
<html lang="zh">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <title>少女前线-练级计算器 by 命运の乐章</title>
    <link href="../vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="../vendor/metisMenu/metisMenu.min.css" rel="stylesheet">
    <link href="../dist/css/sb-admin-2.css" rel="stylesheet">
    <link href="../vendor/morrisjs/morris.css" rel="stylesheet">
    <link href="../vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <script type="text/javascript">
        var levelUpExp_Tdoll = [0, 0, 100, 300, 600, 1000, 1500, 2100, 2800, 3600, 4500, 5500, 6600, 7800, 9100, 10500, 12000, 13600, 15300, 17100, 19000, 21000, 23100, 25300, 27600, 30000, 32500, 35100, 37900, 41000, 44400, 48600, 53200, 58200, 63600, 69400, 75700, 82400, 89600, 97300, 105500, 114300, 123600, 133500, 144000, 155100, 166900, 179400, 192500, 206400, 221000, 236400, 252500, 269400, 287200, 305800, 325300, 345700, 367000, 389300, 412600, 436900, 462200, 488500, 515900, 544400, 574000, 604800, 636800, 670000, 704400, 749500, 796300, 844900, 895300, 947500, 1001500, 1057400, 1115300, 1175100, 1236900, 1300800, 1366800, 1434900, 1505200, 1577800, 1652600, 1729700, 1809200, 1891100, 1975400, 2088000, 2204100, 2323600, 2446700, 2573400, 2703800, 2837900, 2975800, 3117600, 3263300, 3363300, 3483300, 3623300, 3783300, 3963300, 4163300, 4383300, 4623300, 4903300, 5263300, 5743300, 6383300, 7283300, 8483300, 10083300, 12283300, 15283300, 19283300, 24283300, 30283300];
        var levelUpExp_Fairy = [0, 0, 300, 600, 900, 1200, 1500, 1800, 2100, 2400, 2700, 3000, 3300, 3600, 3900, 4200, 4500, 4800, 5100, 5500, 6000, 6500, 7100, 8000, 9000, 10000, 11000, 12200, 13400, 14700, 16000, 17500, 18900, 20500, 22200, 23900, 25700, 27600, 29500, 31600, 33700, 35900, 38200, 40500, 43000, 45500, 48200, 50900, 53700, 56600, 59600, 62700, 65900, 69200, 72600, 76000, 79600, 83300, 87000, 90900, 94900, 99000, 103100, 107400, 111800, 116300, 120900, 125600, 130400, 135300, 140400, 145500, 150800, 156100, 161600, 167200, 172900, 178700, 184700, 190700, 196900, 203200, 209600, 216100, 222800, 229600, 236500, 243500, 250600, 257900, 265300, 272800, 280400, 288200, 296100, 304100, 312300, 320600, 329000, 337500, 357000];
        window.onload = function () {
            var chart = document.getElementById("resultChart");
            var tab = '人形的结果将在这里显示';
            var chartF = document.getElementById("resultChartF");
            var tabF = '妖精的结果将在这里显示';
            var chartH = document.getElementById("resultChartH");
            var tabH = '重装部队的结果将在这里显示';
            chart.innerHTML = tab;
            chartF.innerHTML = tabF;
            chartH.innerHTML = tabH;
        }

        function freeTeamExpan() {
            var ExpanF1 = document.getElementById('ExpanF1');
            var teamExpan = document.getElementById('teamExpan');
            if (ExpanF1.checked) {
                teamExpan.disabled = true;
                teamExpan.value = 1635;
            } else {
                teamExpan.disabled = false;
            }
        }

        function inputCardData(cardname, value, declinelevel) {
            var expData = new Object;
            expData.cardname = cardname;
            expData.value = value;
            expData.declinelevel = declinelevel;
            return expData;
        }

        function setMap(mapInfo) {
            var MP = document.getElementById('MapInfo');
            switch (mapInfo) {
                case 1:
                    MP.value = 1; break; //0-2
                case 2:
                    MP.value = 54; break; //4-3E
                case 3:
                    MP.value = 71; break; //5-2N
                case 4:
                    MP.value = 86; break; //6-3N
                case 5:
                    MP.value = 112; break; //8-1N
                case 6:
                    MP.value = 140; break; //11-5
            }
        }

        function setLevel(levelInfo) {
            var CL = document.getElementById('CurLev');
            var TL = document.getElementById('TarLev');
            switch (levelInfo) {
                case 1:
                    CL.value = 30; TL.value = 70; break;
                case 2:
                    CL.value = 70; TL.value = 90; break;
                case 3:
                    CL.value = 100; TL.value = 110; break;
                case 4:
                    CL.value = 110; TL.value = 115; break;
            }
        }

        function setLevelF(levelInfo) {
            var CLF = document.getElementById('CurLevF');
            var TLF = document.getElementById('TarLevF');
            switch (levelInfo) {
                case 1:
                    CLF.value = 1; TLF.value = 20; break;
                case 2:
                    CLF.value = 20; TLF.value = 40; break;
                case 3:
                    CLF.value = 40; TLF.value = 70; break;
                case 4:
                    CLF.value = 70; TLF.value = 100; break;
            }
        }

        function setLevelH(levelInfo) {
            var CLH = document.getElementById('CurLevH');
            var TLH = document.getElementById('TarLevH');
            switch (levelInfo) {
                case 1:
                    CLH.value = 1; TLH.value = 40; break;
                case 2:
                    CLH.value = 1; TLH.value = 60; break;
                case 3:
                    CLH.value = 40; TLH.value = 60; break;
            }
        }

        function checkError(levelUpExp) {
            var CurLevId = document.getElementById('CurLev');
            var CurLev = parseInt(CurLevId.value);
            var TarLevId = document.getElementById('TarLev');
            var TarLev = parseInt(TarLevId.value);
            var CurExpId = document.getElementById('CurExp');
            var CurExp = parseInt(CurExpId.value);
            var Ep1 = document.getElementById('Expan1');
            var Ep3 = document.getElementById('Expan3');
            var Ep4 = document.getElementById('Expan4');
            var Ep5 = document.getElementById('Expan5');
            var Ep6 = document.getElementById('Expan6');
            var TimeAvgId = document.getElementById('TimeAvg');
            var AmmAvgId = document.getElementById('AmmAvg');
            var RatAvgId = document.getElementById('RatAvg');
            if (isNaN(CurLevId.value) || isNaN(TarLevId.value) || isNaN(CurExpId.value) || !((CurLev >= 1 && CurLev < 120) && (TarLev > 1 && TarLev <= 120))) {
                return 1;
            } else if (CurLev >= TarLev) {
                return 2;
            } else if (levelUpExp[CurLev + 1] - levelUpExp[CurLev] <= CurExp) {
                return 3;
            } else if ((CurLev < 10 && Ep3.checked) || (CurLev < 30 && Ep4.checked) || (CurLev < 70 && Ep5.checked) || (CurLev < 90 && Ep6.checked) || ((CurLev >= 100 || TarLev >= 101) && (!Ep1.checked && !Ep6.checked))) {
                return 4;
            } else if (isNaN(TimeAvgId.value) || isNaN(AmmAvgId.value) || isNaN(RatAvgId.value)) {
                return 5;
            }
            return 0;
        }

        function correctInput(inputLable) { //page+inputNum, X0 means whole page
            switch (inputLable) {
                case 20:
                    var CurLevId = document.getElementById('CurLevF');
                    var CurLev = parseInt(CurLevId.value);
                    var TarLevId = document.getElementById('TarLevF');
                    var TarLev = parseInt(TarLevId.value);
                    var CurExpId = document.getElementById('CurExpF');
                    var CurExp = parseInt(CurExpId.value);
                    if ((parseFloat(CurLevId.value) - parseInt(CurLevId.value) != 0) || (parseFloat(TarLevId.value) - parseInt(TarLevId.value) != 0) || (parseFloat(CurExpId.value) - parseInt(CurExpId.value) != 0) || (isNaN(CurLevId.value) || (CurLevId.value).length === 0) || (isNaN(TarLevId.value) || (TarLevId.value).length === 0) || (isNaN(CurExpId.value) || (CurExpId.value).length === 0) || !((CurLev >= 1 && CurLev < 100) && (TarLev > 1 && TarLev <= 100) && (CurLev < TarLev) && (levelUpExp_Fairy[CurLev + 1] > CurExp))) {
                        CurLevId.value = 1;
                        TarLevId.value = 100;
                        CurExpId.value = 0;
                    }
                    break;
                case 41:
                    var TimeAvgId = document.getElementById('TimeAvg');
                    if (isNaN(TimeAvgId.value) || (TimeAvgId.value).length === 0 || parseFloat(TimeAvgId.value) <= 0) {
                        TimeAvgId.value = 0.4;
                    }
                    break;
                case 42:
                    var AmmAvgId = document.getElementById('AmmAvg');
                    if (isNaN(AmmAvgId.value) || (AmmAvgId.value).length === 0 || parseFloat(AmmAvgId.value) <= 0 || (parseFloat(AmmAvgId.value) - parseInt(AmmAvgId.value) != 0)) {
                        AmmAvgId.value = 12;
                    }
                    break;
                case 43:
                    var RatAvgId = document.getElementById('RatAvg');
                    if (isNaN(RatAvgId.value) || (RatAvgId.value).length === 0 || parseFloat(RatAvgId.value) <= 0 || (parseFloat(RatAvgId.value) - parseInt(RatAvgId.value) != 0)) {
                        RatAvgId.value = 12;
                    }
                    break;
                case 44:
                    var SimuNumId = document.getElementById('SimuNum');
                    if (isNaN(SimuNumId.value) || (SimuNumId.value).length === 0 || !(parseInt(SimuNumId.value) >= 1 && parseInt(SimuNumId.value) <= 10) || (parseFloat(SimuNumId.value) - parseInt(SimuNumId.value) != 0)) {
                        SimuNumId.value = 5;
                    }
                    break;
                case 45:
                    var ExpanF1 = document.getElementById('ExpanF1');
                    var teamExpanId = document.getElementById('teamExpan');
                    var teamExpan = parseInt(teamExpanId.value);
                    if (isNaN(teamExpanId.value) || (teamExpanId.value).length === 0 || teamExpan <= 0 || (parseFloat(teamExpanId.value) - teamExpan != 0)) {
                        teamExpanId.value = 1635;
                    }
                    break;
            }
        }

        function checkErrorH(levelUpExp) {
            var CurLevId = document.getElementById('CurLevH');
            var CurLev = parseInt(CurLevId.value);
            var TarLevId = document.getElementById('TarLevH');
            var TarLev = parseInt(TarLevId.value);
            var CurExpId = document.getElementById('CurExpH');
            var CurExp = parseInt(CurExpId.value);
            if (isNaN(CurLevId.value) || isNaN(TarLevId.value) || isNaN(CurExpId.value) || !((CurLev >= 1 && CurLev < 100) && (TarLev > 1 && TarLev <= 100))) {
                return 1;
            } else if (CurLev >= TarLev) {
                return 2;
            } else if (levelUpExp[CurLev + 1] <= CurExp) {
                return 3;
            }
            return 0;
        }

        function getChart(selectMapInfo, Num_normal, Num_leader, Num_MVP, Num_leaderMVP, Num_book, total_EXP) {
            var SimuNum = parseInt(document.getElementById('SimuNum').value);
            var SimuType = parseInt(document.getElementById('SimuType').value);
            var kineticNum, simuBattleNum, simuExp;
            switch (SimuType) {
                case 1:
                    simuExp = Math.ceil(20000 / SimuNum);
                    simuBattleNum = Math.ceil(total_EXP / (20000 / SimuNum));
                    kineticNum = 1 * simuBattleNum;
                    break;
                case 2:
                    simuExp = Math.ceil(80000 / SimuNum);
                    simuBattleNum = Math.ceil(total_EXP / (80000 / SimuNum));
                    kineticNum = 2 * simuBattleNum;
                    break;
                case 3:
                    simuExp = Math.ceil(240000 / SimuNum);
                    simuBattleNum = Math.ceil(total_EXP / (240000 / SimuNum));
                    kineticNum = 3 * simuBattleNum;
                    break;
            }
            var TimeAvgId = document.getElementById('TimeAvg');
            var maxTime = parseFloat(TimeAvgId.value) * Num_leaderMVP / 60,
                minTime = parseFloat(TimeAvgId.value) * Num_normal / 60;
            var AmmAvgId = document.getElementById('AmmAvg');
            var maxAmm = parseFloat(AmmAvgId.value) * Num_leaderMVP,
                minAmm = parseFloat(AmmAvgId.value) * Num_normal;
            var RatAvgId = document.getElementById('RatAvg');
            var maxRat = parseFloat(RatAvgId.value) * Num_leaderMVP,
                minRat = parseFloat(RatAvgId.value) * Num_normal;
            var chart = document.getElementById("resultChart");
            var tab = '<p><h4>地图信息</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>所需经验</th><th>所选地图</th><th>战斗经验</th><th>衰减等级</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (total_EXP + "");
            tab += '</td>';
            tab += '<td>';
            tab += (selectMapInfo.cardname);
            tab += '</td>';
            tab += '<td>';
            tab += (selectMapInfo.value + "");
            tab += '</td>';
            tab += '<td>';
            tab += (selectMapInfo.declinelevel + "");
            tab += '</td>';
            tab += '</tr></tbody></table>';
            tab += '<p><h4>战斗次数</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>队员</th><th>队长</th><th>MVP</th><th>队长MVP</th><th>作战报告书</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (Num_normal + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_leader + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_MVP + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_leaderMVP + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_book + "");
            tab += '</td></tr>';
            tab += '</tr></tbody></table>';
            tab += '<p><h4>资源消耗</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>弹药</th><th>口粮</th><th>耗时</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (maxAmm.toFixed(0) + "");
            tab += " ~ ";
            tab += (minAmm.toFixed(0) + "");
            tab += '</td>';
            tab += '<td>';
            tab += (maxRat.toFixed(0) + "");
            tab += " ~ ";
            tab += (minRat.toFixed(0) + "");
            tab += '</td>';
            tab += '<td>';
            tab += (maxTime.toFixed(1) + "");
            tab += " ~ ";
            tab += (minTime.toFixed(1) + "");
            tab += 'h</td>';
            tab += '</tr></tbody></table>';
            tab += '<p><h4>模拟战</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>模拟战经验</th><th>模拟战场次</th><th>动能消耗</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (simuExp + "");
            tab += '</td>';
            tab += '<td>';
            tab += (simuBattleNum + "");
            tab += '</td>';
            tab += '<td>';
            tab += (kineticNum + "");
            tab += '</td>';
            tab += '</tr></tbody></table>';
            chart.innerHTML = tab;
        }

        function getChartF(selectMapInfo, Num, Num_book, total_EXP, fairyExp) {
            var TimeAvgId = document.getElementById('TimeAvg');
            var Time = parseFloat(TimeAvgId.value) * Num / 60;
            var AmmAvgId = document.getElementById('AmmAvg');
            var Amm = parseFloat(AmmAvgId.value) * Num;
            var RatAvgId = document.getElementById('RatAvg');
            var Rat = parseFloat(RatAvgId.value) * Num;
            var chart = document.getElementById("resultChartF");
            var tab = '<p><h4>地图信息</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>所需经验</th><th>所选地图</th><th>战斗经验</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (total_EXP + "");
            tab += '</td>';
            tab += '<td>';
            tab += (selectMapInfo.cardname);
            tab += '</td>';
            tab += '<td>';
            tab += (fairyExp + "");
            tab += '</td>';
            tab += '</tr></tbody></table>';
            tab += '<p><h4>战斗次数</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>次数</th><th>作战报告书</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (Num + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_book + "");
            tab += '</td></tr>';
            tab += '</tr></tbody></table>';
            tab += '<p><h4>资源消耗</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>弹药</th><th>口粮</th><th>耗时</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (Amm.toFixed(0) + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Rat.toFixed(0) + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Time.toFixed(1) + "");
            tab += 'h</td>';
            tab += '</tr></tbody></table>';
            chart.innerHTML = tab;
        }

        function getChartH(trainTime, Num_book, total_EXP) {
            var chart = document.getElementById("resultChartH");
            var tab = '<p><h4>训练信息</h4></p>';
            tab += '<table class="table table-striped table-bordered table-hover"><thead><tr><th>所需经验</th><th>特种作战报告书</th><th>训练时间</th></tr></thead>';
            tab += '<tbody><tr>';
            tab += '<td>';
            tab += (total_EXP + "");
            tab += '</td>';
            tab += '<td>';
            tab += (Num_book + "");
            tab += '</td>';
            tab += '<td>';
            tab += (trainTime + "");
            tab += 'h</td>';
            tab += '</tr></tbody></table>';
            chart.innerHTML = tab;
        }

        function getOnceExp(onceExpFull, declinelevel, currentlevel, expUp, OATHValue, Multiple) {
            var Exp = onceExpFull * expUp * Multiple;
            var Ep1 = document.getElementById('Expan1');
            var Ep2 = document.getElementById('Expan2');
            var Ep3 = document.getElementById('Expan3');
            var Ep4 = document.getElementById('Expan4');
            var Ep5 = document.getElementById('Expan5');
            var Ep6 = document.getElementById('Expan6');
            if (currentlevel >= 10 && currentlevel < 30) {
                if (Ep1.checked || Ep3.checked) Exp *= 1.5;
            }
            if (currentlevel >= 30 && currentlevel < 70) {
                if (Ep1.checked || Ep4.checked) Exp *= 2;
                else if (Ep3.checked) Exp *= 1.5;
            }
            if (currentlevel >= 70 && currentlevel < 90) {
                if (Ep1.checked || Ep5.checked) Exp *= 2.5;
                else if (Ep4.checked) Exp *= 2;
                else if (Ep3.checked) Exp *= 1.5;
            }
            if (currentlevel >= 90 && currentlevel < 100) {
                if (Ep1.checked || Ep6.checked) Exp *= 3;
                else if (Ep5.checked) Exp *= 2.5;
                else if (Ep4.checked) Exp *= 2;
                else if (Ep3.checked) Exp *= 1.5;
            }
            if (currentlevel >= 100) Exp = Exp * 3 * OATHValue;
            if (currentlevel - declinelevel >= 1 && currentlevel - declinelevel < 10) Exp *= 0.8;
            if (currentlevel - declinelevel >= 10 && currentlevel - declinelevel < 20) Exp *= 0.6;
            if (currentlevel - declinelevel >= 20 && currentlevel - declinelevel < 30) Exp *= 0.4;
            if (currentlevel - declinelevel >= 30 && currentlevel - declinelevel < 40) Exp *= 0.2;
            if (currentlevel - declinelevel >= 40) Exp = 5;
            return Exp;
        }

        function getNum(levelUpExp, selectMapInfo, CurLev, TarLev, CurExp, expUp, OATHValue, Multiple) {
            var resultNum = 0;
            var this_level = CurLev;
            var this_leftexp = CurExp;
            var this_exp;
            while (this_level < TarLev) {
                this_exp = getOnceExp(selectMapInfo.value, selectMapInfo.declinelevel, this_level, expUp, OATHValue, Multiple);
                resultNum += Math.ceil((levelUpExp[this_level + 1] - levelUpExp[this_level] - this_leftexp) / this_exp);
                if (this_level != 99) this_leftexp = (this_exp * Math.ceil((levelUpExp[this_level + 1] - levelUpExp[this_level] - this_leftexp) / this_exp)) - (levelUpExp[this_level + 1] - levelUpExp[this_level] - this_leftexp);
                else this_leftexp = 0;
                this_level++;
            }
            return resultNum;
        }

        function getFairyExp(selectMapInfo, expUp) {
            var ExpanF1 = document.getElementById('ExpanF1');
            var teamExpanId = document.getElementById('teamExpan');
            var teamExpan = parseInt(teamExpanId.value);
            var WeatherDevice = parseInt(document.getElementById('WeatherDevice').value);
            var this_exp;
            if (ExpanF1.checked) this_exp = Math.ceil(selectMapInfo.value * 16.68 * (0.05 + 0.015 * WeatherDevice));
            else this_exp = teamExpan;
            this_exp *= expUp;
            return this_exp;
        }

        function getFairyTotalExp(levelUpExp, CurLev, TarLev, CurExp) {
            var thisLevel = CurLev;
            var totalExp = 0;
            while (thisLevel < TarLev) {
                totalExp += levelUpExp[thisLevel + 1];
                thisLevel++;
            }
            return totalExp - CurExp;
        }

        function getHFTotalExp(levelUpExp, CurLev, TarLev, CurExp) {
            var thisLevel = CurLev;
            var totalExp = 0;
            while (thisLevel < TarLev) {
                totalExp += levelUpExp[thisLevel + 1];
                thisLevel++;
            }
            return totalExp - CurExp;
        }

        function getHFTrainTime(Num_book) { //1,3,3,5,7,7,9,11,11,13,15
            var bph;
            var TCLevel = parseInt(document.getElementById('TrainingCourse').value);
            switch (TCLevel) {
                case 0: bph = 1; break;
                case 1: bph = 3; break;
                case 2: bph = 3; break;
                case 3: bph = 5; break;
                case 4: bph = 7; break;
                case 5: bph = 7; break;
                case 6: bph = 9; break;
                case 7: bph = 11; break;
                case 8: bph = 11; break;
                case 9: bph = 13; break;
                case 10: bph = 15; break;
            }
            return Math.ceil(Num_book / bph);
        }

        function getNumBook(levelUpExp, CurLev, TarLev, CurExp, OATHValue) {
            var resultNum;
            var totalExp;
            if (TarLev <= 100) {
                totalExp = levelUpExp[TarLev] - levelUpExp[CurLev] - CurExp;
                resultNum = Math.ceil(totalExp / 3000);
            } else if (CurLev < 100 && TarLev > 100) {
                resultNum = Math.ceil((levelUpExp[100] - levelUpExp[CurLev] - CurExp) / 3000) + Math.ceil((levelUpExp[TarLev] - levelUpExp[100]) / (3000 * OATHValue));
            } else {
                resultNum = Math.ceil((levelUpExp[TarLev] - levelUpExp[CurLev] - CurExp) / (3000 * OATHValue));
            }
            return resultNum;
        }

        function getResult(typeInfo) { //1=T-dool, 2=Fairy, 3=Heavy-Fire
            var panelT = document.getElementById('panelT');
            var panelF = document.getElementById('panelF');
            var panelH = document.getElementById('panelH');
            var MP = document.getElementById('MapInfo');
            var MPidx = MapInfo.selectedIndex;
            var MPval = parseInt(MP[MPidx].value);
            var expUpId = document.getElementById('expUp');
            var OATHId = document.getElementById('OATH');
            var expUp, OATHValue;
            if (expUpId.checked) expUp = 1.5;
            else expUp = 1;
            if (OATHId.checked) OATHValue = 2;
            else OATHValue = 1;
            var mapList = [];
            mapList.push(inputCardData("0-1", 480, 110));
            mapList.push(inputCardData("0-2", 490, 112));
            mapList.push(inputCardData("0-3", 500, 113));
            mapList.push(inputCardData("0-4", 510, 116));
            mapList.push(inputCardData("1-1", 150, 11));
            mapList.push(inputCardData("1-2", 160, 15));
            mapList.push(inputCardData("1-3", 170, 18));
            mapList.push(inputCardData("1-4", 180, 20));
            mapList.push(inputCardData("1-5", 190, 22));
            mapList.push(inputCardData("1-6", 200, 25));
            mapList.push(inputCardData("1-1E", 200, 22));
            mapList.push(inputCardData("1-2E", 210, 25));
            mapList.push(inputCardData("1-3E", 220, 30));
            mapList.push(inputCardData("1-4E", 230, 35));
            mapList.push(inputCardData("1-1N", 280, 45));
            mapList.push(inputCardData("1-2N", 290, 50));
            mapList.push(inputCardData("1-3N", 300, 55));
            mapList.push(inputCardData("1-4N", 320, 60));
            mapList.push(inputCardData("2-1", 200, 25));
            mapList.push(inputCardData("2-2", 210, 28));
            mapList.push(inputCardData("2-3", 220, 30));
            mapList.push(inputCardData("2-4", 230, 30));
            mapList.push(inputCardData("2-5", 240, 30));
            mapList.push(inputCardData("2-6", 250, 35));
            mapList.push(inputCardData("2-1E", 250, 35));
            mapList.push(inputCardData("2-2E", 260, 35));
            mapList.push(inputCardData("2-3E", 270, 40));
            mapList.push(inputCardData("2-4E", 280, 45));
            mapList.push(inputCardData("2-1N", 330, 65));
            mapList.push(inputCardData("2-2N", 350, 70));
            mapList.push(inputCardData("2-3N", 360, 75));
            mapList.push(inputCardData("2-4N", 380, 80));
            mapList.push(inputCardData("3-1", 250, 40));
            mapList.push(inputCardData("3-2", 260, 40));
            mapList.push(inputCardData("3-3", 270, 45));
            mapList.push(inputCardData("3-4", 280, 48));
            mapList.push(inputCardData("3-5", 290, 50));
            mapList.push(inputCardData("3-6", 300, 55));
            mapList.push(inputCardData("3-1E", 300, 55));
            mapList.push(inputCardData("3-2E", 310, 58));
            mapList.push(inputCardData("3-3E", 320, 60));
            mapList.push(inputCardData("3-4E", 330, 65));
            mapList.push(inputCardData("3-1N", 400, 83));
            mapList.push(inputCardData("3-2N", 410, 87));
            mapList.push(inputCardData("3-3N", 420, 91));
            mapList.push(inputCardData("3-4N", 450, 97));
            mapList.push(inputCardData("4-1", 300, 55));
            mapList.push(inputCardData("4-2", 310, 60));
            mapList.push(inputCardData("4-3", 320, 63));
            mapList.push(inputCardData("4-4", 330, 65));
            mapList.push(inputCardData("4-5", 340, 68));
            mapList.push(inputCardData("4-6", 350, 70));
            mapList.push(inputCardData("4-1E", 350, 70));
            mapList.push(inputCardData("4-2E", 360, 73));
            mapList.push(inputCardData("4-3E", 370, 75));
            mapList.push(inputCardData("4-4E", 380, 80));
            mapList.push(inputCardData("4-1N", 450, 97));
            mapList.push(inputCardData("4-2N", 460, 99));
            mapList.push(inputCardData("4-3N", 470, 100));
            mapList.push(inputCardData("4-4N", 480, 100));
            mapList.push(inputCardData("5-1", 350, 75));
            mapList.push(inputCardData("5-2", 360, 75));
            mapList.push(inputCardData("5-3", 370, 78));
            mapList.push(inputCardData("5-4", 380, 80));
            mapList.push(inputCardData("5-5", 390, 80));
            mapList.push(inputCardData("5-6", 400, 85));
            mapList.push(inputCardData("5-1E", 400, 85));
            mapList.push(inputCardData("5-2E", 410, 88));
            mapList.push(inputCardData("5-3E", 420, 90));
            mapList.push(inputCardData("5-4E", 430, 93));
            mapList.push(inputCardData("5-1N", 480, 102));
            mapList.push(inputCardData("5-2N", 480, 104));
            mapList.push(inputCardData("5-3N", 490, 106));
            mapList.push(inputCardData("5-4N", 490, 108));
            mapList.push(inputCardData("6-1", 400, 85));
            mapList.push(inputCardData("6-2", 410, 87));
            mapList.push(inputCardData("6-3", 420, 89));
            mapList.push(inputCardData("6-4", 430, 91));
            mapList.push(inputCardData("6-5", 440, 93));
            mapList.push(inputCardData("6-6", 450, 95));
            mapList.push(inputCardData("6-1E", 450, 95));
            mapList.push(inputCardData("6-2E", 450, 97));
            mapList.push(inputCardData("6-3E", 460, 99));
            mapList.push(inputCardData("6-4E", 470, 100));
            mapList.push(inputCardData("6-1N", 490, 110));
            mapList.push(inputCardData("6-2N", 490, 112));
            mapList.push(inputCardData("6-3N", 500, 114));
            mapList.push(inputCardData("6-4N", 500, 116));
            mapList.push(inputCardData("7-1", 450, 95));
            mapList.push(inputCardData("7-2", 450, 96));
            mapList.push(inputCardData("7-3", 460, 97));
            mapList.push(inputCardData("7-4", 460, 98));
            mapList.push(inputCardData("7-5", 470, 99));
            mapList.push(inputCardData("7-6", 470, 100));
            mapList.push(inputCardData("7-1E", 470, 97));
            mapList.push(inputCardData("7-2E", 470, 98));
            mapList.push(inputCardData("7-3E", 480, 100));
            mapList.push(inputCardData("7-4E", 480, 100));
            mapList.push(inputCardData("7-1N", 500, 118));
            mapList.push(inputCardData("7-2N", 500, 120));
            mapList.push(inputCardData("7-3N", 500, 120));
            mapList.push(inputCardData("7-4N", 500, 120));
            mapList.push(inputCardData("8-1", 470, 100));
            mapList.push(inputCardData("8-2", 470, 100));
            mapList.push(inputCardData("8-3", 470, 100));
            mapList.push(inputCardData("8-4", 480, 100));
            mapList.push(inputCardData("8-5", 480, 100));
            mapList.push(inputCardData("8-6", 480, 100));
            mapList.push(inputCardData("8-1E", 480, 100));
            mapList.push(inputCardData("8-2E", 480, 100));
            mapList.push(inputCardData("8-3E", 490, 100));
            mapList.push(inputCardData("8-4E", 490, 100));
            mapList.push(inputCardData("8-1N", 500, 120));
            mapList.push(inputCardData("8-2N", 500, 120));
            mapList.push(inputCardData("8-3N", 500, 120));
            mapList.push(inputCardData("8-4N", 500, 120));
            mapList.push(inputCardData("9-1", 480, 100));
            mapList.push(inputCardData("9-2", 480, 100));
            mapList.push(inputCardData("9-3", 480, 100));
            mapList.push(inputCardData("9-4", 490, 100));
            mapList.push(inputCardData("9-5", 490, 100));
            mapList.push(inputCardData("9-6", 490, 100));
            mapList.push(inputCardData("9-1E", 490, 100));
            mapList.push(inputCardData("9-2E", 490, 100));
            mapList.push(inputCardData("9-3E", 500, 100));
            mapList.push(inputCardData("9-4E", 500, 100));
            mapList.push(inputCardData("10-1", 490, 110));
            mapList.push(inputCardData("10-2", 490, 112));
            mapList.push(inputCardData("10-3", 490, 114));
            mapList.push(inputCardData("10-4", 490, 116));
            mapList.push(inputCardData("10-5", 490, 118));
            mapList.push(inputCardData("10-6", 490, 120));
            mapList.push(inputCardData("10-1E", 500, 120));
            mapList.push(inputCardData("10-2E", 500, 120));
            mapList.push(inputCardData("10-3E", 500, 120));
            mapList.push(inputCardData("10-4E", 500, 120));
            mapList.push(inputCardData("11-1", 510, 120));
            mapList.push(inputCardData("11-2", 520, 120));
            mapList.push(inputCardData("11-3", 530, 120));
            mapList.push(inputCardData("11-4", 540, 120));
            mapList.push(inputCardData("11-5", 550, 120));
            mapList.push(inputCardData("11-6", 560, 120));
            mapList.push(inputCardData("11-1E", 560, 120));
            mapList.push(inputCardData("11-2E", 570, 120));
            mapList.push(inputCardData("11-3E", 580, 120));
            mapList.push(inputCardData("11-4E", 600, 120));
            switch (typeInfo) {
                case 1: //T-doll
                    panelT.className = "active";
                    panelF.className = "";
                    panelH.className = "";
                    var Num_normal, Num_leader, Num_MVP, Num_leaderMVP, Num_book;
                    var CurLev = parseInt(document.getElementById('CurLev').value);
                    var TarLev = parseInt(document.getElementById('TarLev').value);
                    var CurExp = parseInt(document.getElementById('CurExp').value);
                    var chartInError = document.getElementById("resultChart");
                    var tab;
                    var levelUpExp = levelUpExp_Tdoll;
                    var errorNum = checkError(levelUpExp);
                    if (errorNum === 0) {
                        var total_EXP = levelUpExp[TarLev] - levelUpExp[CurLev] - CurExp;
                        var selectMapInfo = mapList[MPval];
                        Num_normal = getNum(levelUpExp, selectMapInfo, CurLev, TarLev, CurExp, expUp, OATHValue, 1);
                        Num_leader = getNum(levelUpExp, selectMapInfo, CurLev, TarLev, CurExp, expUp, OATHValue, 1.2);
                        Num_MVP = getNum(levelUpExp, selectMapInfo, CurLev, TarLev, CurExp, expUp, OATHValue, 1.3);
                        Num_leaderMVP = getNum(levelUpExp, selectMapInfo, CurLev, TarLev, CurExp, expUp, OATHValue, 1.56);
                        Num_book = getNumBook(levelUpExp, CurLev, TarLev, CurExp, OATHValue);
                        getChart(selectMapInfo, Num_normal, Num_leader, Num_MVP, Num_leaderMVP, Num_book, total_EXP);
                    } else { //不合法输入（在1~120间），等级上下逆转，现有经验超标，扩编信息不符，口粮弹药时间输入非法
                        if (errorNum === 1) {
                            tab = "等级或经验输入非法";
                        } else if (errorNum === 2) {
                            tab = "当前等级大于或等于目标等级";
                        } else if (errorNum === 3) {
                            tab = "现有经验超过了当前等级的升级经验";
                        } else if (errorNum === 4) {
                            tab = "扩编信息与当前等级矛盾";
                        } else if (errorNum === 5) {
                            tab = "弹药、口粮或平均时间输入非法";
                        }
                        chartInError.innerHTML = tab;
                    }
                    break;
                case 2: //Fairy
                    panelT.className = "";
                    panelF.className = "active";
                    panelH.className = "";
                    var Num, Num_book;
                    var CurLev = parseInt(document.getElementById('CurLevF').value);
                    var TarLev = parseInt(document.getElementById('TarLevF').value);
                    var CurExp = parseInt(document.getElementById('CurExpF').value);
                    var levelUpExp = levelUpExp_Fairy;
                    var total_EXP = getFairyTotalExp(levelUpExp, CurLev, TarLev, CurExp);
                    var selectMapInfo = mapList[MPval];
                    var fairyExp = getFairyExp(selectMapInfo, expUp);
                    Num = Math.ceil(total_EXP / fairyExp);
                    Num_book = Math.ceil(total_EXP / 3000);
                    getChartF(selectMapInfo, Num, Num_book, total_EXP, fairyExp);
                    break;
                case 3: //Heavy-fire
                    panelT.className = "";
                    panelF.className = "";
                    panelH.className = "active";
                    var Num_book, trainTime;
                    var CurLev = parseInt(document.getElementById('CurLevH').value);
                    var TarLev = parseInt(document.getElementById('TarLevH').value);
                    var CurExp = parseInt(document.getElementById('CurExpH').value);
                    var chartInError = document.getElementById("resultChartH");
                    var tab;
                    var levelUpExp = [0, 0, 500, 900, 1300, 1800, 2200, 2700, 3200, 3600, 4000, 4500, 5000, 5400, 5800, 6300, 6800, 7200, 7600, 8300, 9000, 9800, 10600, 12000, 13500, 15000, 16500, 18300, 20100, 22000, 24000, 26300, 28300, 30800, 33300, 35800, 38600, 41400, 44200, 47400, 50600, 53800, 57300, 60800, 64500, 68200, 72300, 76400, 80500, 84900, 89400, 94100, 98800, 103800, 108900, 114000, 119500, 124900, 130500, 136300, 142400, 148500, 154600, 161100, 167700, 174500, 181500, 188500, 195500, 203000, 210600, 218200, 226200, 234200, 242500, 250800, 259500, 268000, 277000, 286000, 295500, 304700, 314500, 324000, 334500, 344000, 355000, 365000, 376000, 387000, 398000, 409000, 421000, 432000, 444000, 456000, 469000, 481000, 493000, 506000, 537000];
                    var errorNum = checkErrorH(levelUpExp);
                    if (errorNum === 0) {
                        var total_EXP = getHFTotalExp(levelUpExp, CurLev, TarLev, CurExp);
                        Num_book = Math.ceil(total_EXP / 3000);
                        trainTime = getHFTrainTime(Num_book);
                        getChartH(trainTime, Num_book, total_EXP);
                    } else { //不合法输入（在1~100间），等级上下逆转，现有经验超标
                        if (errorNum === 1) {
                            tab = "等级或经验输入非法";
                        } else if (errorNum === 2) {
                            tab = "当前等级大于或等于目标等级";
                        } else if (errorNum === 3) {
                            tab = "现有经验超过了当前等级的升级经验";
                        }
                        chartInError.innerHTML = tab;
                    }
                    break;
            }
        }
    </script>
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
                            <h1 class="page-header">练级计算器 <button type="button" data-toggle="tooltip" data-placement="bottom" title="计算升级需要各种战斗场次" class="btn btn-outline btn-default">?</button></h1>
                        </div>
                    </div>
                </div>
                <!-- /.row -->
                <div class="row">
                    <!--Setting-->
                    <div class="col-lg-10">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                设置
                            </div>
                            <!--card info-->
                            <div class="panel-body" style="background:url(../img/Leveling-SF.png) no-repeat right 15px bottom 15px">
                                <div class="col-lg-4">
                                    <h4>练级地图</h4>
                                    <p>
                                        <button type="button" class="btn btn-outline btn-danger" onclick="setMap(1)">0-2</button>
                                        <button type="button" class="btn btn-outline btn-default" onclick="setMap(2)">4-3E</button>
                                        <button type="button" class="btn btn-outline btn-default" onclick="setMap(3)">5-2N</button>
                                        <button type="button" class="btn btn-outline btn-default" onclick="setMap(4)">6-3N</button>
                                        <button type="button" class="btn btn-outline btn-danger" onclick="setMap(5)">8-1N</button>
                                        <button type="button" class="btn btn-outline btn-default" onclick="setMap(6)">11-5</button>
                                    </p>
                                    <!--card selection-->
                                    <p>
                                        <select class="form-control" id="MapInfo">
                                            <option value=0>0-1</option>
                                            <option value=1 selected="selected">0-2</option>
                                            <option value=2>0-3</option>
                                            <option value=3>0-4</option>
                                            <option value=4>1-1</option>
                                            <option value=5>1-2</option>
                                            <option value=6>1-3</option>
                                            <option value=7>1-4</option>
                                            <option value=8>1-5</option>
                                            <option value=9>1-6</option>
                                            <option value=10>1-1E</option>
                                            <option value=11>1-2E</option>
                                            <option value=12>1-3E</option>
                                            <option value=13>1-4E</option>
                                            <option value=14>1-1N</option>
                                            <option value=15>1-2N</option>
                                            <option value=16>1-3N</option>
                                            <option value=17>1-4N</option>
                                            <option value=18>2-1</option>
                                            <option value=19>2-2</option>
                                            <option value=20>2-3</option>
                                            <option value=21>2-4</option>
                                            <option value=22>2-5</option>
                                            <option value=23>2-6</option>
                                            <option value=24>2-1E</option>
                                            <option value=25>2-2E</option>
                                            <option value=26>2-3E</option>
                                            <option value=27>2-4E</option>
                                            <option value=28>2-1N</option>
                                            <option value=29>2-2N</option>
                                            <option value=30>2-3N</option>
                                            <option value=31>2-4N</option>
                                            <option value=32>3-1</option>
                                            <option value=33>3-2</option>
                                            <option value=34>3-3</option>
                                            <option value=35>3-4</option>
                                            <option value=36>3-5</option>
                                            <option value=37>3-6</option>
                                            <option value=38>3-1E</option>
                                            <option value=39>3-2E</option>
                                            <option value=40>3-3E</option>
                                            <option value=41>3-4E</option>
                                            <option value=42>3-1N</option>
                                            <option value=43>3-2N</option>
                                            <option value=44>3-3N</option>
                                            <option value=45>3-4N</option>
                                            <option value=46>4-1</option>
                                            <option value=47>4-2</option>
                                            <option value=48>4-3</option>
                                            <option value=49>4-4</option>
                                            <option value=50>4-5</option>
                                            <option value=51>4-6</option>
                                            <option value=52>4-1E</option>
                                            <option value=53>4-2E</option>
                                            <option value=54>4-3E</option>
                                            <option value=55>4-4E</option>
                                            <option value=56>4-1N</option>
                                            <option value=57>4-2N</option>
                                            <option value=58>4-3N</option>
                                            <option value=59>4-4N</option>
                                            <option value=60>5-1</option>
                                            <option value=61>5-2</option>
                                            <option value=62>5-3</option>
                                            <option value=63>5-4</option>
                                            <option value=64>5-5</option>
                                            <option value=65>5-6</option>
                                            <option value=66>5-1E</option>
                                            <option value=67>5-2E</option>
                                            <option value=68>5-3E</option>
                                            <option value=69>5-4E</option>
                                            <option value=70>5-1N</option>
                                            <option value=71>5-2N</option>
                                            <option value=72>5-3N</option>
                                            <option value=73>5-4N</option>
                                            <option value=74>6-1</option>
                                            <option value=75>6-2</option>
                                            <option value=76>6-3</option>
                                            <option value=77>6-4</option>
                                            <option value=78>6-5</option>
                                            <option value=79>6-6</option>
                                            <option value=80>6-1E</option>
                                            <option value=81>6-2E</option>
                                            <option value=82>6-3E</option>
                                            <option value=83>6-4E</option>
                                            <option value=84>6-1N</option>
                                            <option value=85>6-2N</option>
                                            <option value=86>6-3N</option>
                                            <option value=87>6-4N</option>
                                            <option value=88>7-1</option>
                                            <option value=89>7-2</option>
                                            <option value=90>7-3</option>
                                            <option value=91>7-4</option>
                                            <option value=92>7-5</option>
                                            <option value=93>7-6</option>
                                            <option value=94>7-1E</option>
                                            <option value=95>7-2E</option>
                                            <option value=96>7-3E</option>
                                            <option value=97>7-4E</option>
                                            <option value=98>7-1N</option>
                                            <option value=99>7-2N</option>
                                            <option value=100>7-3N</option>
                                            <option value=101>7-4N</option>
                                            <option value=102>8-1</option>
                                            <option value=103>8-2</option>
                                            <option value=104>8-3</option>
                                            <option value=105>8-4</option>
                                            <option value=106>8-5</option>
                                            <option value=107>8-6</option>
                                            <option value=108>8-1E</option>
                                            <option value=109>8-2E</option>
                                            <option value=110>8-3E</option>
                                            <option value=111>8-4E</option>
                                            <option value=112>8-1N</option>
                                            <option value=113>8-2N</option>
                                            <option value=114>8-3N</option>
                                            <option value=115>8-4N</option>
                                            <option value=116>9-1</option>
                                            <option value=117>9-2</option>
                                            <option value=118>9-3</option>
                                            <option value=119>9-4</option>
                                            <option value=120>9-5</option>
                                            <option value=121>9-6</option>
                                            <option value=122>9-1E</option>
                                            <option value=123>9-2E</option>
                                            <option value=124>9-3E</option>
                                            <option value=125>9-4E</option>
                                            <option value=126>10-1</option>
                                            <option value=127>10-2</option>
                                            <option value=128>10-3</option>
                                            <option value=129>10-4</option>
                                            <option value=130>10-5</option>
                                            <option value=131>10-6</option>
                                            <option value=132>10-1E</option>
                                            <option value=133>10-2E</option>
                                            <option value=134>10-3E</option>
                                            <option value=135>10-4E</option>
                                            <option value=136>11-1</option>
                                            <option value=137>11-2</option>
                                            <option value=138>11-3</option>
                                            <option value=139>11-4</option>
                                            <option value=140>11-5</option>
                                            <option value=141>11-6</option>
                                            <option value=142>11-1E</option>
                                            <option value=143>11-2E</option>
                                            <option value=144>11-3E</option>
                                            <option value=145>11-4E</option>
                                        </select>
                                    </p>
                                    <div class="checkbox">
                                        <label> <input type="checkbox" id="expUp">圣肝日(exp x1.5)&nbsp&nbsp&nbsp</label>
                                        <label> <input type="checkbox" id="OATH">誓约(心智升级exp x2)</label>
                                    </div>
                                </div>
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <!-- Nav tabs -->
                                <ul class="nav nav-tabs">
                                    <li class="active">
                                        <a href="#TdollLevel" data-toggle="tab">人形练级</a>
                                    </li>
                                    <li>
                                        <a href="#FairyLevel" data-toggle="tab">妖精练级</a>
                                    </li>
                                    <li>
                                        <a href="#HeavyfireLevel" data-toggle="tab">重装部队练级</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <!--TDOLL-->
                                    <div class="tab-pane fade in active" id="TdollLevel">
                                        <!--level/exp info-->
                                        <div class="col-lg-6">
                                            <h4>人形等级经验</h4>
                                            <p>
                                                <button type="button" class="btn btn-default" onclick="setLevel(1)">30 → 70</button>
                                                <button type="button" class="btn btn-default" onclick="setLevel(2)">70 → 90</button>
                                                <button type="button" class="btn btn-outline btn-danger" onclick="setLevel(3)">MODⅡ</button>
                                                <button type="button" class="btn btn-outline btn-danger" onclick="setLevel(4)">MODⅢ</button>
                                            </p>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">当前等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurLev" value=1>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">目标等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="TarLev" value=100>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">现有经验</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurExp" value=0>
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <h4>细节设置</h4>
                                            <div class="panel panel-default">
                                                <div class="panel-heading">
                                                    <h4 class="panel-title">
                                                        <a data-toggle="collapse" href="#colla-tdoll">扩编和消耗</a>
                                                    </h4>
                                                </div>
                                                <div id="colla-tdoll" class="panel-collapse collapse">
                                                    <div class="panel-body">
                                                        <p>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan1" value="option1" checked><span style="color:dodgerblue">随等级扩编</span>
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan2" value="option2">x1
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan3" value="option3">x2
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan4" value="option4">x3
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan5" value="option5">x4
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitch" id="Expan6" value="option5">x5
                                                            </label>
                                                        </p>
                                                        <div class="form-group input-group">
                                                            <span class="input-group-addon">每战均摊时间(min)</span>
                                                            <input type="text" class="form-control" placeholder="输入正数" id="TimeAvg" value=0.4 onblur="correctInput(41)">
                                                        </div>
                                                        <div class="form-group input-group">
                                                            <span class="input-group-addon">每战弹药</span>
                                                            <input type="text" class="form-control" placeholder="输入整数" id="AmmAvg" value=12 onblur="correctInput(42)">
                                                        </div>
                                                        <div class="form-group input-group">
                                                            <span class="input-group-addon">每战口粮</span>
                                                            <input type="text" class="form-control" placeholder="输入整数" id="RatAvg" value=12 onblur="correctInput(43)">
                                                        </div>
                                                    </div>
                                                </div>
                                            </div>
                                            <div class="panel panel-default">
                                                <div class="panel-heading">
                                                    <h4 class="panel-title">
                                                        <a data-toggle="collapse" href="#colla-tdoll-simu">模拟战设定</a>
                                                    </h4>
                                                </div>
                                                <div id="colla-tdoll-simu" class="panel-collapse collapse">
                                                    <div class="panel-body">
                                                        <p>
                                                            <select class="form-control" id="SimuType">
                                                                <option value=1>低级经验模拟 (20,000 / 1 动能)</option>
                                                                <option value=2>中级经验模拟 (80,000 / 2 动能)</option>
                                                                <option value=3 selected="selected">高级经验模拟 (240,000 / 3 动能)</option>
                                                            </select>
                                                        </p>
                                                        <div class="form-group input-group">
                                                            <span class="input-group-addon">参战人数</span>
                                                            <input type="text" class="form-control" placeholder="输入整数" id="SimuNum" value=5 onblur="correctInput(44)">
                                                        </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <!--Button -->
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-info" onclick="getResult(1)" href="#TdollResult" data-toggle="tab">人形练级计算</button></p>
                                        </div>
                                    </div>
                                    <!--FAIRY-->
                                    <div class="tab-pane fade" id="FairyLevel">
                                        <!--level/exp info-->
                                        <div class="col-lg-6">
                                            <h4>妖精等级经验</h4>
                                            <p>
                                                <button type="button" class="btn btn-outline btn-default" onclick="setLevelF(1)">1 → 20</button>
                                                <button type="button" class="btn btn-outline btn-primary" onclick="setLevelF(2)">20 → 40</button>
                                                <button type="button" class="btn btn-outline btn-success" onclick="setLevelF(3)">40 → 70</button>
                                                <button type="button" class="btn btn-outline btn-warning" onclick="setLevelF(4)">70 → 100</button>
                                            </p>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">当前等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurLevF" value=1 onblur="correctInput(20)">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">目标等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="TarLevF" value=100 onblur="correctInput(20)">
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">现有经验</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurExpF" value=0 onblur="correctInput(20)">
                                            </div>
                                        </div>
                                        <div class="col-lg-6">
                                            <h4>细节设置</h4>
                                            <div class="panel panel-default">
                                                <div class="panel-heading">
                                                    <h4 class="panel-title">
                                                        <a data-toggle="collapse" href="#colla-fairy">设施和经验</a>
                                                    </h4>
                                                </div>
                                                <div id="colla-fairy" class="panel-collapse collapse">
                                                    <div class="panel-body">
                                                        <p>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitchF" id="ExpanF1" value="option1" onclick="freeTeamExpan()" checked><span style="color:dodgerblue">全员五扩/队长MVP</span>
                                                            </label>
                                                            <label class="radio-inline">
                                                                <input type="radio" name="ExpanSwitchF" id="ExpanF2" value="option2" onclick="freeTeamExpan()">指定经验
                                                            </label>
                                                        </p>
                                                        <div class="form-group input-group">
                                                            <span class="input-group-addon">单次战斗经验值</span>
                                                            <input type="text" class="form-control" placeholder="输入整数" id="teamExpan" value=1635 onblur="correctInput(45)" disabled>
                                                        </div>
                                                        <!--weather-device level-->
                                                        <p>
                                                            <select class="form-control" id="WeatherDevice">
                                                                <option value=0>Lv.0 空白的天气系统 (5%)</option>
                                                                <option value=1>Lv.1 乌云天气系统 (6.5%)</option>
                                                                <option value=2>Lv.2 乌云天气系统 (8%)</option>
                                                                <option value=3>Lv.3 乌云天气系统 (9.5%)</option>
                                                                <option value=4>Lv.4 乌云天气系统 (11%)</option>
                                                                <option value=5>Lv.5 乌云天气系统 (12.5%)</option>
                                                                <option value=6>Lv.6 暗月天气系统 (14%)</option>
                                                                <option value=7>Lv.7 暗月天气系统 (15.5%)</option>
                                                                <option value=8>Lv.8 暗月天气系统 (17%)</option>
                                                                <option value=9>Lv.9 暗月天气系统 (18.5%)</option>
                                                                <option value=10 selected="selected">Lv.10 双月天气系统 (20%)</option>
                                                            </select>
                                                        </p>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <!--Button -->
                                        <div class="col-lg-12">
                                            <p><button type="button" class="btn btn-success" onclick="getResult(2)" href="#FairyResult" data-toggle="tab">妖精练级计算</button></p>
                                        </div>
                                    </div>
                                    <!--HEAVYFIRE-->
                                    <div class="tab-pane fade" id="HeavyfireLevel">
                                        <!--level/exp info-->
                                        <div class="col-lg-4">
                                            <h4>重装部队等级经验</h4>
                                            <p>
                                                <button type="button" class="btn btn-outline btn-success" onclick="setLevelH(1)">1 → 40</button>
                                                <button type="button" class="btn btn-outline btn-warning" onclick="setLevelH(2)">1 → 60</button>
                                                <button type="button" class="btn btn-outline btn-warning" onclick="setLevelH(3)">40 → 60</button>
                                            </p>
                                            <!--training-course level-->
                                            <p>
                                                <select class="form-control" id="TrainingCourse">
                                                    <option value=0>Lv.0 简单的训练场 (1本/h)</option>
                                                    <option value=1>Lv.1 简单的训练场 (3本/h)</option>
                                                    <option value=2>Lv.2 简单的训练场 (3本/h)</option>
                                                    <option value=3>Lv.3 小规模训练场 (5本/h)</option>
                                                    <option value=4>Lv.4 小规模训练场 (7本/h)</option>
                                                    <option value=5>Lv.5 小规模训练场 (7本/h)</option>
                                                    <option value=6>Lv.6 中等规模训练场 (9本/h)</option>
                                                    <option value=7>Lv.7 中等规模训练场 (11本/h)</option>
                                                    <option value=8>Lv.8 中等规模训练场 (11本/h)</option>
                                                    <option value=9>Lv.9 中等规模训练场 (13本/h)</option>
                                                    <option value=10 selected="selected">Lv.10 综合室内训练场 (15本/h)</option>
                                                </select>
                                            </p>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">当前等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurLevH" value=1>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">目标等级</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="TarLevH" value=100>
                                            </div>
                                            <div class="form-group input-group">
                                                <span class="input-group-addon">现有经验</span>
                                                <input type="text" class="form-control" placeholder="输入整数" id="CurExpH" value=0>
                                            </div>
                                        </div>
                                        <!--Button -->
                                        <div class="col-lg-10">
                                            <p><button type="button" class="btn btn-warning" onclick="getResult(3)" href="#HeavyfireResult" data-toggle="tab">重装练级计算</button></p>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <!--Result -->
                <div class="row">
                    <div class="col-lg-10">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                计算结果
                            </div>
                            <!-- /.panel-heading -->
                            <div class="panel-body">
                                <!-- Nav tabs -->
                                <ul class="nav nav-tabs">
                                    <li id="panelT" class="active">
                                        <a href="#TdollResult" data-toggle="tab">人形练级结果</a>
                                    </li>
                                    <li id="panelF" class="">
                                        <a href="#FairyResult" data-toggle="tab">妖精练级结果</a>
                                    </li>
                                    <li id="panelH" class="">
                                        <a href="#HeavyfireResult" data-toggle="tab">重装部队练级结果</a>
                                    </li>
                                </ul>
                                <!-- Tab panes -->
                                <div class="tab-content">
                                    <!--TDOLL RESULTS-->
                                    <div class="tab-pane fade in active" id="TdollResult">
                                        <div class="panel-body">
                                            <div class="table-responsive" id="resultChart"></div>
                                        </div>
                                    </div>
                                    <!--FAIRY RESULTS-->
                                    <div class="tab-pane fade" id="FairyResult">
                                        <div class="panel-body">
                                            <div class="table-responsive" id="resultChartF"></div>
                                        </div>
                                    </div>
                                    <!--HEAVYFIRE RESULTS-->
                                    <div class="tab-pane fade" id="HeavyfireResult">
                                        <div class="panel-body">
                                            <div class="table-responsive" id="resultChartH"></div>
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
