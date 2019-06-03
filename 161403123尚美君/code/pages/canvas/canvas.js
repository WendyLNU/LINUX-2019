const App = getApp();
var ctx = null;
var timer;
var changed = false;
var saving = false;
var press = false;

//注册页面
Page({
  // 画板事件
  canvasIdErrorCallback: function(e) {
    console.error(e.detail.errMsg)
  },

  canvasStart: function(e) {
    var that = this;
    that.pointData.begin_x = that.pointData.move_x = e.touches[0].x;
    that.pointData.begin_y = that.pointData.move_y = e.touches[0].y;
    if(that.data.eraserMode){
      ctx.setStrokeStyle(that.data.eraserData.color);
      ctx.setLineWidth(that.data.eraserData.penSize);
      ctx.setLineCap('round'); // 让线条圆润
      ctx.beginPath();
    }else{
      ctx.setStrokeStyle(that.data.penData.color);
      ctx.setLineWidth(that.data.penData.penSize);
      ctx.setLineCap('round'); // 让线条圆润
      ctx.beginPath();
    }
    
    changed = true;
    press = true;

  },
  canvasEnd: function(e) {
    var that = this;
    changed = true;
    press = false
  },


  canvasMove: function(e) {
    if (!press) return;
    //借鉴https://github.com/jsososo/wx-app-painting 改用曲线
    var that = this;
    const x = e.touches[0].x
    const y = e.touches[0].y
    const py = that.pointData.begin_y;
    const px = that.pointData.begin_x;
    const mx = that.pointData.move_x;
    const my = that.pointData.move_y;
    //直线
    // ctx.moveTo(px, py); 
    // ctx.lineTo(x, y); 
    if (0) {

      ctx.moveTo(px, py);
      ctx.lineTo(x, y);
      ctx.stroke(); //对当前路径进行描边
      ctx.draw(true);
      that.pointData.begin_y = y;
      that.pointData.begin_x = x;
    } else {
      //曲线
      ctx.moveTo(mx, my);
      ctx.quadraticCurveTo(px, py, (px + x) / 2, (py + y) / 2);
      ctx.stroke(); //对当前路径进行描边
      ctx.draw(true);

      if (that.max_x < x)
        that.max_x = x;
      if (that.max_y < y)
        that.max_y = y;
      if (that.min_x > x)
        that.min_x = x;
      if (that.min_y > y)
        that.min_y = y;


      that.pointData.move_x = (x + px) / 2;
      that.pointData.move_y = (y + py) / 2;
      that.pointData.begin_y = y;
      that.pointData.begin_x = x;
    }


  },

  //切换画笔和橡皮擦
  switchMode: function() {
    var that = this;
    var eraserMode = that.data.eraserMode;
    if (changed && !saving) { //只有在有改动且不在保存状态中的时候,才能执行临时保存
      changed = false; //此时消除改动
      saving = true; // 改为保存状态
      that.temporarySave(function () { //异步执行临时保存
        saving = false; //消除保存状态
        if (changed) { //如果有改动就不重绘画板了
          return;
        } else { //没有改动的话,重绘画板
          that.refresh(that.data.canvasBgData.bgsrc);
        }
      });
    }
    if (eraserMode) {
      eraserMode = false;
    } else {
      eraserMode = true;
    }
    that.setData({
      eraserMode: eraserMode
    },function(){
      wx.hideToast();
      wx.showToast({
        title: eraserMode ? '已切换为橡皮' : '已切换为画笔' ,
        icon: "none"
      })
      
    });
  },

  // 清除画板
  cleardraw: function() {
    changed = true;
    var that = this;
    var bg = this.data.canvasBgData;
    var pen = this.data.penData;
    //把画布填充默认背景颜色
    ctx.rect(0, 0, 9999, 9999);
    ctx.setFillStyle(bg.color);
    ctx.fill();
    ctx.draw();
    this.data.x_canvasPositon = 0;
    var w = 750;
    this.max_y = 0;
    this.min_y = 65535;
    this.max_x = 0;
    this.min_x = 65535;

  },
  preview: function() {
    var that = this;
    var w = that.max_x - that.min_x + 20;
    var h = that.max_y - that.min_y + 20;
    wx.canvasToTempFilePath({
      canvasId: 'canvas',
      x: that.min_x - 10,
      y: that.min_y - 10,
      width: w,
      height: h,
      fileType: 'jpg',
      quality: 0.8,
      success: function(res) {
        var urls = [];
        urls.push(res.tempFilePath);
        console.log(res.tempFilePath);
        wx.previewImage({
          current: '',
          urls: urls,
          success: function(res) {},
          fail: function(res) {},
          complete: function(res) {},
        })
      }
    })

  },

  scale: function() {
    var that = this;

  },
  // 移动画板
  leftMove: function() {
    var x = this.data.x_canvasPositon;
    var w = this.data.w_canvasSize;
    var that = this;
    x = x - 300
    if (x < -1500)
      x = -1500
    that.setData({
      x_canvasPositon: x,
    })

    if (changed && !saving) { //只有在有改动且不在保存状态中的时候,才能执行临时保存
      changed = false; //此时消除改动
      saving = true; // 改为保存状态
      that.temporarySave(function() { //异步执行临时保存
        saving = false; //消除保存状态
        if (changed) { //如果有改动就不重绘画板了
          return;
        } else { //没有改动的话,重绘画板
          that.refresh(that.data.canvasBgData.bgsrc);
        }
      });
    }

  },
  rightMove: function() {
    var x = this.data.x_canvasPositon;
    // this.refresh();
    x = x + 300
    if (x > 0)
      x = 0;
    this.setData({
      x_canvasPositon: x
    })

    if (changed && !saving) { //只有在有改动且不在保存状态中的时候,才能执行临时保存
      changed = false; //此时消除改动
      saving = true; // 改为保存状态
      that.temporarySave(function() { //异步执行临时保存
        saving = false; //消除保存状态
        if (changed) { //如果有改动就不重绘画板了
          return;
        } else { //没有改动的话,重绘画板
          that.refresh(that.data.canvasBgData.bgsrc);
        }
      });
    }

  },

  // 添加到记忆
  addToMemory: function() {
    var pages = getCurrentPages()
    var prevPage = pages[pages.length - 1] //当前界面
    var prevPage = pages[pages.length - 2] //上一个页面
    var that = this;
    wx.showToast({
      title: '正在生成图片',
      icon: "loading",
      duration: 2000000, //提示的延迟时间，单位毫秒，默认：1500
      mask: true,
    })
    wx.canvasToTempFilePath({
      canvasId: 'canvas',
      x: that.min_x - 10,
      y: that.min_y - 10,
      width: that.max_x - that.min_x + 20,
      height: that.max_y - that.min_y + 20,
      fileType: 'jpg',
      quality: 0.8,
      success: function(res) {
        if (prevPage.addCanvas)
          prevPage.addCanvas(res.tempFilePath, that.data.options)
        wx.hideToast();
        wx.navigateBack({
          delta: 1,
        })
      }
    })
  },
  // 页面数据
  data: {
    //画布背景颜色数据
    canvasBgData: {
      color: '#434343',
      // color: '#f5f5f5',
      bgsrc: null,
      lastBgsrc: null,
    },
    x_canvasPositon: 0,
    y_canvasPositon: 0,
    h_canvasSize: 900,
    w_canvasSize: 2250,
    //画笔数据
    penData: {
      penSize: 2,
      color: '#fff'
      // color: '#434343',
    },
    eraserData: {
      penSize: 20,
      color: '#434343'
    },
    eraserMode: false,
    options: null,
    tempSrc: null,
  },
  pointData: {
    begin_x: 0,
    begin_y: 0,
    move_x: 0,
    move_y: 0
  },
  max_y: 0,
  min_y: 65535,
  max_x: 0,
  min_x: 65535,
  rpx: 0,


  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function(options) {

    // 使用 wx.createContext 获取绘图上下文 context
    var that = this;
    that.data.options = options
    ctx = wx.createCanvasContext('canvas')
    ctx.setLineCap('round')
    ctx.setLineJoin('round')

    that.cleardraw();

    wx.getSystemInfo({
      success: function(res) {
        console.log(res);
        that.rpx = res.windowWidth / 750;
      },
    })



  },


  // 将画板内容临时保存为图片
  temporarySave: function(callback) {
    var that = this;
    const h = that.data.h_canvasSize * that.rpx;
    const w = that.data.w_canvasSize * that.rpx;
    wx.canvasToTempFilePath({
      canvasId: 'canvas',
      width: w,
      height: h,
      fileType: 'jpg',
      quality: 0.9,
      success: function(res) {
        that.data.canvasBgData.bgsrc = res.tempFilePath;
        if (callback)
          callback(res);
      }
    })



  },

  // 将图片重绘到画板之中
  refresh: function(src) {
    var that = this;
    const h = that.data.h_canvasSize * that.rpx;
    const w = that.data.w_canvasSize * that.rpx;
    if (src) {
      ctx.drawImage(src, 0, 0, w, h);
      ctx.setStrokeStyle(that.data.penData.color);
      ctx.setLineWidth(that.data.penData.penSize);
      ctx.setLineCap('round'); // 让线条圆润
      ctx.beginPath();
      ctx.draw();
    }


  }
})