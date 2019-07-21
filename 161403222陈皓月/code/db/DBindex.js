var util = require('../util/util.js')
class DBindex{
  constructor(indexId){
    this.storageKeyName='indexList';
    this.indexId=indexId;
  }
  //得到文章全部信息
  getAllindexData() {
    var res = wx.getStorageSync(this.storageKeyName);
    if (!res) {
      res = require('../data/data.js').indexList;
      this.execSetStorageSync(res);
    }
    return res;
  }
  //保存或者更新缓存数据
  execSetStorageSync(data){
    wx.setStorageSync(this.storageKeyName, data);
  }
  //获取指定Id号的文章数据
  getindexItemById() {
    var indexsData = this.getAllindexData();
    var len = indexsData.length;
    for (var i = 0; i < len; i++) {
      if (indexsData[i].indexId == this.indexId) {
        return {
          index: i,
          data: indexsData[i]
        }
      }
    }
  }
  collect(){
    return this.updateindexData('collect');
  }
  up(){
    var data=this.updateindexData('up');
    return data;
  }
  newComment(newComment){
    this.updateindexData('comment',newComment);
  }
  addReadingTimes(){
    this.updateindexData('reading');
  }
  updateindexData(category, newComment) {
    var itemData = this.getindexItemById(),
      indexData = itemData.data,
      allindexData = this.getAllindexData();
    switch (category) {
      case 'collect':
        //处理收藏
        if (!indexData.collectionStatus) {
          //如果当前状态是未收藏
          indexData.collectionNum++;
          indexData.collectionStatus = true;
        } else {
          // 如果当前状态是收藏
          indexData.collectionNum--;
          indexData.collectionStatus = false;
        }
        break;
      case 'up':
        if (!indexData.upStatus) {
          indexData.upNum++;
          indexData.upStatus = true;
        } else {
          indexData.upNum--;
          indexData.upStatus = false;
        }
        break;
      case 'comment':
        indexData.comments.push(newComment);
        indexData.commentNum++;
        break;
      case 'reading':
        indexData.readingNum++;
        break;
      default:
        break;
    }
    allindexData[itemData.index] = indexData;
    this.execSetStorageSync(allindexData);
    return indexData;
  }
  getCommentData() {
    var itemData = this.getindexItemById().data;
    itemData.comments.sort(this.compareWithTime); //按时间降序
    var len = itemData.comments.length,
      comment;
    for (var i = 0; i < len; i++) {
      // 将comment中的时间戳转换成可阅读格式
      comment = itemData.comments[i];
      comment.create_time = util.getDiffTime(comment.create_time, true);
    }
    return itemData.comments;
  }
  compareWithTime(value1, value2) {
    var flag = parseFloat(value1.create_time) - parseFloat(value2.create_time);
    if (flag < 0) {
      return 1;
    } else if (flag > 0) {
      return -1
    } else {
      return 0;
    }
  }
  
}
export {DBindex}