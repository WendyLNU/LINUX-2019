// pages/other/xinyuan.js
var app = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    pagenow: "",
    havepost: false,
    xinyuan: '',
    qiandaoyu: "点我签到, 随机获取10~100乐币",
    ifqiandao: false,
    buttontext: "点击提交",
    xinshouyu: "点我随机获取50~300乐币",
    ifxinshou: false,
  },

  postit: function(e) {
    var that = this;
    this.setData({
      havepost: true,
      buttontext: "正在提交..."
    })
    var formId = e.detail.formId;
    var xinyuan = e.detail.value.xinyuan;
    wx.request({
      url: 'https://lottery.glede.top/xinyuan.php',
      data: {
        xinyuan: xinyuan,
        formid: formId
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        if (res.data.msg == "success") {
          wx.showToast({
            title: '成功提交',
            icon: 'success',
            duration: 2000
          })
          that.setData({
            havepost: true,
            buttontext: "您已提交"
          })
        } else {
          wx.showToast({
            title: '提交失败，请检查网络',
            icon: 'none',
            duration: 2000
          })
        }
      }
    })
  },

  previewimg1: function() {
    wx.previewImage({
      current: "https://lottery.glede.top/images/local.png", // 当前显示图片的http链接
      urls: ["https://lottery.glede.top/images/local.png"] // 需要预览的图片http链接列表
    })
  },
  previewimg2: function() {
    wx.previewImage({
      current: 'https://lottery.glede.top/images/front.jpg', // 当前显示图片的http链接
      urls: ['https://lottery.glede.top/images/front.jpg'] // 需要预览的图片http链接列表
    })
  },
  previewimg3: function() {
    wx.previewImage({
      current: 'https://lottery.glede.top/images/manage.png', // 当前显示图片的http链接
      urls: ['https://lottery.glede.top/images/manage.png'] // 需要预览的图片http链接列表
    })
  },
  previewimg4: function() {
    wx.previewImage({
      current: "https://lottery.glede.top/images/show.png", // 当前显示图片的http链接
      urls: ["https://lottery.glede.top/images/show.png"] // 需要预览的图片http链接列表
    })
  },
  previewimg5: function() {
    wx.previewImage({
      current: "https://lottery.glede.top/images/bigdata.png", // 当前显示图片的http链接
      urls: ["https://lottery.glede.top/images/bigdata.png"] // 需要预览的图片http链接列表
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function(options) {
    var timestamp = Date.parse(new Date()) / 1000;
    var that = this;
    var that2 = this;
    //签到
    wx.getStorage({
      key: 'qiandaoriqi',
      success(res) {
        //判断有没有过一天
        //console.log(res)
        if (timestamp - res.data >= 86400) {
          that.setData({
            qiandaoyu: "点我签到, 随机获取10~100乐币",
            ifqiandao: false
          })
        } else {
          that.setData({
            qiandaoyu: "一天后再来签到哦",
            ifqiandao: true
          })
        }
      },
      fail(res) {
        wx.setStorage({
          key: 'qiandaoriqi',
          data: timestamp
        })
      }
    })
//新手
    wx.getStorage({
      key: 'xinshouriqi',
      success(res) {
        //判断有没有过7天
        //console.log(res)
        if (timestamp - res.data >= 86400*7) {
          that.setData({
            xinshouyu: "点我随机获取50~300乐币",
            ifxinshou: false
          })
        } else {
          that.setData({
            xinshouyu: "7天后再来签到吧",
            ifxinshou: true
          })
        }
      },
      fail(res) {
        wx.setStorage({
          key: 'xinshouriqi',
          data: timestamp
        })
      }
    })
    this.setData({
      pagenow: options.page
    })
  },
  //签到
  randomNum: function(minNum, maxNum) {
    switch (arguments.length) {
      case 1:
        return parseInt(Math.random() * minNum + 1, 10);
        break;
      case 2:
        return parseInt(Math.random() * (maxNum - minNum + 1) + minNum, 10);
        break;
      default:
        return 0;
        break;
    }
  },
  qiandaonow: function() {
    var timestamp = Date.parse(new Date()) / 1000;
    var lecoin = this.randomNum(10, 100);
    var title = "获"+lecoin+"乐币!";
    var that = this;
    wx.request({
      url: 'https://lottery.glede.top/addcoin.php',
      data: {
        userid: app.globalData.userid,
        add: lecoin
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        wx.showToast({
          title: title,
          icon: 'success',
          duration: 2000
        })
        //console.log(res.data)
        that.setData({
          qiandaoyu: "签到成功，一天后再来签到哦",
          ifqiandao: true
        })
        wx.setStorage({
          key: 'qiandaoriqi',
          data: timestamp
        })
      }
    })
  },
  xinshounow: function () {
    var timestamp = Date.parse(new Date()) / 1000;
    var lecoin = this.randomNum(50, 300);
    var title = "获" + lecoin + "乐币!";
    var that = this;
    wx.request({
      url: 'https://lottery.glede.top/addcoin.php',
      data: {
        userid: app.globalData.userid,
        add: lecoin
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        wx.showToast({
          title: title,
          icon: 'success',
          duration: 2000
        })
        //console.log(res.data)
        that.setData({
          xinshouyu: "7天后再来签到吧",
          ifxinshou: true
        })
        wx.setStorage({
          key: 'xinshouriqi',
          data: timestamp
        })
      }
    })
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function() {},

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