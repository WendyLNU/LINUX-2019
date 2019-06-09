path='mnist-original.mat'
import scipy.io as sio
import os
load_plane = os.path.join(os.getcwd(),path)  #mat文件路径
data = sio.loadmat(load_plane)                  #使用scipy读入mat文件数据
# print(data)

X=data["data"]
y=data["label"]
# print(X.shape)
# print(y.shape)


train=data['data'].T
label_i=data['label'].T
label=label_i.reshape([70000,])
# print(label.shape)



from sklearn.model_selection import train_test_split
x_train,x_test,y_train,y_test=train_test_split(train,label,test_size=0.33,random_state=666)

from sklearn.preprocessing import StandardScaler
standardScaler=StandardScaler()

standardScaler.fit(x_train)

x_train=standardScaler.transform(x_train)

x_test=standardScaler.transform(x_test)

from sklearn.linear_model import LinearRegression

lin_reg=LinearRegression()

lin_reg.fit(x_train,y_train)

print(lin_reg.coef_)
print()
print(lin_reg.intercept_)
print()
score=lin_reg.score(x_test,y_test)
print()
print(score)
print()

import numpy as np
y_predict=np.round(lin_reg.predict(x_test))


print("_______")
print(np.sum(y_test==y_predict)/len(y_test))
print("_______")

from sklearn.linear_model import SGDRegressor

sgd_reg=SGDRegressor()

sgd_reg.fit(x_train,y_train)

print(sgd_reg.score(x_test,y_test))

