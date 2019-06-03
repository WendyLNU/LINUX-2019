var App=getApp();
var libraryService = require("../../common/service/LibraryService.js")
var marketService = require("../../common/service/MarketService.js")
var hidden = {
  type: "hidden",
  title: "",
  content: "",
  button: "",
  bindconfirm: "",
  placeholder: ""
};
var treasureBox = {
  type: "input",
  title: "开启神秘宝箱",
  content: "获取钥匙请关注微信《后浪记忆仓库》公众号",
  button: "开启",
  bindconfirm: "open",
  placeholder: "请输入开启宝箱的钥匙"
};
var warnModal = {
  type: "warn",
  title: "开启失败",
  content: "钥匙不对哟，快去公众号寻找钥匙吧!",
  button: "好哒",
  bindconfirm: "hidden",
  placeholder: ""
}
Page({

  /**
   * 页面的初始数据
   */
  data: {
    modalObject: {
      type: "hidden",
      title: "",
      content: "",
      button: "",
      bindconfirm: "",
      placeholder: ""
    },
    key:""
  },

  onLoad:function(){
   
 
  },
  apply:function(){
    wx.navigateTo({
      url: '../certify/certify',
    })
  },
  goMessage:function(){
    wx.navigateTo({
      url: '../message/message',
    })
  },
  goMyOrder:function(){
    wx.navigateTo({
      url: '../shared_history/shared_history',
    })
  },

  //跳转到记忆库管理页面
  openTreasureBox: function(){
  
    this.setData({
      modalObject: treasureBox
    })
  },
  //跳转到回顾队列页面
  gomanage_queue: function(){
    wx.navigateTo({
      url: '../manage_queue/manage_queue',
    })
  },

  //跳转到记忆管理页面
  goShop: function(){
    wx.navigateTo({
      url: '../market/market',
    })
  },
  
  hidden:function(){
    this.setData({
      modalObject: hidden
    })
  },
  //注销
  logout: function () {
    wx.reLaunch({
      url: '../login/login',
    })
  },
  open: function (e) {
    var that = this;
    //console.log(e.detail.value);
    var key = e.detail.value;
    wx.showToast({
      title: '正在请求..',
      icon: 'loading',
      duration: 200000,
      mask: true
    })
    libraryService.openTreasureBox(key, function (res) {
      that.hidden();
      wx.showToast({
        title: '开启成功',
        duration: 500,
        icon: "ok",
        success: function () {
          setTimeout(function () {
            wx.showToast({
              title: '导入中..',
              icon: 'loading',
              duration: 200000,
              mask: true
            })
            marketService.importLibrary(res.data.data.id, function () {
              wx.showToast({
                title: '导入成功',
              })
            })
          }, 800)

        }

      })
    },function(){
      that.setData({
        modalObject: warnModal
      })
    });

  },
})