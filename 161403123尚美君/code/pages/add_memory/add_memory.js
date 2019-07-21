var App = getApp();
var editService = require("../../common/service/EditService.js")
Page({

  /**
   * 页面的初始数据
   */
  data: {
    titleClass: "title-content",
    contentClass: "content",
    memory: [{
      paragraph: [{
        isImg: false,
        isTitle: false,
        pid: new Date().getTime(),
        imgSrc: "",
      }],
      mid: new Date().getTime(),
    }],
    saveTo: {
      name: "",
      id: null
    },
    option:{},
    imageList: [{
      m: 0,
      p: 0,
      url: ""
    }]
  },
  onLoad: function(o) {
    var that = this;
    this.setData({
      option:o,
      saveTo:{
        name: o.saveToName,
        id: o.saveToId
      }
    })
    if (o.usedTo=='import'){

      var pages = getCurrentPages()
      var prevPage = pages[pages.length - 1] //当前界面
      var prevPage = pages[pages.length - 2] //上一个页面
      var text = prevPage.getText();
      text = text.replace(/\r\n/g, "\n")
      text = text.replace(/\r/g, "\n"); 
      that.data.memory = [];
      that.importMemory(text,1);
      editService.init(that.data.memory);
      that.setData({
        memory: that.data.memory
      })
      // wx.getClipboardData({
      //   success: function (res) {
      //     console.log(res.data);
      //     var text = res.data; 
      //     text = text.replace(/\r\n/g, "\n")
      //     text = text.replace(/\r/g, "\n"); 
      //     that.data.memory = [];
      //     that.importMemory(text,1);
      //     editService.init(that.data.memory);
      //     that.setData({
      //       memory: that.data.memory
      //     })
      //   }
      // })
    }else{
      editService.init(this.data.memory);
    }
    
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
        if (res.tapIndex==3){
          wx.navigateTo({
            url: '/pages/canvas/canvas?m=' + position.m + '&&p=' + position.p,
          })
        }else{
          editService.addParagraph(position, res.tapIndex, function (result) {
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
        }
        }
       
    });
  },
  addCanvas: function (src, position){
    var that = this;
    editService.addCanvas(src, position, function (result){
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
  addMemory: function(e) {
    var that = this;
    var position = {
      m: e.currentTarget.dataset.mi,
    }
    memory: editService.addMemmory(position, function(memory) {
      that.setData({
        memory: memory
      });
      var query = wx.createSelectorQuery().in(that);
      var currentTop;
      query.select('.memory' + position.m).boundingClientRect(function(res) {
        currentTop = res.top;
      }).exec();
      wx.createSelectorQuery().selectViewport().scrollOffset(function(res) {
        wx.pageScrollTo({
          scrollTop: res.scrollTop + currentTop - 50,
        })
      }).exec()
    })
  },
  removeMemory: function(e) {
    var that = this;
    var position = {
      m: e.currentTarget.dataset.mi,
    }
    editService.removeMemory(position, function(memory) {
      that.setData({
        memory: memory
      });
    })
  },

  submit: function(e) {
    var that = this;
    var data = e.detail.value;
    var arr = that.data.memory;
    var length = arr.length;
    var pathId = that.data.saveTo.id;
    var ps=[];
    var ms=that.data.memory;
    if (that.data.option.usedTo == 'import'){
      var pages = getCurrentPages()
      var prevPage = pages[pages.length - 2] //上一个页面
      prevPage.save({},"");
    }
    editService.submit(data, arr, pathId, function() {
      that.setData({
        memory:[]
      },function(){
        editService.init(that.data.memory);
        wx.showToast({
          title: '提交成功',
          icon: "succes",
          duration: 3000
        });
        var e = {};
        e.currentTarget = {};
        e.currentTarget.dataset = {};
        e.currentTarget.dataset.mi = 0;
        that.addMemory(e);
      })
    
    });
  },
  chooseLib: function() {
    wx.navigateTo({
      url: "../manage_select_view/manage_select_view?type=select&target=library&usedTo=saveMemory"
    })
  },
  importMemory:function(text,count){
    while (text.charAt(0) == '\n') {
      text = text.substring(1);
    }
    var that=this;
    var memoryText;
    var titleText;
    var contentText;
    var memoryLength = text.indexOf("\n\n\n");
    var titleLength;
    var pEnd;
    var ps=[];
    var ms=this.data.memory;
    if (memoryLength < 0)
      memoryText = text;
    else
      memoryText = text.substring(0, memoryLength);
    titleLength = memoryText.indexOf("\n");
    if (titleLength < 0){
      memoryText+="\n";
      titleLength = memoryText.indexOf("\n");
    }
    titleText = memoryText.substring(0, titleLength);
    contentText = memoryText.substring(titleLength + 1);

    pEnd = contentText.indexOf("\n\n");
    while (pEnd>=0){
      
      ps.push({
        isImg: false,
        isTitle: false,
        pid: new Date().getTime(),
        content: contentText.substring(0,pEnd) ,
        imgSrc: "",
      });
      contentText = contentText.substring(pEnd + 2);
      pEnd = contentText.indexOf("\n\n");
    }
    ps.push({
      isImg: false,
      isTitle: false,
      pid: new Date().getTime(),
      content: contentText,
      imgSrc: "",
    });
    ms.push({
      paragraph: ps,
      mid: new Date().getTime(),
      title: titleText
    })
    if (memoryLength >= 0)
      that.importMemory(text.substring(memoryLength + 3), count + 1);
    else
    wx.showModal({
      title: '操作成功',
      content: '成功导入' + count+'个记忆',
      showCancel:false
    })
  },


  textInput: function (e) {
    var id = e.target.id;
    var value = e.detail.value;
    var mi = e.currentTarget.dataset.mi
    this.data.memory[mi].paragraph[id].content = value
    editService.init(this.data.memory,null);
    console.log(value);
  },
  titleInput: function (e) {
    var value = e.detail.value;
    var mi = e.currentTarget.dataset.mi
    this.data.memory[mi].title = value;
    editService.init(this.data.memory, null);
  }
})