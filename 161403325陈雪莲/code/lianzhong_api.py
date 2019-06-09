# coding: utf-8
import requests
import json



def main(file_name):
    '''
            main() 参数介绍
            api_username    （API账号）             --必须提供
            api_password    （API账号密码）         --必须提供
            file_name       （需要识别的图片路径）   --必须提供
            api_post_url    （API接口地址）         --必须提供
            yzm_min         （识别结果最小长度值）        --可空提供
            yzm_max         （识别结果最大长度值）        --可空提供
            yzm_type        （识别类型）          --可空提供
            tools_token     （工具或软件token）     --可空提供
    '''

    api_post_url = "http://v1-http-api.jsdama.com/api.php?mod=php&act=upload"
    headers = {
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language': 'zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3',
        'Accept-Encoding': 'gzip, deflate',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0',
        # 'Content-Type': 'multipart/form-data; boundary=---------------------------227973204131376',
        'Connection': 'keep-alive',
        'Host': 'v1-http-api.jsdama.com',
        'Upgrade-Insecure-Requests': '1'
    }

    files = {
        'upload': (file_name, open(file_name, 'rb'), 'image/png')
    }

    data = {
        'user_name': r'',#联众账号
        'user_pw': r'',#联众密码
        'yzm_minlen': 1,
        'yzm_maxlen': 8,
        'yzmtype_mark': 1303,
        'zztool_token': 14264
    }
    s = requests.session()
    # r = s.post(api_post_url, headers=headers, data=data, files=files, verify=False, proxies=proxies)
    r = s.post(api_post_url, headers=headers, data=data, files=files, verify=False)
    print(r.json())
    return r.json()['data']['val']


def download_vcode():
    try:
        url = '识别图片URL地址'
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'}
        s = requests.session()
        resp = s.get(url, headers=headers, verify=False)
        file_name = 'c:/temp/lianzhong_vcode.png'
        with open(file_name, 'wb') as f:
            f.write(resp.content)
    except Exception as e:
        print(e)


if __name__ == '__main__':
    # download_vcode()
    res = main('API/yzm.jpg',"http://v1-http-api.jsdama.com/api.php?mod=php&act=upload")

    '''
		main() 参数介绍
		api_username    （API账号）             --必须提供
		api_password    （API账号密码）         --必须提供
		file_name       （需要识别的图片路径）   --必须提供
		api_post_url    （API接口地址）         --必须提供
		yzm_min         （识别结果最小长度值）        --可空提供
		yzm_max         （识别结果最大长度值）        --可空提供
		yzm_type        （识别类型）          --可空提供
		tools_token     （工具或软件token）     --可空提供
    '''
    # print(type(res))
    # result = res['data']['val'].replace('|', ',')
    # print(result)
    print(res)