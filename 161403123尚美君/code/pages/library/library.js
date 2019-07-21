var libraryService = require("../../common/service/LibraryService.js")
var memoryService = require("../../common/service/MemoryService.js");
var marketService = require("../../common/service/MarketService.js");
var App = getApp();
var createLibModal = {
  type: "input",
  title: "创建记忆库",
  content: "创建一个新的记忆库",
  button: "创建",
  bindconfirm: "createLib",
  placeholder: "输入新记忆库的名称"
}
var renameLibModal = {
  type: "input",
  title: "重命名记忆库",
  content: "更改该记忆库的名称",
  button: "确定",
  bindconfirm: "renameLib",
  placeholder: "输入新的记忆库名称"
}
var acquireLibModal = {
  type: "input",
  title: "获取分享记忆库",
  content: "通过分享码获取一个记忆库",
  button: "获取",
  bindconfirm: "acquireLib",
  placeholder: "请输入分享码"
}
var deleteLibModal = {
  type: "warn",
  title: "注意",
  content: "记忆库内的记忆也会一并删除",
  button: "继续",
  bindconfirm: "deleteLib",
  placeholder: "输入新记忆库的名称"
}
var deleteMemoryModal = {
  type: "warn",
  title: "注意",
  content: "记忆删除后将无法恢复",
  button: "继续",
  bindconfirm: "deleteMemory",
  placeholder: "输入新记忆库的名称"
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
var shareMessage={
  title: '分享记忆库',
  imageUrl:'/img/icon/logo.png',
  path: '/pages/library/library'
}
var receiveLibraryModal = {
  type: "primary",
  title: "收到分享的记忆库",
  content: "点击保存选择储存位置",
  button: "保存",
  bindconfirm: "receiveLibrary",
}

Page({

  /**
   * 页面的初始数据
   */
  data: {
    modalObject: {
      type: "hidden",
      title: "",
      content: "",
      button: "",
      bindconfirm: "",
      placeholder: ""
    },
    shareModal: { 
      type: "hidden",
      code:""
    },
    currentLibraryId: null,
    which:{},
    whichMemory:{},
    path:[],
    list:null,
    list2:null
  },

  onPullDownRefresh:function(){
    var that=this;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    that.getList(function(){
      wx.stopPullDownRefresh();
    });
  },
  onShow: function () {
    this.getList();
  },
  onLoad:function(o){
    var that=this;
    wx.hideShareMenu();
    that.data.options=o;
    if (o.sharedCode){//测试时取反
      that.setData({
        modalObject:receiveLibraryModal
      })
    }
    /***********************************未完成,接收好友分享的记忆库 */
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
  },

  onShareAppMessage: function (res){
    if (res.from === 'button') {
      console.log(res.target);
      return shareMessage;
    }else{
    
    }
    
  },

  //点击底部加号按钮显示上拉选项栏
  openBottomSheet: function () {
    var that=this;
    wx.showActionSheet({
      itemList: ['添加记忆库', '添加记忆','文字生成记忆'],
      success: function (res) {
        switch (res.tapIndex) {
          case 0:
            that.createSubmenu();
            break;
          case 1:
            var path = that.data.path;
            var which={id:null};
            if (path.length != 0){
              which = path[path.length - 1];
            }
            memoryService.create(which.id,which.name);
            break;
          case 2:
            var path = that.data.path;
            var which = { id: null };
            if (path.length != 0) {
              which = path[path.length - 1];
            }
            memoryService.importTextMemory(which.id, which.name);
            break;
        }
      }
    })
  },

  //点击右方设置按钮显示上拉选项栏
  openMiddleSheet: function (e) {
    var that = this;
    if (e.currentTarget.dataset.type=="memory"){
      that.data.whichMemory = that.data.list2[e.currentTarget.dataset.index];
      wx.showActionSheet({
        itemList: ['删除', '编辑'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              that.setData({
                modalObject: deleteMemoryModal
              })
              break;
            case 1:
              memoryService.edit(that.data.whichMemory.id);
              break;
          }
        }
      })
    }else{
      that.data.which = that.data.list[e.currentTarget.dataset.index];
      wx.showActionSheet({
        itemList: ['删除', '重命名','浏览纲要','回顾记忆库','分享记忆库'],
        success: function (res) {
          switch (res.tapIndex) {
            case 0:
              that.setData({
                modalObject: deleteLibModal
              })
              break;
            case 1:
              that.setData({
                modalObject: renameLibModal
              })
              break;
            case 2:
              wx.navigateTo({
                url: '/pages/note_mode/note_mode?id=' + that.data.which.id + "&path=" + that.data.which.name,
              })
              break;
            case 3:
              wx.navigateTo({
                url: '/pages/review_system/review_system?lid=' + that.data.which.id,
              })
              break;
            case 4:
              that.shareSubmenu();
              break;
          }
        }
      })
    }
    
  },
  shareSubmenu:function(){//分享记忆库子菜单
    var that = this;
    wx.showActionSheet({
      itemList: ['分享给好友', '申请出售'],
      success: function (res) {
        switch (res.tapIndex) {
          case 0://分享给好友
            wx.showToast({
              title: '操作中..',
              icon: 'loading',
              duration:2000000
            })
            libraryService.shareLibrary(that.data.which.id,function(res){
              wx.hideToast();
              var modal = {
                type: "primary",
                code: res.data.msg,
              }
              shareMessage.path = '/pages/library/library?sharedCode=' + res.data.msg;
              wx.hideToast();
              that.setData({
                shareModal: modal
              })
            })            
            
            break;
          case 1://申请出售
            wx.showModal({
              title: '注意',
              content: '出售将视为您已同意《用户协议》',
              success: function (res) {
                if (res.confirm) {
                  marketService.sellLibrary(that.data.which.id, function () {
                    wx.showToast({
                      title: '申请成功',
                    })
                    setTimeout(function () {
                      wx.navigateTo({
                        url: "/pages/my_order/my_order"
                      })
                    }, 800)
                  })
                }
              }
            })
            break;
        }
      }
    })
  },
 
  createSubmenu: function () {//创建记忆库子菜单
    var that = this;
    wx.showActionSheet({
      itemList: ['创建新的记忆库', '获取分享记忆库'],
      success: function (res) {
        switch (res.tapIndex) {
          case 0://创建记忆库
            that.setData({
              modalObject: createLibModal
            });
            break;
          case 1://获取分享记忆库
            that.setData({
              modalObject: acquireLibModal
            });
            break;
        }
      }
    })
  },


  //获取记忆库
  acquireLib: function (res) {
    var that = this;
    var supid = that.data.currentLibraryId;
    var code = res.detail.value;
    wx.showToast({
      title: '操作中..',
      duration:30*1000,
      mask:true,
      icon: 'loading'
    })
    libraryService.acquireLibrary(supid,code,function(res){
      that.setData({
        modalObject: hiddenModal
      });
      that.getList();
    })
    
  },

  receiveLibrary:function(){
    var that = this;
    wx.navigateTo({
      url: "../manage_select_view/manage_select_view?type=select&target=library&usedTo=recieveLibrary&code=" + that.data.options.sharedCode
    })
  },

  //创建记忆库
  createLib: function (res) {
    var that = this;
    var id = that.data.currentLibraryId;
    var name = res.detail.value;
    wx.showToast({
      title: '操作中..',
      mask:true,
      duration:30*1000,
      icon:'loading'
    })
    that.setData({
      modalObject: hiddenModal
    });
    libraryService.create(id, name,function(res){
      that.getList();
    });
    
  },

  //删除
  deleteLib:function(){
    var that = this;
    console.log("删除记忆,点击确定按钮");
    //输入框内容在res.detail.value
    var which=that.data.which;
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
    libraryService.remove(id,function(res){
      that.getList();
    })
  },
  deleteMemory: function () {
    var that = this;
    console.log("删除记忆,点击确定按钮");
    //输入框内容在res.detail.value
    var which = that.data.whichMemory;
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
    memoryService.remove(id, function (res) {
      that.getList();
    })
  },
  //重命名
  renameLib:function(res){
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
    libraryService.rename(id, name,function(){
      that.getList();
    });
  },
  //获取列表
  getList: function (callback) {
    var that = this;
    var list;
    libraryService.getList(that.data.currentLibraryId,function(res){
      list = res.data.data;
        memoryService.getList(that.data.currentLibraryId, function (res) {
          that.setData({
            list:list,
            list2: res.data.data,
            path:that.data.path
          }, function(){
            wx.hideToast();
            if (callback)
             callback();
          });
        });
    });

  },

  //点击记忆库
  checkItem:function(e){
    console.log("点击记忆库");
    var that = this;
    var which = that.data.which = that.data.list[e.currentTarget.dataset.index];
    var path=that.data.path;
    path.push(which)
    that.data.currentLibraryId = which.id;
    that.data.path = path;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    that.getList(function(){

    });
  },

  //点击记忆
  viewMemory:function(e){
    var that = this;
    var which =  that.data.list2[e.currentTarget.dataset.index];
    memoryService.view(which.id)
  },

  //返回上一层
  goBack:function(){
    var that = this;
    var path = that.data.path;
    if(path.length<=1){
      that.data.currentLibraryId = null;
    }else{
      that.data.currentLibraryId = path[path.length-2].id;
    }
    path.pop();
    that.data.path = path;
    wx.showToast({
      title: '正在加载..',
      mask: true,
      duration: 30 * 1000,
      icon: 'none'
    })
    that.getList(function () {
    });
  },
  onUnload(){
    console.log(12313);
  }
})