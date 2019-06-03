// pages/correct/correct.js
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },

  tap:function(){
    wx.showModal({
      title: '提交成功',
      content: '我们将会尽快核实并通知作者处理',
      showCancel: false,
      success: function(res) {
        wx.navigateBack({
          delta:1
        })
      },
      fail: function(res) {},
      complete: function(res) {},
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    wx.showModal({
      title: '操作提醒',
      content: '平台承诺将会尽快对用户提交的信息进行核实与处理,并对恶意纠错的用户进行惩罚,您是否要继续?',
      showCancel: true,
      success: function (res) {
        if (res.cancel)
          wx.navigateBack({
            delta: 1
          })
      },
      fail: function (res) { },
      complete: function (res) { },
    })
  },

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
})