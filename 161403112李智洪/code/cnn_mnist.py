from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

# Imports
import numpy as np
import tensorflow as tf

tf.logging.set_verbosity(tf.logging.INFO)

# Our application logic will be added here

if __name__ == "__main__":
  tf.app.run()


# 卷积神经网络 (CNN) 是目前用于图像分类任务的先进模型架构。CNN 将一系列过滤器应用于图像的原始像素数据，以提取和学习更高级别的特征，然后模型可以使用这些特征进行分类。CNN 包含下列 3 个组成部分：

# 卷积层：将指定数量的卷积过滤器应用于图像。对于每个子区域，该层会执行一组数学运算，以在输出特征图中生成单个值。然后，卷积层通常会向输出应用 ReLU 激活函数，以便在模型中引入非线性规律。

# 池化层：对卷积层提取的图像数据进行下采样，以降低特征图的维度，从而缩短处理时间。常用的池化算法是最大池化，它会提取特征图的子区域（例如 2x2 像素区块），保留子区域的最大值，并舍弃其他所有值。

# 密集（全连接）层：对由卷积层提取并由池化层下采样的特征进行分类。密集层中的每个节点都连接到前一层中的所有节点。

# 通常，CNN 包括多个执行特征提取的卷积模块。每个模块都由一个卷积层后跟一个池化层组成。最后一个卷积模块后跟一个或多个执行分类的密集层。在 CNN 的最终密集层中，模型中的每个目标类别（模型会预测的所有可能类别）都对应一个节点，并应用 softmax 激活函数，该函数针对每个节点生成一个介于 0 到 1 之间的值（所有这些 softmax 值的总和等于 1）。我们可以将某张给定图像的 softmax 值解析为相对测量值，表示该图像属于每个目标类别的概率。

# 构建 CNN MNIST 分类器
# 我们使用以下 CNN 架构构建一个模型，用于对 MNIST 数据集中的图像进行分类：

# 卷积层 1：应用 32 个 5x5 过滤器（提取 5x5 像素的子区域），并应用 ReLU 激活函数
# 池化层 1：使用 2x2 过滤器和步长 2（指定不重叠的池化区域）执行最大池化运算
# 卷积层 2：应用 64 个 5x5 过滤器，并应用 ReLU 激活函数
# 池化层 2：同样，使用 2x2 过滤器和步长 2 执行最大池化运算
# 密集层 1：包含 1024 个神经元，其中丢弃正则化率为 0.4（任何指定元素在训练期间被丢弃的概率为 0.4）
# 密集层 2（对数层）：包含 10 个神经元，每个数字目标类别 (0–9) 对应一个神经元。
# tf.layers 模块包含用于创建上述 3 种层的方法：

# conv2d()。构建一个二维卷积层。接受的参数为过滤器数量、过滤器核大小、填充和激活函数。
# max_pooling2d()。构建一个使用最大池化算法的二维池化层。接受的参数为池化过滤器大小和步长。
# dense()。构建密集层。接受的参数为神经元数量和激活函数。
# 上述这些方法都接受张量作为输入，并返回转换后的张量作为输出。这样可轻松地将一个层连接到另一个层：只需从一个层创建方法中获取输出，并将其作为输入提供给另一个层即可。

# 打开 cnn_mnist.py 并添加以下 cnn_model_fn 函数，该函数符合 TensorFlow Estimator API 预期接口的要求（之后的创建 Estimator 部分对此进行了详细介绍）。cnn_mnist.py 接受的参数为 MNIST 特征数据、标签和模式（来自 tf.estimator.ModeKeys：TRAIN、EVAL、PREDICT）；配置 CNN，然后返回预测、损失和训练操作：


def cnn_model_fn(features, labels, mode):
  """Model function for CNN."""
  # Input Layer
  input_layer = tf.reshape(features["x"], [-1, 28, 28, 1])

  # Convolutional Layer #1
  conv1 = tf.layers.conv2d(
      inputs=input_layer,
      filters=32,
      kernel_size=[5, 5],
      padding="same",
      activation=tf.nn.relu)

# Pooling Layer #1
  pool1 = tf.layers.max_pooling2d(inputs=conv1, pool_size=[2, 2], strides=2)

  # Convolutional Layer #2 and Pooling Layer #2
  conv2 = tf.layers.conv2d(
      inputs=pool1,
      filters=64,
      kernel_size=[5, 5],
      padding="same",
      activation=tf.nn.relu)
  pool2 = tf.layers.max_pooling2d(inputs=conv2, pool_size=[2, 2], strides=2)

  # Dense Layer
  pool2_flat = tf.reshape(pool2, [-1, 7 * 7 * 64])
  dense = tf.layers.dense(inputs=pool2_flat, units=1024, activation=tf.nn.relu)
  dropout = tf.layers.dropout(
      inputs=dense, rate=0.4, training=mode == tf.estimator.ModeKeys.TRAIN)

  # Logits Layer
  logits = tf.layers.dense(inputs=dropout, units=10)

  predictions = {
      # Generate predictions (for PREDICT and EVAL mode)
      "classes": tf.argmax(input=logits, axis=1),
      # Add `softmax_tensor` to the graph. It is used for PREDICT and by the
      # `logging_hook`.
      "probabilities": tf.nn.softmax(logits, name="softmax_tensor")
  }

  if mode == tf.estimator.ModeKeys.PREDICT:
    return tf.estimator.EstimatorSpec(mode=mode, predictions=predictions)

  # Calculate Loss (for both TRAIN and EVAL modes)
  loss = tf.losses.sparse_softmax_cross_entropy(labels=labels, logits=logits)

  # Configure the Training Op (for TRAIN mode)
  if mode == tf.estimator.ModeKeys.TRAIN:
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001)
    train_op = optimizer.minimize(
        loss=loss,
        global_step=tf.train.get_global_step())
    return tf.estimator.EstimatorSpec(mode=mode, loss=loss, train_op=train_op)

  # Add evaluation metrics (for EVAL mode)
  eval_metric_ops = {
      "accuracy": tf.metrics.accuracy(
          labels=labels, predictions=predictions["classes"])}
  return tf.estimator.EstimatorSpec(
      mode=mode, loss=loss, eval_metric_ops=eval_metric_ops)


# 输入层
# 默认情况下，对于 layers 模块中用于为二维图像数据创建卷积层和池化层的方法，输入张量的形状应该为 [batch_size, image_height, image_width, channels]。可以使用 data_format 参数更改这种行为；具体定义如下：

# batch_size。在训练期间执行梯度下降法时使用的样本子集的大小。
# image_height。样本图像的高度。
# image_width。样本图像的宽度。
# channels。样本图像中颜色通道的数量。彩色图像有 3 个通道（红色、绿色、蓝色）。单色图像只有 1 个通道（黑色）。
# data_format。一个字符串，channels_last（默认）或 channels_first 之一。 channels_last 对应于形状为 (batch, ..., channels) 的输入，而 channels_first 对应于形状为 (batch, channels, ...) 的输入。
# 在此教程中，我们的 MNIST 数据集由 28x28 像素的单色图像组成，因此输入层的形状应该为 [batch_size, 28, 28, 1]。

# 要将我们的输入特征图 (features) 转换为此形状，我们可以执行以下 reshape 操作：

#input_layer = tf.reshape(features["x"], [-1, 28, 28, 1])

# 在我们的第一个卷积层中，我们需要将 32 个 5x5 过滤器应用到输入层，并应用 ReLU 激活函数。
# 我们可以使用 layers 模块中的 conv2d() 方法创建该层
#   卷积层 1
# 在我们的第一个卷积层中，我们需要将 32 个 5x5 过滤器应用到输入层，并应用 ReLU 激活函数。
# 我们可以使用 layers 模块中的 conv2d() 方法创建该层，如下所示：
# conv1 = tf.layers.conv2d(
#     inputs=input_layer,
#     filters=32,
#     kernel_size=[5, 5],
#     padding="same",
#     activation=tf.nn.relu)

#如果过滤器高度和宽度的值相同，则可以为 kernel_size 指定单个整数（例如 kernel_size=5）。

# padding 参数指定以下两个枚举值之一（不区分大小写）：valid（默认值）或 same。要指定输出张量与输入张量具有相同的高度和宽度值，我们在此教程中设置 padding=same，它指示 TensorFlow 向输入张量的边缘添加 0 值，使高度和宽度均保持为 28（没有填充的话，在 28x28 张量上进行 5x5 卷积运算将生成一个 24x24 张量，因为在 28x28 网格中，可以从 24x24 个位置提取出一个 5x5 图块）。

# activation 参数指定要应用于卷积输出的激活函数。在此教程中，我们使用 tf.nn.relu 指定 ReLU 激活函数。

# conv2d() 生成的输出张量的形状为 [batch_size, 28, 28, 32]：高度和宽度维度与输入相同，但现在有 32 个通道，用于保存每个过滤器的输出。

#池化层 1
# 接下来，我们将第一个池化层连接到刚刚创建的卷积层。我们可以使用 layers 中的 max_pooling2d() 方法构建一个层，该层使用 2x2 过滤器和步长 2 执行最大池化运算：

# pool1 = tf.layers.max_pooling2d(inputs=conv1, pool_size=[2, 2], strides=2)

# 卷积层 2 和池化层 2
# 像之前一样，我们可以使用 conv2d() 和 max_pooling2d() 将第二个卷积层和池化层连接到 CNN。对于卷积层 2，我们配置 64 个 5x5 过滤器，并应用 ReLU 激活函数；
# 对于池化层 2，我们使用与池化层 1 相同的规格（一个 2x2 最大池化过滤器，步长为 2）：

# conv2 = tf.layers.conv2d(
#     inputs=pool1,
#     filters=64,
#     kernel_size=[5, 5],
#     padding="same",
#     activation=tf.nn.relu)

# pool2 = tf.layers.max_pooling2d(inputs=conv2, pool_size=[2, 2], strides=2)


# 密集层
# 接下来，我们需要向 CNN 添加密集层（具有 1024 个神经元和 ReLU 激活函数），
# 以对卷积/池化层提取的特征执行分类。不过，在我们连接该层之前，我们会先扁平化特征图 (pool2)，
# 以将其变形为 [batch_size, features]，使张量只有两个维度：

# pool2_flat = tf.reshape(pool2, [-1, 7 * 7 * 64])

#在上面的 reshape() 操作中，-1 表示 batch_size 维度将根据输入数据中的样本数量动态计算。
# 每个样本都具有 7（pool2 高度）* 7（pool2 宽度）* 64（pool2 通道）个特征，因此我们希望 features 维度的值为 7 * 7 * 64（总计为 3136）。
# 输出张量 pool2_flat 的形状为 [batch_size, 3136]。

#使用 layers 中的 dense() 方法连接密集层
# dense = tf.layers.dense(inputs=pool2_flat, units=1024, activation=tf.nn.relu)

# inputs 参数指定输入张量：扁平化后的特征图 pool2_flat。
# units 参数指定密集层中的神经元数量 (1024)。activation 参数会接受激活函数；
# 同样，使用 tf.nn.relu 添加 ReLU 激活函数
# 为了改善模型的结果，使用 layers 中的 dropout 方法，向密集层应用丢弃正则化

# dropout = tf.layers.dropout(
#     inputs=dense, rate=0.4, training=mode == tf.estimator.ModeKeys.TRAIN)


# 同样，inputs 指定输入张量，即密集层 (dense) 的输出张量。

# rate 参数指定丢弃率；在此教程中，我们使用 0.4，该值表示 40% 的元素会在训练期间被随机丢弃。

# training 参数采用布尔值，表示模型目前是否在训练模式下运行；只有在 training 为 True 的情况下才会执行丢弃操作。在此教程中，我们检查传递到模型函数 cnn_model_fn 的 mode 是否为 TRAIN 模式。

# 输出张量 dropout 的形状为 [batch_size, 1024]。





# 对数层
# 我们的神经网络中的最后一层是对数层，该层返回预测的原始值。
# 创建一个具有 10 个神经元（介于 0 到 9 之间的每个目标类别对应一个神经元）的密集层，
# 并应用线性激活函数（默认函数）：
# logits = tf.layers.dense(inputs=dropout, units=10)

#CNN 的最终输出张量 logits 的形状为 [batch_size, 10]


# 生成预测
# 模型的对数层以 [batch_size, 10] 维张量中原始值的形式返回预测。我们将这些原始值转换成模型函数可以返回的两种不同格式：

# 每个样本的预测类别：一个介于 0 到 9 之间的数字。
# 每个样本属于每个可能的目标类别的概率：样本属于以下类别的概率：0、1、2 等。
# 对于某个给定的样本，预测的类别是对数张量中具有最高原始值的行对应的元素。
# 我们可以使用 tf.argmax 函数查找该元素的索引：
# tf.argmax(input=logits, axis=1)




# input 参数指定要从其中提取最大值的张量，在此教程中为 logits。
# axis 参数指定要沿着 input 张量的哪个轴查找最大值。
# 需要沿着索引为 1 的维度查找最大值，该维度对应于预测结果（已经知道对数张量的形状为 [batch_size, 10]）。

# 我们可以使用 tf.nn.softmax 应用 softmax 激活函数，以从对数层中得出概率：
# tf.nn.softmax(logits, name="softmax_tensor")


#使用 name 参数明确将该操作命名为 softmax_tensor，以便稍后引用它

# predictions = {
#     "classes": tf.argmax(input=logits, axis=1),
#     "probabilities": tf.nn.softmax(logits, name="softmax_tensor")
# }
# if mode == tf.estimator.ModeKeys.PREDICT:
#   return tf.estimator.EstimatorSpec(mode=mode, predictions=predictions)


#预测编译为字典，并返回 EstimatorSpec 对象


# 计算损失
# 对于训练和评估，我们需要定义损失函数来衡量模型的预测结果与目标类别之间的匹配程度。
# 对于像 MNIST 这样的多类别分类问题，通常将交叉熵用作损失指标。
# 以下代码计算模型在 TRAIN 或 EVAL 模式下运行时的交叉熵：
# loss = tf.losses.sparse_softmax_cross_entropy(labels=labels, logits=logits)


#上述代码中
# labels 张量包含样本的预测索引列表，例如 [1, 9, ...]。
# logits 包含最后一层的线性输出。

# tf.losses.sparse_softmax_cross_entropy 以高效的数值稳定方式计算以上两个输入的 softmax 交叉熵（又名：类别交叉熵、负对数似然率）。


# 配置训练操作
# 在上一部分中，我们将 CNN 的损失定义为对数层和标签之间的 softmax 交叉熵。
# 下面我们配置模型以在训练期间优化该损失值。我们将学习速率设为 0.001，并将优化算法设为随机梯度下降法：

# if mode == tf.estimator.ModeKeys.TRAIN:
#   optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001)
#   train_op = optimizer.minimize(
#       loss=loss,
#       global_step=tf.train.get_global_step())
#   return tf.estimator.EstimatorSpec(mode=mode, loss=loss, train_op=train_op)


#添加评估指标
#要在模型中添加准确率指标，我们在评估模式下定义 eval_metric_ops 字典
#   eval_metric_ops = {
#     "accuracy": tf.metrics.accuracy(
#         labels=labels, predictions=predictions["classes"])}
#   return tf.estimator.EstimatorSpec(mode=mode, loss=loss, eval_metric_ops=eval_metric_ops)

#加载训练和测试数据 
def main(unused_argv):
  # Load training and eval data
  mnist = tf.contrib.learn.datasets.load_dataset("mnist")
  train_data = mnist.train.images # Returns np.array
  train_labels = np.asarray(mnist.train.labels, dtype=np.int32)
  eval_data = mnist.test.images # Returns np.array
  eval_labels = np.asarray(mnist.test.labels, dtype=np.int32)
  # Create the Estimator
  mnist_classifier = tf.estimator.Estimator(
  model_fn=cnn_model_fn, model_dir="/tmp/mnist_convnet_model")
  # 由于 CNN 可能需要一段时间才能完成训练，因此我们设置一些日志记录，以在训练期间跟踪进度。
  # 我们可以使用 TensorFlow 的 tf.train.SessionRunHook 创建 tf.train.LoggingTensorHook，它将记录 CNN 的 softmax 层的概率值。
  # Set up logging for predictions
  tensors_to_log = {"probabilities": "softmax_tensor"}
  logging_hook = tf.train.LoggingTensorHook(
    tensors=tensors_to_log, every_n_iter=50)
  # Train the model
  train_input_fn = tf.estimator.inputs.numpy_input_fn(
    x={"x": train_data},
    y=train_labels,
    batch_size=100,
    num_epochs=None,
    shuffle=True)
  mnist_classifier.train(
    input_fn=train_input_fn,
    steps=20000,
    hooks=[logging_hook])
    # Evaluate the model and print results
  eval_input_fn = tf.estimator.inputs.numpy_input_fn(
    x={"x": eval_data},
    y=eval_labels,
    num_epochs=1,
    shuffle=False)
  eval_results = mnist_classifier.evaluate(input_fn=eval_input_fn)
  print(eval_results)


#   在 train_data 和 train_labels 中将训练特征数据（55000 张手写数字图像的原始像素值）和训练标签（每张图像在 0 到 9 之间的对应值）分别存储为 Numpy 数组。
#   同样，我们将评估特征数据（10000 张图像）和评估标签分别存储在 eval_data 和 eval_labels 中。
# model_fn 参数指定用于训练、评估和预测的模型函数；
# 我们将在构建 CNN MNIST 分类器部分创建的 cnn_model_fn 传递到该参数。model_dir 参数指定要用于保存模型数据（检查点）的目录


