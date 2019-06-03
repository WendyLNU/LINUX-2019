module.exports = {
  getMasterNumb: getMasterNumb,

}
var App = getApp();
function getMasterNumb(success, error) {
  App.requestAPI(
    "memory/getMasterNumb",
    {

    },
    function (res) {
      callback(res, success, error);
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