module.exports = {
  getList: getList,
  create: create,
  rename: rename,
  remove:remove,
  getMemoryList: getMemoryList,
  insertMemory: insertMemory,
  removeMemory: removeMemory,
  importMemory: importMemory
}
var App=getApp();

function getList(success,error){
  App.requestAPI(
    "queue/getList",
    {
    },
    function (res) {
      callback(res, success, error);
    }
  )
};
function create(name,success, error){
  App.requestAPI(
    "queue/create",
    {
      name: name
    },
    function (res) {
      callback(res, success, error);
    })
};
function rename(id, name, success, error){
  App.requestAPI(
    "queue/rename",
    {
      id: id,
      name: name
    },
    function (res) {
      callback(res, success, error);
    })
};
function remove(id,success, error){
  App.requestAPI(
    "queue/delete",
    {
      id: id
    },
    function (res) {
        callback(res, success, error);
    });
};

function getMemoryList(id,success, error){
  App.requestAPI(
    "queue/getMemoryList",
    {
      id: id
    },
    function (res) {
      callback(res, success, error);
    });
}

function removeMemory(qid,mid,success, error) {
  App.requestAPI(
    "queue/removeMemory",
    {
      qid: qid,
      mid: mid
    },
    function (res) {
      callback(res, success, error);
    });
}

function insertMemory(mid, qid, success, error) {
  App.requestAPI(
    "queue/insertMemory",
    {
      qid: qid,
      mid: mid
    },
    function (res) {
      callback(res, success, error);
    });
}

function importMemory(qid,lid, success, error) {
  App.requestAPI(
    "queue/importMemory",
    {
      qid: qid,
      lid: lid
    },
    function (res) {
      callback(res, success, error);
    });
}

function callback(res,success,error){
  if (res.data.status == "ok") {
    if (success)
      success(res);
  } else {
    if (error)
      error(error(res));
  }
}