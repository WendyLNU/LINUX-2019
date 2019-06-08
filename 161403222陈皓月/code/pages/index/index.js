import {DBindex} from'../../db/DBindex.js';
Page({
  data: {
    indicatorDots:true,
    autoplay:true,
    interval:3000,
    duration:1000,
    array: [],
    imgUrls:[
      "/images/movie/1.jpg", "/images/movie/2.jpg","/images/movie/3.jpg"
    ]
  },
  onLoad: function () {
    var dbindex=new DBindex();
    this.setData({
      indexList: dbindex.getAllindexData()
    });
  },
  onTapToDetail(event) {
    var indexId=event.currentTarget.dataset.indexId;
    console.log(indexId);
    wx.navigateTo({
      url: "../detail/detail?id="+indexId,
    })
  },


  onxiaoxue(event) {
    wx.navigateTo({
      url: "../xiaoxue/xiaoxue"
    })
  },
  onchuzhong(event) {
      wx.navigateTo({
        url: "../chuzhong/chuzhong",
      })
  },
  ongaozhong(event) {
    wx.navigateTo({
      url: "../gaozhong/gaozhong"
    })
  },
  onkaoyan(event) {
    wx.navigateTo({
      url: "../kaoyan/kaoyan"
    })
  },
  onliuxue(event) {
    wx.navigateTo({
      url: "../liuxue/liuxue"
    })
  },
  onyishu(event) {
    wx.navigateTo({
      url: "../yishu/yishu"
    })
  },
  ondongda(event){
    wx.navigateTo({
      url: "../dongda/dongda"
    })
  },
  onliaoda(event) {
    wx.navigateTo({
      url: "../liaoda/liaoda"
    })
  }
  
  
  
  
})
