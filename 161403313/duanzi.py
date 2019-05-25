import requests
import re
import time
from bs4 import BeautifulSoup
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36'}
info_lists =[]
def judgment_sex(class_name):
    if class_name == 'womenIcon':
        return '女'
    else:
        return '男'

def get_info(url):
    res =requests.get(url,headers=headers)
    ids = re.findall('<h2>(.*?)</h2>',res.text,re.S)
    print(ids)
    levels =re.findall('<div class="articleGender manIcon">(.*?)</div>',res.text,re.S)
    print(levels)
    sexs = re.findall('<div class="articleGender (.*?)">', res.text, re.S)
    print(sexs)
    contents =re.findall('<div class="content">.*?<span>(.*?)</span>',res.text,re.S)
    print(contents)
    for id,level,sex,content in zip(ids,levels,sexs,contents):
        info = {
            'id':id.strip(),
            'level':level.strip(),
            'sex':judgment_sex(sex),
            'content':content.strip()
        }
        info_lists.append(info)



if __name__ == "__main__":
    urls = ['https://www.qiushibaike.com/text/page/{}/'.format(str(num)) for num in range(1,36)]
    for single_url in urls:
        get_info(single_url)
        for info_list in info_lists:
            f = open('C:\\Users\\456\\Desktop\\duanzi.txt', 'a+',encoding='utf-8')
            try:
                f.write(info_list['id']+'\n',)
                f.write(info_list['level'] + '\n')
                f.write(info_list['sex'] + '\n')
                f.write(info_list['content'] + '\n')
                f.close()
            except UnboundLocalError:
                pass


