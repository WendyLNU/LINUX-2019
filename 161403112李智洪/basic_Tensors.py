import tensorflow as tf

tf.enable_eager_execution()


#张量是一个多维数组。与NumPy ndarray对象类似，Tensor对象具有数据类型和形状。此外，Tensors可以驻留在加速器（如GPU）内存中。
print(tf.add(1, 2))
print(tf.add([1, 2], [3, 4]))
print(tf.square(5))
print(tf.reduce_sum([1, 2, 3]))
print(tf.encode_base64("hello world"))

# Operator overloading is also supported
print(tf.square(2) + tf.square(3))


#每个Tensor都有一个形状和一个数据类型
x = tf.matmul([[1]], [[2, 3]])
print(x.shape)
print(x.dtype)