// pages/manage_system/manage_select_view.js
var service = require("../../common/service/LibraryService.js");
var App = getApp();
var createLibModal = {
  type: "input",
  title: "创建记忆库",
  content: "创建一个新的记忆库",
  button: "创建",
  bindconfirm: "createLib",
  placeholder: "输入新记忆库的名称"
}
var hiddenModal = {
  type: "hidden",
  title: "",
  content: "",
  button: "",
  bindconfirm: "",
  placeholder: ""
}
Page({

  /**
   * 页面的初始数据
   */
  data: {
    basePath: "library",
    options: {},
    confirm: {
      disable: true
    },
    which: {},
    path: [],
    currentPathId: null,
    list: [],
    modalObject: {
      type: "hidden",
      title: "",
      content: "",
      button: "",
      bindconfirm: "",
      placeholder: ""
    },
  },
  onPullDownRefresh: function () {
    var that = this;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    });
    that.getList(function () {
      wx.stopPullDownRefresh()
    });
  },
  tapItem: function (e) {
    var that = this;
    var which = that.data.which = that.data.list[e.currentTarget.dataset.index];
    var path = that.data.path;
    path.push(which)
    
    service.getList(which.id, function (res) {
      if (that.data.options.usedTo != 'saveMemory'&&res.data.data.length==0){
        that.tapItemButton(e);
        wx.showToast({
          icon:'none',
          title: '该记忆库下没有记忆库',
        })
        path.pop();
        return;
      }
      
      that.data.currentPathId = which.id;
      that.data.path = path;
      console.log(res)
      var confirm = {
        disable: true
      }
      that.setData({
        list: res.data.data,
        path: that.data.path,
        confirm: confirm
      }, function () {
        wx.hideToast();
      });
    });
  },
  tapItemButton: function (e) {
    var that = this;
    var list = that.data.list;
    var index = e.currentTarget.dataset.index;
    var which = that.data.which = that.data.list[e.currentTarget.dataset.index];
    if (that.data.options.type == "select") {
      for (var i = 0; i < list.length; i++) {
        list[i].chosen = false
      }
      list[Number(index)].chosen = true;
      var confirm = {
        disable: false
      }
      that.setData({
        list: list,
        confirm: confirm,
      });

    }
  },
  confirm: function (e) {
    if (this.data.confirm.disable) {
      return;
    }
    var usedTo = this.data.options.usedTo;
    var that = this;
    var which = that.data.which;
    var items = that.data.items;
    if (usedTo == "saveMemory") {//用于添加记忆时执行的功能
      var pages = getCurrentPages()
      var prevPage = pages[pages.length - 1] //当前界面
      var prevPage = pages[pages.length - 2] //上一个页面
      prevPage.setData({
        saveTo: which
      });
      wx.navigateBack({
        delta: 1
      })
    } else if (usedTo == "reviewLibrary") {//用户回顾记忆库时执行功能
      wx.redirectTo({
        url: '/pages/review_system/review_system?lid=' + which.id,
      })
    } else if (usedTo == "importMemory") {
      var pages = getCurrentPages()
      var prevPage = pages[pages.length - 1] //当前界面
      var prevPage = pages[pages.length - 2] //上一个页面
      prevPage.importMemory(which.id);
    } else if (usedTo == "recieveLibrary"){
      wx.showToast({
        title: '操作中..',
        mask: true,
        duration: 30 * 1000,
        icon: 'loading'
      })
      service.acquireLibrary(which.id, this.data.options.code, function (res) {
        wx.showToast({
          title: '接受完成..',
        })
        wx.navigateBack({
          delta:1
        })
      })
    }

  },

  //获取列表
  getList: function (callback) {
    var that = this;
    var confirm = {
      disable: true
    }
    service.getList(that.data.currentPathId, function (res) {
      that.setData({
        list: res.data.data,
        path: that.data.path,
        confirm: confirm
      }, function () {
        wx.hideToast();
        if (callback)
          callback()
      });
    });
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    var that = this;
    this.setData({
      options: options,
      basePath: options.target + '/'
    }, function () {
      that.getList(function () {

      });
    });
  },

  //返回上一层
  goBack: function () {
    var that = this;
    var path = that.data.path;
    if (path.length == 1) {
      that.data.currentPathId = null;
    } else {
      that.data.currentPathId = path[path.length - 2].id;
    }
    path.pop();

    that.getList(function () {
    });

  },

  create:function(){
    var that=this;
    that.setData({
      modalObject: createLibModal
    });
  },
  createLib: function (res) {
    var that = this;
    var id = that.data.currentPathId;
    var name = res.detail.value;
    wx.showToast({
      title: '操作中..',
      mask: true,
      duration: 30 * 1000,
      icon: 'loading'
    })
    that.setData({
      modalObject: hiddenModal
    });
    service.create(id, name, function (res) {
      that.getList();
    });

  },

})