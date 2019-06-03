module.exports = {
  init: init,
  addParagraph: addParagraph,
  addCanvas: addCanvas,
  removeParagraph: removeParagraph,
  addMemmory: addMemmory,
  removeMemory: removeMemory,
  changeImg: changeImg,
  submit: submit
}
var arr;
var memoryId=null;
var App = getApp();
var host = App.getHost();

function init(memory,id) {
  arr = memory;
  if(id)
    memoryId=id;
  else
    memoryId = null;
}
function addCanvas(src, position, callBack){
  var paragraph = arr[position.m].paragraph;
  var length = paragraph.length;
  var element;
  element = {
    isImg: true,
    isTitle: false,
    pid: 'time' + new Date().getTime(),
    imgSrc: src,
  }
  for (var i = length; i > position.p; i--) {
    paragraph[i] = paragraph[i - 1];
  }
  paragraph[position.p] = element;
  arr[position.m].paragraph = paragraph;
  callBack(arr);
}
function addParagraph(position, paragraphType, callBack) {
  var paragraph = arr[position.m].paragraph;
  var length = paragraph.length;
  var element;
  if (paragraphType != 2) {
    element = {
      isImg: false,
      isTitle: paragraphType == 0,
      pid: 'time' + new Date().getTime(),
      imgSrc: "",
    };
    for (var i = length; i > position.p; i--) {
      paragraph[i] = paragraph[i - 1];
    }
    paragraph[position.p] = element;
    arr[position.m].paragraph = paragraph;
    callBack(arr);
  } else {
    var tempFilePaths;
    var synchronize = true;
    wx.chooseImage({
      pcount: 1, // 默认9
      sizeType: ['original', 'compressed'], // 可以指定是原图还是压缩图，默认二者都有
      sourceType: ['album', 'camera'], // 可以指定来源是相册还是相机，默认二者都有
      success: function(res) {
        // 返回选定照片的本地文件路径列表，tempFilePath可以作为img标签的src属性显示图片
        tempFilePaths = res.tempFilePaths
        element = {
          isImg: true,
          isTitle: false,
          pid: 'time'+new Date().getTime(),
          imgSrc: tempFilePaths[0],
        }
        for (var i = length; i > position.p; i--) {
          paragraph[i] = paragraph[i - 1];
        }
        paragraph[position.p] = element;
        arr[position.m].paragraph = paragraph;
        callBack(arr);
      }
    })
  }


}

function removeParagraph(position, callBack) {
  var pi = position.p;
  var mi = position.m;
  var paragraph = arr[position.m].paragraph;
  var length = paragraph.length;
  for (var i = pi; i < length - 1; i++) {
    paragraph[i] = paragraph[Number(i) + 1];
  }
  paragraph.pop();
  arr[mi].paragraph = paragraph;
  callBack(arr);
}

function addMemmory(position, callBack) {
  var mi = position.m;
  var length = arr.length;
  for (var i = length; i > mi; i--) {
    arr[i] = arr[i - 1];
  }
  var element = {
    paragraph: [{
      isImg: false,
      isTitle: false,
      pid: new Date().getTime(),
      imgSrc: ""
    }],
    mid: new Date().getTime(),
  }
  arr[mi] = element;
  callBack(arr);
}

function removeMemory(position, callBack) {
  var mi = position.m;
  var length = arr.length;
  for (var i = mi; i < length - 1; i++) {
    arr[i] = arr[Number(i) + 1];
  }
  arr.pop();
  callBack(arr);
}

function changeImg(position, callBack) {
  var paragraph = arr[position.m].paragraph;
  wx.showActionSheet({
    itemList: ['查看图片','更改图片'],
    success: function(res) {
      if(res.tapIndex==1){
        wx.chooseImage({
          pcount: 1, // 默认9
          sizeType: ['original', 'compressed'], // 可以指定是原图还是压缩图，默认二者都有
          sourceType: ['album', 'camera'], // 可以指定来源是相册还是相机，默认二者都有
          success: function (res) {
            paragraph[position.p].imgSrc = res.tempFilePaths[0];
            arr[position.m].paragraph = paragraph;
            callBack(arr);
          }
        })
      }else{
        var imgs = [];
        imgs.push(paragraph[position.p].imgSrc)
          wx.previewImage({
            urls: imgs// 需要预览的图片http链接列表
          })
      }
      
    }
  });
}

function submit(formData, memory, pathId, success, error) {
  var data = formData;
  var arr = memory;
  var length = arr.length;
  var imageList = [];
  if (arr == null || arr.length == 0) {
    wx.showToast({
      title: '当前没有可提交的记忆',
      icon: 'none',
      duration: 3000
    })
    return;
  }
  for (var i = 0; i < length; i++) {
    var ps = arr[i].paragraph;
    var pl = ps.length;
    for (var j = 0; j < pl; j++) {
      if (ps[j].isImg && ps[j].imgSrc.substr(0, 4)!='http') {
        imageList.push({
          m: i,
          p: j,
          url: ps[j].imgSrc
        })
      } else if (ps[j].isTitle) {
        ps[j].content = data["titlem" + i + 'p' + j];
        data["titlem" + i + 'p' + j] = null;

      } else {

        ps[j].content = data["textaream" + i + 'p' + j];
        data["textaream" + i + 'p' + j] = null;
      }
      ps[j].position = j;
    }
    arr[i].title = data["memoryTitlem" + i];
    arr[i].pathId = pathId;
    data["memoryTitlem" + i] = null;

    if (arr[i].pathId == null) {
      wx.showToast({
        title: '请选择存储位置',
        icon: 'none',
        duration: 3000
      })
      return;
    }
    if (arr[i].title == null || arr[i].title == '') {
      wx.showToast({
        title: '请填写记忆标题',
        icon: 'none',
        duration: 3000
      })
      return;
    }
  }
  wx.showToast({
    title: '正在传输数据',
    icon: "loading",
    duration: 2000000, //提示的延迟时间，单位毫秒，默认：1500
    mask: true,
  })

  upload(arr, imageList, 0, success, error);
}


function upload(arr, imageList, k, success, error) {
  if (k != imageList.length) {
    if (!imageList[k].url.indexOf(host)){
      upload(arr, imageList, Number(k) + 1, success, error);
      return;
    }
    wx.uploadFile({
      url: host+'imageUpload',
      filePath: imageList[k].url,
      name: 'fileName',
      success: function(res) {
        res.data = JSON.parse(res.data);
        console.log(res.data);
        if (res.data.status == "ok") {
          imageList[k].url = host + 'getImg?fileName=' + res.data.data;
          console.log(imageList[k].url);
        }
        upload(arr, imageList, Number(k) + 1, success, error);
      }
    })
  } else { //图片上传完成,开始提交memory数组

    for (var i = 0; i < imageList.length; i++) {
      arr[imageList[i].m].paragraph[imageList[i].p].imgSrc = imageList[i].url;
    }
    var API = "memory/create";
    if(memoryId){
      arr[0].id = memoryId;
      API ="memory/edit"
    }
    //console.log(arr); 
    App.requestAPI(API, arr, function(res) {
      if (res.data.status == "ok") {
        wx.hideToast();
        callback(res, success, error);
      }
    })
  }
}

function callback(res, success, error) {
  if (res.data.status == "ok") {
    if (success)
      success(res);
  } else {
    if (error)
      error(error(res));
  }
}