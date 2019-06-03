// var host = "http://localhost:8080/Memorinn/";
var host = "https://logicforeach.net/Memorinn/"
var token=null;
App({
  data: {},
  /**
   * 当小程序初始化完成时，会触发 onLaunch（全局只触发一次）
   */
  onLaunch: function() {

  },

  /**
   * 当小程序启动，或从后台进入前台显示，会触发 onShow
   */
  onShow: function(options) {

  },

  /**
   * 当小程序从前台进入后台，会触发 onHide
   */
  onHide: function() {

  },

  /**
   * 当小程序发生脚本错误，或者 api 调用失败时，会触发 onError 并带上错误信息
   */
  onError: function(msg) {

  },
  login: function(success) {
    //console.log("执行login方法,重新申请token");
    var that = this;
    var time = new Date().getTime();
    wx.login({
      success: function(res) {
        if (res.code) {
          wx.request({
            url: host + "/user/weChatLogin",
            data: {
              code: res.code
            },
            method: "POST",
            header: {
              'content-type': 'application/x-www-form-urlencoded',
            },
            success: function(res) {
              console.log("重新登录响应时间:");
              console.log((new Date().getTime() - time) * 0.001);
              //token
              token = res.data;
              //console.log("setStorage token :" + token);
              if (success) {
                success(res.data);
              }
              wx.setStorage({
                key: 'token',
                data: res.data,
                success: function() {
                }
              });

            },
            fail: function(error) {
              wx.showToast({
                title: '登录异常',
                icon: 'icon'
              });
              that.onLaunch();
            }
          })
        } else {

        }
      }
    })
  },
  requestAPI: function(url, data, success, error) {
    var that = this;
    var time = new Date().getTime();
    var requestObject = {//wx.request方法的参数
      url: host + url,
      data: data,
      method: "POST",
      header: {
        'Token': token,
        'content-type': 'application/json;charset=utf-8',
      },
      success: function (res) {
        console.log("请求响应时间:");
        console.log((new Date().getTime() - time) * 0.001);
        if (res.data.status == 'error') {
          if (res.data.msg == "Token expired") {
            //console.log("Token expired");
            that.login(function () {
              that.requestAPI(url, data, success, error);
            });
          } else {
            wx.hideToast();
            wx.showModal({
              title: '服务器程序异常',
              content: res.data.msg,
              showCancel: false
            })
          }

        }
        success(res);

      },
      fail: function (info) {
        if (error) {
          error(info);
        }
        wx.showToast({
          title: '网络异常',
          icon: 'none'
        });
      }
    }//end requestObject

    if(token==null){
      //console.log("token is null");
      wx.getStorage({
        key: 'token',
        success: function(res) {
          token = res.data;
          //console.log("getStorage token :" + token);
          requestObject.header.Token = token;
          //request
          wx.request(requestObject);
          //end request

        },
        fail: function(error) {
          //console.log("getStorage fail");
          that.login(function() {
            that.requestAPI(url, data, success, error);
          });
        }
      })
    }else{//内存中有token

      //request
      //console.log("token is not null");
      wx.request(requestObject);
      //end request
    }
    

  },
  getHost: function() {
    return host;
  },
  encode: function(str) {
    str = str.replace(/\+/g, "%2B");
    str = str.replace(/ /g, "%20");
    str = str.replace(/\//g, "%2F");
    str = str.replace(/\?/g, "%3F");
    str = str.replace(/#/g, "%23");
    str = str.replace(/\&/g, "%26");
    str = str.replace(/=/g, "%3D");
    str = str.replace(/\%/g, "%25");
    return str;
  },
  decode: function(str) {
    str = str.replace(/%25/g, "%");
    str = str.replace(/%2B/g, "+");
    str = str.replace(/%20/g, " ");
    str = str.replace(/%2F/g, "/");
    str = str.replace(/%3F/g, "?");
    str = str.replace(/%23/g, "#");
    str = str.replace(/%26/g, "&");
    str = str.replace(/%3D/g, "=");
    return str;
  }
})