Linux—2019（PHP在Linux上的实现）

**实验目的：**

1、服务器（apache2或者nginx）的搭建

2、数据库（Mysql）的链接

3、PHP在linux上的运行

**操作系统：**

Ubuntu16.04 LInux系统

**实验步骤**：

*1、nginx在liunx上的下载、配置*

①通过sudo apt-get install nginx命令行 进行下载；

②下载完毕后用service nginx start对nginx进行启动 ；

③用service nginx status 查看nginx启动状态

![](/home/wsy/Pictures/Screenshot from 2019-06-10 00-03-57.png)

④通过sudo su命令进入可编辑状态，然后进入/etc/nginx/nginx.conf文件进行文本编辑 可用vim或者nano

![](/home/wsy/Pictures/Screenshot from 2019-06-10 00-10-30.png)

⑤配置完毕，打开服务器输入地址localhost即可进入通过nginx搭建的个人服务器（可通过对ports，conf文件的修改来改变地址）

*2,、mysql在liunx上的安装及配置*

①通过sudo apt-get installmysql命令行 进行下载；

②下载完毕后用service mysql start对mysql进行启动 ；

③用service mysql status 查看mysql动状态

![](/home/wsy/Pictures/Screenshot from 2019-06-10 00-20-39.png)

④对mysql进行配置 设置用户名及密码 

*3、PHP（网页制作）*

①下载vscode，通过vscode进行代码的书写及修改

![](/home/wsy/Pictures/Screenshot from 2019-06-10 00-27-34.png)

②将代码存入nginx服务器默认文档 /var/www/html 

③测试网页状态

![](/home/wsy/Pictures/Screenshot from 2019-06-10 10-09-17.png)

4、php链接mysql

php代码中包含有链接mysql的操作，可以通过在mysql中修改表来进行网页内容的替换

**实验结果：**

![](/home/wsy/Pictures/Screenshot from 2019-06-10 00-29-31.png)

![](/home/wsy/Pictures/Screenshot from 2019-06-10 10-03-45.png)