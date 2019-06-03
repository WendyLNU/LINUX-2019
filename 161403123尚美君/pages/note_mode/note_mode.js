var memoryService = require("../../common/service/MemoryService.js");
var libraryService = require("../../common/service/LibraryService.js")
var App = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    list: null, //记忆列表
    list2: [], //记忆库列表
    paragraphs: [],
    openStatus: [],
    className: {
      show: "show",
      hidden: "hidden",
      title: "title",
      body: "body"
    },
    currentLibraryId: null,
    path: "",
    mLoadStatus: [],
    pLoadStatus: [],
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function(options) {
    var that = this;
    that.data.currentLibraryId = options.id;
    // that.data.currentLibraryId = 2612
    if (options.path)
      var path = that.data.path = options.path;
    else
      var path = ""
    // var path = "测试记忆库"
    wx.showToast({
      title: '正在加载',
      icon: 'loading'
    });
    that.getList(function(mres, lres) {
      that.setData({
        path: path,
        list: mres.data.data,
        list2: lres.data.data,
      });
    });
  },
  reviewLibrary: function() {
    var that = this;
    wx.navigateTo({
      url: '/pages/review_system/review_system?lid=' + that.data.currentLibraryId,
    })
  },
  loadFinish: function (e) {
    var id = e.currentTarget.id;
    var mi = e.currentTarget.dataset.mi;
    var that = this;
    that.data.mLoadStatus[mi] = true;
    that.data.pLoadStatus[id] = true;
    that.setData({
      mLoadStatus:that.data.mLoadStatus,
      pLoadStatus: that.data.pLoadStatus
    })
  },
  getList: function(callback) {
    var that = this;
    var list;
    memoryService.getList(that.data.currentLibraryId, function(mres) {
      libraryService.getList(that.data.currentLibraryId, function(lres) {
        wx.hideToast();
        if (callback)
          callback(mres, lres);
      })
    });
  },
  getList2: function(callback) {
    var that = this;
    var list;
    memoryService.getList(that.data.currentLibraryId, function(res) {
      wx.hideToast();
      if (callback)
        callback(res);
    });
  },
  viewSubLibrary: function(e) {
    var that = this;
    var id = e.currentTarget.id;
    var li = e.currentTarget.dataset.li;
    var path = that.data.list2[li].name;
    wx.navigateTo({
      url: '/pages/note_mode/note_mode?id=' + id + "&path=" + path,
    })
  },

  openFolder: function(e) {
    var that = this;
    var id = e.currentTarget.id;
    var mi = e.currentTarget.dataset.mi;
    var paragraphs = that.data.paragraphs;
    var openStatus = that.data.openStatus;

    if (openStatus[mi] == 1) {
      openStatus[mi] = 0
    } else {
      openStatus[mi] = 1
    }
    that.setData({
      openStatus: openStatus
    });
    if (!paragraphs[mi]) {
      wx.showToast({
        title: '正在加载',
        icon: 'loading'
      });
      console.log("第一次加载");
      memoryService.getMemory(id, function(res) {
        wx.hideToast()
        paragraphs[mi] = res.data.data;
        that.setData({
          paragraphs: paragraphs
        })
      });
    }

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function() {

  },

  previewImage: function(e) {
    var current = [];
    current.push(e.target.dataset.src);
    wx.previewImage({
      urls: current // 需要预览的图片http链接列表
    })
  }

})