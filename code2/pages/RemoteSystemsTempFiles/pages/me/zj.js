// pages/mycj/mycj.js
var app = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    done: 1,
    lotterynamelistnone: [],
    lotteryidlistnone: [],
    over: ["完成一", "完成二"]
  },
  onLoad: function() {
    var that = this;
    wx.request({
      url: "https://lottery.glede.top/getmyluck.php",
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
          lotterynamelistnone: res.data.namenone,
          lotteryidlistnone: res.data.idnone
        })
      }
    })
  },

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