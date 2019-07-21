const API_URL = 'https://api.iclient.ifeng.com';
const API_URL2 = 'https://api.3g.ifeng.com';
const API_LIVE = 'https://sports.live.ifeng.com/API';
const Promise = require('./bluebird')

function fetchApi (type, params, flag) {
  return new Promise((resolve, reject) => {
    wx.request({
      url: `${flag == true ? API_LIVE : API_URL}/${type}`,
      data: Object.assign({}, params),
      header: { 'Content-Type': 'json' },
      success: resolve,
      fail: reject
    })
 
  })
}

module.exports = {
  API_URL: API_URL,
  API_URL2: API_URL2,
  find(type, params) {
    return fetchApi(type, params, null)
      .then(res => res.data)
  }, 
  findLive(type, params) {
    return fetchApi(type, params, true)
      .then(res => res.data)
  },
  findOne (id) {
    return fetchApi('subject/' + id)
      .then(res => res.data)
  }
}

