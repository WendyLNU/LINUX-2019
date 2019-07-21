# -*- coding: utf-8 -*-
"""
Created on Tue Oct 23 22:01:26 2018

@author: asus
"""


import os
import numpy as np
from PIL import Image
import cv2
import random

path = '/Users/yangzixuan/Desktop'
os.chdir(path)


#训练集数据路径
train_images_path = path + '\\data\\training\\images'
train_manual_path = path + '\\data\\training\\1st_manual'
train_mask_path = path + '\\data\\training\\mask'

#数据参数
Nimgs = 20       #图片数量
channels = 3     #通道数rgb
height = 584     #图片高度
width = 565      #图片宽度

######################读入训练数据#########################
train_imgs = np.empty((Nimgs,height,width,channels))
train_groundTruth = np.empty((Nimgs,height,width))
train_border_masks = np.empty((Nimgs,height,width))
#读入原始图像
os.chdir(train_images_path)
files = os.listdir()
for i in range(len(files)):
    img = Image.open(files[i])
    train_imgs[i] = np.asarray(img)
#读入真实值
os.chdir(train_manual_path)
for i in range(len(files)):
    img = Image.open(files[i][0:2] + "_manual1.gif")
    train_groundTruth[i] = np.asarray(img)
#读入边缘
os.chdir(train_mask_path)
for i in range(len(files)):
    img = Image.open(files[i][0:2] + "_training_mask.gif")
    train_border_masks[i] = np.asarray(img)
#调整矩阵形状
train_imgs = np.transpose(train_imgs,(0,3,1,2))
train_groundTruth = np.reshape(train_groundTruth,(Nimgs,1,height,width))
train_border_masks = np.reshape(train_border_masks,(Nimgs,1,height,width))


####################原始图像预处理###################
def preproccess(origin_imgs):
    #将rgb图片转换为灰度图片
    bn_imgs = origin_imgs[:,0,:,:]*0.299 + origin_imgs[:,1,:,:]*0.587 + origin_imgs[:,2,:,:]*0.114
    bn_imgs = np.reshape(bn_imgs,(origin_imgs.shape[0],1,origin_imgs.shape[2],origin_imgs.shape[3]))

    #数据标准化
    imgs_normalized = (bn_imgs - np.mean(bn_imgs)) / np.std(bn_imgs) #整体标准化 z-score normalization
    for i in range(bn_imgs.shape[0]):                                #每张图内部标准化到0-255 Min-max normalization
        imgs_normalized[i] = ((imgs_normalized[i] - np.min(imgs_normalized[i])) / 
        (np.max(imgs_normalized[i])-np.min(imgs_normalized[i])))*255

    #直方图均衡画
    #图像增强：https://en.wikipedia.org/wiki/Adaptive_histogram_equalization#Contrast_Limited_AHE
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



#预处理训练集原始图像
train_imgs = preproccess(train_imgs)
train_masks = train_groundTruth/255. #血管图像转换到0-1
#剪掉图像的上部和底部，使得图像大小为565*565
train_imgs = train_imgs[:,:,9:574,:]  
train_masks = train_masks[:,:,9:574,:]

#生成图片增加数据量，把图片分成很多块
patch_h = 48  #每一块的高度
patch_w = 48   #每一块的宽度
N_patches = 200000 #图片数量

patches = np.empty((N_patches, train_imgs.shape[1], patch_h, patch_w))
patches_masks = np.empty((N_patches, train_imgs.shape[1], patch_h, patch_w))
img_h = train_imgs.shape[2]  #图像的宽和高
img_w = train_imgs.shape[3] 
patch_per_img = int(N_patches/train_imgs.shape[0])   #每张图抽多少个patch

iter_tot = 0   #总共选出的patch的数目
for i in range(train_imgs.shape[0]):
    k = 0 #每张图选中的patch数目
    while k < patch_per_img:
        #随机寻找一个中心
        x_center = random.randint(0+int(patch_w/2), img_w-int(patch_w/2))
        y_center = random.randint(0+int(patch_h/2), img_h-int(patch_h/2))
        #寻找的中心相对于图片中心的坐标
        x_ = x_center - int(img_w/2) 
        y_ = y_center - int(img_h/2)
        #如果选出的patch区域全部在眼球内（正方形patch的半对角线+正方形patch中心到图片中心（原点）的距离
        if True:#int(patch_h * np.sqrt(2.0) / 2.0) + np.sqrt((x_*x_)+(y_*y_)) < 270:
            #取出选中的区域（原始图和血管图）
            patch = train_imgs[i,:,y_center-int(patch_h/2):y_center+int(patch_h/2),x_center-int(patch_w/2):x_center+int(patch_w/2)]
            patch_mask = train_masks[i,:,y_center-int(patch_h/2):y_center+int(patch_h/2),x_center-int(patch_w/2):x_center+int(patch_w/2)]
            patches[iter_tot] = patch
            patches_masks[iter_tot] = patch_mask
            iter_tot += 1   
            k += 1  
        else:
            continue

#patch实例图，展示50张，5行10列
def show_examples(patches, filename = 'C:\\Users\\asus\\Desktop\\sw\\patch_examples'):
    data = np.transpose(patches[0:50,:,:,:],(0,2,3,1))
    all_stripe = []
    for i in range(5):
        stripe = data[i*10] #每行起始第一张
        for k in range(i*10+1, i*10+10): #每行10张拼起来
            stripe = np.concatenate((stripe, data[k]),axis=1)
        all_stripe.append(stripe)
    #5行拼起来
    data = all_stripe[0]
    for i in range(1,len(all_stripe)):
        data = np.concatenate((data,all_stripe[i]),axis=0)
    #转换为图片
    data = np.reshape(data,(data.shape[0],data.shape[1]))
    img = Image.fromarray((data*255).astype(np.uint8))
    img.show()
    img.save(filename + '.png')

show_examples(patches, filename = path + '\\patch_examples')
show_examples(patches_masks, filename = path + '\\patch_mask_examples')

        
####################搭建深度学习网络U-net进行训练######################
n_ch = patches.shape[1]  #通道channel数目
patch_height = patches.shape[2]  #图片高度
patch_width = patches.shape[3]   #图片宽度


####定义网络结构
from keras.models import Model
from keras.layers import Input, concatenate, Conv2D, MaxPooling2D, UpSampling2D, core, Dropout
from keras.utils.vis_utils import plot_model
from keras.callbacks import ModelCheckpoint

#输入层
inputs = Input(shape=(n_ch,patch_height,patch_width))
#第一层，卷积，dropout，卷积，池化
conv1 = Conv2D(32, (3, 3), activation='relu', padding='same',data_format='channels_first')(inputs)
conv1 = Dropout(0.2)(conv1)
conv1 = Conv2D(32, (3, 3), activation='relu', padding='same',data_format='channels_first')(conv1)
pool1 = MaxPooling2D((2, 2),data_format='channels_first')(conv1)
#第二层，卷积，dropout，卷积，池化
conv2 = Conv2D(64, (3, 3), activation='relu', padding='same',data_format='channels_first')(pool1)
conv2 = Dropout(0.2)(conv2)
conv2 = Conv2D(64, (3, 3), activation='relu', padding='same',data_format='channels_first')(conv2)
pool2 = MaxPooling2D((2, 2), data_format='channels_first')(conv2)
#第三层，卷积，dropout，卷积
conv3 = Conv2D(128, (3, 3), activation='relu', padding='same',data_format='channels_first')(pool2)
conv3 = Dropout(0.2)(conv3)
conv3 = Conv2D(128, (3, 3), activation='relu', padding='same',data_format='channels_first')(conv3)
#第四层，上采样，合并，卷积，dropout，卷积
up1 = UpSampling2D(size=(2, 2), data_format='channels_first')(conv3)
up1 = concatenate([conv2,up1],axis=1)
conv4 = Conv2D(64, (3, 3), activation='relu', padding='same',data_format='channels_first')(up1)
conv4 = Dropout(0.2)(conv4)
conv4 = Conv2D(64, (3, 3), activation='relu', padding='same',data_format='channels_first')(conv4)
#第五层，上采样，合并，卷积，dropout，卷积
up2 = UpSampling2D(size=(2, 2), data_format='channels_first')(conv4)
up2 = concatenate([conv1,up2], axis=1)
conv5 = Conv2D(32, (3, 3), activation='relu', padding='same',data_format='channels_first')(up2)
conv5 = Dropout(0.2)(conv5)
conv5 = Conv2D(32, (3, 3), activation='relu', padding='same',data_format='channels_first')(conv5)
#第六层
conv6 = Conv2D(2, (1, 1), activation='relu',padding='same',data_format='channels_first')(conv5)
#reshape为指定形式
conv6 = core.Reshape((2,patch_height*patch_width))(conv6)
#Permute层将输入的维度按照给定模式进行重排
conv6 = core.Permute((2,1))(conv6)
#激活
conv7 = core.Activation('softmax')(conv6)

model = Model(inputs=inputs, outputs=conv7)
model.compile(optimizer='sgd', loss='categorical_crossentropy',metrics=['accuracy'])

#画出网络结构，保存网络结构
os.chdir(path)
#plot_model(model, to_file='model.png', show_shapes = True)
json_string = model.to_json()
open('model.json', 'w').write(json_string)

#训练模型
checkpointer = ModelCheckpoint(filepath=path +'\\best_weights.h5', verbose=1, 
                               monitor='val_loss', mode='auto', save_best_only=True)
#one hot形式
def masks_Unet(masks):
    im_h = masks.shape[2]
    im_w = masks.shape[3]
    masks = np.reshape(masks,(masks.shape[0],im_h*im_w))
    new_masks = np.empty((masks.shape[0],im_h*im_w,2))
    for i in range(masks.shape[0]):
        for j in range(im_h*im_w):
            if  masks[i,j] == 0:
                new_masks[i,j,0]=1
                new_masks[i,j,1]=0
            else:
                new_masks[i,j,0]=0
                new_masks[i,j,1]=1
    return new_masks

del train_border_masks
del train_groundTruth
del train_imgs
del train_masks
    
N_epochs = 20    #迭代20轮
batch_size = 32  #每个batch32张图片
patches_masks = masks_Unet(patches_masks)
model.fit(patches, patches_masks, epochs=N_epochs, batch_size=batch_size, verbose=1, 
          shuffle=True, validation_split=0.1, callbacks=[checkpointer])

#保存模型
model.save_weights('last_weights.h5', overwrite=True)
