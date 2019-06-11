---
typora-copy-images-to: imgs
typora-root-url: imgs
---

# Linux实验报告

## 实验目的

1. 了解Linux编程环境；
2. 掌握在Linux环境下编程的常用工具，例如：shell, vim, make, gedit, git及各种语言的集成开发环境。
3. 了解Linux系统的内存、进程、线程、同步、通信的基本原理和其在实际程序实际中的应用。
4. 掌握Linux环境下的应用程序设计、开发和项目管理。
5. 通过16学时的实验，在Linux环境下设计并实现一个代码量不小于2000的项目。

## 编程语言和工具

编程语言：Python

工具：Docker，pytorch

## 项目介绍 基于强化学习实现的斗地主程序

### 项目组成：

自己编写的斗地主env，以及用pytorch实现的dqn

#### env编写：

- agent.py 提供env的接口
- gameutil.py 负责游戏初始化和卡片显示和ai的选择 其中内置randomAI和手动打牌（用来测试env）
- myclass.py 核心类，用来实现斗地主逻辑
- rlutil.py 连接agent.py 和myclass.py
- gen_actions 用来生成action的dict，实现把action转化成数

env运行函数调用图

![agent](/../../doudizhu/read/agent.png)

#### model：

- dqn的pytorch实现

### 模型分析

#### 记忆库实现

![1560135816721](/1560135816721.png)

#### 参数更新

![1560135901273](/1560135901273.png)

#### 参数冻结

![1560135991724](/1560135991724.png)

### 运行效果图![1560134960703](/1560134960703.png)

在game类的的初始化参数中设置对手的类型，目前支持rl（dqn），random，human（手动选择）![1560135069620](/1560135069620.png)

![1560135162090](/1560135162090.png)

出牌记录![1560135223718](/1560135223718.png)

游戏结果，可以看到ai还是赢了的，但是目前的训练结果仍然不太理想





