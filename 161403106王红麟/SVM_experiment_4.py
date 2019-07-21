path='mnist-original.mat'
import scipy.io as sio
import os
load_plane = os.path.join(os.getcwd(),path)
data = sio.loadmat(load_plane)
# print(data)

X=data["data"]
y=data["label"]
# print(X.shape)
# print(y.shape)


train=data['data'].T
label_i=data['label'].T
label=label_i.reshape([70000,])
# print(label.shape)

# import matplotlib
# import matplotlib.pyplot as plt
# digit_5=train[36001]
# digit_5_image=digit_5.reshape(28,28)
# plt.imshow(digit_5_image,cmap=matplotlib.cm.binary,interpolation="nearest")
# plt.axis("on")
# plt.savefig("some_digit_plot")



from sklearn.model_selection import train_test_split
x_train,x_test,y_train,y_test=train_test_split(train,label,test_size=0.33,random_state=666)
# print(x_train.shape)
# print(x_test.shape)
# print(y_train.shape)
# print(y_test.shape)

from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

# from sklearn.preprocessing import StandardScaler
# standardScaler=StandardScaler()
#
# standardScaler.fit(x_train)
#
# x_train=standardScaler.transform(x_train)
#
# x_test=standardScaler.transform(x_test)

from sklearn.svm import SVC
svm=SVC()
svm.fit(x_train,y_train)
result=svm.score(x_test,y_test)
print(result)