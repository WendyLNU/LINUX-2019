from __future__ import absolute_import, division, print_function

import pathlib

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

print(tf.__version__)

#step1-get the data
dataset_path = keras.utils.get_file("auto-mpg.data", "https://archive.ics.uci.edu/ml/machine-learning-databases/auto-mpg/auto-mpg.data")
print(dataset_path)

#ps:MPG 意为 Miles per Gallon，用于衡量一辆汽车在你的油箱中只加一加仑汽油或柴油可以行驶多少英里。

#结果如下
# Downloading data from https://archive.ics.uci.edu/ml/machine-learning-databases/auto-mpg/auto-mpg.data
#32768/30286 [================================] - 0s 9us/step
#/home/lzh/.keras/datasets/auto-mpg.data

#使用pandas导入数据集
column_names=['MPG','Cylinders','Displacement','Horsepower','Weight',
'Acceleration','Model Year','Origin']
raw_dataset=pd.read_csv(dataset_path,names=column_names,
na_values="?",comment='\t',sep=" ",skipinitialspace=True)

dataset=raw_dataset.copy()
print(dataset.tail())

#na_values = "?"：na 意为 not available，即不可用。
#dataset.tail()输出最后5行，也可以执行dataset.tail(10)来输出10行或自定义一个数字，来观察表格数据。

#step2-clean the data

print(dataset.isna().sum())
#使用pandas统计数据集中某些行中有几个?的值


dataset=dataset.dropna()

origin=dataset.pop('Origin')

dataset['USA']=(origin==1)*1.0
dataset['Europe']=(origin==2)*1.0
dataset['Japan']=(origin==3)*1.0
print(dataset.tail())

#step3-split the data into train and test
train_dataset = dataset.sample(frac=0.8,random_state=0)
test_dataset = dataset.drop(train_dataset.index)


#查看训练数据集
sns.pairplot(train_dataset[["MPG", "Cylinders", "Displacement", "Weight"]], diag_kind="kde")

#查看全部数据统计
train_stats = train_dataset.describe()
train_stats.pop("MPG")
train_stats = train_stats.transpose()
print(train_stats)

#将目标值或“标签”与要素分开。标签是训练模型进行预测的值。
train_labels = train_dataset.pop('MPG')
test_labels = test_dataset.pop('MPG')

#规范化数据
def norm(x):
      return (x - train_stats['mean']) / train_stats['std']
normed_train_data = norm(train_dataset)
normed_test_data = norm(test_dataset)

#step4-build the model
def build_model():
    model = keras.Sequential([
    layers.Dense(64, activation=tf.nn.relu, input_shape=[len(train_dataset.keys())]),
    layers.Dense(64, activation=tf.nn.relu),
    layers.Dense(1)
    ])
    optimizer = tf.keras.optimizers.RMSprop(0.001)
    model.compile(loss='mean_squared_error',
                optimizer=optimizer,
                metrics=['mean_absolute_error', 'mean_squared_error'])
    return model


model=build_model()


model.summary()

#样例
example_batch=normed_train_data[:10]
example_result=model.predict(example_batch)
print(example_result)

#step5-train the model
# Display training progress by printing a single dot for each completed epoch
class PrintDot(keras.callbacks.Callback):
      def on_epoch_end(self, epoch, logs):
            if epoch % 100 == 0: print('')
            print('.', end='')

EPOCHS = 1000
history = model.fit(
  normed_train_data, train_labels,
  epochs=EPOCHS, validation_split = 0.2, verbose=0,
  callbacks=[PrintDot()])

#使用存储在history对象中的统计数据可视化模型的训练进度
hist = pd.DataFrame(history.history)
hist['epoch'] = history.epoch
hist.tail()

def plot_history(history):
  hist = pd.DataFrame(history.history)
  hist['epoch'] = history.epoch
  
  plt.figure()
  plt.xlabel('Epoch')
  plt.ylabel('Mean Abs Error [MPG]')
  plt.plot(hist['epoch'], hist['mean_absolute_error'],
           label='Train Error')
  plt.plot(hist['epoch'], hist['val_mean_absolute_error'],
           label = 'Val Error')
  plt.ylim([0,5])
  plt.legend()
  
  plt.figure()
  plt.xlabel('Epoch')
  plt.ylabel('Mean Square Error [$MPG^2$]')
  plt.plot(hist['epoch'], hist['mean_squared_error'],
           label='Train Error')
  plt.plot(hist['epoch'], hist['val_mean_squared_error'],
           label = 'Val Error')
  plt.ylim([0,20])
  plt.legend()
  plt.show()


plot_history(history)


model = build_model()

# The patience parameter is the amount of epochs to check for improvement
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=10)

history = model.fit(normed_train_data, train_labels, epochs=EPOCHS,
                    validation_split = 0.2, verbose=0, callbacks=[early_stop, PrintDot()])

plot_history(history)

#用测试集来概括模型，我们在训练模型时没有使用。
loss, mae, mse = model.evaluate(normed_test_data, test_labels, verbose=0)

print("Testing set Mean Abs Error: {:5.2f} MPG".format(mae))

#step6-predict：
test_predictions = model.predict(normed_test_data).flatten()

plt.scatter(test_labels, test_predictions)
plt.xlabel('True Values [MPG]')
plt.ylabel('Predictions [MPG]')
plt.axis('equal')
plt.axis('square')
plt.xlim([0,plt.xlim()[1]])
plt.ylim([0,plt.ylim()[1]])
_ = plt.plot([-100, 100], [-100, 100])

#看错误分布
error = test_predictions - test_labels
plt.hist(error, bins = 25)
plt.xlabel("Prediction Error [MPG]")
_ = plt.ylabel("Count")


# 均方误差（MSE）是用于回归问题的常见损失函数（不同的损失函数用于分类问题）。
# 同样，用于回归的评估指标与分类不同。常见的回归度量是平均绝对误差（MAE）。
# 当数字输入数据要素具有不同范围的值时，应将每个要素独立地缩放到相同范围。
# 如果没有太多的训练数据，一种技术是偏好一个隐藏层很少的小网络，以避免过度拟合。
# 早期停止是防止过度拟合的有用技术。