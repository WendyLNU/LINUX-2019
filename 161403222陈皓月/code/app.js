var dataObj=require("data/data.js")
App({
  onLaunch:function()
  {
    wx.setStorageSync('indexList', dataObj.indexList);
  },
})