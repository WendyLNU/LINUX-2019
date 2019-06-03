module.exports = {
  getList: getList,
  create: create,
  rename: rename,
  remove:remove,
  importLibrary: importLibrary,
  openTreasureBox: openTreasureBox,
  shareLibrary: shareLibrary,
  getSharedHistory: getSharedHistory,
  acquireLibrary: acquireLibrary,
  deleteSharedHistory: deleteSharedHistory
}
var App=getApp();

function deleteSharedHistory(id,success, error){
  App.requestAPI(
    "library/deleteSharedHistory",
    {
      id:id
    },
    function (res) {
      callback(res, success, error);
    }
  )
}

function getSharedHistory(success, error){
  App.requestAPI(
    "library/getSharedHistory",
    {
    },
    function (res) {
      callback(res, success, error);
    }
  )
}

function acquireLibrary(supid,code, success, error){
  if (!supid) {
    supid = null;
  }
  App.requestAPI(
    "library/acquireLibrary",
    {
      supid: supid,
      code:code
    },
    function (res) {
      callback(res, success, error);
    }
  )
}

function shareLibrary(id, success, error){
  App.requestAPI(
    "library/shareLibrary",
    {
      id: id
    },
    function (res) {
      callback(res, success, error);
    }
  )
}

function openTreasureBox(key, success, error) {
  App.requestAPI(
    "library/openTreasureBox",
    {
      name: key
    },
    function (res) {
      callback(res, success, error);
    }
  )
};
function getList(supid,success,error){
  if(!supid){
    supid=null;
  }
  App.requestAPI(
    "library/getList",
    {
      supid: supid
    },
    function (res) {
      callback(res, success, error);
    }
  )
};
function create(supid, name,success, error){
  App.requestAPI(
    "library/create",
    {
      supid: supid,
      name: name
    },
    function (res) {
      callback(res, success, error);
    })
};
function rename(id, name, success, error){
  App.requestAPI(
    "library/rename",
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
    "library/delete",
    {
      id: id
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};
function importLibrary(id, success, error) {
  App.requestAPI(
    "library/importLibrary",
    {
      id: id
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};
function callback(res,success,error){
  if (res.data.status == "ok") {
    if (success)
      success(res);
  } else {
    if (error)
      error(error(res));
  }
}