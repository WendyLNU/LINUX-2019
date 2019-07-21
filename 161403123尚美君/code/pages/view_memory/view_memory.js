var memoryService = require("../../common/service/MemoryService.js");
var App = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    memory:null,
    className:{
      show: "show",
      hidden: "hidden",
      title:"title",
      body:"body"
    },
    loadStatus:[],
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this;
    var id = options.id;
    wx.showToast({
      title: '正在加载',
      icon:'loading'
    })
    memoryService.getMemory(id,function(res){
      that.setData({
        memory: res.data.data,
      },function(){
        wx.hideToast();
      });
    })
 
    
  },
  changeStatus: function () {
    var that = this;
    
      wx.showActionSheet({
        itemList: ['加入回顾队列', '编辑记忆'],
        success: function (res) {
          console.log(res.tapIndex);
          if (res.tapIndex == 0) {
            wx.navigateTo({
              url: "../manage_queue/manage_queue?type=select&usedTo=insertToQueue&mid=" + that.data.memory.id,
            })
          } else {
            memoryService.edit(that.data.memory.id);
          }
        }
      })
    
  },

  loadFinish:function(e){
    var id = e.currentTarget.id;
    var that = this;
    that.data.loadStatus[id]=true;
    that.setData({
      loadStatus: that.data.loadStatus
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
    var that = this;
    wx.showToast({
      title: '正在加载',
      icon: 'loading'
    })
    if (that.data.memory){
      memoryService.getMemory(that.data.memory.id, function (res) {
        that.setData({
          memory: res.data.data
        }, function () {
          wx.hideToast();
        });
      })
    }
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

  },
  previewImage: function (e) {
    var current = [];
    current.push(e.target.dataset.src);
    wx.previewImage({
      urls: current// 需要预览的图片http链接列表
    })
  }  

})