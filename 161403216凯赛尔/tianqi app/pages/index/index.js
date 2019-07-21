const app = getApp()

Page({
  data: {
    weather: [],//实况天气
    weatherweek: [],//七日天气
  },
  onLoad: function () {
    this.getapi();
  },
  getapi: function () {
    var _this = this;
    // 获取IP地址
    wx.request({
      url: 'https://ip.tianqiapi.com/',
      data: {
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        console.log(res);
        // 根据IP获取天气数据
        _this.weathertoday(res.data.ip);
        _this.weatherweekday(res.data.ip);
      }
    });
  },
  // 天气api实况天气
  weathertoday: function (ip) {
    var _this = this;
    wx.request({
      url: 'https://www.tianqiapi.com/api/?version=v6',
      data: {
        'ip': ip
      },
      method: 'GET',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        _this.setData({
          weather: res.data
        });
        console.log(_this.data.weather)
      }
    });
  },
  // 天气api实况天气
  weatherweekday: function (ip) {
    var _this = this;
    wx.request({
      url: 'https://www.tianqiapi.com/api/?version=v1',
      data: {
        'ip': ip
      },
      method: 'GET',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        _this.setData({
          weatherweek: res.data
        });
        console.log(_this.data.weatherweek)
      }
    });
  }
})