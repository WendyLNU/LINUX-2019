// pages/search/search.js
var service = require("../../common/service/MemoryService.js")
Page({

  /**
   * 页面的初始数据
   */
  data: {
    list:[]
  },

  onInput:function(e){
    var that = this;
    service.search(e.detail.value,function(res){
      that.setData({
        list:res.data.data
      })
    });
  },
  viewMemory: function (e) {
    var that = this;
    var which = that.data.list[e.currentTarget.dataset.index];
    service.view(which.id)
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
})