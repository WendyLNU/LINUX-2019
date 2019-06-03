module.exports = {
  importLibrary: importLibrary,
  buyLibrary: buyLibrary,
  sellLibrary: sellLibrary,
  getSalesHistory: getSalesHistory,
  getPurchaseHistory: getPurchaseHistory,
  removeSalesHistory: removeSalesHistory,
  removePurchaseHistory: removePurchaseHistory
}
var App = getApp();
function removeSalesHistory(id, success, error) {
  App.requestAPI(
    "market/removeSalesHistory", {
      id: id
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};
function removePurchaseHistory(id,success, error) {
  App.requestAPI(
    "market/removePurchaseHistory", {
      id:id
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};

function getSalesHistory(success, error) {
  App.requestAPI(
    "market/getSalesHistory", {
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};
function getPurchaseHistory(success, error) {
  App.requestAPI(
    "market/getPurchaseHistory", {
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};

function importLibrary(id, success, error) {
  App.requestAPI(
    "market/importLibrary", {
      id: id
    },
    function(res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};

function sellLibrary(id, success, error) {
  App.requestAPI(
    "market/sellLibrary", {
      id: id
    },
    function (res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
};


function buyLibrary(id, success, error) {
  App.requestAPI(
    "market/buyLibrary", {
      id: id
    },
    function(res) {
      if (res.data.status == "ok") {
        callback(res, success, error);
      }
    });
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