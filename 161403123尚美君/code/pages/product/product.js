// pages/product/product.js
var marketService = require("../../common/service/MarketService.js")
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },
  correct:function(){
    wx.navigateTo({
      url: '/pages/correct/correct',
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

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

  buy:function(){
    var that=this;
    wx.showToast({
      title: '正在请求..',
      icon: 'loading',
      duration: 30*1000,
      mask: true
    })
    marketService.buyLibrary(22,function(){
      wx.showToast({
        title: '购买成功',
        duration: 500,
        icon: "ok",
        success: function () {
          setTimeout(function () {
         
            wx.showToast({
              title: '导入中..',
              icon: 'loading',
              duration: 30 * 1000,
              mask: true
            })
            marketService.importLibrary(22,function(){
             wx.showToast({
               title: '导入成功',
             })
            })
          }, 800)

        }

      })
    });
    
  }
})