var memoryService = require("../../common/service/MemoryService.js");
Page({

  /**
   * 页面的初始数据
   */
  data: {
    lid:null,
    qid:null,
    shared:0,
    index: 0,
    loadStatus:[],
    status: null,
    className: {
      show: "show",
      hidden: "hidden",
      title: "title",
      body: "body"
    },
    reviewList: [],
    reviewedList:[],
    notMasteredList: [],
    current: 0,
    total: 0,
    memory: {
      paragraph: [],
      title: ""
    }

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var lid = this.data.lid = options.lid;
    var qid = this.data.qid = options.qid;
    console.log(options);
    if (options.shared)
      this.data.shared = options.shared;
    var that = this;
    wx.showToast({
      icon: 'loading',
      title: '正在加载..',
      duration: 5000,
    })
    if (lid) {
      // if (that.data.shared==1){
      //   memoryService.getSharedReviewList(lid, function (res) {
      //     that.data.reviewList = res.data.data;
      //     that.next();
      //   });
      // }else{
        memoryService.getReviewList(lid, function (res) {
          that.data.reviewList = res.data.data;
          that.init();
        });
      // }
    } else if (qid) {
      memoryService.getQueueList(qid, function (res) {
        that.data.reviewList = res.data.data;
        that.next();
      });
    }


  },
  init:function(){
    var that = this;
    var reviewList = that.data.reviewList;
    if (0 == reviewList.length){
      wx.showToast({
        title: '回顾完成',
        icon: "ok"
      });
      that.setData({
        status: -2,
      });
    }else{
      that.next();
    }
  },
  next: function () {
    wx.showToast({
      title: '正在加载..',
      icon: 'none'
    })
    var that = this;
    var current = Number(that.data.current);
    var reviewList = that.data.reviewList;
    var notMasteredList = that.data.notMasteredList;
    if (current == reviewList.length) {
      wx.hideToast();
      if (notMasteredList.length == 0) {
        that.setData({
          status: -1,
          loadStatus: [],
        });
      } else {
        var memory = that.data.notMasteredList.shift()
        that.setData({
          status: 0,
          loadStatus: [],
          memory: memory,
        });
      }
    } else {
      memoryService.getMemory(reviewList[current], function (res) {
        that.setData({
          status: 0,
          loadStatus: [],
          memory: res.data.data,
          total: reviewList.length,
          current: current + 1
        }, function () {
          that.data.reviewedList.push(that.data.memory);
          wx.hideToast();
        });
      });
    }
  },
  mastered: function () {
    var that = this;
    var notMasteredList = that.data.notMasteredList;
    that.setData({
      status: 1,
      notMasteredList: notMasteredList
    }, function () {
      if(that.data.shared==1)
        return;
      memoryService.mastered(that.data.memory.id)
    })


  },
  notMastered: function () {
    var that = this;
    var memory = that.data.memory;
    var notMasteredList = that.data.notMasteredList;
    notMasteredList.push(memory);
    that.setData({
      notMasteredList: notMasteredList,
      status: 2
    }, function () {
      if (that.data.shared == 1)
        return;
      memoryService.notMastered(that.data.memory.id)
    })


  },
  previewImage: function (e) {
    var current = [];
    current.push(e.target.dataset.src);
    wx.previewImage({
      urls: current// 需要预览的图片http链接列表
    })
  },
  loadFinish: function (e) {
    var id = e.currentTarget.id;
    var that = this;
    console.log(id);
    that.data.loadStatus[id] = true;
    that.setData({
      loadStatus: that.data.loadStatus
    })
  },
  goback: function () {
    wx.navigateBack({
      delta: 1
    })
  },
  again:function(){
    var that = this;
    var lid = this.data.lid;
    wx.showToast({
      icon: 'loading',
      title: '正在加载..',
      duration: 5000,
    })
    that.setData({
      status:null,
      reviewList: [],
      reviewedList: [],
      notMasteredList: [],
      current: 0,
      total: 0,
      memory: {
        paragraph: [],
        title: ""
      }
    },function(){
      if (lid) {
        memoryService.getReviewList(lid, function (res) {
          that.data.reviewList = res.data.data;
          that.init();
        });
        // }
      } else if (qid) {
        // memoryService.getQueueList(qid, function (res) {
        //   that.data.reviewList = res.data.data;
        //   that.next();
        // });
      }
    });
   

  },
  changeStatus: function () {
    var that = this;
    if (that.data.status == 1) {
      wx.showActionSheet({
        itemList: ['加入回顾队列', '标记为未掌握','查看回顾记录'],
        success: function (res) {
          console.log(res.tapIndex);
          if (res.tapIndex == 0) {
            wx.navigateTo({
              url: "../manage_queue/manage_queue?type=select&usedTo=insertToQueue&mid=" + that.data.memory.id,
            })
          } else if (res.tapIndex == 1) {
            that.notMastered();
          }else{
            that.viewReviewHistory();
          }
        }
      })
    } else {
      wx.showActionSheet({
        itemList: ['加入回顾队列', '标记为掌握', '查看回顾记录'],
        success: function (res) {
          console.log(res.tapIndex);
          if (res.tapIndex == 0) {
            wx.navigateTo({
              url: "../manage_queue/manage_queue?type=select&usedTo=insertQueue&mid=" + that.data.memory.id,
            })
          } else if (res.tapIndex == 1) {
            that.data.notMasteredList.shift()
            that.mastered();
          }else{
            that.viewReviewHistory();
          }
        }
      })
    }
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
   
  },

  addToNotMasteredList: function (memory,callback){
    var that =this;
    that.data.notMasteredList.push(memory);
    that.setData({
      notMasteredList: that.data.notMasteredList,
    }, function () {
      callback();
    })
  },

  viewReviewHistory:function (){
    wx.navigateTo({
      url: "../review_history/review_history"
    })
  },
  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  // /**
  //  * 用户点击右上角分享
  //  */
  // onShareAppMessage: function (res) {
  //   var that = this;
  //   console.log(res)
  //   return {
  //     title: '分享记忆库',
  //     path: 'pages/review_system/review_system?shared=1&&lid=' + that.data.lid
  //   }
  // }
})