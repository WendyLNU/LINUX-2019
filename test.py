import requests
from bs4 import BeautifulSoup
import time
headers ={
     'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36'
         }
def judement_sex(class_name):  #定义判别用户性别的函数
    if class_name==['number_icol']:
        return '女'
    else:
        return '男'

def get_links(url):           #定义获取详细页url的函数
    wb_data=requests.get(url,headers=headers)
    soup=BeautifulSoup(wb_data.text,'lxml')
    links =soup
    # for link in links:
    #     href =link.get("href")
    get_info(links)            #循环出的url,依次调用函数

def get_info(url):
    wb_data =requests.get(url,headers=headers)
    soup =BeautifulSoup(wb_data.text,'html.parser')
    tittles = soup.select('body > div.wrap.clearfix.con_bg > div.con_l > div.pho_info > h4 > em ')
    for title in tittles:
        print(title.get_text().strip())
    addresses =soup.select('body > div.wrap.clearfix.con_bg > div.con_l > div.pho_info > p > span')
    prices =soup.select('#pricePart > div.day_l > span')
    imgs =soup.select('#floatRightBox > div.js_box.clearfix > div.member_pic > a > img ')
    sexs=soup.select('#floatRightBox > div.js_box.clearfix > div.member_pic > div')
    names =soup.select('#floatRightBox > div.js_box.clearfix > div.w_240 > h6 > a')
    # print(type(list(zip(tittles,addresses,imgs,sexs,names))))
    for tittle,address,price,img,name,sex in zip(tittles,addresses,prices,imgs,sexs,names):
        data ={
            'title':tittle.get_text().strip(),
            'address':address.get_text().strip(),
            'price':price.get_text(),
            'img':img.get("src"),
            'name':name.get_text(),
            'sex':judement_sex(sex.get("class"))
        }
        print(data)


if __name__ =='__main__':
    links =[100066136603,101806505301]
    urls = ['http://bj.xiaozhu.com/fangzi/{}.html'.format(num) for num in links]
    for single_url in urls:

        get_info(single_url)
        time.sleep(2)


# res = requests.get('http://bj.xiaozhu.com/fangzi/101806505301.html',headers=headers)
# try:
#     soup = BeautifulSoup(res.text,'html.parser')
    # print(
    #       soup.find_all('div',attrs={"class":'group_item'})
    # )
#     prices =soup.select('body > div.wrap.clearfix.con_bg > div.con_l > div.pho_info > h4 > em')
#     print(prices)
#     for price in prices:
#         print(price.get_text())
# except ConnectionError:
#     print('拒绝链接')
