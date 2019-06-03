Page({

  /**
   * 页面的初始数据
   */
  data: {
    imgUrls: [
      '/img/bg/banner.png',
      '/img/bg/banner2.png',
    ],
    indicatorDots: true,
    autoplay: true,
    interval: 5000,
    duration: 1000
  },



  moreProduct:function(){
    wx.navigateTo({
      url: '/pages/market/market',
    })
  },
  checkProduct:function(){
    wx.navigateTo({
      url: '/pages/product/product',
    })
  }
})