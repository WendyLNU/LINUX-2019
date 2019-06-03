// pages/manage_queue/manage_queue.js
var service = require("../../common/service/QueueService.js");
var memoryService = require("../../common/service/MemoryService.js");
var createQueueModal = {
  type: "input",
  title: "创建回顾队列",
  content: "创建一个新的回顾队列",
  button: "创建",
  bindconfirm: "createQueue",
  placeholder: "输入新队列的名称"
}
var renameQueueModal = {
  type: "input",
  title: "重命名该队列",
  content: "更改该队列的名称",
  button: "确定",
  bindconfirm: "renameQueue",
  placeholder: "输入新的队列名称"
}
var deleteQueueModal = {
  type: "warn",
  title: "注意",
  content: "删除的队列将无法恢复",
  button: "继续",
  bindconfirm: "deleteQueue",
}
var deleteMemoryModal = {
  type: "warn",
  title: "注意",
  content: "记忆将移出该队列",
  button: "继续",
  bindconfirm: "deleteMemory",
}
var okModal = {
  type: "primary",
  title: "操作成功",
  button: "确定",
  bindconfirm: "hiddenModal",
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
    options: {
    },
    modalObject: {
      type: "hidden",
      title: "",
      content: "",
      button: "",
      bindconfirm: "",
      placeholder: ""
    },
    confirm: {
      disable: true
    },
    which: {},
    whichMemory:{},
    path: [],
    currentPathId: null,
    list: [],
    list2:[]
  },
  onPullDownRefresh: function () {
    var that = this;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    });
    if (that.data.path.length == 0){
      that.getList(function () {
        wx.stopPullDownRefresh()
      });
    }else{
      that.viewQueue(function () {
        wx.stopPullDownRefresh()
      });
    }
   

  },
  tapItem: function (e) {
    var that = this;
    var which = that.data.which = that.data.list[e.currentTarget.dataset.index];
    var path = that.data.path;
    path.push(which)
    if (this.data.options.usedTo=="reviewQueue"){
      return;
    }
    wx.showToast({
      title: '正在加载..',
      icon: 'none',
      image: '',
      duration: 30*1000,
      mask: true,
      success: function(res) {},
      fail: function(res) {},
      complete: function(res) {},
    })
    service.getMemoryList(which.id,function(res){
      that.setData({
        path: path,
        list: [],
        list2:res.data.data
      });
    })


  },
  tapMemory:function(e){
    var that = this;
    var which = that.data.list2[e.currentTarget.dataset.index];
    memoryService.view(which.id)
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

    } else {
      wx.showActionSheet({
        itemList: ['删除', '重命名'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              that.setData({
                modalObject: deleteQueueModal
              })
              break;
            case 1:
              that.setData({
                modalObject: renameQueueModal
              })
              break;
          }
        }
      })
    }
  },


  tapMemoryButton:function(e){
    var that = this;
    var list = that.data.list;
    var index = e.currentTarget.dataset.index;
    var which = that.data.whichMemory = that.data.list2[e.currentTarget.dataset.index];

      wx.showActionSheet({
        itemList: ['移出队列'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              that.setData({
                modalObject: deleteMemoryModal
              })
              break;
          }
        }
      })

  },
  create:function(){
    var that = this;
    that.setData({
      modalObject: createQueueModal
    });
  },
  openBottomSheet: function() {
    var that = this;
    if(that.data.path.length==0){
      wx.showActionSheet({
        itemList: ['添加回顾队列'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              that.setData({
                modalObject: createQueueModal
              });
              break;
          }
        }
      })
    }else{
      wx.showActionSheet({
        itemList: ['批量导入记忆'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              wx.navigateTo({
                url: "../manage_select_view/manage_select_view?type=select&target=library&usedTo=importMemory"
              })
              break;
          }
        }
      })
    }
  
  },
  //创建
  createQueue: function (res) {
    var that = this;
    var id = that.data.currentQueueraryId;
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
    service.create(name, function (res) {
      that.getList();
      
    });
  },

  //删除
  deleteQueue: function () {
    var that = this;
    var which = that.data.which;
    var id = which.id;
    wx.showToast({
      title: '操作中..',
      mask: true,
      duration: 30 * 1000,
      icon: 'loading'
    })
    that.setData({
      modalObject: hiddenModal
    });
    service.remove(id, function (res) {
      that.getList();
    })
  },

  viewQueue:function(success){
    var that = this;
    var qid = that.data.path[0].id;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    service.getMemoryList(qid, function (res) {
      that.setData({
        list2: res.data.data,
        list:[]
      },function(){
        wx.hideToast();
        if (success)
          success();
      });
    })
  },
  //移除记忆
  deleteMemory: function () {
    var that = this;
    console.log("删除记忆,点击确定按钮");
    //输入框内容在res.detail.value
    var which = that.data.whichMemory;
    var mid = which.id;
    var qid = that.data.path[0].id;
    wx.showToast({
      title: '操作中..',
      mask: true,
      duration: 30 * 1000,
      icon: 'loading'
    })
    that.setData({
      modalObject: hiddenModal
    });
    service.removeMemory(qid, mid,function(){
      that.viewQueue(function(){
      });
    })
   

  },
  //重命名
  renameQueue: function (res) {
    var that = this;
    var which = that.data.which;
    var id = which.id;
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
    service.rename(id, name, function () {
      that.getList();
    });
  },
  confirm: function (e) {
    if (this.data.confirm.disable) {
      return;
    }
    var usedTo = this.data.options.usedTo;
    var that = this;
    var which = that.data.which;
    var items = that.data.items;
    if (usedTo == "reviewQueue") {//用于回顾自定义队列时
      wx.redirectTo({
        url: '/pages/review_system/review_system?qid=' + which.id,
      })
    } else if (usedTo == "insertToQueue"){//用于添加入记忆队列时
      service.insertMemory(that.data.options.mid,which.id,function(){
        wx.navigateBack({
          delta: 1,
        })
        wx.showToast({
          title: '添加成功',
          success:function(){
          }
        })
      })
    }

  },
  importMemory:function(lid){
    var that = this;
    var qid = that.data.path[0].id
    service.importMemory(qid,lid,function(res){
      that.viewQueue(function(){
        wx.navigateBack({
          delta:1
        })
      })
    })
  },

  //获取列表
  getList: function (callback) {
    var that = this;
    var confirm = {
      disable: true
    }
    service.getList(function (res) {
      that.setData({
        list: res.data.data,
        path:that.data.path,
        list2:[],
        confirm: confirm
      }, function(){
        wx.hideToast();
        if (callback)
         callback();
      });
    });
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    this.setData({
      options: options,
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
    that.data.path = path;

      that.getList(function () {
      });

  },

})