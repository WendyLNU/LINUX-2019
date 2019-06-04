//app.js，@作者：戚子强
App({
  //小程序全局变量数据
  globalData: {
    userInfo: null,
    usercode: null,
    userid: null,
    nikename: null
  },
  onLaunch: function() {
    // 先从本地缓存获取用户信息，没有的话再去微信服务器索取，节约时间
    try {
      const value = wx.getStorageSync('userInfo')
      if (value) {
        this.globalData.userInfo = value;
        this.globalData.nikename = value.nikename;
      }
    } catch (e) {}
    if (this.globalData.userInfo == null) {
      wx.getSetting({
        success: res => {
          if (res.authSetting['scope.userInfo']) {
            // 已经授权，可以直接调用 getUserInfo 获取头像昵称，不会弹框
            wx.getUserInfo({
              success: res => {
                // 可以将 res 发送给后台解码出 unionId
                this.globalData.userInfo = res.userInfo
                // 由于 getUserInfo 是网络请求，可能会在 Page.onLoad 之后才返回
                // 所以此处加入 callback 以防止这种情况
                if (this.userInfoReadyCallback) {
                  this.userInfoReadyCallback(res)
                }
              }
            })
          }
        }
      })
    }
  }
})