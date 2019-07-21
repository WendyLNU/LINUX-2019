//index.js，@作者：戚子强
//获取应用实例
const app = getApp()

function getRandomColor() {
  const rgb = []
  for (let i = 0; i < 3; ++i) {
    let color = Math.floor(Math.random() * 256).toString(16)
    color = color.length == 1 ? '0' + color : color
    rgb.push(color)
  }
  return '#' + rgb.join('')
}


Page({
  //页面数据
  data: {
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    targetId: '',
    mycode: '',
    myopenid: '',
    lotteryname: '',
    introduce: '',
    prizename: '',
    coin: null,
    winnernum: 1,
    lotterytime: '',
    maxnum: 1,
    lotterypassword: '',
    imgurl: '',
    cond: '',
    sponsor: '',
    mycoin: null,
    candel: 'none'
  },

  onReady(res) {},
  onLoad: function(options) {
    //检查获取权限
    if (app.globalData.userInfo) {
      this.setData({
        userInfo: app.globalData.userInfo,
        hasUserInfo: true
      })
    } else if (this.data.canIUse) {
      // 由于 getUserInfo 是网络请求，可能会在 Page.onLoad 之后才返回所以此处加入 callback 以防止这种情况
      app.userInfoReadyCallback = res => {
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    }
    var that = this;
    var that2 = this;
    //换取OPENID
    wx.login({
      success: res => {
        app.globalData.usercode = res.code;
        this.setData({
          mycode: res.code
        })
        // 获取openid
        if (that.data.myopenid == '') {
          //console.log("llldsds");
          wx.request({
            url: "https://lottery.glede.top/getopenid.php",
            data: {
              code: this.data.mycode
            },
            method: 'POST',
            header: {
              'content-type': 'application/x-www-form-urlencoded'
            },
            success(res) {
              app.globalData.userid = res.data.openid;
              that.setData({
                myopenid: res.data.openid
              })
              //判断是否需要注册
              try {
                const value = wx.getStorageSync('hasLogup')
                if (!value) {
                  wx.request({
                    url: "https://lottery.glede.top/appenduser.php",
                    data: {
                      id: app.globalData.userid,
                      coin: 0,
                      partinnum: 0,
                      pubnum: 0,
                      lucknum: 0
                    },
                    method: 'POST',
                    header: {
                      'content-type': 'application/x-www-form-urlencoded'
                    },
                    success(res) {
                      //console.log(res.data.msg);
                      wx.setStorage({
                        key: 'hasLogup',
                        data: 'true'
                      })
                    }
                  })
                }
              } catch (e) {}
            }
          })
        }
      }
    })
    //console.log(app.globalData.userid);
    /*增加金币
    wx.request({
      url: 'https://lottery.glede.top/addcoin.php',
      data: {
        userid: app.globalData.userid,
        add: 7
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function (res) {
        //console.log(res.data)
      }
    })
    */
    this.setData({
      targetId: options.id,
    })
    this.onPullDownRefresh();
  },

  //下拉刷新事件
  onPullDownRefresh: function() {
    var that = this;
    var that2 = this;
    var that3 = this;
    var that4 = this;
    var lotteryid = this.data.targetId;
    //获取图文
    wx.request({
      url: "https://lottery.glede.top/showlotteryall.php",
      data: {
        id: lotteryid,
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success(res) {
        if (res.data[1] == app.globalData.userid) {
          that2.setData({
            candel: ''
          })
        }
        that2.setData({
          lotteryname: res.data[2],
          introduce: res.data[3],
          prizename: res.data[4],
          coin: res.data[5],
          winnernum: res.data[6],
          lotterytime: res.data[7],
          maxnum: res.data[8],
          lotterypassword: res.data[9],
          imgurl: "https://lottery.glede.top/uploadimages/" + res.data[11],
          cond: "至少满" + res.data[8] + "人开奖，现已参与" + res.data[13] + "人；最早开奖时间：" + that3.fmtDate(Number(res.data[7]), 'Y年M月D日 h:m:s'),
          sponsor: res.data[12]
        })
        //判断金币够不够
        wx.request({
          url: "https://lottery.glede.top/define.php",
          data: {
            userid: app.globalData.userid
          },
          method: "POST",
          header: {
            'content-type': 'application/x-www-form-urlencoded'
          },
          success: function(res) {
            var coin = Number(that4.data.coin);
            var mycoin = Number(res.data.userinfo[0]);
            if (mycoin < coin) {
              that4.setData({
                isdisable: true,
                joinbuttontext: "您的乐币不足"
              })
            } else {}
          },
          fail: function(err) {}, //请求失败
          complete: function() {} //请求完成后执行的函数
        })
      }
    })
    //检查是否参加了活动
    var userid = app.globalData.userid;
    var lotteryid = this.data.targetId;
    wx.request({
      url: "https://lottery.glede.top/ifpartin.php",
      data: {
        lotteryid: lotteryid,
        userid: userid
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success(res) {
        var flag = null;
        if (res.data.flag == "1") {
          flag = true;
        } else {
          flag = false;
        }
        var des = flag ? "您已参与了此次抽奖" : "点击参与抽奖";
        that.setData({
          isdisable: flag,
          joinbuttontext: des
        })
      }
    })
    wx.stopPullDownRefresh();
  },
  onShareAppMessage: function() {

  },
  joinlottery: function(e) {
    var that = this;
    var formId = e.detail.formId;
    //console.log(formId);
    wx.request({
      url: "https://lottery.glede.top/appendinfo.php",
      data: {
        formid: e.detail.formId,
        lotteryid: this.data.targetId,
        userid: app.globalData.userid,
        coin: this.data.coin
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success(res) {
        that.setData({
          isdisable: true,
          joinbuttontext: "您已参与抽奖"
        })
      }
    })
  },
  getUserInfo: function(e) {
    if (e.detail.userInfo == null) {} else {
      app.globalData.userInfo = e.detail.userInfo
      wx.setStorage({
        key: 'userInfo',
        data: e.detail.userInfo
      })
      this.setData({
        userInfo: e.detail.userInfo,
        hasUserInfo: true
      })
    }
  },
  randomNum: function(minNum, maxNum) {
    switch (arguments.length) {
      case 1:
        return parseInt(Math.random() * minNum + 1, 10);
        break;
      case 2:
        return parseInt(Math.random() * (maxNum - minNum + 1) + minNum, 10);
        break;
      default:
        return 0;
        break;
    }
  },
  dellottery: function() {
    wx.request({
      url: "https://lottery.glede.top/dellottery.php",
      data: {
        lotteryid: this.data.targetId,
        id:app.globalData.userid
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success(res) {
        wx.showToast({
          title: '删除成功，请退出此页面',
          icon: 'none',
          duration: 3000
        })
      }
    })
  },
  /*
  fmtDate: function(nS) {
      return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/, ' ');
  },
  */
  formatNumber: function(n) {
    n = n.toString()
    return n[1] ? n : '0' + n
  },
  fmtDate: function(number, format) {
    var formateArr = ['Y', 'M', 'D', 'h', 'm', 's'];
    var returnArr = [];
    var date = new Date(number * 1000);
    returnArr.push(date.getFullYear());
    returnArr.push(this.formatNumber(date.getMonth() + 1));
    returnArr.push(this.formatNumber(date.getDate()));
    returnArr.push(this.formatNumber(date.getHours()));
    returnArr.push(this.formatNumber(date.getMinutes()));
    returnArr.push(this.formatNumber(date.getSeconds()));
    for (var i in returnArr) {
      format = format.replace(formateArr[i], returnArr[i]);
    }
    return format;
  },
  mulstring: function(str, num) {
    var strs = "";
    for (var i = 0; i < num; i++) {
      strs += str;
    }
    return strs;
  }
})