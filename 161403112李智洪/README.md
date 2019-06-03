|  姓名  |   学号    |     班级     |
| :----: | :-------: | :----------: |
| 李智洪 | 161403112 | 16级硬件一班 |



# 实验题目

​	学习使用Tensorflow完成神经网络实验

# 实验相关

1. 数据集

    MNIST_data和.keras文件夹包含所用的数据集合，基本不可在线下载，所以下载到本地，ubuntu 18.04下可以在/home下手动创建一个.keras文件夹,然后在./keras下再创建一个datasets文件夹，将下载后的文件放入其中即可

# 实验结果

## lab1手写数字识别--cnn_mnist.py & Num.py

​	MNIST 数据集包含手写数字（0、1、2 等）的图像,用作计算机视觉机器学习程序的“Hello, World”入门数据集。

## lab2图像分类--basic_classification.py

### 数据集

训练一个对服饰（例如运动鞋和衬衫）图像进行分类的神经网络模型。数据集为Fashion MNIST ，使用其中 60000 张图像训练网络，并使用 10000 张图像评估经过学习的网络分类图像的准确率。

### 模型构建: 

序贯模型：单输入，单输出，层与层之间线性连接（不夸通道连接），函数模型：任意都行

序贯模型的使用：

1模型构建(model=Sequential())：两种方式，list传入或者add添加

2模型编译(model.compile())：主要传入三个参数（optimizer,loss,metric）

3模型训练（model.fit()）：epochs，batch，validation_split。

4模型测试（model.evaluate()）：test数据集

5模型预测（model.predict()）
### 训练模型步骤
训练神经网络模型需要执行以下步骤：
1.将训练数据馈送到模型中，在本示例中为 train_images 和 train_labels 数组。
2.模型学习将图像与标签相关联。
3.要求模型对测试集进行预测，在本示例中为 test_images 数组。验证预测结果是否与 test_labels 数组中的标签一致。


## lab3文本分类--text_classification.py

### 数据集
文本形式的影评分为“正面”或“负面”影评。这是一个二元分类（又称为两类分类）的示例。使用 [IMDB 数据集]，其中包含来自[互联网电影数据库]的 50000 条影评文本，+将这些影评拆分为训练集（25000 条影评）和测试集（25000 条影评）

### 网络构建：

​	第一层是 `Embedding` 层。该层会在整数编码的词汇表中查找每个字词-索引的嵌入向量。模型在接受训练时会学习这些向量。这些向量会向输出数组添加一个维度。生成的维度为：`(batch, sequence, embedding)`。

接下来，一个 `GlobalAveragePooling1D` 层通过对序列维度求平均值，针对每个样本返回一个长度固定的输出向量。这样，模型便能够以尽可能简单的方式处理各种长度的输入。

该长度固定的输出向量会传入一个全连接 (`Dense`) 层（包含 16 个隐藏单元）。

最后一层与单个输出节点密集连接。应用 `sigmoid` 激活函数后，结果是介于 0 到 1 之间的浮点值，表示概率或置信水平。

## lab4--预测模型--predict fuel efficiency.py

### 数据集

[Auto MPG]数据集

### 建立模型

将使用`Sequential`具有两个密集连接的隐藏层的模型，以及返回单个连续值的输出层。模型构建步骤包含在一个函数中`build_model`

## lab5--过拟合和欠拟合--overfitting and underfitting.py

在训练周期达到一定次数后，模型在验证数据上的准确率会达到峰值，然后便开始下降,即模型会过拟合训练数据。

与过拟合相对的是欠拟合。当测试数据仍存在改进空间时，便会发生欠拟合。出现这种情况的原因有很多：模型不够强大、过于正则化，或者根本没有训练足够长的时间。这意味着网络未学习训练数据中的相关模式。

如果训练时间过长，模型将开始过拟合，并从训练数据中学习无法泛化到测试数据的模式

为了防止发生过拟合，最好的解决方案是使用更多训练数据。用更多数据进行训练的模型自然能够更好地泛化，比如权重正则化和丢弃。

## lab6-保存和恢复模型--save and restore models.py

模型进度可在训练期间和之后保存。这意味着，可以从上次暂停的地方继续训练模型，避免训练时间过长。主要方法就是在训练期间或训练结束时自动保存检查点。无需重新训练该模型，或从上次暂停的地方继续训练，以防训练过程中断。[`tf.keras.callbacks.ModelCheckpoint`] 是执行此任务的回调。该回调需要几个参数来配置检查点。

文件结果保存在training_1、training_2和checkpoints文件夹和my_model.h5中，以及包含检查点的保存等



## lab7- 张量/GPU加速的使用/自建数据源--basic_Tensors.py &basic_gpu_acceleration.py

1. **张量**是一个多维数组。与NumPy `ndarray`对象类似，`Tensor`对象具有数据类型和形状。此外，Tensors可以驻留在加速器（如GPU）内存中。TensorFlow提供了丰富的操作库[tf.add]，[tf.matmul]，tf.linalg.inv等），它们使用和生成Tensors。

2. **TensorFlow张量和NumPy ndarrays之间的转换**非常简单，如：

- TensorFlow操作自动将NumPy ndarrays转换为Tensors。

- NumPy操作自动将Tensors转换为NumPy ndarrays。

   通过调用`.numpy()`它们的方法，可以将张量显式转换为NumPy ndarrays 

3. **通过使用GPU进行计算**，可以加速许多TensorFlow操作。在没有任何注释的情况下，TensorFlow会自动决定是使用GPU还是CPU进行操作（如果需要，还可以复制CPU和GPU内存之间的张量）。由操作产生的张量通常由执行操作的设备的存储器支持。

## lab8--优化模型方法

Automatic_differentiation.py--Automatic differentiation and gradient tape--计算梯度

Custom_training_basics.py--建立和培养一个简单的模型

Custom_layers.py--自定义图层

## lab9-自建模型完成预测--Custom_training_walkthrough.py

Custom_training_walkthrough.py--鸢尾花分类问题

## lab10- 尝试建立构建卷积神经网络(it doesn't work-ORZ)--cnn_mnist.py

卷积神经网络 (CNN) 是目前用于图像分类任务的先进模型架构。CNN 将一系列过滤器应用于图像的原始像素数据，以提取和学习更高级别的特征，然后模型可以使用这些特征进行分类。CNN 包含下列 3 个组成部分：

卷积层：将指定数量的卷积过滤器应用于图像。对于每个子区域，该层会执行一组数学运算，以在输出特征图中生成单个值。然后，卷积层通常会向输出应用 ReLU 激活函数，以便在模型中引入非线性规律。

池化层：对卷积层提取的图像数据进行下采样，以降低特征图的维度，从而缩短处理时间。常用的池化算法是最大池化，它会提取特征图的子区域（例如 2x2 像素区块），保留子区域的最大值，并舍弃其他所有值。

密集（全连接）层：对由卷积层提取并由池化层下采样的特征进行分类。密集层中的每个节点都连接到前一层中的所有节点。

通常，CNN 包括多个执行特征提取的卷积模块。每个模块都由一个卷积层后跟一个池化层组成。最后一个卷积模块后跟一个或多个执行分类的密集层。在 CNN 的最终密集层中，模型中的每个目标类别（模型会预测的所有可能类别）都对应一个节点，并应用 softmax 激活函数，该函数针对每个节点生成一个介于 0 到 1 之间的值（所有这些 softmax 值的总和等于 1）。我们可以将某张给定图像的 softmax 值解析为相对测量值，表示该图像属于每个目标类别的概率。

# 实验小结

学习了一下TensorFlow的使用，连续模型创建模型的方法。
整个学习流程基本如下：
探索数据格式-->清洗数据->划分数据集用于训练和预测->选择模型进行创建->模型编译(主要是设置优化器和损失函数)->训练模型(划分训练块)->测试模型(使用划分的test数据集用于测试)->预测模型
了解了一下卷积神经网络的层级结构
   •   数据输入层/ Input layer
　　•	卷积计算层/ CONV layer
　　•	ReLU激励层 / ReLU layer
　　•	池化层 / Pooling layer
　　•	全连接层 / FC layer

其他一些注意点：

NumPy阵列和TensorFlow张量之间最明显的区别是：

1. 张量可以由加速器内存（如GPU，TPU）支持。
2. 张量是不可改变的。

Conversion between TensorFlow Tensors and NumPy ndarrays is quite simple as:

- TensorFlow operations automatically convert NumPy ndarrays to Tensors.
- NumPy operations automatically convert Tensors to NumPy ndarrays.

通过调用`.numpy()`它们的方法，可以将张量显式转换为NumPy ndarrays 。这些转换通常很便宜，因为如果可能，数组和Tensor共享底层内存表示。但是，共享底层表示并不总是可行的，因为Tensor可以托管在GPU内存中，而NumPy阵列总是由主机内存支持，因此转换将涉及从GPU到主机内存的复制。

# 实验中遇到的一些问题

在solution of problems.md中