# -*- coding: utf-8 -*-
"""
Created on Sun Oct 14 13:52:47 2018

@author: Administrator
"""

import numpy as np  # 常用包
import xlrd  # 读excel使用的包
# from sklearn import preprocessing #进行标准化数据时，需要引入这个包
from sklearn import svm  # 调用支持向量机
from sklearn.model_selection import train_test_split  # 将数据分开
from sklearn.metrics import accuracy_score   #引入正确率
from sklearn.metrics import classification_report  # 结果评估
from sklearn.neural_network import MLPClassifier
from sklearn.tree import DecisionTreeClassifier
from xgboost import XGBClassifier

import xgboost as xgb

def open_excel(file):
    """
    打开excel文件获取数据
    :param file: 文件所在的位置
    :return: 文件数据
    """
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception as e:
        print(str(e))


def split_feature(row):
    """
    将该行特征处理后放入列表中
    :param row:一行特征数据
    :return: 返回数据列表
    """
    # print(row[17])
    app = []  # 定义列表
    for i in range(3,17):
        app = app + [row[i]]
    return app


def loadDataSet(path, training_sample, colnameindex=0, by_name=u'sheet1'):
    """
    加载数据
    :param path: 数据文件存放路径
    :param training_sample: 数据文件名
    :param colnameindex: 文件列名下标
    :param by_name: 表名
    :return: 数据集和类别标签
    """
    dataMat = []  # 定义数据列表
    labelMat = []  # 定义标签列表
    filename = path + training_sample  # 形成特征数据的完整路径
    data = open_excel(filename)  # 打开文件获取数据
    table = data.sheet_by_name(by_name)  # 获得数据表
    nrows = table.nrows  # 得到表数据总行数
    for rownum in range(1, nrows):  # 也就是从Excel第二行开始，第一行表头不算
        row = table.row_values(rownum)  # 取一行数据
        if row:
            app = split_feature(row)  # 将特征值转化为列表
            dataMat.append(app)
            labelMat.append(float(row[-1]))  # 获取类别标签
    return dataMat, labelMat

def main():
    """
    主函数
    :return: null
    # """
    # path = "C:\\Users\\456\\Desktop\\"
    # training_sample = 'foo.xlsx'  # 特征数据文件

    path = "C:\\Users\\456\\Desktop\\"
    training_sample = 'featuredata.xls'  # 特征数据文件
    trainingSet, trainingLabels = loadDataSet(path, training_sample)  # 取特征数据和标签数据
    x = np.array(trainingSet,dtype=np.int64)  # 将数据部分列表（list）格式转化为数组(array)格式
    y = np.array(trainingLabels,dtype=np.int64)  # 将标签部分的列表（list）格式转化为数组格式（array）
    print(x.shape)
    print(y.shape)
    '''
    将数据分为训练数据和测试数据两部分
    train_data 训练数据   train_label 训练数据标签   
    test_data  测试数据    test_label 测试数据标签
    '''
    train_data, test_data, train_label, test_label = train_test_split(x, y, random_state=42, test_size=0.3)

    """
    svm.SVC API说明
    功能：使用SVM分类器进行模型构建
    参数说明：
    C:误差项的惩罚系数，默认为1.0；一般为大于0的一个数字，C越大表示在训练过程中对总误差的关注度越高，也就是说当C越大的时候
    ，对于训练集的表现会越好，但是有可能引发过度拟合的问题。
    kernel:指定SVM内部函数的类型，可选值：linear、poly、rbf、sigmoid、precomputed（基本不用，有前提要求，
    要求特征属性数目和样本数目一样）;，默认是rbf;
    degree:当使用多项式函数作为svm内部的函数的时候，给定多项式的项数，默认为3
    gamma:当SVM内部使用poly、rbf、sigmoid的时候，核函数的系数值，当默认值为auto的时候，实际系数为1/n_features.
    coef0:当核函数为poly或者sigmoid的时候，给定的独立系数，默认为0
    probability：是否启用概率估计，默认不启动，不太建议启动。
    probability：是否启用概率估计，默认不启动，不太建议启动。
    shrinking：是否开启收缩启发式计算，默认为true
    tol：模型构建收敛参数，当模型的误差变化率小于该值的时候，结束模型构建的过程，默认值：1e-3
    cache_size:在模型构建过程中，缓存数据的最大内存大小，默认为空，单位MB
    class_weight:给定各个类别的权重，默认为空
    max_iter:最大迭代次数，默认-1表示不限制
    decision_function_shape:决策函数，可选值：ovo和ovr,默认为：None:推荐使用ovr;(1.7以上版本才有)
    """
    # clf = svm.SVC(C=0.8, kernel='rbf', gamma=1, decision_function_shape='ovr')
    """
    gamma值越大，训练集的拟合就越好，但是会造成过拟合，导致测试集拟合变差
    gamma值越小，模型的泛华能力越好，训练集和测试集的拟合相近，但是会导致训练集出现欠拟合问题，
    从而，准确率变低，导致测试集准确率也变低。
    """
    # model = XGBClassifier(learning_rate=0.1,
    #                       n_estimators=1000,  # 树的个数--1000棵树建立xgboost
    #                       max_depth=6,  # 树的深度
    #                       min_child_weight=1,  # 叶子节点最小权重
    #                       gamma=0.,  # 惩罚项中叶子结点个数前的参数
    #                       subsample=0.8,  # 随机选择80%样本建立决策树
    #                       colsample_btree=0.8,  # 随机选择80%特征建立决策树
    #                       objective="binary:logistic",  # 指定损失函数
    #                       scale_pos_weight=1,  # 解决样本个数不平衡的问题
    #                       random_state=27)  # 随机数
    # model.fit(train_data,
    #           train_label,
    #           eval_set=[(test_data,test_label)],
    #           eval_metric="mlogloss",
    #           early_stopping_rounds=10,
    #           verbose=True
    #           )
    # y_pred = model.predict(test_data)
    # accuracy = accuracy_score(test_label, y_pred)
    # print("accuarcy: %.2f%%" % (accuracy * 100.0))

    clf.fit(train_data, train_label.ravel())  # 利用训练数据训练模型
    # hat_test_label = clf.predict(test_data)  # 对x_test数据进行预测
    # # precision:精准率，recall：召回率
    # print(classification_report(test_label, hat_test_label))
    # print(accuracy_score(test_label, hat_test_label))
    # clf = MLPClassifier(activation='relu', solver='adam', alpha=0.0001)
    # clf.fit(train_data, train_label)  # 利用训练数据训练模型
    # hat_test_label = clf.predict(test_data)
    # print(classification_report(test_label, hat_test_label))
    clf = DecisionTreeClassifier()
    clf.fit(train_data, train_label)  # 利用训练数据训练模型
    hat_test_label = clf.predict(test_data)
    print(classification_report(hat_test_label, test_label))


if __name__ == '__main__':
    """
    程序入口
    """
    main()
