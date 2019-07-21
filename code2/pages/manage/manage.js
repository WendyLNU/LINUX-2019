//// pages/manage/manage.js
/**
 * author：_Ragnarok
 * time:2019/4/1/19:48
 */
const app = getApp()

Page({

  /**
   * 页面的初始数据
   */
  data: {
    menuList: ["吃喝", "美妆", "日用", "文娱", "电子", "运动", "服饰"],
    menuindex: 0,
    imgurl: '../../res/icon/pic.png',
    array: ['小面积', '中等面积', '大面积', '轮播图Banner'],
    index: 0,
    passList:["展示","隐藏"],
    passindex:0,
    dateStart: "2019-04-17",
    dateEnd: "2019-04-17",
    disable: false,
    timeStart: "00:00",
    timeEnd: "00:00",
    lotteryName: '',
    prizeName: '',
    winnerNum: 1,
    coin: 0,
    maxnum: 1,
    mode: 0,
    introduce: '',
    cond: 2,
    lotteryid: '',
    qrurl: '',
    progress: 0,
    sponsor: '',
    uploadlottery:"上传活动"
  },
  previewqr: function() {
    wx.previewImage({
      current: this.data.qrurl, // 当前显示图片的http链接
      urls: [this.data.qrurl] // 需要预览的图片http链接列表
    })
  },
  chooseimg: function() {
    var that = this;
    wx.chooseImage({
      count: 1,
      sizeType: ['original', 'compressed'],
      sourceType: ['album', 'camera'],
      success(res) {
        // tempFilePath可以作为img标签的src属性显示图片
        const tempFilePaths = res.tempFilePaths
        that.setData({
          imgurl: tempFilePaths
        })
      }
    })
  },
  getform: function(e) {
    var that = this;
    var that2 = this;
    var that3 = this;
    var that4 = this;
    var lotteryName = e.detail.value.lotteryname;
    var introduce = e.detail.value.introduce;
    var prizeName = e.detail.value.prizename;
    var winnerNum = e.detail.value.prizenum;
    var maxnum = e.detail.value.maxnum;
    var coin = e.detail.value.coin;
    var openid = app.globalData.userid;
    var imgurl = this.data.imgurl;
    var cla = this.data.menuindex;
    var sponsor = e.detail.value.sponsor;
    if (openid == "") {
      wx.showToast({
        title: '您还没有给我们授权，请到首页基于授权！',
        icon: 'none',
        duration: 3000
      })
      return false;
    } else if (!lotteryName) {
      wx.showToast({
        title: '请输入活动标题！',
        icon: 'none',
        duration: 2000
      })
      return false;
    } else if (!prizeName) {
      wx.showToast({
        title: '请输入奖品名称！',
        icon: 'none',
        duration: 2000
      })
      return false;
    } else if (imgurl == '../../res/icon/pic.png') {
      wx.showToast({
        title: '请选择插入图片！',
        icon: 'none',
        duration: 2000
      })
      return false;
    } else {
      if (!winnerNum) {
        winnerNum = 1;
      }
      if (!maxnum) {
        maxnum = 1;
      }
      if (!coin) {
        coin = 0;
      }
      if (!introduce) {
        introduce = '';
      }
      if(!sponsor){
        sponsor = app.globalData.userInfo.nickName;
      }
    }
    //just for debug
    this.setData({
      lotteryName: lotteryName,
      introduce: introduce,
      prizeName: prizeName,
      winnerNum: winnerNum,
      maxnum: maxnum,
      coin: coin
    })
    var datatime = this.data.dateEnd + " " + this.data.timeEnd;
    var datatimes = new Date(datatime.replace(/-/g, "/")).getTime() / 1000;
    var mode = this.data.index;
    var cond = 2;
    var pass = this.data.passindex;
    wx.showToast({
      title: '正在上传...',
      icon: 'loading',
      duration: 2800
    })
    this.setData({
      progress: 20,
      disable: true
    });
    wx.request({
      url: 'https://lottery.glede.top/appendlottery.php',
      data: {
        pubid: openid,
        lotteryname: lotteryName,
        introduce: introduce,
        prizename: prizeName,
        coin: coin,
        winnernum: winnerNum,
        cond: 2,
        lotterytime: datatimes,
        maxnum: maxnum,
        lotterypassword: pass,
        mode: mode,
        cla:cla,
        uncover: 0,
        sponsor:sponsor
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        //文字上传成功，接下来上传图片
        //console.log(res.data)
        if (res.data.msg == "success") {
          that.setData({
            lotteryid: res.data.id,
            progress: 40,
            disable: true
          });
          wx.uploadFile({
            url: 'https://lottery.glede.top/uploadpic.php',
            filePath: that2.data.imgurl[0],
            name: 'file',
            formData: {
              id: res.data.id
            },
            success(res) {
              const data = res.data;
              //console.log(data);
              that2.setData({
                progress: 60,
                disable: true
              });
              var sence = "id=" + that2.data.lotteryid;
              var lotteryid = that2.data.lotteryid;
              //未获取二维码(需要发布后)
              that3.setData({
                progress: 100,
                qrurl: ''
              })
              wx.showToast({
                title: '成功',
                icon: 'success',
                duration: 2000
              })
              that3.formReset();
              var urlto = "../detail/detail?id=" + that3.data.lotteryid;
              wx.navigateTo({
                url: urlto,
              })
              //图片上传成功，接下来获取二维码(需要发布后)
              /*
              wx.request({
                url: 'https://lottery.glede.top/getqr.php',
                data: {
                  sence: sence,
                  id: lotteryid
                },
                method: 'POST',
                header: {
                  'content-type': 'application/x-www-form-urlencoded'
                },
                success: function(res) {
                  //console.log(res.data);
                  that3.setData({
                    progress: 100,
                    qrurl: res.data.url
                  })
                  //完全成功
                  wx.showToast({
                    title: '成功',
                    icon: 'success',
                    duration: 2000
                  })
                }
              })
              */
            }
          })
        } else {
          var errorres = '上传失败，请联系我们，错误原因：' + res.data.msg;
          wx.showToast({
            title: errorres,
            icon: 'none',
            duration: 3000
          })
          that2.setData({
            progress: 100,
            disable: false
          });
        }
      },
      fail: function(res) {
        wx.showToast({
          title: '上传失败，请联系我们，错误码：20001',
          icon: 'none',
          duration: 2000
        })
        that2.setData({
          progress: 100,
          disable: false
        });
      }
    });
  },
  bindPassChange:function(e){
    this.setData({
      passindex:e.detail.value
    })
  },
  bindClassChange: function(e) {
    this.setData({
      menuindex: e.detail.value
    })
  },
  bindModeChange: function(e) {
    //console.log('picker发送选择改变，携带值为', e.detail.value)
    this.setData({
      index: e.detail.value,
      mode: e.detail.value
    })
  },
  /*
  bindStartDateChange: function(e) {
    this.setData({
      dateStart: e.detail.value
    })
  },
  bindStartTimeChange: function(e) {
    this.setData({
      timeStart: e.detail.value
    })
  },*/
  bindEndDateChange: function(e) {
    this.setData({
      dateEnd: e.detail.value
    })
  },
  bindEndTimeChange: function(e) {
    this.setData({
      timeEnd: e.detail.value
    })
  },
  formReset() {
    //console.log('form发生了reset事件')
    this.setData({
      disable:false,
      menuindex: 0,
      index: 0,
      imgurl: '../../res/icon/pic.png',
      dateStart: "2019-04-01",
      dateEnd: "2019-04-17",
      timeStart: "00:00",
      timeEnd: "00:00"
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function(options) {},

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function() {

  }
})