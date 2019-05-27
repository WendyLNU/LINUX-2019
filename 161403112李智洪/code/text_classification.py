import tensorflow as tf
from tensorflow import keras

import numpy as np
import matplotlib.pyplot as plt

print(tf.__version__)

#imdb数据集包含5w条记录，其中训练集和测试集各占一半
#step1-下载 IMDB 数据集
#基本不可在线下载，所以下载到本地
#ubuntu 18.04下可以在/home下手动创建一个.keras文件夹
#然后在./keras下再创建一个datasets文件夹，将下载后的文件放入其中即可
imdb = keras.datasets.imdb

(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000)
#参数 num_words=10000 会保留训练数据中出现频次在前 10000 位的字词。为确保数据规模处于可管理的水平，罕见字词将被舍弃。

#step2-Explore the data
#这一步主要是理解一下数据的格式,而此时下载玩的数据已经经过了数据预处理
#每个样本中包含一个整数数组，即字词，换句话说，每个整数都表示字典中一个特定的字词
#每个样本中的标签为0/1,0表示负面影评，1表示正面影评

#查看数据规模
print("Trainning entries: {},labels: {}".format(len(train_data),len(train_labels)))

#查看第一个影评
print(train_data[0])

#查看第一个影评和第二个影评的长度
print("({},{})".format(len(train_data[0]),len(train_data[1])))

#step3-Convert the integers back to words
#创建一个整数到字符串的映射对象字典

word_index=imdb.get_word_index()

word_index={k:(v+3) for k,v in word_index.items()}
word_index["<PAD>"]=0
word_index["<START>"]=1
word_index["UNK"]=2 #unknown
word_index["UNUSED"]=3

reverse_word_index=dict([(value,key) for (key,value) in word_index.items()])
def decode_review(text):
    return ' '.join([reverse_word_index.get(i,'?')for i in text])


#使用edcoe_review显示第一条影评的内容
print(decode_review(train_data[0]))

#step4-prepare the data
#影评先转换为张量，然后送入神经网络中。
#做法：填充数据，使其长度相同，来创建一个max_length*num_reviews大小的整数张量
#pad_sequences函数可以让长度标准化
#sequences：浮点数或整数构成的两层嵌套列表
#maxlen：None或整数，为序列的最大长度。大于此长度的序列将被截短，小于此长度的序列将在后部填0.在命名实体识别任务中，主要是指句子的最大长度
#dtype：返回的numpy array的数据类型
#padding：‘pre’或‘post’，确定当需要补0时，在序列的起始还是结尾补
#truncating：‘pre’或‘post’，确定当需要截断序列时，从起始还是结尾截断
#value：浮点数，此值将在填充时代替默认的填充值

train_data=keras.preprocessing.sequence.pad_sequences(train_data,value=word_index['<PAD>'],padding='post',maxlen=256)
test_data=keras.preprocessing.sequence.pad_sequences(test_data,value=word_index['<PAD>'],padding='post',maxlen=256)

#再次查看第一个影评和第二个影评的长度
print("({},{})".format(len(train_data[0]),len(train_data[1])))

#检查已经填充的第一条影评
print(train_data[0])

#step5-build the model
#神经网络的构建主要是通过层层堆叠而成，所以主要问题是:
#question 1:要在模型中使用多少个层？
#question 2:要针对每个层使用多少个隐藏单元？
#此时的输入数据是由word+index的数组组成，需要预测的label为0/1

#input shape is the vocabulary count used for the movie reviews (10,000 words)
vocab_size=10000

#快速开始序贯（Sequential）模型
#序贯模型是多个网络层的线性堆叠，也就是“一条路走到黑”。
#可以通过向Sequential模型传递一个layer的list来构造该模型：
#此时选择通过.add()方法一个个的将layer加入模型中：
model=keras.Sequential()
model.add(keras.layers.Embedding(vocab_size,16))
model.add(keras.layers.GlobalAveragePooling1D())
model.add(keras.layers.Dense(16,activation=tf.nn.relu))
model.add(keras.layers.Dense(1,activation=tf.nn.sigmoid))

model.summary()
#嵌入层将正整数（下标）转换为具有固定大小的向量，Embedding层只能作为模型的第一层
#该层会在整数编码的词汇表中查找每个字词-索引的嵌入向量。
#模型在接受训练时会学习这些向量。这些向量会向输出数组添加一个维度。
#生成的维度为：(batch, sequence, embedding)。

#GlobalAveragePooling1D层为时域信号施加全局平均值池化,针对每个样本返回一个长度固定的输出向量。
#这样，模型便能够以尽可能简单的方式处理各种长度的输入。

#Dense层由core模块内部定义，core中定义了一系列常用的网络层，如全连接层Dense,此时包含 16 个隐藏单元

#最后一层与单个输出节点密集连接。应用 sigmoid 激活函数后，结果是介于 0 到 1 之间的浮点值，表示概率或置信水平。


#隐藏单元
#上述模型在输入和输出之间有两个中间层（也称为“隐藏”层）。
# 输出（单元、节点或神经元）的数量是相应层的表示法空间的维度。
# 换句话说，该数值表示学习内部表示法时网络所允许的自由度。

#如果模型具有更多隐藏单元（更高维度的表示空间）和/或更多层，
# 则说明网络可以学习更复杂的表示法。不过，这会使网络耗费更多计算资源，
# 并且可能导致学习不必要的模式（可以优化在训练数据上的表现，
# 但不会优化在测试数据上的表现）。

#损失函数和优化器loss and optimizer
#模型在训练时需要一个损失函数和一个优化器。
# 由于这是一个二元分类问题且模型会输出一个概率（应用 S 型激活函数的单个单元层），
# 因此我们将使用 binary_crossentropy 损失函数。

#该函数并不是唯一的损失函数，例如，您可以选择 mean_squared_error。
# 但一般来说，binary_crossentropy 更适合处理概率问题，它可测量概率分布之间的“差距”，在本例中则为实际分布和预测之间的“差距”。


#配置模型以使用优化器和损失函数：
model.compile(optimizer=tf.train.AdamOptimizer(),
              loss='binary_crossentropy',
              metrics=['accuracy'])


#step6-create test set
x_val=train_data[:10000]
partial_x_train=train_data[10000:]

y_val=train_labels[:10000]
partial_y_train=train_labels[10000:]

#step7-train the model
#用有 512 个样本的小批次训练模型 40 个周期。
# 这将对 x_train 和 y_train 张量中的所有样本进行 40 次迭代。
# 在训练期间，监控模型在验证集的 10000 个样本上的损失和准确率：
history=model.fit(partial_x_train,
                  partial_y_train,
                  epochs=40,
                  batch_size=512,
                  validation_data=(x_val,y_val),
                  verbose=1)


#step8-evaluate the model
#模型会返回两个值：损失（表示误差的数字，越低越好）和准确率。
results=model.evaluate(test_data,test_labels)
print(results)

#step9-Create a graph of accuracy and loss over time
#model.fit() 返回一个 History 对象，
# 该对象包含一个字典，其中包括训练期间发生的所有情况：
history_dict=history.history
history_dict.keys()

acc = history.history['acc']
val_acc = history.history['val_acc']
loss = history.history['loss']
val_loss = history.history['val_loss']

epochs=range(1,len(acc)+1)

# "bo" is for "blue dot"
plt.plot(epochs,loss,'bo',label='Training loss')
#b is or "solid blue line"
plt.plot(epochs,val_loss,'b',label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()

plt.show()

plt.clf()   # clear figure
acc_values = history_dict['acc']
val_acc_values = history_dict['val_acc']

plt.plot(epochs, acc, 'bo', label='Training acc')
plt.plot(epochs, val_acc, 'b', label='Validation acc')
plt.title('Training and validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()

plt.show()