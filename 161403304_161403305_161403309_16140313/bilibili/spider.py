import requests
import time
import html
import re
from lxml import etree
from random import choice
from useragent import USERAGNET
from settings import SETTINGS

s = SETTINGS["spider"]


def get_data(aid):
    b = time.perf_counter()
    data = {}
    while True:
        time.sleep(s["interval"])

        json_raw = get_json(aid)
        html_raw = get_html(aid)

        if json_raw != None and html_raw != None:
            if json_raw["code"] != 0:
                data["aid"] = aid
                data["status"] = 1
            else:
                data = json_raw["data"]
                if data["view"] == "--":
                    data["status"] = 2
                else:
                    tree = etree.HTML(html_raw)
                    data["title"] = "_".join(
                        tree.xpath("/html/head/meta[8]")[0].xpath("@content")
                        [0].split("_")[0:-1])
                    data["desc"] = html.unescape(
                        tree.xpath("/html/head/meta[6]")[0].xpath("@content")
                        [0])
                    data["tname"] = tree.xpath(
                        '//*[@id="viewbox_report"]/div[1]/span[1]/a[2]/text()'
                    )
                    data["bname"] = tree.xpath(
                        '//*[@id="viewbox_report"]/div[1]/span[1]/a[1]/text()'
                    )
                    data["ctime"] = int(
                        re.findall(r'"pubdate":(\d+),', html_raw)[0])
                    data["status"] = 0
            return data
        e = time.perf_counter()

        if e - b > s["timeout"]:
            data["aid"] = aid
            data["status"] = -1
            return data


def get_json(aid):
    retry = s["maxretry"]

    headers = {
        "Accept": "*/*",
        "Origin": "https://www.bilibili.com",
        "Referer": "https://www.bilibili.com/video/av%s/" % aid,
        "User-Agent": choice(USERAGNET)
    }

    while retry > 0:
        #https://api.bilibili.com/x/web-interface/view?aid=
        try:
            #proxy = get_proxy()
            r = requests.get(
                "https://api.bilibili.com/x/web-interface/archive/stat?aid=%s" %
                aid,
                headers=headers,
                # proxies={
                #     "http": "http://{}".format(proxy),
                #     "https": "http://{}".format(proxy)
                # },
                timeout=3)
            #print(r)
            if r.status_code in [200, 301, 302, 303, 307]:
                return r.json()
        except Exception:
            retry -= 1

    delete_proxy(proxy)
    return None


def get_html(aid):
    retry = s["maxretry"]

    headers = {
        "Accept":
        "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3",
        "Host": "www.bilibili.com",
        "Referer": "https://www.bilibili.com/",
        "User-Agent": choice(USERAGNET)
    }


    while retry > 0:
        try:
            #proxy = get_proxy()
            r = requests.get("https://www.bilibili.com/video/av%s/" % aid,
                            headers=headers,
                            # proxies={
                            #     "http": "http://{}".format(proxy),
                            #     "https": "http://{}".format(proxy)
                            # },
                            timeout=3)
            #print(r)
            if r.status_code in [200, 301, 302, 303, 307]:
                return r.text
        except Exception:
            retry -= 1

    delete_proxy(proxy)
    return None


def get_proxy():
    return requests.get("http://67.216.208.198:5010/get/").text


#67.216.208.198


def delete_proxy(proxy):
    requests.get("http://67.216.208.198:5010/delete/?proxy={}".format(proxy))


if __name__ == "__main__":
    print(get_data(3))