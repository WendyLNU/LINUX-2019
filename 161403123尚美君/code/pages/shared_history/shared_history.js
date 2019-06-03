// pages/review_history/review_history.js
var libraryService = require("../../common/service/LibraryService.js")
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
    var that = this;
    libraryService.getSharedHistory(function(res){
      that.setData({
        list: res.data.data
      });
     
    });
  },
  tapItem:function(e){
    var that = this;
    var index = e.currentTarget.id;
    var list = that.data.list;
    wx.setClipboardData({
      data: list[index].code,
      success: function(res) {
        wx.showToast({
          icon:'none',
          title: '已经复制分享码',
        })
      },
    })
  },

  openMenu:function(e){
    var that = this;
    var index = e.currentTarget.id;
    var list = that.data.list;
    console.log(list[index]);
    wx.showActionSheet({
      itemList: ["取消分享","复制分享码"],
      success: function(res) {
        switch (res.tapIndex) {
          case 0:
            wx.showToast({
              title: '操作中..',
              icon: 'loading'
            })
            libraryService.deleteSharedHistory(list[index].id, function (res) {
              wx.hideToast();
              libraryService.getSharedHistory(function (res) {
                that.setData({
                  list: res.data.data
                });
              });
            });
            break;
          case 1:
            wx.setClipboardData({
              data: list[index].code,
              success: function (res) {
                wx.showToast({
                  icon: 'none',
                  title: '已经复制分享码',
                })
              },
            })
            break;
        }
       
      },
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