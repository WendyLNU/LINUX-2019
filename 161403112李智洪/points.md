NumPy阵列和TensorFlow张量之间最明显的区别是：

1. 张量可以由加速器内存（如GPU，TPU）支持。
2. 张量是不可改变的。

Conversion between TensorFlow Tensors and NumPy ndarrays is quite simple as:

- TensorFlow operations automatically convert NumPy ndarrays to Tensors.
- NumPy operations automatically convert Tensors to NumPy ndarrays.

通过调用`.numpy()`它们的方法，可以将张量显式转换为NumPy ndarrays 。这些转换通常很便宜，因为如果可能，数组和Tensor共享底层内存表示。但是，共享底层表示并不总是可行的，因为Tensor可以托管在GPU内存中，而NumPy阵列总是由主机内存支持，因此转换将涉及从GPU到主机内存的复制。