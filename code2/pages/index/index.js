//index.js，@作者：戚子强
//获取应用实例
const app = getApp()

Page({
  //页面数据
  data: {
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    bannerto: [],
    menuList: [{
      index: 1,
      name: "推荐"
    }, {
      index: 2,
      name: "吃喝"
    }, {
      index: 3,
      name: "美妆"
    }, {
      index: 4,
      name: "日用"
    }, {
      index: 5,
      name: "文娱"
    }, {
      index: 6,
      name: "电子"
    }, {
      index: 7,
      name: "运动"
    }, {
      index: 8,
      name: "服饰"
    }],
    menuLists: [
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
      [
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg",
        "../../res/img/banner1.jpg"
      ],
    ],
    c1List: [],
    c2List: [],
    tabScroll: 0,
    currentTab: 0,
    windowHeight: '',
    windowWidth: '',
    feedHeight: 2160,
    mycode: '',
    myopenid: ''
  },


  onReady(res) {},
  onLoad: function(options) {
    // console.log(decodeURIComponent(options.query.scene));
    /*
    const scene = decodeURIComponent(options.query.scene);
    const page = decodeURIComponent(options.query.page);
    var url = page + "?" + scene;
    wx.navigateTo({
      url: url
    })
    */
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
    // 获取当前设备的宽高
    wx.getSystemInfo({
      success: (res) => {
        this.setData({
          windowHeight: res.windowHeight,
          windowWidth: res.windowWidth
        })
      },
    })
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
    this.onPullDownRefresh();
  },
  clickMenu: function(e) {
    var current = e.currentTarget.dataset.current //获取当前tab的index
    var tabWidth = this.data.windowWidth / 8; //导航tab共5个，获取一个的宽度
    this.setData({
      tabScroll: (current - 2) * tabWidth //使点击的tab始终在居中位置
    })
    if (this.data.currentTab == current) {
      return false
    } else {
      this.setData({
        currentTab: current
      })
    }
  },
  changeContent: function(e) {
    var current = e.detail.current;
    //console.log(current);
    var tabWidth = this.data.windowWidth / 5;
    this.setData({
      currentTab: current,
      tabScroll: (current - 2) * tabWidth
    });
    this.onPullDownRefresh();
  },
  changePageToDetail: function(e) {
    //console.log(e);
    var tourl = "../detail/detail?id=" + e.currentTarget.dataset.toid;
    //console.log(tourl);
    wx.navigateTo({
      url: tourl
    })
  },

  //下拉刷新事件
  onPullDownRefresh: function() {
    var that = this;
    var that2 = this;
    //获取轮播图
    wx.request({
      url: 'https://lottery.glede.top/showconfig.php',
      data: {},
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        //console.log(res.data);
        var templists = new Array();
        var bannertos = new Array();
        for (var i = 0; i < 8; i++) {
          var list1 = new Array();
          var list2 = new Array();
          for (var j = 0; j < 3; j++) {
            var url1 = "https://lottery.glede.top/uploadimages/" + res.data.imglist[3 * i + j];
            var url2 = "../detail/detail?id=" + res.data.idlist[3 * i + j];
            list1.push(url1);
            list2.push(url2);
          }
          templists.push(list1);
          bannertos.push(list2);
        }
        bannertos[0][0] = "other?page=xinshou";
        that.setData({
          menuLists: templists,
          bannerto: bannertos
        })
      }
    })
    var type = new Array("litter", "medium", "big", "wheel");
    var lists1 = new Array();
    var lists2 = new Array();
    var h = 0,
      h1 = 0,
      h2 = 0;
    var cla = this.data.currentTab - 1;
    //瀑布图
    wx.request({
      url: 'https://lottery.glede.top/getlotteryrandom.php',
      data: {
        cla: cla
      },
      method: 'POST',
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success: function(res) {
        //console.log(res.data);
        //左侧
        for (var i = 0; i < 6; i++) {
          var listItem = new Array("http://lottery.glede.top/uploadimages/" + res.data.imglist[i], type[res.data.modelist[i]], res.data.idlist[i]);
          lists1[i] = listItem;
          h1 += listItem[1] == "big" ? 645 : (listItem[1] == "litter" ? 180 : 360);
        }
        that.setData({
          c1List: lists1
        })
        //右侧
        for (var i = 0; i < 6; i++) {
          var j = i + 6;
          var listItem = new Array("http://lottery.glede.top/uploadimages/" + res.data.imglist[j], type[res.data.modelist[j]], res.data.idlist[j]);
          lists2[i] = listItem;
          h2 += listItem[1] == "big" ? 645 : (listItem[1] == "litter" ? 180 : 360);
        }
        h = h1 > h2 ? h1 : h2;
        //console.log("h:" + h1);
        that.setData({
          c2List: lists2,
          feedHeight: h
        })
      }
    })
    wx.stopPullDownRefresh();
    //console.log("refrerh")
  },
  refreshindex: function() {
    this.onPullDownRefresh();
  },
  onShareAppMessage: function() {},
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
})