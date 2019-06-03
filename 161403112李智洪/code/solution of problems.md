# 当遇到ValueError: Object arrays cannot be loaded when allow_pickle=False

这个是到导入IMDB数据集时出现的错误，解决如下

```shell
pip3 uninstall numpy
pip3 install numpy==1.16.2
```

# 当训练时间过长时

模型进度可在训练期间和之后保存。这可以从上次暂停的地方继续训练模型，避免训练时间过长。此外，可以保存意味着可以分享模型，而他人可以对结果进行再创作。

# 快速开始序贯（Sequential）模型

序贯模型是多个网络层的线性堆叠，也就是“一条路走到黑”。

可以通过向`Sequential`模型传递一个layer的list来构造该模型：

```
from keras.models import Sequential
from keras.layers import Dense, Activation

model = Sequential([
Dense(32, units=784),
Activation('relu'),
Dense(10),
Activation('softmax'),
])
```

也可以通过`.add()`方法一个个的将layer加入模型中：

```
model = Sequential()
model.add(Dense(32, input_shape=(784,)))
model.add(Activation('relu'))
```

## 指定输入数据的shape

模型需要知道输入数据的shape，因此，`Sequential`的第一层需要接受一个关于输入数据shape的参数，后面的各个层则可以自动的推导出中间数据的shape，因此不需要为每个层都指定这个参数。有几种方法来为第一层指定输入数据的shape

- 传递一个`input_shape`的关键字参数给第一层，`input_shape`是一个tuple类型的数据，其中也可以填入`None`，如果填入`None`则表示此位置可能是任何正整数。数据的batch大小不应包含在其中。
- 有些2D层，如`Dense`，支持通过指定其输入维度`input_dim`来隐含的指定输入数据shape,是一个Int类型的数据。一些3D的时域层支持通过参数`input_dim`和`input_length`来指定输入shape。
- 如果你需要为输入指定一个固定大小的batch_size（常用于stateful RNN网络），可以传递`batch_size`参数到一个层中，例如你想指定输入张量的batch大小是32，数据shape是（6，8），则你需要传递`batch_size=32`和`input_shape=(6,8)`。

```
model = Sequential()
model.add(Dense(32, input_dim=784))
model = Sequential()
model.add(Dense(32, input_shape=(784,)))
```

# 关于Keras的“层”（Layer）

所有的Keras层对象都有如下方法：

- `layer.get_weights()`：返回层的权重（numpy array）
- `layer.set_weights(weights)`：从numpy array中将权重加载到该层中，要求numpy array的形状与* `layer.get_weights()`的形状相同
- `layer.get_config()`：返回当前层配置信息的字典，层也可以借由配置信息重构:

```
layer = Dense(32)
config = layer.get_config()
reconstructed_layer = Dense.from_config(config)
```

或者：

```
from keras import layers

config = layer.get_config()
layer = layers.deserialize({'class_name': layer.__class__.__name__,
                            'config': config})
```

如果层仅有一个计算节点（即该层不是共享层），则可以通过下列方法获得输入张量、输出张量、输入数据的形状和输出数据的形状：

- `layer.input`
- `layer.output`
- `layer.input_shape`
- `layer.output_shape`

如果该层有多个计算节点（参考[层计算节点和共享层](https://keras-cn.readthedocs.io/en/latest/getting_started/functional_API/#node)）。可以使用下面的方法

- `layer.get_input_at(node_index)`
- `layer.get_output_at(node_index)`
- `layer.get_input_shape_at(node_index)`
- `layer.get_output_shape_at(node_index)`

# 嵌入层 Embedding

## Embedding层

```
keras.layers.embeddings.Embedding(input_dim, output_dim, embeddings_initializer='uniform', embeddings_regularizer=None, activity_regularizer=None, embeddings_constraint=None, mask_zero=False, input_length=None)
```

嵌入层将正整数（下标）转换为具有固定大小的向量，如[[4],[20]]->[[0.25,0.1],[0.6,-0.2]]

Embedding层只能作为模型的第一层

### 参数

- input_dim：大或等于0的整数，字典长度，即输入数据最大下标+1
- output_dim：大于0的整数，代表全连接嵌入的维度
- embeddings_initializer: 嵌入矩阵的初始化方法，为预定义初始化方法名的字符串，或用于初始化权重的初始化器。参考[initializers](https://keras-cn.readthedocs.io/en/latest/other/initializations)
- embeddings_regularizer: 嵌入矩阵的正则项，为[Regularizer](https://keras-cn.readthedocs.io/en/latest/other/regularizers)对象
- embeddings_constraint: 嵌入矩阵的约束项，为[Constraints](https://keras-cn.readthedocs.io/en/latest/other/constraints)对象
- mask_zero：布尔值，确定是否将输入中的‘0’看作是应该被忽略的‘填充’（padding）值，该参数在使用[递归层](https://keras-cn.readthedocs.io/en/latest/layers/recurrent_layer)处理变长输入时有用。设置为`True`的话，模型中后续的层必须都支持masking，否则会抛出异常。如果该值为True，则下标0在字典中不可用，input_dim应设置为|vocabulary| + 1。
- input_length：当输入序列的长度固定时，该值为其长度。如果要在该层后接`Flatten`层，然后接`Dense`层，则必须指定该参数，否则`Dense`层的输出维度无法自动推断。

### 输入shape

形如（samples，sequence_length）的2D张量

### 输出shape

形如(samples, sequence_length, output_dim)的3D张量

### 例子

```
model = Sequential()
model.add(Embedding(1000, 64, input_length=10))
# the model will take as input an integer matrix of size (batch, input_length).
# the largest integer (i.e. word index) in the input should be no larger than 999 (vocabulary size).
# now model.output_shape == (None, 10, 64), where None is the batch dimension.

input_array = np.random.randint(1000, size=(32, 10))

model.compile('rmsprop', 'mse')
output_array = model.predict(input_array)
assert output_array.shape == (32, 10, 64)
```

# 添加丢弃层

丢弃是由 Hinton 及其在多伦多大学的学生开发的，是最有效且最常用的神经网络正则化技术之一。丢弃（应用于某个层）是指在训练期间随机“丢弃”（即设置为 0）该层的多个输出特征。假设某个指定的层通常会在训练期间针对给定的输入样本返回一个向量 [0.2, 0.5, 1.3, 0.8, 1.1]；在应用丢弃后，此向量将随机分布几个 0 条目，例如 [0, 0.5, 1.3, 0, 1.1]。“丢弃率”指变为 0 的特征所占的比例，通常设置在 0.2 和 0.5 之间。在测试时，网络不会丢弃任何单元，而是将层的输出值按等同于丢弃率的比例进行缩减，以便平衡以下事实：测试时的活跃单元数大于训练时的活跃单元数。

在 tf.keras 中，您可以通过丢弃层将丢弃引入网络中，以便事先将其应用于层的输出。

# 下面总结一下防止神经网络出现过拟合的最常见方法：

- 获取更多训练数据。
- 降低网络容量。
- 添加权重正则化。
- 添加丢弃层。

还有两个重要的方法在本指南中没有介绍：数据增强和批次归一化。

# 模拟过拟合和欠拟合实验结果

```shell
Layer (type)                 Output Shape              Param #   
=================================================================
dense (Dense)                (None, 16)                160016    
_________________________________________________________________
dense_1 (Dense)              (None, 16)                272       
_________________________________________________________________
dense_2 (Dense)              (None, 1)                 17        
=================================================================
Total params: 160,305
Trainable params: 160,305
Non-trainable params: 0
_________________________________________________________________
Train on 25000 samples, validate on 25000 samples
WARNING:tensorflow:From /home/lzh/.local/lib/python3.6/site-packages/tensorflow/python/ops/math_ops.py:3066: to_int32 (from tensorflow.python.ops.math_ops) is deprecated and will be removed in a future version.
Instructions for updating:
Use tf.cast instead.
2019-05-26 22:19:13.613679: I tensorflow/core/platform/cpu_feature_guard.cc:141] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
2019-05-26 22:19:13.897460: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2793605000 Hz
2019-05-26 22:19:13.932827: I tensorflow/compiler/xla/service/service.cc:150] XLA service 0x16cf430 executing computations on platform Host. Devices:
2019-05-26 22:19:13.932867: I tensorflow/compiler/xla/service/service.cc:158]   StreamExecutor device (0): <undefined>, <undefined>
Epoch 1/20
 - 5s - loss: 0.4955 - acc: 0.8078 - binary_crossentropy: 0.4955 - val_loss: 0.3378 - val_acc: 0.8785 - val_binary_crossentropy: 0.3378
Epoch 2/20
 - 4s - loss: 0.2498 - acc: 0.9124 - binary_crossentropy: 0.2498 - val_loss: 0.2844 - val_acc: 0.8890 - val_binary_crossentropy: 0.2844
Epoch 3/20
 - 3s - loss: 0.1826 - acc: 0.9359 - binary_crossentropy: 0.1826 - val_loss: 0.2909 - val_acc: 0.8852 - val_binary_crossentropy: 0.2909
Epoch 4/20
 - 3s - loss: 0.1486 - acc: 0.9498 - binary_crossentropy: 0.1486 - val_loss: 0.3193 - val_acc: 0.8756 - val_binary_crossentropy: 0.3193
Epoch 5/20
 - 4s - loss: 0.1233 - acc: 0.9593 - binary_crossentropy: 0.1233 - val_loss: 0.3329 - val_acc: 0.8743 - val_binary_crossentropy: 0.3329
Epoch 6/20
 - 4s - loss: 0.1033 - acc: 0.9681 - binary_crossentropy: 0.1033 - val_loss: 0.3608 - val_acc: 0.8726 - val_binary_crossentropy: 0.3608
Epoch 7/20
 - 4s - loss: 0.0874 - acc: 0.9738 - binary_crossentropy: 0.0874 - val_loss: 0.3929 - val_acc: 0.8681 - val_binary_crossentropy: 0.3929
Epoch 8/20
 - 4s - loss: 0.0754 - acc: 0.9789 - binary_crossentropy: 0.0754 - val_loss: 0.4274 - val_acc: 0.8642 - val_binary_crossentropy: 0.4274
Epoch 9/20
 - 4s - loss: 0.0622 - acc: 0.9841 - binary_crossentropy: 0.0622 - val_loss: 0.4628 - val_acc: 0.8624 - val_binary_crossentropy: 0.4628
Epoch 10/20
 - 4s - loss: 0.0536 - acc: 0.9871 - binary_crossentropy: 0.0536 - val_loss: 0.5016 - val_acc: 0.8587 - val_binary_crossentropy: 0.5016
Epoch 11/20
 - 4s - loss: 0.0428 - acc: 0.9916 - binary_crossentropy: 0.0428 - val_loss: 0.5393 - val_acc: 0.8571 - val_binary_crossentropy: 0.5393
Epoch 12/20
 - 4s - loss: 0.0338 - acc: 0.9940 - binary_crossentropy: 0.0338 - val_loss: 0.5780 - val_acc: 0.8545 - val_binary_crossentropy: 0.5780
Epoch 13/20
 - 4s - loss: 0.0268 - acc: 0.9963 - binary_crossentropy: 0.0268 - val_loss: 0.6175 - val_acc: 0.8530 - val_binary_crossentropy: 0.6175
Epoch 14/20
 - 4s - loss: 0.0205 - acc: 0.9978 - binary_crossentropy: 0.0205 - val_loss: 0.6570 - val_acc: 0.8518 - val_binary_crossentropy: 0.6570
Epoch 15/20
 - 4s - loss: 0.0162 - acc: 0.9987 - binary_crossentropy: 0.0162 - val_loss: 0.6825 - val_acc: 0.8524 - val_binary_crossentropy: 0.6825
Epoch 16/20
 - 4s - loss: 0.0127 - acc: 0.9993 - binary_crossentropy: 0.0127 - val_loss: 0.7166 - val_acc: 0.8512 - val_binary_crossentropy: 0.7166
Epoch 17/20
 - 4s - loss: 0.0104 - acc: 0.9995 - binary_crossentropy: 0.0104 - val_loss: 0.7422 - val_acc: 0.8508 - val_binary_crossentropy: 0.7422
Epoch 18/20
 - 3s - loss: 0.0083 - acc: 0.9997 - binary_crossentropy: 0.0083 - val_loss: 0.7735 - val_acc: 0.8509 - val_binary_crossentropy: 0.7735
Epoch 19/20
 - 4s - loss: 0.0067 - acc: 0.9998 - binary_crossentropy: 0.0067 - val_loss: 0.7985 - val_acc: 0.8505 - val_binary_crossentropy: 0.7985
Epoch 20/20
 - 4s - loss: 0.0055 - acc: 0.9998 - binary_crossentropy: 0.0055 - val_loss: 0.8198 - val_acc: 0.8498 - val_binary_crossentropy: 0.8198
_________________________________________________________________
Layer (type)                 Output Shape              Param #   
=================================================================
dense_3 (Dense)              (None, 4)                 40004     
_________________________________________________________________
dense_4 (Dense)              (None, 4)                 20        
_________________________________________________________________
dense_5 (Dense)              (None, 1)                 5         
=================================================================
Total params: 40,029
Trainable params: 40,029
Non-trainable params: 0
_________________________________________________________________
Train on 25000 samples, validate on 25000 samples
Epoch 1/20
 - 3s - loss: 0.6258 - acc: 0.6318 - binary_crossentropy: 0.6258 - val_loss: 0.5739 - val_acc: 0.7664 - val_binary_crossentropy: 0.5739
Epoch 2/20
 - 3s - loss: 0.5212 - acc: 0.8026 - binary_crossentropy: 0.5212 - val_loss: 0.5128 - val_acc: 0.8261 - val_binary_crossentropy: 0.5128
Epoch 3/20
 - 3s - loss: 0.4646 - acc: 0.8678 - binary_crossentropy: 0.4646 - val_loss: 0.4802 - val_acc: 0.8628 - val_binary_crossentropy: 0.4802
Epoch 4/20
 - 3s - loss: 0.4258 - acc: 0.8994 - binary_crossentropy: 0.4258 - val_loss: 0.4588 - val_acc: 0.8725 - val_binary_crossentropy: 0.4588
Epoch 5/20
 - 3s - loss: 0.3949 - acc: 0.9208 - binary_crossentropy: 0.3949 - val_loss: 0.4452 - val_acc: 0.8741 - val_binary_crossentropy: 0.4452
Epoch 6/20
 - 3s - loss: 0.3694 - acc: 0.9348 - binary_crossentropy: 0.3694 - val_loss: 0.4397 - val_acc: 0.8703 - val_binary_crossentropy: 0.4397
Epoch 7/20
 - 3s - loss: 0.3466 - acc: 0.9458 - binary_crossentropy: 0.3466 - val_loss: 0.4332 - val_acc: 0.8742 - val_binary_crossentropy: 0.4332
Epoch 8/20
 - 3s - loss: 0.3268 - acc: 0.9533 - binary_crossentropy: 0.3268 - val_loss: 0.4273 - val_acc: 0.8766 - val_binary_crossentropy: 0.4273
Epoch 9/20
 - 3s - loss: 0.3089 - acc: 0.9601 - binary_crossentropy: 0.3089 - val_loss: 0.4195 - val_acc: 0.8784 - val_binary_crossentropy: 0.4195
Epoch 10/20
 - 3s - loss: 0.2929 - acc: 0.9660 - binary_crossentropy: 0.2929 - val_loss: 0.4311 - val_acc: 0.8736 - val_binary_crossentropy: 0.4311
Epoch 11/20
 - 3s - loss: 0.2776 - acc: 0.9698 - binary_crossentropy: 0.2776 - val_loss: 0.4272 - val_acc: 0.8723 - val_binary_crossentropy: 0.4272
Epoch 12/20
 - 3s - loss: 0.2640 - acc: 0.9737 - binary_crossentropy: 0.2640 - val_loss: 0.4295 - val_acc: 0.8717 - val_binary_crossentropy: 0.4295
Epoch 13/20
 - 3s - loss: 0.2512 - acc: 0.9774 - binary_crossentropy: 0.2512 - val_loss: 0.4261 - val_acc: 0.8717 - val_binary_crossentropy: 0.4261
Epoch 14/20
 - 3s - loss: 0.2399 - acc: 0.9796 - binary_crossentropy: 0.2399 - val_loss: 0.4374 - val_acc: 0.8699 - val_binary_crossentropy: 0.4374
Epoch 15/20
 - 3s - loss: 0.2286 - acc: 0.9822 - binary_crossentropy: 0.2286 - val_loss: 0.4422 - val_acc: 0.8682 - val_binary_crossentropy: 0.4422
Epoch 16/20
 - 3s - loss: 0.2186 - acc: 0.9833 - binary_crossentropy: 0.2186 - val_loss: 0.4538 - val_acc: 0.8676 - val_binary_crossentropy: 0.4538
Epoch 17/20
 - 3s - loss: 0.2094 - acc: 0.9848 - binary_crossentropy: 0.2094 - val_loss: 0.4540 - val_acc: 0.8670 - val_binary_crossentropy: 0.4540
Epoch 18/20
 - 3s - loss: 0.2006 - acc: 0.9861 - binary_crossentropy: 0.2006 - val_loss: 0.4571 - val_acc: 0.8663 - val_binary_crossentropy: 0.4571
Epoch 19/20
 - 3s - loss: 0.1927 - acc: 0.9872 - binary_crossentropy: 0.1927 - val_loss: 0.4688 - val_acc: 0.8654 - val_binary_crossentropy: 0.4688
Epoch 20/20
 - 3s - loss: 0.1852 - acc: 0.9878 - binary_crossentropy: 0.1852 - val_loss: 0.4693 - val_acc: 0.8659 - val_binary_crossentropy: 0.4693
_________________________________________________________________
Layer (type)                 Output Shape              Param #   
=================================================================
dense_6 (Dense)              (None, 512)               5120512   
_________________________________________________________________
dense_7 (Dense)              (None, 512)               262656    
_________________________________________________________________
dense_8 (Dense)              (None, 1)                 513       
=================================================================
Total params: 5,383,681
Trainable params: 5,383,681
Non-trainable params: 0
_________________________________________________________________
Train on 25000 samples, validate on 25000 samples
Epoch 1/20
 - 15s - loss: 0.3403 - acc: 0.8572 - binary_crossentropy: 0.3403 - val_loss: 0.2989 - val_acc: 0.8775 - val_binary_crossentropy: 0.2989
Epoch 2/20
 - 15s - loss: 0.1450 - acc: 0.9475 - binary_crossentropy: 0.1450 - val_loss: 0.3335 - val_acc: 0.8730 - val_binary_crossentropy: 0.3335
Epoch 3/20
 - 16s - loss: 0.0496 - acc: 0.9855 - binary_crossentropy: 0.0496 - val_loss: 0.4527 - val_acc: 0.8688 - val_binary_crossentropy: 0.4527
Epoch 4/20
 - 15s - loss: 0.0090 - acc: 0.9984 - binary_crossentropy: 0.0090 - val_loss: 0.6223 - val_acc: 0.8605 - val_binary_crossentropy: 0.6223
Epoch 5/20
 - 15s - loss: 0.0015 - acc: 1.0000 - binary_crossentropy: 0.0015 - val_loss: 0.6916 - val_acc: 0.8706 - val_binary_crossentropy: 0.6916
Epoch 6/20
 - 15s - loss: 2.5907e-04 - acc: 1.0000 - binary_crossentropy: 2.5907e-04 - val_loss: 0.7364 - val_acc: 0.8696 - val_binary_crossentropy: 0.7364
Epoch 7/20
 - 14s - loss: 1.3373e-04 - acc: 1.0000 - binary_crossentropy: 1.3373e-04 - val_loss: 0.7631 - val_acc: 0.8701 - val_binary_crossentropy: 0.7631
Epoch 8/20
 - 15s - loss: 9.3521e-05 - acc: 1.0000 - binary_crossentropy: 9.3521e-05 - val_loss: 0.7839 - val_acc: 0.8700 - val_binary_crossentropy: 0.7839
Epoch 9/20
 - 15s - loss: 7.0843e-05 - acc: 1.0000 - binary_crossentropy: 7.0843e-05 - val_loss: 0.8006 - val_acc: 0.8702 - val_binary_crossentropy: 0.8006
Epoch 10/20
 - 15s - loss: 5.5931e-05 - acc: 1.0000 - binary_crossentropy: 5.5931e-05 - val_loss: 0.8151 - val_acc: 0.8704 - val_binary_crossentropy: 0.8151
Epoch 11/20
 - 15s - loss: 4.5078e-05 - acc: 1.0000 - binary_crossentropy: 4.5078e-05 - val_loss: 0.8288 - val_acc: 0.8702 - val_binary_crossentropy: 0.8288
Epoch 12/20
 - 15s - loss: 3.7212e-05 - acc: 1.0000 - binary_crossentropy: 3.7212e-05 - val_loss: 0.8403 - val_acc: 0.8703 - val_binary_crossentropy: 0.8403
Epoch 13/20
 - 15s - loss: 3.0959e-05 - acc: 1.0000 - binary_crossentropy: 3.0959e-05 - val_loss: 0.8509 - val_acc: 0.8705 - val_binary_crossentropy: 0.8509
Epoch 14/20
 - 15s - loss: 2.6152e-05 - acc: 1.0000 - binary_crossentropy: 2.6152e-05 - val_loss: 0.8620 - val_acc: 0.8704 - val_binary_crossentropy: 0.8620
Epoch 15/20
 - 15s - loss: 2.2266e-05 - acc: 1.0000 - binary_crossentropy: 2.2266e-05 - val_loss: 0.8716 - val_acc: 0.8705 - val_binary_crossentropy: 0.8716
Epoch 16/20
 - 14s - loss: 1.9187e-05 - acc: 1.0000 - binary_crossentropy: 1.9187e-05 - val_loss: 0.8811 - val_acc: 0.8704 - val_binary_crossentropy: 0.8811
Epoch 17/20
 - 15s - loss: 1.6585e-05 - acc: 1.0000 - binary_crossentropy: 1.6585e-05 - val_loss: 0.8898 - val_acc: 0.8704 - val_binary_crossentropy: 0.8898
Epoch 18/20
 - 15s - loss: 1.4452e-05 - acc: 1.0000 - binary_crossentropy: 1.4452e-05 - val_loss: 0.8983 - val_acc: 0.8703 - val_binary_crossentropy: 0.8983
Epoch 19/20
 - 15s - loss: 1.2672e-05 - acc: 1.0000 - binary_crossentropy: 1.2672e-05 - val_loss: 0.9058 - val_acc: 0.8706 - val_binary_crossentropy: 0.9058
Epoch 20/20
 - 15s - loss: 1.1178e-05 - acc: 1.0000 - binary_crossentropy: 1.1178e-05 - val_loss: 0.9135 - val_acc: 0.8703 - val_binary_crossentropy: 0.9135
Train on 25000 samples, validate on 25000 samples
Epoch 1/20
 - 4s - loss: 0.5628 - acc: 0.7977 - binary_crossentropy: 0.5259 - val_loss: 0.4093 - val_acc: 0.8712 - val_binary_crossentropy: 0.3706
Epoch 2/20
 - 4s - loss: 0.3258 - acc: 0.9019 - binary_crossentropy: 0.2807 - val_loss: 0.3399 - val_acc: 0.8875 - val_binary_crossentropy: 0.2901
Epoch 3/20
 - 3s - loss: 0.2661 - acc: 0.9244 - binary_crossentropy: 0.2130 - val_loss: 0.3380 - val_acc: 0.8862 - val_binary_crossentropy: 0.2828
Epoch 4/20
 - 4s - loss: 0.2417 - acc: 0.9355 - binary_crossentropy: 0.1846 - val_loss: 0.3484 - val_acc: 0.8827 - val_binary_crossentropy: 0.2899
Epoch 5/20
 - 4s - loss: 0.2256 - acc: 0.9441 - binary_crossentropy: 0.1660 - val_loss: 0.3592 - val_acc: 0.8792 - val_binary_crossentropy: 0.2987
Epoch 6/20
 - 3s - loss: 0.2136 - acc: 0.9489 - binary_crossentropy: 0.1520 - val_loss: 0.3688 - val_acc: 0.8777 - val_binary_crossentropy: 0.3068
Epoch 7/20
 - 3s - loss: 0.2055 - acc: 0.9521 - binary_crossentropy: 0.1427 - val_loss: 0.3886 - val_acc: 0.8733 - val_binary_crossentropy: 0.3253
Epoch 8/20
 - 3s - loss: 0.1982 - acc: 0.9548 - binary_crossentropy: 0.1342 - val_loss: 0.3948 - val_acc: 0.8735 - val_binary_crossentropy: 0.3306
Epoch 9/20
 - 4s - loss: 0.1919 - acc: 0.9568 - binary_crossentropy: 0.1270 - val_loss: 0.4101 - val_acc: 0.8695 - val_binary_crossentropy: 0.3448
Epoch 10/20
 - 4s - loss: 0.1872 - acc: 0.9590 - binary_crossentropy: 0.1216 - val_loss: 0.4211 - val_acc: 0.8694 - val_binary_crossentropy: 0.3550
Epoch 11/20
 - 3s - loss: 0.1822 - acc: 0.9615 - binary_crossentropy: 0.1156 - val_loss: 0.4313 - val_acc: 0.8680 - val_binary_crossentropy: 0.3642
Epoch 12/20
 - 3s - loss: 0.1785 - acc: 0.9618 - binary_crossentropy: 0.1111 - val_loss: 0.4446 - val_acc: 0.8645 - val_binary_crossentropy: 0.3770
Epoch 13/20
 - 3s - loss: 0.1736 - acc: 0.9647 - binary_crossentropy: 0.1056 - val_loss: 0.4567 - val_acc: 0.8641 - val_binary_crossentropy: 0.3885
Epoch 14/20
 - 3s - loss: 0.1693 - acc: 0.9657 - binary_crossentropy: 0.1008 - val_loss: 0.4682 - val_acc: 0.8613 - val_binary_crossentropy: 0.3996
Epoch 15/20
 - 3s - loss: 0.1667 - acc: 0.9672 - binary_crossentropy: 0.0980 - val_loss: 0.4852 - val_acc: 0.8611 - val_binary_crossentropy: 0.4163
Epoch 16/20
 - 3s - loss: 0.1643 - acc: 0.9689 - binary_crossentropy: 0.0947 - val_loss: 0.4952 - val_acc: 0.8586 - val_binary_crossentropy: 0.4255
Epoch 17/20
 - 3s - loss: 0.1647 - acc: 0.9670 - binary_crossentropy: 0.0948 - val_loss: 0.5017 - val_acc: 0.8594 - val_binary_crossentropy: 0.4314
Epoch 18/20
 - 3s - loss: 0.1632 - acc: 0.9677 - binary_crossentropy: 0.0922 - val_loss: 0.5344 - val_acc: 0.8538 - val_binary_crossentropy: 0.4631
Epoch 19/20
 - 3s - loss: 0.1609 - acc: 0.9683 - binary_crossentropy: 0.0895 - val_loss: 0.5238 - val_acc: 0.8568 - val_binary_crossentropy: 0.4523
Epoch 20/20
 - 3s - loss: 0.1532 - acc: 0.9735 - binary_crossentropy: 0.0818 - val_loss: 0.5345 - val_acc: 0.8552 - val_binary_crossentropy: 0.4633
WARNING:tensorflow:From /home/lzh/.local/lib/python3.6/site-packages/tensorflow/python/keras/layers/core.py:143: calling dropout (from tensorflow.python.ops.nn_ops) with keep_prob is deprecated and will be removed in a future version.
Instructions for updating:
Please use `rate` instead of `keep_prob`. Rate should be set to `rate = 1 - keep_prob`.
Train on 25000 samples, validate on 25000 samples
Epoch 1/20
 - 4s - loss: 0.5968 - acc: 0.6832 - binary_crossentropy: 0.5968 - val_loss: 0.4344 - val_acc: 0.8611 - val_binary_crossentropy: 0.4344
Epoch 2/20
 - 3s - loss: 0.4141 - acc: 0.8378 - binary_crossentropy: 0.4141 - val_loss: 0.3221 - val_acc: 0.8822 - val_binary_crossentropy: 0.3221
Epoch 3/20
 - 4s - loss: 0.3199 - acc: 0.8814 - binary_crossentropy: 0.3199 - val_loss: 0.2914 - val_acc: 0.8805 - val_binary_crossentropy: 0.2914
Epoch 4/20
 - 4s - loss: 0.2717 - acc: 0.9062 - binary_crossentropy: 0.2717 - val_loss: 0.2798 - val_acc: 0.8839 - val_binary_crossentropy: 0.2798
Epoch 5/20
 - 4s - loss: 0.2338 - acc: 0.9199 - binary_crossentropy: 0.2338 - val_loss: 0.2825 - val_acc: 0.8853 - val_binary_crossentropy: 0.2825
Epoch 6/20
 - 3s - loss: 0.2024 - acc: 0.9326 - binary_crossentropy: 0.2024 - val_loss: 0.3060 - val_acc: 0.8792 - val_binary_crossentropy: 0.3060
Epoch 7/20
 - 4s - loss: 0.1804 - acc: 0.9416 - binary_crossentropy: 0.1804 - val_loss: 0.3110 - val_acc: 0.8842 - val_binary_crossentropy: 0.3110
Epoch 8/20
 - 4s - loss: 0.1592 - acc: 0.9483 - binary_crossentropy: 0.1592 - val_loss: 0.3181 - val_acc: 0.8827 - val_binary_crossentropy: 0.3181
Epoch 9/20
 - 4s - loss: 0.1453 - acc: 0.9527 - binary_crossentropy: 0.1453 - val_loss: 0.3302 - val_acc: 0.8812 - val_binary_crossentropy: 0.3302
Epoch 10/20
 - 4s - loss: 0.1280 - acc: 0.9572 - binary_crossentropy: 0.1280 - val_loss: 0.3636 - val_acc: 0.8794 - val_binary_crossentropy: 0.3636
Epoch 11/20
 - 4s - loss: 0.1140 - acc: 0.9616 - binary_crossentropy: 0.1140 - val_loss: 0.3877 - val_acc: 0.8776 - val_binary_crossentropy: 0.3877
Epoch 12/20
 - 4s - loss: 0.1067 - acc: 0.9640 - binary_crossentropy: 0.1067 - val_loss: 0.4106 - val_acc: 0.8768 - val_binary_crossentropy: 0.4106
Epoch 13/20
 - 3s - loss: 0.0980 - acc: 0.9645 - binary_crossentropy: 0.0980 - val_loss: 0.4360 - val_acc: 0.8731 - val_binary_crossentropy: 0.4360
Epoch 14/20
 - 4s - loss: 0.0891 - acc: 0.9694 - binary_crossentropy: 0.0891 - val_loss: 0.4355 - val_acc: 0.8752 - val_binary_crossentropy: 0.4355
Epoch 15/20
 - 4s - loss: 0.0812 - acc: 0.9717 - binary_crossentropy: 0.0812 - val_loss: 0.4726 - val_acc: 0.8745 - val_binary_crossentropy: 0.4726
Epoch 16/20
 - 4s - loss: 0.0771 - acc: 0.9733 - binary_crossentropy: 0.0771 - val_loss: 0.5096 - val_acc: 0.8748 - val_binary_crossentropy: 0.5096
Epoch 17/20
 - 4s - loss: 0.0746 - acc: 0.9720 - binary_crossentropy: 0.0746 - val_loss: 0.5187 - val_acc: 0.8746 - val_binary_crossentropy: 0.5187
Epoch 18/20
 - 4s - loss: 0.0727 - acc: 0.9730 - binary_crossentropy: 0.0727 - val_loss: 0.5314 - val_acc: 0.8729 - val_binary_crossentropy: 0.5314
Epoch 19/20
 - 4s - loss: 0.0670 - acc: 0.9748 - binary_crossentropy: 0.0670 - val_loss: 0.5434 - val_acc: 0.8714 - val_binary_crossentropy: 0.5434
Epoch 20/20
 - 4s - loss: 0.0638 - acc: 0.9756 - binary_crossentropy: 0.0638 - val_loss: 0.6037 - val_acc: 0.8739 - val_binary_crossentropy: 0.6037
[1]    4731 terminated  env PYTHONIOENCODING=UTF-8 PYTHONUNBUFFERED=1 /usr/bin/python3  --default    

```

# 保存整个模型

整个模型可以保存到一个文件中，其中包含权重值、模型配置乃至优化器配置。这样，您就可以为模型设置检查点，并稍后从完全相同的状态继续训练，而无需访问原始代码。

在 Keras 中保存完全可正常使用的模型非常有用，您可以在 [TensorFlow.js](https://js.tensorflow.org/tutorials/import-keras.html) 中加载它们，然后在网络浏览器中训练和运行它们。

Keras 使用 [HDF5](https://en.wikipedia.org/wiki/Hierarchical_Data_Format) 标准提供基本的保存格式。对于我们来说，可将保存的模型视为一个二进制 blob。

此技巧可保存以下所有内容：

- 权重值
- 模型配置（架构）
- 优化器配置

Keras 通过检查架构来保存模型。目前，它无法保存 TensorFlow 优化器（来自 [`tf.train`](https://www.tensorflow.org/api_docs/python/tf/train)）。使用此类优化器时，您需要在加载模型后对其进行重新编译，使优化器的状态变松散。