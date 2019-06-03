// Components/modal-custom/modal-custom.js
Component({
  /**
   * 组件的属性列表
   */
  properties: {
    type: {
      type: String,
      value: "hidden",//0,1,2,3 分别代表warn primary input 三种类别的窗口
    },
    title: {
      type: String,
      value: "标题",
    },
    content: {
      type: String,
      value: "内容",
    },
  },

  /**
   * 组件的初始数据
   */
  data: {
    inputValue:"",
    value:""
  },

  /**
   * 组件的方法列表
   */
  methods: {
    cancel: function (e) {
      console.log(e);
      this.setData({
        type: "hidden",
        value: ""
      });
      var myEventDetail = {} // detail对象，提供给事件监听函数
      var myEventOption = {} // 触发事件的选项
      this.triggerEvent('cancel', myEventDetail, myEventOption)
    },
    confirm: function (e) {
      var that=this;
      console.log(that.properties.content);
      wx.setClipboardData({
        data: that.properties.content,
        success:function(){
          that.cancel();
          wx.showToast({
            title: '复制成功',
          })
        }
      })
    },
    inputText:function(e){
      this.setData({
        inputValue: e.detail.value
      })
    },
    catch:function(){
      return;
    }
  }
})
