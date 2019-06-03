// pages/add_memories/add_memories.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    text:"",
    value:"",
    edited:false,
    saveTo: {
      name: "",
      id: ""
    }
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (o) {
    console.log(o);
    var that = this;
    if(1){
      this.setData({
        saveTo: {
          name: o.saveToName,
          id: o.saveToId
        }
      })
    }
    
    wx.getStorage({
      key: 'tempText',
      success: function(res) {
        
        if (res.data){
          that.data.text = res.data;
          that.setData({
            value: that.data.text
          },function(){
            wx.showToast({
              icon:"none",
              title:"载入未保存内容"
            })
            
          })
        }
      },
      fail:function(res){
      }
    })
  },



  save: function (e,str) {
    var that = this;
    console.log(str)
    if(str||str==""){
      wx.setStorageSync("tempText", str);
      // wx.showToast({
      //   title: '保存成功',
      // })
    }else{
      // if (!this.data.text)
      //   this.data.text=""
      wx.setStorageSync("tempText",this.data.text);
      wx.showToast({
        icon:"none",
        title: '保存成功',
      })
    }
   
  },

  generate:function(e){
    var supid=this.data.saveTo.id;
    var name=this.data.saveTo.name;
    if (this.data.saveTo.id){
      wx.navigateTo({
        url: '/pages/add_memory/add_memory?saveToId=' + supid + '&saveToName=' + name + '&usedTo=import',
      })
    }else{
      wx.navigateTo({
        url: '/pages/add_memory/add_memory?usedTo=import',
      })
    }
   
  },
  formClipboard:function(e){
    this.data.edited = true;
    var that=this;
    wx.getClipboardData({
      success: function (res) {
        console.log(res.data);
        that.data.text += res.data;
        that.setData({
          value: that.data.text
        })
      }
    })
    that.save({}, that.data.text);
  },
  toClipboard: function (e) {
    var that = this;
    wx.setClipboardData({
      data: that.data.text,
    })
  },
  clearText: function (e) {
    this.data.edited = true;
    var that = this;
    that.data.text ="";
    that.setData({
      value: that.data.text
    })
    that.save({}, that.data.text);
  },
  input:function(e){
    var that =this ;
    this.data.text = e.detail.value;
    that.save({},that.data.text);
  },
  getText:function(){
    return this.data.text.replace(/(\s*$)/g,"") || "";
  }
})