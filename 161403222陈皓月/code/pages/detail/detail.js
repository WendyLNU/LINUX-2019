import { DBindex } from '../../db/DBindex.js';

Page({
  data:{},
  onLoad: function (options) {
    var indexId = options.id;
    this.dbindex = new DBindex(indexId);
    this.indexData = this.dbindex.getindexItemById().data;
    this.setData({
      oop: this.indexData
    })
    
  },
  onCollectionTap:function(event){
    var newData=this.dbindex.collect();
    this.setData({
      'oop.collectionStatus':newData.collectionStatus,
      'oop.collectionNum':newData.collectionNum
    })
    wx.showToast({
      title: newData.collectionStatus ? "收藏成功" : "取消成功",
      duration: 1000,
      icon: "success",
      mask: true
    })
  },
  onUpTap: function (event) {
    var newData = this.dbindex.up();

    this.setData({
      'oop.upStatus': newData.upStatus,
      'oop.upNum': newData.upNum
    })
    
  },
  
  onCommentTap:function(event){
    var id=event.currentTarget.dataset.indexId;
    wx.navigateTo({
      url:'../comment/comment?id=' + id
    })
  },
  onShareAppMessage:function(){
    return {
      title: this.indexData.title,
      desc: this.indexData.content,
      path:"/pages/detail/detail"
    }
  },
  
  onReady:function(){
    wx.setNavigationBarTitle({
      title:this.indexData.title
    })
  }
})