# 匿名函数,Python的lambda表达式基本语法是在冒号（：）左边放原函数的参数，可以有多个参数，用逗号（，）隔开即可；冒号右边是返回值。
#写一些执行脚本时，使用lambda就可以省下定义函数过程，简化代码的可读性，由于普通的函数阅读经常要跳到开头def定义部分，
# 使用lambda函数可以省去这样的步骤。
from PIL import Image, ImageDraw, ImageFont
import os
#gen_text_img函数根据设定的文字以及字体大小生成一张图片（包含设定的文字），
# 先用给定的字符串生成一张图片，然后将该图片的每个像素的宽扩张edge_len倍，高也扩张edge_len倍，假设edge_len=60，
# 那么原文字图片（如上图）的每个像素就变成了60*60像素的一个图片（我们会将每个朋友圈头像放进去）；原文字图片的每个像素的
# 透明度不同，比如显示芒种这2个字的地方，透明度低（不透明），这2个字周边的地方，透明度高（透明），我们根据原文字图片每个
# 像素的透明度，来设定放到这个像素（其实宽高已经扩大了60倍）位置的微信好友头像的透明度（trans_alpha方法实现）。
def gen_text_img(text, font_size=20, font_path=None):
    # 从文字生成图像，输入：文字内容，文字字体大小，字体路径
    font = ImageFont.truetype(font_path, font_size) if font_path is not None else None
    #加载一个TrueType字体文件,并且创建一个字体对象。
    (width, length) = font.getsize(text)  # 获取文字大小,元组拆包
    text_img = Image.new('RGBA', (width, length))   #文字图片
    draw = ImageDraw.Draw(text_img) #创建一个可以在给定图像上绘图的对象。
    # 第一个tuple表示未知(left,up)，之后是文字，然后颜色，最后设置字体
    draw.text((0, 0), text, fill=(0, 0, 0), font=font)  #参数：位置，文本，颜色，字体
    text_img.save('testtext.png')
    return text_img

def trans_alpha(img, pixel):
    '''根据pixel的rgba调节img的透明度
    这里传进来的pixel是一个四元组（r,g,b,alpha）
    '''
    _, _, _, alpha = img.split()    #分离通道
    alpha = alpha.point(lambda i: pixel[-1]*10) #point()改变像素点(函数),匿名函数，提高图片透明度，使观察方便
    img.putalpha(alpha) #对图像添加 alpha 层，即将给定通道拷贝到图像 alpha 层.
    return img

def picture_wall_mask(text_img, edge_len, pic_dir="./user"):
    # 根据文字图像生成对应的照片墙，输入：文字图像，各个照片边长，照片所在路径
    new_img = Image.new('RGBA', (text_img.size[0] * edge_len, text_img.size[1] * edge_len))
    file_list = os.listdir(pic_dir) #返回指定的文件夹包含的文件或文件夹的名字的列表。
    img_index = 0
    for x in range(0, text_img.size[0]):
        for y in range(0, text_img.size[1]):
            pixel = text_img.getpixel((x, y))   #获取某个像素位置的值
            file_name = file_list[img_index % len(file_list)]
            try:
                img = Image.open(os.path.join(pic_dir, file_name)).convert('RGBA')  #把目录和文件名合成一个路径
                img = img.resize((edge_len, edge_len))
                img = trans_alpha(img, pixel)

                new_img.paste(img, (x * edge_len, y * edge_len))
                img_index += 1
            except Exception as e:
                print(f"open file {file_name} failed! {e}")
    return new_img

def main(text='', font_size = 20, edge_len = 60,pic_dir = "./user", out_dir = "./out/", font_path = './demo.ttf'):

    if len(text) >= 1:
        text_ = ' '.join(text)#将字符串用空格分隔开
            print(f"generate text wall for '{text_}' with picture path:{pic_dir}")
            #加f后可以在字符串里面使用用花括号括起来的变量和表达式,
        text_img = gen_text_img(text_, font_size, font_path)
        # text_img.show()
        img_ascii = picture_wall_mask(text_img, edge_len, pic_dir)
        # img_ascii.show()
        img_ascii.save(out_dir + os.path.sep + '_'.join(text) + '.png') #os.path.sep:路径分隔符

if __name__ == '__main__':
    main(text='芒种')