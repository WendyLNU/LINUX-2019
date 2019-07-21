// JavaScript Document<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title> 果果无敌坦克团 - 主坦克用方向键移动，空格发射。 右坦克用IJKL键移动，F键发射。每辆坦克一次可发射2颗炮弹</title>
<style>
html,body{background:#16242C url(img1.gif);cursor:default;height:100%;overflow:hidden;margin:0;color:#eee;text-align:center;}
#popTxt{padding:10px;font-size:100px;font-family:Arial;position:relative; top:36%; color:#eee;}
#popTxt span{position:absolute;top:10px;left:-1px;color:#990000;}
#iMap{position:absolute;left:0;top:0;z-index:999}
#iMap span{width:20px;height:20px;overflow:hidden;font-size:10px;display:block; float:left;}
#iMap span.steel{background:url(imga.gif) no-repeat;}
#iMap span.tod{background:url(imgf.gif) no-repeat;}
#iMap span.wall{background:url(imgb.gif) no-repeat;}
#iMap span.sea{background:url(imgd.gif) no-repeat;}
#iMap span.podium1{background:url(imgi.gif) no-repeat;}
#iMap span.podium2{background:url(imgi.gif) no-repeat -20px 0;}
#iMap span.podium3{background:url(imgi.gif) no-repeat 0 -20px;}
#iMap span.podium4{background:url(imgi.gif) no-repeat -20px -20px;}
#gameMap{
	position:absolute;background:black; 
	border:10px outset #C65D05;
	width:520px;height:520px;
	top:50%;margin-top:-270px;
	left:50%;margin-left:-270px;
}
#gameInfo{
	position:absolute;background:#993300; 
	border:2px outset #000;
	top:50%;margin-top:-270px;
	left:50%;margin-left:280px;
}
.shell{
	margin:10px; 
	width:200px; height:516px; 
	background:#996600; 
	border:1px inset #6C120D; 
	text-align:left; 
	color:#333; font-family:Arial;
}
.shell div{margin:10px; }
h3{
	color:#FFCC00; 
	text-align:center; 
	margin:3px; 
	background:#990000; padding:5px; 
	border:1px outset #900;font-family:Arial;
	font-size:16px;
}
#tanks{
	margin:3px; 
}
.etank,.tank{
	width:40px;height:40px;background:url(imgc.gif) no-repeat;   
	position:absolute;top:480px;left:180px;z-index:99;
}
.etank{
	background:url(imgh.gif) no-repeat;   
}
.ball{
	width:40px;height:40px;overflow:hidden;font-size:4px;background:url(imgg.gif) no-repeat;   
	position:absolute;z-index:1000;
}
#win{z-index:0}
#goal1{color:#eee;}
#goal2{color:#006600}
#tanks{overflow:hidden; }
#tanks span{
	width:40px;height:40px;background:url(imgc.gif) no-repeat; display:block; float:left; margin:3px; 
}
#myTanks{
	position:absolute; bottom:0;left:20px;color:#000;font-weight:bold; 
}
#myCount1,#myCount2{
	height:40px;line-height:40px;  background:url(imgc.gif) no-repeat; text-indent:50px;
	font-size:18px;font-weight:bold;color:#003333; 
}
#stageIndex{font-size:20px;color:#FFFF00;padding:10px;  }
</style>
 </head>

 <body>
 <div id="gameBox">
	 <div id="gameMap">
		<div id="win"></div>
	</div>
	<div id="gameInfo"><div class="shell">
		<div>&nbsp;I P:  <strong id="goal1">0</strong> </div>
		<div>II P: <strong id="goal2">0</strong></div>
		<div id="tanks"></div>
		<div id="myTanks">
			<div id="myCount1">3</div>
			<div id="myCount2">3</div>
			<div>第<strong id="stageIndex">1</strong>关</div>
		</div>
	</div></div>	
 </div>


</body>

<script>
/*
游戏配置
*/
Game={
	stage:1,/* 关数 */
	end:false,
	win:false,
	sendMax:2,/* 坦克默认每次可发射弹量 */
	enemy:20,/* 敌机数 */
	full:20,
	kill:0,
	play1:3,
	play2:3,
	val1:0,
	val2:0
};
/*
地址栏控制关数
*/
autoStage=location.href.split('?')[1];
if(!isNaN(autoStage))Game.stage=autoStage;

Game.begin=function($){/* --------------------- Tank1998 Begin-------------------------------------------------------- */

/*
map Data
*/
tankMap=[
	/*NO.1*/'0,0,001100110011001100110011,001100110011001100110011,001100110011001100110011,001100110011001100110011,001100110011221100110011,001100110011221100110011,001100110011001100110011,001100110011001100110011,001100110000000000110011,0000000000110011,0000000000110011,11001111000000000011110011,22001111000000000011110022,0000000000110011,0000000000111111,001100110011111100110011,001100110011001100110011,001100110011001100110011,001100110011001100110011,001100110000000000110011,001100110000000000110011,001100110001111000110011,000000000001561,000000000001781'
	/*NO.2*/,'0000002200000022,0000002200000022,001100220000001100110011,001100220000001100110011,001100000000111100112211,001100000000111100112211,00000011000000000022,00000011000000000022,33000011000022000011331122,33000011000022000011331122,3333000000110000220033,3333000000110000220033,001111113333332200003311,001111113333332200003311,000000223311001100110011,000000223311001100110011,221100220011001100000011,221100220011001100000011,001100110011111100112211,001100110011111100112211,0011001100111111,0011001100111111,001100000000000000110011,001100000001111000110011,001100110001561000111111,001100110001781000111111'
	/*NO.3*/,'000000001100000011,000000001100000011,0033333311,00333333110000000000222222,00333333,11333333,00333333000000110011111110,00333333000000110011111110,333333331111111100110001,333333331111110000110001,333333330000110000000001,333333330000110000000001,003300000000222222000033,003300000000222222000033,00000000000000000033333333,00110011000000000033333333,11100111100111111133333333,11100111100100000033333333,00000000001100000033333333,00000000001100111133333333,110000200000001111333333,110000200000000000333333,111100200000000000333333,111100200001111000333333,22111100000156100011,22111100000178100011'
	/*NO.4*/,'003333000000000000000033,003333000000000000000033,33330000001100000000000033,33330000111111111100000033,33000001111111111111000022,3300000111111111111111,22000011111111111111111,00000011111111111111111,00000111000000111111001,00000100000000001111001,0000010020002000111,0000010020002000111,44001100000000001110004444,44001100111100001110004444,00001111111111111111,00001111111111111111,000111111111111111111,001111111111111111111,001111111111111111111,00000001111111111,00111100111111110011110033,00111111001111001111110033,33000000000000001111003333,33000000000111100000003333,22330000000156100000333322,22330000000178100000333322'
	/*NO.5*/,'000000001111,000000001111,0000000011000000222222,2200110011000000000022,22001100000011,22001100000011,11001111110011110044440044,11001111110011110044440044,11000000110000000044,00000000000000000044,00000000444400444444,00001100444400444444,11110000441100111000001111,11110000441100111000001111,0000000044000000000022,0000000044000000000022,444444004400220011002,444444004400220011002,00000000000000000000201111,00000011110000000000201111,000000001111111111,00000000110000001111,1111110000000000001111,1111000000011110000011,110000000001561,000000000001781'
];

var battleField=[];/* 战场网格 */
var mainKey=false;/* 独占的主键 */
var subKey=false;/* 独占的子键 */
var autoMove=function(){};
/*
crate gameMap
*/
var reload=function(w,h,shell){
	var stage=Math.max(1,this.stage)||1;
	if(stage>tankMap.length)stage=1;/* 关卡设置与检测 */
	$.getElementById("stageIndex").innerHTML=Game.stage;
	var map=tankMap[stage-1].split(',');
	shell.innerHTML='';
	var View=Jc('DIV','iMap',false,shell);
	for (var i=0, html=[];i<h;i++ ){/* 游戏场景视图生成 */
		var line=Jc('DIV',0,0,View);
		battleField[i]=[];/* save cells info */
		for (var j=0,tmp=[];j<w;j++ ){
			var v=map[i]&&map[i].charAt(j)||0;/* 逐字符读取贴图数据 */
			var css=['empty','wall','steel','tod','sea','podium1','podium2','podium3','podium4'][v];
			var cell=Jc('SPAN',0,css,line);
			battleField[i][j]={'cell':cell,type:v,tank:false,ball:false};/* 使用type记录撞击特性,tank记录是否有停放坦克 */
		}
	};
	var tanksHTML=[];
	for (var i=0;i<Game.enemy;i++ ) {
		tanksHTML.push('<span></span>');
	};
	$.getElementById("tanks").innerHTML=tanksHTML.join('');
	function Jc(type,id,className,parentNode){/* 生成UI的快捷函数 */
		var J=document.createElement(type);
		if(id)J.id=id;
		if(className)J.className=className;
		return parentNode.appendChild(J);
	};
	if(window.ActiveXObject)/* IE6 下禁止重载背景 */
		$.execCommand("BackgroundImageCache", false, true);
};
reload.call(this,26,26,$.getElementById('win'));

/*
Mover Class
*/
Mover=function(){}
Mover.prototype={
	move:function(dir){
		if(this.lock||!this.use){return;};/* 停用或者尚在步进中,操作无效 */
		if(this.army=='enemy'&&Math.random()*100>96)/* 敌机有4%的机率会中途变换方向  */
			return this.dir=Math.max(0,Math.min(3,parseInt(Math.random()*5)-1));
		if(isNaN(dir))dir=this.dir;
		var J=/[02]/.test(dir)?'top':'left',view=this.UI.style,This=this,i=0,INI=this.type=='ball'?[5,2]:[4,3];/* speed ini */
		view.backgroundPosition='0 -'+dir*40+'px';/* change direction 移动对象转向 */
		this.dir=dir;

		if(this.hit())return this.onhit();/* hit test----------------- */
		/* ----------------*/

		this.lock=true;/* 加锁 */
		var subMove=setInterval(function (){/* 阶段移动 20px */
			view[J]=parseInt(view[J])+INI[0]*(/[21]/.test(dir)?1:-1)+'px';/* 移动 */
			if(i++>INI[1]){
				clearInterval(subMove);
				This.lock=false;/* 解锁,允许再次步进 */
				This.freeGrid();/* 放弃原先占位 */
				This.x=Math.round(This.UI.offsetLeft/20);/* 保存网格坐标 */
				This.y=Math.round(This.UI.offsetTop/20);
				This.useGrid();/* 登记当前占位 */
				if(This.type=='ball'&&This.use)This.move(dir);/* 使用中的炮弹自动连续步进 */
			}
		},This.speed);
	}

	,hit:function(){
		if(this.dir==0&&this.y==0||
			this.dir==1&&this.x==24||
			this.dir==2&&this.y==24||
			this.dir==3&&this.x==0
		)return true;/* 场景越界 */

		var x=this.x,y=this.y,a,b;
		switch(this.dir){/* test cells */
			case 0:/* up 探测 */
				a=battleField[y-1][x];
				b=battleField[y-1][x+1];
				break;
			case 1:/* right 探测 */
				a=battleField[y][x+2];
				b=battleField[y+1][x+2];
				break;
			case 2:/* down 探测 */
				a=battleField[y+2][x];
				b=battleField[y+2][x+1];
				break;
			case 3:/* left 探测 */
				a=battleField[y][x-1];
				b=battleField[y+1][x-1];
				break;
		};

		if(a.tank||b.tank){/* 先测试是否停有其它坦克 */
			if(this.type=='ball'){/* 击中坦克 */
				if((a.tank&&a.tank.army!=this.owner.army)){	this.update(a);return true};/* 子弹受阻即爆 */
				if((b.tank&&b.tank.army!=this.owner.army)){this.update(b);;return true};/* 子弹受阻即爆 */
			}else{
				return true;/* 坦克相撞 */			
			}
		};

		if(a.ball&&b.ball){/* 先测试是否掠过其它炮弹(用&&表示全对齐,不包含部分交叉) */
			if(this.type=='ball'){/* 炮弹对撞 */
				if(a.ball.owner.army!=this.owner.army){a.ball.onhit();return true};/*  两颗子弹同时爆炸 */
				if(b.ball.owner.army!=this.owner.army){b.ball.onhit();return true};/* 两颗子弹同时爆炸 */
			}
		};

		if(a.type==0&&b.type==0)return;/* 空地不撞击 */

		if(/[1245678]/.test(a.type)||/[1245678]/.test(b.type)){/* 前方非空非迷彩 */
			if(this.type=='ball'){/* 撞击者为子弹, 砖块标记为空 */
				this.free(a);
				this.free(b);
			};
			if(this.type=='ball'&&(a.type==4||b.type==4))return false;/* 击中大海无效 */
			return true;/* 确定有阻挡 */
		};

	}
	,onhit:function(){}

	,free:function(net){/* 使用偏移方式来防止渲染效率恶化 */
		if(/[5678]/.test(net.type))Game.end=true;/* 击中指挥部结束 */
		if(net.type!=1)return;/* 不是砖块不变化 */
		net.cell.style.backgroundPosition='-10000px 0';
		net.type=0;
	}

	,useGrid:function(isUse){/* 占据网格 */
		var X=this.type;/* 坦克与炮弹即时停放记录 */
		if(!this.use)return;
		if(isUse===undefined)isUse=this;/* 无参数时记录自已 */
		var x=this.x,y=this.y;
		battleField[y][x][X]=isUse;
		battleField[y+1][x+1][X]=isUse;
		battleField[y][x+1][X]=isUse;
		battleField[y+1][x][X]=isUse;
	}
	,freeGrid:function (){/* 释放网格 */
		this.useGrid(false);
	}
	,update:function (a){
		if(this.owner.name=='mainTank'){
			var J=$.getElementById("goal1");
			Game.val1+=200;
			J.innerHTML=Game.val1;
		};
		if(this.owner.name=='subTank'){
			var J=$.getElementById("goal2");
			Game.val2+=200;
			J.innerHTML=Game.val2;
		};
		if(a.tank.name=='mainTank'){
			var J=$.getElementById("myCount1");
			Game.play1-=1;
			J.innerHTML=Game.play1;
		};
		if(a.tank.name=='subTank'){
			var J=$.getElementById("myCount2");
			Game.play2-=1;
			J.innerHTML=Game.play2;
		};
		if(Game.play1==0&&Game.play2==0)Game.end=true;
		a.tank.reLoad();	
	}
}
/*
Tank Class
*/
var Tank=function (x,y,speed,ballSpeed,dir,army){
	var UI=document.createElement('DIV');
	UI.className="tank";
	this.type='tank';
	this.firstPos={'x':x,'y':y,'dir':dir||0};/* 坦克出口位置, 击中后重载坦克用 */
	this.x=x;
	this.y=y;
	this.army=army||'our';

	if(army=='enemy'){
		UI.className="etank";
		this.onhit=function (){/* 敌机受阻后暂停0.5秒随机转向 */
			var This=this;
			setTimeout(function (){
				This.dir=Math.max(0,Math.min(3,parseInt(Math.random()*5)-1));
			},500);
		};
		Tank.autoClip.push(this);/* 加入群机驱动 */
	};

	var J=battleField[y][x].cell;/* 占用地图标识 */
	UI.style.top=J.offsetTop+'px';
	UI.style.left=J.offsetLeft+'px';
	this.speed=speed||20;/* 坦克移动速度 */
	this.ballSpeed=ballSpeed||10;/* 子弹速度 */
	this.UI=$.getElementById('gameMap').appendChild(UI);
	this.dir=dir||0;/* 坦克移动方向 */
	UI.style.backgroundPosition='0 -'+this.dir*40+'px';/* 对象初始朝向 */
	this.max=Game.sendMax||1;/* 单次可发射子弹限量 */
	this.sendCount=0;/* 单次已发射子弹计数 */
	this.lock=false;
	this.use=true;/* 声明投放使用 */
	this.useGrid();/* 声明占位 */
};
Tank.autoClip=[];/* 敌机列表 */
Tank.auto=function(){/* 敌机的自动运行 */
	for (var i=0;i<this.autoClip.length;i++ ) {
		var J=this.autoClip[i];
		if(J.use){/* 如果坦克使用中 */
			J.move();/* 移动 */
			if(Math.random()*100<10)
				ballClip.shot(J);/* 0.5%的机率射击 */
		}
	}
}
Tank.prototype=new Mover;/* 继承自Mover类, 以拥有移动与撞击自检功能 */
Tank.prototype.reLoad=function(){/* 击中后重新加载 */
	this.freeGrid();/* 清扫战场 */
	this.UI.style.left='-1000px';
	this.use=false;/* 标记闲置 */
	var This=this;
	if(this.army=='enemy'){
		Game.kill++;
		$.getElementById("tanks").removeChild($.getElementById("tanks").firstChild);
		if(Game.enemy==Game.kill)return Game.win=true ;
		if(Game.kill>Game.enemy-3)return;/* 已经用尽存储的生命,无法再复活 */
	}
	if(this.name=='subTank'&&Game.play2==0)return;
	if(this.name=='mainTank'&&Game.play1==0)return;
	/* 1秒后复活击中过的坦克 */
	setTimeout(function (){This.relive()},1000);

};
Tank.prototype.relive=function (){
		this.x=this.firstPos.x;/* 复位网格坐标 */
		this.y=this.firstPos.y;
		this.dir=this.firstPos.dir;
		this.useGrid();/* 网格占用声明 */
		this.UI.style.left=this.firstPos.x*20+'px';/* 复位物理坐标 */
		this.UI.style.top=this.firstPos.y*20+'px';
		this.UI.style.backgroundPosition='0 -'+this.dir*40+'px';/* 对象初始朝向 */
		this.use=true;/* 标记为可用 */
}
/*
爆炸特效类
*/
Fx=function(file,step){
	var UI=document.createElement('DIV');
	UI.style.cssText='position:absolute;width:60px;height:60px;overflow:hidden;background:url('+file+') no-repeat 0 0;z-index:1009;';
	this.UI=UI;
	this.speed=50;
	this.step=step||1;
	this.moveTo=function(x,y){
		this.UI.style.top=y+'px';
		this.UI.style.left=x+'px';
		return this;
	}
	var This=this;
	this.play=function (){
		var i=0;
		var FxTimer=setInterval(function (){
			This.UI.style.backgroundPosition='0 -'+i++*60+'px';
			if(i==This.step){
				clearInterval(FxTimer);
				This.moveTo(-1000,0);
			}
		},This.speed)
	}
	this.moveTo(-1000,0);
	$.getElementById('gameMap').appendChild(UI);
};

var iFx=new Fx('imgk.gif',8);

/*
Ball Class 炮弹类
*/
var Ball=function(owner/* Tank class */){
	var UI=document.createElement('DIV');
	UI.className="ball";
	UI.style.top='0';
	UI.style.left='-1000px';/* hidden  to srceen left */
	this.UI=$.getElementById('gameMap').appendChild(UI);
	this.type='ball';
	this.use=false;/* 是否使用中, 不在弹夹内 */
	this.lock=false;
}
Ball.prototype=new Mover;/* 继承自Mover类, 以拥有移动与撞击自检功能 */
/*
Magazine clip 弹夹类
*/
MagazineClip=function(count){
	this.clip=[];
	var This=this;
	for (var i=0;i<count;i++ ) {/* 生成count个炮弹 */
		var ball=new Ball;
		ball.onhit=function (){/* 实现撞击事件接口 */
			var x=y=0;
			switch (this.dir){/* 效果位置调整 */
				case 0:x=-.5;y=-2;break;
				case 1:x=1;y=-0.5;break;
				case 2:x=-.5;y=1;break;
				case 3:x=-2;y=-.5;
			}
			iFx.moveTo((this.x+x)*20,(this.y+y)*20).play();/* 爆炸效果回放 */
			this.freeGrid();
			this.UI.style.left='-1000px';/* 炮弹回收, 存放到屏幕外  */
			this.use=false;/* 状态切换到非使用中 */
			this.owner.sendCount--;/* 刷新已发射量 */
			This.clip.push(this);/* 再次装入夹中循环利用 */
		}
		this.clip.push(ball);
	}
	this.shot=function(owner){/* 将炮弹装入坦克 */
		if(!owner.use)return;
		if(owner.sendCount==owner.max)return;/* 如果发射量满,放弃操作 */
		var ball=this.clip.pop();/* 从弹夹中弹出一个炮弹 */
		if(ball==undefined)return;/* 用光了则填弹失败 */
		owner.sendCount++;/* 计数 */
		ball.owner=owner;
		ball.x=owner.x;/* 虚拟网格位置 */
		ball.y=owner.y;
		ball.dir=owner.dir;
		ball.UI.style.backgroundPosition='0 -'+ball.dir*40+'px';/* 炮弹方向视图 */
		var J=battleField[ball.y][ball.x].cell,Jx=ball.UI.style;
		Jx.top=J.offsetTop+'px';/* 物理位置 */
		Jx.left=J.offsetLeft+'px';
		ball.speed=owner.ballSpeed||2;/* 炮弹定速 */
		ball.use=true;
		ball.move(owner.dir);/* 炮弹开始发射 */
	}
}
/*
创建角色 Tank(x,y,坦克速率,子弹速度(默认2),初始朝向(0-3),敌友识别番号(默认our))
*/
var ballClip=new MagazineClip(20);/* 弹夹(所有坦克共用) */
var mainTank=new Tank(9,24,30);/* 主坦克 */
mainTank.name='mainTank';
var subTank=new Tank(15,24,30);/* 子坦克 */
subTank.name='subTank';
/* 敌方坦克 */
var enemy1=new Tank(0,0,30,10,2,'enemy');
var enemy2=new Tank(12,0,30,10,2,'enemy');
var enemy3=new Tank(24,0,30,10,2,'enemy');

/*
按键按下
*/
window.onkeydown=
$.body.onkeydown=function (e){
	var J=(window.event||e).keyCode;
	if(/^(37|38|39|40)$/.test(J))mainKey=J;/* 记录主坦克移动键 */
	if(/^(73|74|75|76)$/.test(J))subKey=J;/* 记录子坦克移动键 AWDS*/
	if(J==32)ballClip.shot(mainTank);/* 主坦克发射 空格*/
	if(J==70)ballClip.shot(subTank);/* 主坦克发射 1键*/
};
/*
按键弹起
*/
window.onkeyup=
$.body.onkeyup=function (e){
	var J=(window.event||e).keyCode;
	if(J==mainKey)mainKey=false;/* 主坦克当前移动键终止 */
	if(J==subKey)subKey=false;/* 子坦克当前移动键终止 */
};

/*
长定时器监听控制键
*/
var keyLister=setInterval(function(){
	if(Game.end){
		clearInterval(keyLister);/* 游戏结束 */
		document.body.innerHTML='<strong id="popTxt">GAME OVER</strong>';
	};
	if(Game.win){
		Game.stage++;/* 下一关 */
		Game.end=false;
		Game.win=false;
		Game.enemy=Game.full;
		Game.kill=0;

		reload.call(Game,26,26,$.getElementById('win'));
		for (var i=0;i<Tank.autoClip.length;i++ ) {
			Tank.autoClip[i].relive();
		};
		if(Game.play1>0){
			$.getElementById("myCount1").innerHTML=++Game.play1;
			mainTank.relive();
		}
		if(Game.play2>0){
			$.getElementById("myCount2").innerHTML=++Game.play2;
			subTank.relive();
		};
	};
	if(/^(37|38|39|40)$/.test(mainKey))mainTank.move([3,0,1,2][mainKey-37]);/* 所有主移动键 */
	if(/^(73|74|75|76)$/.test(subKey)){/* 所有子移动键 */
		subTank&&subTank.move({'73':0,'76':1,'75':2,'74':3}[subKey]);
	}
	Tank.auto();
},19);

};
Game.begin(document)/* -------------------------Tank1998 End------------------------------------------ */
</script>
</html>