// pages/review_history/review_history.js
var memoryService = require("../../common/service/MemoryService.js");
Page({

  /**
   * 页面的初始数据
   */
  data: {
    list: []
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function(options) {
    var pages = getCurrentPages()
    if (pages.length >= 2) {
      var prevPage = pages[pages.length - 2] //上一个页面
      console.log(prevPage.data.reviewedList);
      this.setData({
        list: prevPage.data.reviewedList
      });
    }
  },
  viewMemory: function(e) {
    var that = this;
    var which = that.data.list[e.currentTarget.dataset.index];
    memoryService.view(which.id)
  },
  tapItemButton: function(e) {
    var that = this;
    var list = that.data.list;
    var index = e.currentTarget.dataset.index;
    var which = that.data.which = that.data.list[e.currentTarget.dataset.index];
    wx.showActionSheet({
      itemList: ['稍后再次回顾'],
      success: function(res) {
        switch (res.tapIndex) {
          case 0:
            var pages = getCurrentPages()
            if (pages.length >= 2) {
              var prevPage = pages[pages.length - 2] //上一个页面
              prevPage.addToNotMasteredList(which,function(){
                wx.showToast({
                  title: '设置成功',
                })
              })
            }
          
            break;
        }
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
  // onShareAppMessage: function () {

  // }
})