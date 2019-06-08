
Page({
  data: {
    teacherList: [
      
      {
        name: "李丽丽",
        sex: "女",
        school: "东北大学",
        subject: "考研",
        relation: "542168461",
        imagePath: "/images/parent/4.jpg"
      },
      {
        name: "赵海莹",
        sex: "女",
        school: "东北大学",
        subject: "高中数学",
        relation: "5234214351",
        imagePath: "/images/parent/5.jpg"
      },
      {
        name: "钱锦",
        sex: "男",
        school: "东北大学",
        subject: "初中理科",
        relation: "542348461",
        imagePath: "/images/parent/6.jpg"
      }
    ]
  },
  onShareAppMessage: function () {
    return {
      
      
      path: "/pages/dongda/dongda"
    }
  }
})