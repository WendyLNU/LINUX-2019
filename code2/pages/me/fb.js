// pages/mycj/mycj.js
var sliderWidth = 96; // 需要设置slider的宽度，用于计算中间位置
var app = getApp();
Page({
  /**
   * 页面的初始数据
   */
  data: {
    tabs: ["进行中", "已结束"],
    ongoing: 1,
    done: 1,
    activeIndex: 0,
    sliderOffset: 0,
    sliderLeft: 0,
    lotterynamelist: [],
    lotteryidlist: [],
    lotterynamelistnone: [],
    lotteryidlistnone: []
  },
  onLoad: function () {
    //console.log("hhhhhhhh");
    var that = this;
    wx.getSystemInfo({
      success: function (res) {
        that.setData({
          sliderLeft: (res.windowWidth / that.data.tabs.length - sliderWidth) / 2,
          sliderOffset: res.windowWidth / that.data.tabs.length * that.data.activeIndex
        });
      }
    })
    wx.request({
      url: "https://lottery.glede.top/getmyfb.php",
      data: {
        userid: app.globalData.userid
      },
      method: "POST",
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        //console.log(res.data);
        that.setData({
          lotterynamelist: res.data.name,
          lotteryidlist: res.data.id,
          lotterynamelistnone: res.data.namenone,
          lotteryidlistnone: res.data.idnone
        })
      }
    })
  },
  tabClick: function (e) {
    this.setData({
      sliderOffset: e.currentTarget.offsetLeft,
      activeIndex: e.currentTarget.id
    });


  },

  /**
   * 生命周期函数--监听页面加载
   */


  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})