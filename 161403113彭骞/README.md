| 姓名 |   学号    |   班级   |
| :--: | :-------: | :------: |
| 彭骞 | 161403113 | 硬件一班 |

# 实验题目

在LINUX上用html和php设计个人博客



# 实验过程

## 1.配置Apache2、PHP和Mysql 

1. 更新

   ```
   sudo apt update && sudo apt upgrade && sudo apt dist-upgrade
   ```

2. 安装apache2

   ```
   sudo apt install apache2
   ```

   如图：

   ![](/home/pq/Desktop/161403113彭骞/image/apache2.png)

3. 安装php

   ```
   sudo apt install php
   ```

   ![](/home/pq/Desktop/161403113彭骞/image/php.png)

4. 安装mysql

   ```
   sudo apt install mysql-server php-mysql
   ```

5. 配置mysql

   ```
   mysql -u root use mysql;
   update mysql.user <span class="hljs-built_in">set</span> authentication_string=PASSWORD(<span class="hljs-string">'你的密码'</span>), plugin=<span class="hljs-string">'mysql_native_password'</span> <span class="hljs-built_in">where</span> user=<span class="hljs-string">'root'</span>; 
   flush privileges; 
   quit; 
   sudo service mysql stop sudo service mysql start
   ```

   

## 2.建立注册页面与登录页面

1. reg.html

   ![](/home/pq/Desktop/161403113彭骞/image/reg.png)

2. login.html

   ![](/home/pq/Desktop/161403113彭骞/image/login.png)

## 3.建立博客首页

index.html![](/home/pq/Desktop/161403113彭骞/image/index.png)

## 4.建立文章页面

文章展示以及评论页面article.html![](/home/pq/Desktop/161403113彭骞/image/article.png)

文章撰写页面write.html![](/home/pq/Desktop/161403113彭骞/image/write.png)

## 5.建立留言板页面

msg.html![](/home/pq/Desktop/161403113彭骞/image/msg.png)

# 

# 

