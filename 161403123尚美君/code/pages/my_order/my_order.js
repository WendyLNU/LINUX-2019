var sliderWidth = 96; // 需要设置slider的宽度，用于计算中间位置
var marketService = require("../../common/service/MarketService.js")
Page({
  data: {
    tabs: ["我出售的", "我购买的"],
    activeIndex: 0,
    sliderOffset: 0,
    sliderLeft: 0,
    list:[],
    list2:[]
  },
  onLoad: function () {
    var that = this;
    wx.getSystemInfo({
      success: function (res) {
        that.setData({
          sliderLeft: (res.windowWidth / that.data.tabs.length - sliderWidth) / 2,
          sliderOffset: res.windowWidth / that.data.tabs.length * that.data.activeIndex
        });
      }
    });
    marketService.getSalesHistory(function(res){
      that.setData({
        list: res.data.data
      })
    });
    marketService.getPurchaseHistory(function(res){
      that.setData({
        list2: res.data.data
      })
    });
  },
  tabClick: function (e) {
    this.setData({
      sliderOffset: e.currentTarget.offsetLeft,
      activeIndex: e.currentTarget.id
    });
  },
  checkHistory1:function(e){
    var that = this;
    var id = e.currentTarget.id;
    wx.showActionSheet({
      itemList: ['撤销申请'],
      success:function(){
        marketService.removeSalesHistory(id, function (res) {
          marketService.getSalesHistory(function (res) {
            that.setData({
              list: res.data.data
            })
          });
        });
      }
    })
   
  },
  checkHistory2: function (e) {
    var that = this;
    var id = e.currentTarget.id;
    wx.showActionSheet({
      itemList: ['删除'],
      success: function () {
        marketService.removePurchaseHistory(id, function (res) {
          marketService.getPurchaseHistory(function (res) {
            that.setData({
              list2: res.data.data
            })
          });
        });
      }
    })
   
  }
});