import os
from PIL import Image
#把目录下的图片拼接成一张大图片

# 图片压缩后的大小
width_i = 200
height_i = 300

# 每行每列显示图片数量
line_max = 5
row_max = 5

# 参数初始化
all_path = []
num = 0
pic_max = line_max * row_max    #列*行,图片最大数量

for filename in os.listdir('./images'): #方法用于返回指定的文件夹包含的文件或文件夹的名字的列表。
    if filename.endswith('jpg') or filename.endswith('png'):
    #函数判断一个文本是否以某个或几个字符结束，结果以True或者False返回。
        all_path.append(os.path.join('./images', filename)) #os.path.join()函数用于路径拼接文件路径。

toImage = Image.new('RGBA', (width_i * line_max, height_i * row_max))   #Image.new(mode,size,color)

for i in range(0, row_max):
    for j in range(0, line_max):
        # 图片比计划的少
        if num >= len(all_path):
            print("break")
            break
        pic_fole_head = Image.open(all_path[num])
        width, height = pic_fole_head.size  #元组拆包
        tmppic = pic_fole_head.resize((width_i, height_i))  #重设宽高，最终图片
        loc = (int(i % line_max * width_i), int(j % line_max * height_i))
        print("第" + str(num) + "存放位置" + str(loc))
        toImage.paste(tmppic, loc)
        #paste函数的参数为(需要修改的图片，粘贴的起始点的横坐标，粘贴的起始点的纵坐标）
        num = num + 1
    # 图片比计划的多
    if num >= pic_max:
        break

print(toImage.size)
toImage.save('merged.png')