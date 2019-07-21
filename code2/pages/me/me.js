// pages/me/me.js
const app = getApp();

Page({

  /**
   * 页面的初始数据
   */

  data: {
    avatarUrl: "",
    nickName: "",
    userid: '',
    coin: "",
    mylottery: "",
    myissue: "",
    myluck: ""
  },

  /**

   */
  onShow: function(options) {
    var that = this;
    //获取用户信息
    that.setData({
      avatarUrl: app.globalData.userInfo.avatarUrl,
      nickName: app.globalData.userInfo.nickName,
      userid: app.globalData.userid
    })
    wx.request({
      url: "https://lottery.glede.top/define.php",
      data: {
        userid: app.globalData.userid
      },
      method: "POST",
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        //console.log(res.data);　　　　　　
        that.setData({
          coin: res.data.userinfo[0],
          mylottery: res.data.userinfo[1],
          myissue: res.data.userinfo[2],
          myluck: res.data.userinfo[3]
        })
      },
      fail: function(err) {}, //请求失败
      complete: function() {} //请求完成后执行的函数
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