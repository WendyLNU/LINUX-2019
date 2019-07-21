#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jan 20 09:35:39 2019

@author: yangzixuan
"""
from tkinter import *
import tkinter.filedialog
import os
import tensorflow as tf
from PIL import Image,ImageTk
import cv2
import matplotlib.pyplot as plt
import numpy as np
import sys
import pandas as pd 



workdir = os.path.split(os.sys.argv[0])[0]
os.chdir(workdir)
#aa = Image.open("Medical.png")
#aa =aa.resize((400,400))



root=Tk()
python def Selectimage():
    global filename
    filename = tkinter.filedialog.askopenfilename()
    if len(filename) != 0:
        string_filename =""
        for i in range(0,len(filename)):
            string_filename += str(filename[i])
        lb.config(text = "成功导入图片"+string_filename)
    else:
        lb.config(text = "您没有选择任何文件");
    b2.config(text='导入成功！')
#定义输入图片的函数并保存图片
        

def show ():
    global allimg
    global asave
    
    if allimg=='':
        c1.config(text='显示错误')
    else:
        allimg=allimg.resize((400,400))    
        asave=allimg
        allimg=ImageTk.PhotoImage(allimg)
        c2.configure(image=allimg)
        c1.config(text='您的图片为')
    
def hold():
    global allimg
    global asave
    asave.save('血管图片.gif')
    d1.config(text='保存成功')
    
def training ():
    import os
    import tensorflow as tf
    from PIL import Image,ImageTk
    import cv2
    import matplotlib.pyplot as plt
    import numpy as np
    #########################模型评价与预测############################
    global filename
    if filename=='':
        b1.config(text='请您导入图片后再提取')
    else:
        b1.config(text='正在提取请稍等')
    
    
    
    #数据参数
    Nimgs = 20       #图片数量
    channels = 3     #通道数rgb
    height = 584     #图片高度
    width = 565      #图片宽a度
    
    #######################读入测试数据#####################
    test_imgs = np.empty((Nimgs,height,width,channels))
    img = Image.open(filename)
    test_imgs[0] = np.asarray(img)
    test_imgs = np.transpose(test_imgs,(0,3,1,2))
    
    
    ####################原始图像预处理###################
    def preproccess(origin_imgs):
        #将rgb图片转换为灰度图片
        bn_imgs = origin_imgs[:,0,:,:]*0.299 + origin_imgs[:,1,:,:]*0.587 + origin_imgs[:,2,:,:]*0.114
        bn_imgs = np.reshape(bn_imgs,(origin_imgs.shape[0],1,origin_imgs.shape[2],origin_imgs.shape[3]))
    
        #数据标准化
        imgs_normalized = (bn_imgs - np.mean(bn_imgs)) / np.std(bn_imgs) #整体标准化 z-score normalization
        for i in range(bn_imgs.shape[0]):                                #图内部标准化到0-255 Min-max normalization
            imgs_normalized[i] = ((imgs_normalized[i] - np.min(imgs_normalized[i])) / 
            (np.max(imgs_normalized[i])-np.min(imgs_normalized[i])))*255
    
        #直方图均衡化
        #CLAHE (Contrast Limited Adaptive Histogram Equalization)
        clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
        imgs_equalized = np.empty(imgs_normalized.shape)
        for i in range(imgs_normalized.shape[0]):
            imgs_equalized[i,0] = clahe.apply(np.array(imgs_normalized[i,0], dtype = np.uint8))
    
        #拉伸直方图:https://blog.csdn.net/sunny2038/article/details/9403059
        invGamma = 1.0 / 1.2
        table = np.array([((i / 255.0) ** invGamma) * 255 for i in np.arange(0, 256)]).astype("uint8")
        new_imgs = np.empty(imgs_equalized.shape)
        for i in range(imgs_equalized.shape[0]):
            new_imgs[i,0] = cv2.LUT(np.array(imgs_equalized[i,0], dtype = np.uint8), table)
            
        new_imgs = new_imgs/255. #转换到0-1
        return(new_imgs)
    
    
    ##########测试集数据准备#########
    test_imgs = preproccess(test_imgs)  #测试集原始图片预处理
    patch_h = 48   #每一块的高度
    patch_w = 48   #每一块的宽度
    stride_h = 65  #横向滑动
    stride_w = 65  #纵向滑动
    img_h = test_imgs.shape[2]     #图片的高度
    img_w = test_imgs.shape[3]     #图片的宽度
    leftover_h = (img_h-patch_h)%stride_h #剩下的行
    leftover_w = (img_w-patch_w)%stride_w #剩下的列
    
    #边上补零，避免最后的位置截取不到
    #1--48，1+5--48+5，...., 1+107*5--48+107*5=583（不补的话584列就取不到）, 1+108*5--48+108*5=588
    if leftover_h != 0:  #如果剩下的行数不为0，则用0补齐
        new_test_imgs = np.zeros((test_imgs.shape[0],test_imgs.shape[1],img_h+(stride_h-leftover_h),img_w))
        new_test_imgs[0:test_imgs.shape[0],0:test_imgs.shape[1],0:img_h,0:img_w] = test_imgs
    if leftover_w != 0:  #如果剩下的列数不为0，则用0补齐
        new_new_test_imgs = np.zeros((new_test_imgs.shape[0],new_test_imgs.shape[1],new_test_imgs.shape[2],img_w+(stride_w - leftover_w)))
        new_new_test_imgs[0:new_test_imgs.shape[0],0:new_test_imgs.shape[1],0:new_test_imgs.shape[2],0:img_w] = new_test_imgs
    
    new_test_imgs = new_new_test_imgs
    del new_new_test_imgs
    
    new_height = new_test_imgs.shape[2]  #图片的高度
    new_width = new_test_imgs.shape[3]  #图片的宽度
    #每张图可以截取出多少个图
    N_patches_img = ((new_height-patch_h)//stride_h+1)*((new_width-patch_w)//stride_w+1)
    #总共可以截取的图片数量
    N_patches_tot = N_patches_img * new_test_imgs.shape[0]
    
    patches = np.empty((N_patches_tot, test_imgs.shape[1], patch_h, patch_w))
    iter_tot = 0   #总的patch数
    for i in range(new_test_imgs.shape[0]):
        for h in range((new_height-patch_h)//stride_h+1):
            for w in range((new_width-patch_w)//stride_w+1):
                #滑动截取patch
                patch = new_test_imgs[i,:,h*stride_h:(h*stride_h)+patch_h,w*stride_w:(w*stride_w)+patch_w]
                patches[iter_tot] = patch
                iter_tot += 1
    ###加载模型
    from keras.models import model_from_json#abc
    global address
    #os.chdir('/Users/yangzixuan/Desktop/ExtractionSystem')
    model = model_from_json(open('model.json').read())
    model.load_weights('best_weights.h5')
    ##识别
    pred = model.predict(patches, batch_size=1024, verbose=1)
    
    
     ##将提取后图像转换回原图像
    pred_images = pred[:,:,1] #取后面一个通道的值
    pred_images = np.reshape(pred_images,(pred_images.shape[0], 1, patch_h, patch_w))
    
    ############将预测的patch拼回图片
    new_height = new_test_imgs.shape[2]    #补零后图片高度
    new_width = new_test_imgs.shape[3]     #补零后图片宽度
    stride_height = 65                  #滑动高度
    stride_width = 65                   #滑动宽度
    patch_h = 48                       #patch的高
    patch_w = 48                       #patch的宽
    N_patches_h = (new_height-patch_h)//stride_h+1   
    N_patches_w = (new_width-patch_w)//stride_w+1
    N_patches_img = N_patches_h * N_patches_w    #总patch数量
    N_full_imgs = pred_images.shape[0]//N_patches_img  #图片数量
    full_prob = np.zeros((N_full_imgs, pred_images.shape[1], new_height, new_width))
    full_sum = np.zeros((N_full_imgs, pred_images.shape[1], new_height, new_width))
    k = 0   #patch
    for i in range(N_full_imgs):
        for h in range((new_height-patch_h)//stride_h+1):
            for w in range((new_width-patch_w)//stride_w+1):
                #记录预测值
                full_prob[i,:,h*stride_h:(h*stride_h)+patch_h,w*stride_w:(w*stride_w)+patch_w] += pred_images[k]
                #记录预测次数
                full_sum[i,:,h*stride_h:(h*stride_h)+patch_h,w*stride_w:(w*stride_w)+patch_w] += 1
                k += 1
    pred_images = full_prob/full_sum #计算平均值
    
    #截取原始图片的大小
    pred_images = pred_images[:,:,0:img_h,0:img_w]
    
    #图片展示
    pred_show = []
    for i in range(test_imgs.shape[0]):
        a = ((pred_images[i][0])*255).astype(np.uint8) #预测血管图片
        pred_show.append(a)
        img = Image.fromarray(a)
       # img.save('test-'+str(i) + '.gif')
    global allimg
    allimg = np.concatenate(pred_show, axis = 0)
    allimg = Image.fromarray(allimg)
    
    b1.config(text='提取完毕')
    
    
    
    
root.title("眼底图像识别系统")
root.geometry('1000x1200')
root.resizable(width=True,height=True)
#设置一个长为1000 宽为1200的窗口 且长宽大小可调

w1=Label(root,text='姓名:')#姓名文本框
w1.place(relx=0.08,rely=0.2,anchor=NW)
w2=Label(root,text='性别')#性别文本框
w2.place(relx=0.08,rely=0.3,anchor=NW)
global allimg
b1= Button(root,text='提取', fg='red',bg='black',command=training)#提取按钮
b1.place(relx=0.08,rely=0.6,anchor=NW)

b2=Button(root,text='导入图片',fg='red',bg='black',command=Selectimage)#输入按钮
b2.place(relx=0.08,rely=0.5,anchor=NW)
lb=Label(root,text='')
lb.place(relx=0.08,rely=0.55,anchor=NW)

e1=Entry(root)#姓名输入框
e1.place(relx=0.12,rely=0.2,anchor=NW)
e2=Entry(root)#性别输入框
e2.place(relx=0.12,rely=0.3,anchor=NW)

c1=Button(root,text='显示血管图片',command=show)#显示按钮
c1.place(relx=0.72,rely=0.1,anchor=NW)

d1= Button(root, text='保存图片', fg='red',command=hold)#保存按钮
d1.place(relx=0.73,rely=0.7,anchor=NW)



#aa=ImageTk.PhotoImage(aa)


#c2=Label (root,image=aa)
#c2.place(relx=0.56,rely=0.15,anchor=NW)

global filename
filename=''
global allimg
allimg=''
#global address
#address=''
#设置一系列全局变量
#获取根目录
#os.getcwd()
#address=os.getcwd()



root.mainloop()



