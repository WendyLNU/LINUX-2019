import requests
import time
import concurrent.futures as futures
from bs4 import BeautifulSoup


# def run(aid):
#     url = "https://api.bilibili.com/x/web-interface/view?aid={}".format(aid)
#     headers = {"Accept": "*/*", "Origin": "https://www.bilibili.com", "Referer": "https://www.bilibili.com/video/av{}/".format(aid), "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36"}
#     try:
#         req = requests.get(url, headers=headers, timeout=3).json()
#         time.sleep(0.2)
#         if req["code"] == 0:
#             print(req["data"]["title"]," {}".format(aid))
#         else:
#             print(req["code"])
#     except:
#         print("error")
start = time.clock()
def run2(aid):

    url = "https://www.bilibili.com/video/av{}".format(aid)
    headers = {"Accept": "*/*", "Accept-Encoding": "gzip, deflate, br", "Accept-Language": "zh-CN,zh;q=0.9", "Host": "www.bilibili.com", "Referer": "https://www.bilibili.com/", "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36"}
    req = requests.get(url, headers=headers, timeout=3)
    soup = BeautifulSoup(req.text, 'html.parser')
    print(soup.select('#viewbox_report > h1 > span')[0].get_text().strip())

if __name__ == "__main__":
    with futures.ThreadPoolExecutor(16) as executor:
        executor.map(run2, range(1, 2000))
    elapsed = (time.clock() - start)
    print("Time used:", elapsed)


