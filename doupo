import requests
import re
import time
from bs4 import BeautifulSoup
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36'}
f = open('C:\\Users\\456\\Desktop\\doupo.txt','a+')
def get_info(url):
    res =requests.get(url,headers=headers)

    if res.status_code==200:
        contents = re.findall('<p>(.*?)</p>',res.content.decode('utf-8'),re.S)
        for content in contents:
           f.write(content+'\n')
    else:
        pass


if __name__ == "__main__":
    urls = ['http://www.doupoxs.com/doupocangqiong/{}.html'.format(str(num)) for num in range(2,1665)]
    for single_url in urls:
        get_info(single_url)
        time.sleep(1)
f.close()
