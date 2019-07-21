## OnlineJudge 1.0

> 基于Java和Bootstrap的简单在线评测系统

[Demo地址](<http://188.131.216.16:8080/hoj_2>)

### 一、概览

- 可以对已有题目提交C/C++代码，交给后台评测
- 评测结果包括正确、答案错误、超过时限、段错误等
- 可以自己添加题目、上传/下载数据
- 可以组建比赛，具有实时排行榜

#### 二、OJ前台

![题目](https://github.com/houzena/LINUX-2019/blob/master/161403214%E4%BE%AF%E6%8C%AF%E6%A1%93/img/e.png)

![判题队列](https://github.com/houzena/LINUX-2019/blob/master/161403214%E4%BE%AF%E6%8C%AF%E6%A1%93/img/b.png)

![排行榜](https://github.com/houzena/LINUX-2019/blob/master/161403214%E4%BE%AF%E6%8C%AF%E6%A1%93/img/d.png)

#### 三、后台技术

- Web程序为eclipse上普通开发，Judge程序使用Maven管理依赖库

- Web程序为Jsp/Servlet+MySql，遵从MVC设计模式

- Judge程序用线程池管理资源，每个线程通过Jni加载封装成共享库的判题程序

- Web和Judge两个进程通过ActiveMQ通信，因此Judge可以分布在不同的机器上

  [详细文档点这里](https://github.com/houzena/LINUX-2019/blob/master/161403214%E4%BE%AF%E6%8C%AF%E6%A1%93/%E5%AE%9E%E9%AA%8C%E6%8A%A5%E5%91%8A.md)

#### 四、安装

- 安装mysql  
  sudo install mysql-server  

- 安装jdk  
  wget http://gw.lvith.cn:8080/201704/tools/jdk-linux-x64.tar.gz  
  tar zxvf  jdk-linux-x64.tar.gz  
  sudo vim /etc/profile  
  source /etc/profile  

- 配置tomcat  
  tar zxvf apache-tomcat-7.0.94.tar.gz  
  cp hoj_2.war /home/ubuntu/apache-tomcat-7.0.94/webapps  
  cp lib/*.jar /home/ubuntu/apache-tomcat-7.0.94/lib  

  启动：/home/ubuntu/apache-tomcat-7.0.94/bin/startup.sh  
  关闭：/home/ubuntu/apache-tomcat-7.0.94/bin/shutdown.sh  

- 安装activemq  
  tar zxvf apache-activemq-5.15.9-bin.tar.gz  

  启动: /home/ubuntu/apache-activemq-5.15.9/bin/linux-x86-64/activemq start  

- 配置Judge  
  mkdir -p /home/ubuntu/judge/data  
  mkdir -p /home/ubuntu/judge/judge_work  
  sudo cp libtestjni.so /usr/lib  

  启动：java -jar jniJudge.jar  
