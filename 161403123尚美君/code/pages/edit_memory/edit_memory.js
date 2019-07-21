var App = getApp();
var editService = require("../../common/service/EditService.js")
var memoryService = require("../../common/service/MemoryService.js");
Page({

  /**
   * 页面的初始数据
   */
  data: {
    id: null,
    titleClass: "title-content",
    contentClass: "content",
    memory: [],
    saveTo: {
      name: "",
      id: null
    },
    imageList: [{
      m: 0,
      p: 0,
      url: ""
    }],
    loadStatus: [],
  },
  loadFinish: function (e) {
    var id = e.currentTarget.id;
    var that = this;
    that.data.loadStatus[id] = true;
    that.setData({
      loadStatus: that.data.loadStatus
    })
  },
  onLoad: function(o) {
    wx.showToast({
      title: '正在加载记忆内容',
      icon: "loading",
      duration: 2000000, //提示的延迟时间，单位毫秒，默认：1500
      mask: true,
    })
    var id = o.id;
    var that = this;
    memoryService.getMemory(id, function(res) {
      var paragraph = res.data.data.paragraph;
      for (var i = 0; i < paragraph.length; i++) {
        paragraph.pid = paragraph.position;
        paragraph.position = null;
      }
      res.data.data.paragraph = paragraph
      var memory = [];
      memory.push(res.data.data)
      var saveTo = {
        name: res.data.data.pathName,
        id: res.data.data.pathId
      }
      editService.init(memory, id);

      that.setData({
        memory: memory,
        saveTo: saveTo,
        id: id
      }, function() {
        wx.hideToast();
      });
    });

  },

  addParagraph: function(e) {
    var that = this;
    var position = {
      m: e.currentTarget.dataset.mi,
      p: e.target.id
    }
    wx.showActionSheet({
      itemList: ['标题', '文字', '图片','画板'],
      success: function(res) {
        if (res.tapIndex == 3) {
          wx.navigateTo({
            url: '/pages/canvas/canvas?m=' + position.m + '&&p=' + position.p,
          })
        } else {
          editService.addParagraph(position, res.tapIndex, function(result) {
            that.setData({
              memory: result
            });
            var query = wx.createSelectorQuery().in(that);
            var currentTop;
            query.select('.m' + position.m + 'p' + position.p).boundingClientRect(function(res) {
              currentTop = res.top;
            }).exec();
            wx.createSelectorQuery().selectViewport().scrollOffset(function(res) {
              wx.pageScrollTo({
                scrollTop: res.scrollTop + currentTop - 50,
              })
            }).exec()
          });
        }
      }
    });
  },
  addCanvas: function (src, position) {
    var that = this;
    editService.addCanvas(src, position, function (result) {
      that.setData({
        memory: result
      });
      var query = wx.createSelectorQuery().in(that);
      var currentTop;
      query.select('.m' + position.m + 'p' + position.p).boundingClientRect(function (res) {
        currentTop = res.top;
      }).exec();
      wx.createSelectorQuery().selectViewport().scrollOffset(function (res) {
        wx.pageScrollTo({
          scrollTop: res.scrollTop + currentTop - 50,
        })
      }).exec()
    });
  },
  removeParagraph: function(e) {
    var that = this;
    var position = {
      m: e.currentTarget.dataset.mi,
      p: e.target.id
    }
    editService.removeParagraph(position, function(memory) {
      that.setData({
        memory: memory
      });
    });

  },
  changeImg: function(e) {
    var that = this;
    var position = {
      p: e.target.id,
      m: e.currentTarget.dataset.mi
    };
    editService.changeImg(position, function(result) {
      that.setData({
        memory: result
      });
    });
  },

  submit: function(e) {
    var that = this;
    var data = e.detail.value;
    var arr = that.data.memory;
    var length = arr.length;
    var pathId = that.data.saveTo.id;
    editService.submit(data, arr, pathId, function() {
      console.log();
      editService.init(arr, that.data.id);
      wx.showToast({
        title: '提交成功',
        icon: "succes",
        duration: 3000
      });
    });

  },
  chooseLib: function() {
    wx.navigateTo({
      url: "../manage_select_view/manage_select_view?type=select&target=library&usedTo=saveMemory"
    })
  },

  textInput: function(e) {
    var id = e.target.id;
    var value = e.detail.value;
    this.data.memory[0].paragraph[id].content = value
    editService.init(this.data.memory, this.data.id);
  },
  titleInput: function(e) {
    var value = e.detail.value;
    this.data.memory[0].title = value;
    editService.init(this.data.memory, this.data.id);
  }
})