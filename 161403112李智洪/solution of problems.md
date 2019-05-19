# 当遇到ValueError: Object arrays cannot be loaded when allow_pickle=False

这个是到导入IMDB数据集时出现的错误，解决如下

```shell
pip3 uninstall numpy
pip3 install numpy==1.16.2
```

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