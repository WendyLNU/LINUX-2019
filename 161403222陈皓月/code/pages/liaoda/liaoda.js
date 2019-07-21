Page({
  data: {
    teacherList: [
      {
        name: "张清",
        sex: "女",
        school: "辽宁大学",
        subject: "高中文科",
        relation: "473785329",
        imagePath: "/images/parent/2.jpg"
      },
      {
        name: "钱锦",
        sex: "男",
        school: "辽宁大学",
        subject: "雅思",
        relation: "542348461",
        imagePath: "/images/parent/6.jpg"
      },
      {
        name: "孙艺",
        sex: "女",
        school: "辽宁大学",
        subject: "小提琴",
        relation: "5436633461",
        imagePath: "/images/parent/9.jpg"
      }
    ]
  },
  onShareAppMessage: function () {
    return {


      path: "/pages/liaoda/liaoda"
    }
  }
})