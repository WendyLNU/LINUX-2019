# -*-coding:utf8-*-
import os
import cv2
import shutil

def getAllPath(dirpath):
    PathArray = []  #定义一个空列表，存文件名
    for filename in os.listdir(dirpath):    #返回指定的文件夹包含的文件或文件夹的名字的列表。
        if filename.endswith('jpg') or filename.endswith('png'):
            PathArray.append(os.path.join(dirpath, filename))   #连接两个或更多的路径名组件
    return PathArray

# 从源路径中读取所有图片放入一个list，然后逐一进行检查，把其中的脸扣下来，存储到目标路径中
def readPicSaveFace(sourcePath,invalidPath):    #无效的
    try:
        ImagePaths = getAllPath(sourcePath)
        # 对list中图片逐一进行检查,找出其中的人脸然后写到目标文件夹下
        # haarcascade_frontalface_alt.xml为库训练好的分类器文件，下载opencv，安装目录中可找到
        face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml') #级联分类器
        for imagePath in ImagePaths:
            img = cv2.imread(imagePath)
            if type(img) != str:
                faces = face_cascade.detectMultiScale(img, 1.1, 5)
                #它可以检测出图片中所有的人脸，并将人脸用vector保存各个人脸的坐标、大小（用矩形表示），函数由分类器对象调用
                # 参数1：image - -待检测图片，一般为灰度图像加快检测速度；
                # 参数3：scaleFactor - -表示在前后两次相继的扫描中，搜索窗口的比例系数。默认为1.1
                # 即每次搜索窗口依次扩大10 %;
                # 参数4：minNeighbors - -表示构成检测目标的相邻矩形的最小个数(默认为3个)。
                # 如果组成检测目标的小矩形的个数和小于min_neighbors - 1都会被排除。
                # 如果min_neighbors为0, 则函数不做任何操作就返回所有的被检候选矩形框，
                # 这种设定值一般用在用户自定义对检测结果的组合程序上；
                if len(faces):
                    print(imagePath + " have face")
                else:
                    shutil.move(imagePath, invalidPath) #移动文件(目录)
    except IOError:
        print("Error")


if __name__ == '__main__':
    invalidPath = './user_no_face'
    sourcePath = 'user'
    readPicSaveFace(sourcePath,invalidPath)