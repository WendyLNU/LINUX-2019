import requests
import re
from bs4 import BeautifulSoup
from lxml import html
import time                #引入相应库文件

headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36'}
#加入请求头
urls = ['https://www.qiushibaike.com/text/page/{}/'.format(str(num)) for num in range(1,36)]
#构造urls

def re_scraper(url):
    res = requests.get(url,headers=headers)
    ids = re.findall('<h2>(.*?)</h2>',res.text,re.S)
    contents = re.findall('<div class="content">.*?<span>(,*?)</span>',res.text,re.S)
    laughs =  re.findall('<span class="stats-vote"><i class="number">(/d+)</i>',res.text,re.S)
    comments = re.findall('<i class="number">(/d+)</i> 评论',res.text,re.S)
    for id, content, laugh, comment, in zip(ids,contents,laughs,comments):
        info={
            'id':id,
            'content':content,
            'laugh':laugh,
            'comment':comment
        }
        return info               #只返回数据，不储存

def lxml_scrapper(url):
    res = requests.get(url,headers = headers)
    etree = html.etree
    selector = etree.HTML(res.text)
    url_infos = selector.xpath('//div[@class="article block untagged mb15"]')
    try:
        for url_info in url_infos:
            id = url_info.xpath('div[1]/a[2]/h2/text()')[0]
            content = url_info.xpath('a[1]/div/span/text()')[0]
            laugh = url_info.xpath('div[2]/span/span[2]/i/text()')[0]
            comment = url_info.xpath('a[1]/div/span/text()')[0]
            info={
                'id':id,
                'content':content,
                'laugh':laugh,
                'comment':comment
            }
            return info
    except IndexError:
        pass         #pass掉IndexError 异常

def bs_scrapper(url):
    res = requests.get(url,headers = headers)
    soup = BeautifulSoup(res.text,'html.parser')
    ids = soup.select(' a > h2')
    contents = soup.select(' div > span')
    laughs = soup.select(' span.stats-vote > i')
    comments = soup.select('i.number')
    for id, content, laugh, comment, in zip(ids, contents, laughs, comments):
        info = {
            'id':id.get_text(),
            'content':content.get_text(),
            'laugh':laugh.get_text(),
            'comment':comment.get_text()
        }
        return info

if __name__ == '__main__':
    for name,scrapper in [('Regular expressions',re_scraper),('Beautifulsoup',bs_scrapper),('Lxml',lxml_scrapper)]:
        start =time.time()
        for url in urls:
            scrapper(url)
        end = time.time()
        print(name,end-start)
