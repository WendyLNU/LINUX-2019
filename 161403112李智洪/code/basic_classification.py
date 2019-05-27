import tensorflow as tf
from tensorflow import keras
 
import numpy as np
import matplotlib.pyplot as plt
 
print(tf.__version__)

fashion_mnist=keras.datasets.fashion_mnist
(train_images,train_labels),(test_images,test_labels)= fashion_mnist.load_data()
class_names=['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

print("The shape of train_images is ",train_images.shape)
print("The shape of train_labels is ",train_labels.shape)
print("The shape of test_images  is ",test_images.shape)
print("The length of test_labels is ",len(test_labels))

#显示第一个样本图
plt.figure()
plt.imshow(train_images[0])#plt.imshow是用来绘制热图的，不是用来显示图片的
plt.colorbar()
plt.grid(False)# 不显示网格线
plt.show()#真正显示图片的

#将这些值缩小到 0 到 1 之间，然后将其馈送到神经网络模型
#归一化
train_images = train_images/255.0
test_images=test_images/255.0
plt.figure(figsize=(10,10))

#显示训练集中的前 25 张图像，并在每张图像下显示类别名称。
for i in range(25):
    plt.subplot(5,5,i+1)
    plt.xticks([])#ticks记号，xticks表示x轴的记号，比如plt.xticks([a,b,c]),x轴则显示a,b,c等间距文本
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i],cmap=plt.cm.binary)#cmap:colormap
    plt.xlabel(class_names[train_labels[i]])
plt.show()

#序贯模型：单输入，单输出，层与层之间线性连接（不夸通道连接），函数模型：任意都行
#序贯模型的使用：
#1模型构建(model=Sequential())：两种方式，list传入或者add添加
#2模型编译(model.compile())：主要传入三个参数（optimizer,loss,metric）
#3模型训练（model.fit()）：epochs，batch，validation_split。
#4模型测试（model.evaluate()）：test数据集
#5模型预测（model.predict()）
model = keras.Sequential([  
    keras.layers.Flatten(input_shape=(28,28)), #第一层
    keras.layers.Dense(128,activation=tf.nn.relu),#第二层
    keras.layers.Dense(10,activation=tf.nn.softmax)#第三层
])
# 该网络中的第一层 tf.keras.layers.Flatten 
# 将图像格式从二维数组（28x28 像素）
# 转换成一维数组（28 * 28 = 784 像素）。
# 可以将该层视为图像中像素未堆叠的行，并排列这些行。
# 该层没有要学习的参数；它只改动数据的格式。
# 该网络包含两个 tf.keras.layers.Dense 层的序列。这些层是密集连接或全连接神经层。
# 第一个 Dense 层具有 128 个节点（或神经元）。
# 第二个（也是最后一个）层是具有 10 个节点的 softmax 层，
# 该层会返回一个具有 10 个概率得分的数组，这些得分的总和为 1。
# 每个节点包含一个得分，表示当前图像属于 10 个类别中某一个的概率。


#optimizer是优化器，是根据模型看到的数据和损失函数来更新模型的方式
#loss是损失函数，来权衡模型在训练时期的准确率
#metrics是一种指标，用于监控训练和测试步骤，比如下列中使用accuracy准确率来表示，
#在此时metrics表示图像被正确分类的比例
model.compile(optimizer=tf.train.AdamOptimizer(),
             loss='sparse_categorical_crossentropy',
             metrics=['accuracy'])
 
#训练模型步骤
#训练神经网络模型需要执行以下步骤：
#1.将训练数据馈送到模型中，在本示例中为 train_images 和 train_labels 数组。
#2.模型学习将图像与标签相关联。
#3.要求模型对测试集进行预测，在本示例中为 test_images 数组。验证预测结果是否与 test_labels 数组中的标签一致。
#model.fit方法作用是让模型和训练数据进行你和   
model.fit(train_images,train_labels,epochs=5)

#评估准确率
test_loss,test_acc=model.evaluate(test_images,test_labels)
print("Test accuracy:",test_acc)


#做出预测
predictions=model.predict(test_images)
predictions[0]
np.argmax(predictions[0])
#预测结果是一个具有 10 个数字的数组。
#这些数字说明模型对于图像对应于 10 种不同服饰中每一个服饰的“置信度”

#该预测绘制成图来查看全部 10 个通道
def plot_image(i, predictions_array, true_label, img):
  predictions_array, true_label, img = predictions_array[i], true_label[i], img[i]
  plt.grid(False)
  plt.xticks([])
  plt.yticks([])

  plt.imshow(img, cmap=plt.cm.binary)

  predicted_label = np.argmax(predictions_array)
  if predicted_label == true_label:
    color = 'blue'
  else:
    color = 'red'

  plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
                                100*np.max(predictions_array),
                                class_names[true_label]),
                                color=color)
plt.show()

def plot_value_array(i, predictions_array, true_label):
  predictions_array, true_label = predictions_array[i], true_label[i]
  plt.grid(False)
  plt.xticks([])
  plt.yticks([])
  thisplot = plt.bar(range(10), predictions_array, color="#777777")
  plt.ylim([0, 1])
  predicted_label = np.argmax(predictions_array)

  thisplot[predicted_label].set_color('red')
  thisplot[true_label].set_color('blue')
plt.show()
#第 0 张图像、预测和预测数组
i = 0
plt.figure(figsize=(6,3))
plt.subplot(1,2,1)
plot_image(i, predictions, test_labels, test_images)
plt.subplot(1,2,2)
plot_value_array(i, predictions,  test_labels)
plt.show()
#第 12 张图像、预测和预测数组
i = 12
plt.figure(figsize=(6,3))
plt.subplot(1,2,1)
plot_image(i, predictions, test_labels, test_images)
plt.subplot(1,2,2)
plot_value_array(i, predictions,  test_labels)
plt.show()

# 用它们的预测绘制几张图像。正确的预测标签为蓝色，错误的预测标签为红色。
# 数字表示预测标签的百分比（总计为 100）。
# 请注意，即使置信度非常高，也有可能预测错误。
# Plot the first X test images, their predicted label, and the true label
# Color correct predictions in blue, incorrect predictions in red
num_rows = 3
num_cols = 3
num_images = num_rows*num_cols
plt.figure(figsize=(2*2*num_cols, 2*num_rows))
for i in range(num_images):
  plt.subplot(num_rows, 2*num_cols, 2*i+1)
  plot_image(i, predictions, test_labels, test_images)
  plt.subplot(num_rows, 2*num_cols, 2*i+2)
  plot_value_array(i, predictions, test_labels)
plt.show()

# Grab an image from the test dataset
img=test_images[0]
print(img.shape)

# Add the image to a batch where it's the only member.
img = (np.expand_dims(img,0))

print(img.shape)

predictions_single=model.predict(img)
print(predictions_single)

plot_value_array(0, predictions_single, test_labels)
_ = plt.xticks(range(10), class_names, rotation=45)
plt.show()

print(np.argmax(predictions_single[0]))