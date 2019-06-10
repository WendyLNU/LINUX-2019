# -*- coding: utf-8 -*-
"""
Created on Tue Oct 23 08:13:39 2018

@author: asus
"""


#########################模型评价与预测############################
import os
import numpy as np
from PIL import Image
import cv2

path = '/Users/yangzixuan/Downloads/sw'
os.chdir(path)

#测试集数据路径
test_images_path = path + '\\data\\test\\images'
test_manual_path = path + '\\data\\test\\1st_manual'
test_mask_path = path + '\\data\\test\\mask'

#数据参数
Nimgs = 20       #图片数量
channels = 3     #通道数rgb
height = 584     #图片高度
width = 565      #图片宽度

#######################读入测试数据#####################
test_imgs = np.empty((Nimgs,height,width,channels))
test_groundTruth = np.empty((Nimgs,height,width))
test_border_masks = np.empty((Nimgs,height,width))
#读入原始图像
os.chdir(test_images_path)
files = os.listdir()
for i in range(len(files)):
    img = Image.open(files[i])
    test_imgs[0] = np.asarray(img)
#读入真实值
os.chdir(test_manual_path)
for i in range(len(files)):
    img = Image.open(files[i][0:2] + "_manual1.gif")
    test_groundTruth[i] = np.asarray(img)
#读入边缘
os.chdir(test_mask_path)
for i in range(len(files)):
    img = Image.open(files[i][0:2] + "_test_mask.gif")
    test_border_masks[i] = np.asarray(img)
#调整矩阵形状
test_imgs = np.transpose(test_imgs,(0,3,1,2))
test_groundTruth = np.reshape(test_groundTruth,(Nimgs,1,height,width))
test_border_masks = np.reshape(test_border_masks,(Nimgs,1,height,width))    


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


##########测试集数据准备#########
test_imgs = preproccess(test_imgs)  #测试集原始图片预处理
test_masks = test_groundTruth/255.  #血管图像转换到0-1

patch_h = 48   #每一块的高度
patch_w = 48   #每一块的宽度
stride_h = 5  #横向滑动
stride_w = 5  #纵向滑动
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
from keras.models import model_from_json
os.chdir(path)
model = model_from_json(open('model.json').read())
model.load_weights('best_weights.h5')

##预测
pred = model.predict(patches, batch_size=128, verbose=2)

##将预测值转换回原图像
pred_images = pred[:,:,1] #取后面一个通道的值
pred_images = np.reshape(pred_images,(pred_images.shape[0], 1, patch_h, patch_w))


############将预测的patch拼回图片
new_height = new_test_imgs.shape[2]    #补零后图片高度
new_width = new_test_imgs.shape[3]     #补零后图片宽度
stride_height = 24                  #滑动高度
stride_width = 24                   #滑动宽度
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

#图片展示对比预测结果与真实结果
pred_show = []
for i in range(test_imgs.shape[0]):
    a = (test_imgs[i][0]*255).astype(np.uint8) #原始图片
    b = (test_masks[i][0]*255).astype(np.uint8) #真实血管图片
    c = ((pred_images[i][0])*255).astype(np.uint8) #预测血管图片
    img = np.concatenate((a,b,c), axis = 1)
    pred_show.append(img)
    img = Image.fromarray(img)
    img.save('test-'+str(i) + '.png')

allimg = np.concatenate(pred_show, axis = 0)
allimg = Image.fromarray(allimg)
allimg.save('alltest.png')



from sklearn.metrics import roc_curve
from sklearn.metrics import roc_auc_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import precision_recall_curve
import matplotlib.pyplot as plt


#转换为向量
height = pred_images.shape[2]
width = pred_images.shape[3]
y_scores = []
y_true = []
for i in range(pred_images.shape[0]):  
    for x in range(width):
        for y in range(height):
            if x < test_border_masks.shape[3] and y < test_border_masks.shape[2]:
                if test_border_masks[i,0,y,x]>0: #在border内部
                    y_scores.append(pred_images[i,:,y,x])
                    y_true.append(test_masks[i,:,y,x])
y_scores = np.asarray(y_scores)
y_true = np.asarray(y_true)


#AUC, ROC
fpr, tpr, thresholds = roc_curve((y_true), y_scores)
AUC_ROC = roc_auc_score(y_true, y_scores)
AUC_ROC  #0.97493768936564451

%matplotlib qt5
plt.figure(figsize = (20,10))
plt.plot(fpr,tpr,'-',label='Area Under the Curve (AUC = %0.4f)' % AUC_ROC)
plt.title('ROC curve', fontsize = 30)
plt.xlabel("FPR (False Positive Rate)", fontsize = 20)
plt.ylabel("TPR (True Positive Rate)", fontsize = 20)
plt.legend(loc="lower right", fontsize = 20)
plt.savefig("ROC.png")

#Precision-recall curve
precision, recall, thresholds = precision_recall_curve(y_true, y_scores)
precision = np.fliplr([precision])[0]  
recall = np.fliplr([recall])[0]  
AUC_prec_rec = np.trapz(precision,recall) #0.89799295835344028

%matplotlib qt5
plt.figure(figsize = (20,10))
plt.plot(recall,precision,'-',label='Area Under the Curve (AUC = %0.4f)' % AUC_prec_rec)
plt.title('Precision - Recall curve', fontsize = 30)
plt.xlabel("Recall", fontsize = 20)
plt.ylabel("Precision", fontsize = 20)
plt.legend(loc="lower right", fontsize = 20)
plt.savefig("Precision_recall.png")

#Confusion matrix
threshold_confusion = 0.5
y_pred = np.empty((y_scores.shape[0]))
for i in range(y_scores.shape[0]):
    if y_scores[i]>=threshold_confusion:
        y_pred[i]=1
    else:
        y_pred[i]=0
confusion = confusion_matrix(y_true, y_pred)
confusion
#array([[3908311,   52183],[ 165428,  412221]], dtype=int64)
accuracy = float(confusion[0,0]+confusion[1,1])/float(np.sum(confusion))
accuracy  #0.9520484480105629
