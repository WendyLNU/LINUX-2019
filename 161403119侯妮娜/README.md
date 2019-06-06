# wxcake-master
电商类小程序 包含预览、购物车、添加地址、支付、购买等一系列完整的流程

wxbestcake-master
电商类小程序 包含预览、购物车、添加地址、支付、购买等一系列完整的流程

项目说明
基于微信小程序开发的一款移动端电商
目录结构
wxbestcake-master/
     |-pages/                      # 小程序页面相关文件
         |- buy
           |- index.js
           |- index.json
           |- index.wxml
           |- index.wxss
         |- ...
     |-app.js                      # 小程序逻辑
     |-app.json                    # 小程序公共设置
     |-app.wxss                    # 小程序公共样式表
     |-...
页面结构

每个页面组件也分为四个文件组成：

[page-name].js

页面逻辑文件，用于创建页面对象，以及处理页面生命周期控制和数据处理

[page-name].json

设置当前页面工作时的window的配置，此处会覆盖app.json中的window设置，也就是说只可以设置window中设置的属性

[page-name].wxml

1 wxml指的是Wei Xin Markup Language 用于定义页面中元素结构的，语法遵循XML语法，注意是XML语法，不是HTML语法

[page-name].wxss

1 wxml指的是Wei Xin Style Sheet 用于定义页面样式的，语法遵循CSS语法，扩展了CSS基本用法和长度单位（主要就是rpx响应式像素）

项目配置

小程序中的配置文件分为两种：

全局配置文件，根目录下的app.json 页面配置文件，每个页面目录下的[page-name].json app.json

项目配置声明文件（指定项目的一些信息，比如导航栏样式颜色等等）

{ // 当前程序是由哪些页面组成的（第一项默认为初始页面） // 所有使用到的组件或页面都必须在此体现 // https://mp.weixin.qq.com/debug/wxadoc/dev/framework/config.html#pages "pages": [ ... ], // 应用程序窗口设置 // https://mp.weixin.qq.com/debug/wxadoc/dev/framework/config.html#window "window": { ... }, // 应用导航栏设置 // https://mp.weixin.qq.com/debug/wxadoc/dev/framework/config.html#tabBar "tabBar": { ... }, // 网络超时设置 // https://mp.weixin.qq.com/debug/wxadoc/dev/framework/config.html#networkTimeout "networkTimeout": {}, // 是否在控制台输出调试信息 // https://mp.weixin.qq.com/debug/wxadoc/dev/framework/config.html#debug "debug": true } [page-name].json

用于指定特定页面工作时，window的设置： { // 导航条背景色 "navigationBarBackgroundColor": "#35495e", // 导航条前景色（只能是white/black） "navigationBarTextStyle": "white", // 导航条文本 "navigationBarTitleText": "", // 窗口背景颜色 "backgroundColor": "#fff", // 窗口前景色 "backgroundTextStyle": "dark", // 是否开启下拉刷新 "enablePullDownRefresh": true } 逻辑层分析

应用程序逻辑app.js

app.js作为项目主入口文件，用于创建应用程序对象

// App函数是一个全局函数，用于创建应用程序对象 App({ // ========== 全局数据对象（可以整个应用程序共享） ========== globalData: { ... },

// ========== 应用程序全局方法 ========== method1 (p1, p2) { ... }, method2 (p1, p2) { ... },

// ========== 生命周期方法 ========== // 应用程序启动时触发一次 onLaunch () { ... },

// 当应用程序进入前台显示状态时触发 onShow () { ... },

// 当应用程序进入后台状态时触发 onHide () { ... } }) 也就是说，当应用程序启动时会自动执行项目目录下的app.js文件。

在app.js中通过调用全局App([option])方法创建一个应用程序实例。

页面逻辑[page-name].js

[page-name].js是一个页面的重要组成部分，用于创建页面对象

// 获取全局应用程序对象 const app = getApp()

// Page也是一个全局函数，用来创建页面对象 Page({ // ========== 页面数据对象（可以暴露到视图中，完成数据绑定） ========== data: { ... },

// ========== 页面方法（可以用于抽象一些公共的行为，例如加载数据，也可以用于定义事件处理函数） ========== method1 (p1, p2) { ... }, method2 (p1, p2) { ... },

// ========== 生命周期方法 ========== // 页面加载触发 onLoad () { ... }

... })
## 商城截图

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture7.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture7.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture6.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture6.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture5.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture5.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture4.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture4.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture3.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture3.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture2.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture2.jpeg" width="375px" style="max-width:100%;"></a></p>

<p><a target="_blank" href="https://github.com/kuhami/wxbestcake-master/blob/master/icon/Capture1.jpeg"><img src="https://raw.githubusercontent.com/kuhami/wxbestcake-master/master/icon/Capture1.jpeg" width="375px" style="max-width:100%;"></a></p>
