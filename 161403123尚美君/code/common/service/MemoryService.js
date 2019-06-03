module.exports = {
  getList: getList,
  create: create,
  rename: rename,
  remove: remove,
  edit: edit,
  view: view,
  getMemory: getMemory,
  getReviewList: getReviewList,
  getSharedReviewList: getSharedReviewList,
  getQueueList: getQueueList,
  mastered: mastered,
  search:search,
  notMastered: notMastered,
  importTextMemory: importTextMemory
}
var App = getApp();

function importTextMemory(supid, name, success, error) {
  if (supid != null) {
   
    wx.navigateTo({
      url: '/pages/add_memories/add_memories?saveToId=' + supid + '&saveToName=' + name+'&usedTo=import',
    })
    // App.requestAPI(
    //   "memory/importTextMemory", {
    //     pathId: supid
    //   },
    //   function (res) {
    //     callback(res, success, error);
    //   }
    // )
  } else {
    wx.navigateTo({
      url: '/pages/add_memories/add_memories?' + 'usedTo=import',
    })
  }
};

function search(value, success, error) {
  App.requestAPI(
    "memory/search", {
      title: value
    },
    function (res) {
      callback(res, success, error);
    }
  )
};

function getList(supid, success, error) {
  if (!supid) {
    supid = null;
  }
  App.requestAPI(
    "memory/getList", {
      lid: supid
    },
    function(res) {
      callback(res, success, error);
    }
  )
};

function create(supid, name, success, error) {
  if (supid != null) {
    wx.navigateTo({
      url: '/pages/add_memory/add_memory?saveToId=' + supid + '&saveToName=' + name,
    })
  } else {
    wx.navigateTo({
      url: '/pages/add_memory/add_memory',
    })
  }
};

function rename(id, name, success, error) {
  return;
};

function edit(id) {
  wx.navigateTo({
    url: '/pages/edit_memory/edit_memory?id=' + id,
  })
}

function remove(id, success, error) {
  App.requestAPI(
    "memory/delete", {
      id: id
    },
    function(res) {

      callback(res, success, error);

    });
};

function view(id) {
  wx.navigateTo({
    url: '/pages/view_memory/view_memory?id=' + id,
  })
}

function getMemory(id, success, error) {
  App.requestAPI(
    "memory/getMemory", {
      id: id
    },
    function(res) {

      callback(res, success, error);

    });
}

function getReviewList(lid, success, error) {
  App.requestAPI(
    "memory/getReviewList", {
      lid: lid
    },
    function(res) {

      callback(res, success, error);

    });
}
function getSharedReviewList(lid, success, error) {
  App.requestAPI(
    "memory/getSharedReviewList", {
      lid: lid
    },
    function (res) {

      callback(res, success, error);

    });
}
function getQueueList(qid, success, error){
  App.requestAPI(
    "memory/getQueueList", {
      id: qid
    },
    function (res) {

      callback(res, success, error);

    });
}
function mastered(id, success, error) {
  App.requestAPI(
    "memory/mastered", {
      id: id
    },
    function(res) {
      callback(res, success, error);
    });
}

function notMastered(id, success, error) {
  App.requestAPI(
    "memory/notMastered", {
      id: id
    },
    function(res) {

      callback(res, success, error);

    });
}
function callback(res, success, error) {
  if (res.data.status == "ok") {
    if (success)
      success(res);
  } else {
    wx.showModal({
      title: 'error',
      content: res.data.msg,
    })
    if (error)
      error(error(res));
  }
}