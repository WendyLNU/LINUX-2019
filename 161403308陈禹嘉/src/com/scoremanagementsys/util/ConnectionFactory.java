package com.scoremanagementsys.util;

import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class ConnectionFactory {
    private static String driver;   //驱动名
    private static String dburl;    //数据库URL
    private static String user;     //用户名
    private static String password; //密码

    private static final ConnectionFactory factory = new ConnectionFactory();

    private Connection conn;
    //    读取配置文件的内容,静态代码块：加载类的过程中执行，只执行一次
    static {
//        以键值对的方式存放配置文件数据
        Properties properties = new Properties();
        try {
//            用于获取属性文件中的内容，先获取属性文件的类加载器，
//         然后使用类加载器的getResourceAsStream方法读取属性文件中的内容到输入流中
            InputStream in = ConnectionFactory.class.getClassLoader()
                    .getResourceAsStream("dbconfig.properties");

//            从输入流中读取属性列表，方便下面以键值对的方式去读取数据
            properties.load(in);
        } catch (Exception e) {
            System.out.println("=========配置文件读取错误========");
        }
        driver = properties.getProperty("driver");
        dburl = properties.getProperty("dburl");
        user = properties.getProperty("user");
        password = properties.getProperty("password");
    }


    //    这使用了单列模式，保证程序在运行期间，只有一个ConnectionFactory实例存在
    private ConnectionFactory() {

    }

//    获取一个连接工厂的实例
    public static ConnectionFactory getInstance() {
        return factory;
    }

//    获取数据库连接的方法
    public Connection makeConnection(){
        try {
            Class.forName(driver);
            conn = DriverManager.getConnection(dburl,user,password);
        }catch (Exception e){
            e.printStackTrace();
        }
        return conn;
    }
} 