Page({

  /**
   * 页面的初始数据
   */
 
  data:{

  },
  onShow: function () {
   
  },
  reviewLib:function(){
    wx.navigateTo({
      url: "../manage_select_view/manage_select_view?type=select&target=library&usedTo=reviewLibrary"
    })
  },
  reviewQue: function () {
    wx.navigateTo({
      url: "../manage_queue/manage_queue?type=select&usedTo=reviewQueue"
    })
  },
})