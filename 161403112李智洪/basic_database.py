
import tensorflow as tf

# 创建一个源 Dataset
# 使用其中一个工厂函数创建源数据集Dataset.from_tensors，Dataset.from_tensor_slices或者
# 使用从TextLineDataset或等文件读取的对象TFRecordDataset
tf.enable_eager_execution()
ds_tensors = tf.data.Dataset.from_tensor_slices([1, 2, 3, 4, 5, 6])

# Create a CSV file
import tempfile
_, filename = tempfile.mkstemp()

with open(filename, 'w') as f:
  f.write("""Line 1
Line 2
Line 3
  """)

ds_file = tf.data.TextLineDataset(filename)


#使用如转换功能map，batch，shuffle等来转换应用到数据集的记录

ds_tensors = ds_tensors.map(tf.square).shuffle(2).batch(2)

ds_file = ds_file.batch(2)

#当启用eager执行时，Dataset对象支持迭代

print('Elements of ds_tensors:')
for x in ds_tensors:
  print(x)

print('\nElements in ds_file:')
for x in ds_file:
  print(x)