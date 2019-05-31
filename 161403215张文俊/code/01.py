from PIL import Image

# 区域由一个4元组定义，表示为坐标是 (left, upper, right, lower)。 Python Imaging Library 使用左上角为 (0, 0)的坐标系统。
# 同时要注意，这些坐标指向像素之间的位置，因此上述例子中描述的区域的大小为300x300像素。
# 后两个数字需要比前两个大
def cut_image(image,count1,count2):
    width, height = image.size
    item_width = int(width / count1)
    item_height = int(height / count2)
    box_list = []   #定义一个空列表，容器
    # (left, upper, right, lower)
    for i in range(0,count1):
        for j in range(0,count2):
            box = (j*item_width,i*item_height,(j+1)*item_width,(i+1)*item_height)
            box_list.append(box) #append向后面添加元素，参数可以是任何东西，将作为元素添加到列表尾部。
    image_list = [image.crop(box) for box in box_list]#截取子图片，列表推导式
    return image_list

#保存
def save_images(image_list):
    index = 1
    for image in image_list:
        image.save(str(index) + '.png', 'PNG')
        index += 1

if __name__ == '__main__':
    file_path = "total1.png"  #图片保存的地址
    image = Image.open(file_path)

    image_list = cut_image(image,5,5)
    save_images(image_list)