var App=getApp();
var utilService = require("../../common/service/UtilService.js")
Page({

  /**
   * 页面的初始数据
   */
  data: {
    masterNumber:0,
    notMasterNumber:0
  },

  onLoad: function () {
    var that = this;
    wx.showToast({
      title: '正在登陆',
      icon: 'loading',
      image: '',
      duration: 2000000,
      mask: true,
    })
  },

  onShow: function () {
    var that = this;

    utilService.getMasterNumb(function(res){
      wx.hideToast();
      that.setData({
        masterNumber: res.data.data.masterNumb,
        notMasterNumber: res.data.data.notMasterNumb,
      },function(){1
      });
    })
  },

  //跳转到开始回顾页面
  goStart: function(){
    wx.navigateTo({
      url: '../start_review/start_review',
    })
  },

  //跳转到写入记忆页面
  goWrite: function(){
    wx.showActionSheet({
      itemList: [ '直接添加记忆', '文字生成记忆'],
      success: function (res) {
        switch (res.tapIndex) {
          case 0:
            wx.navigateTo({
              url: '../add_memory/add_memory',
            })
            break;
          case 1:
            wx.navigateTo({
              url: '../add_memories/add_memories',
            })
            break;
        }
      }
    })
   
  },
})