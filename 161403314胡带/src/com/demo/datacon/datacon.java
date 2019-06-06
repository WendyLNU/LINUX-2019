package com.demo.datacon;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class datacon {
	private static final String DBDRIVER = "com.mysql.jdbc.Driver" ; 
	private static final String DBURL = "jdbc:mysql://localhost:8888/HDweb" ;
	private static final String DBUSER = "root" ;
	private static final String DBPASSWORD = "19971016" ;
	public static Connection con=null;

	static{

	try {

	Class.forName(DBDRIVER);//得到DriverManager，在下面建立连接时使用

	} catch (ClassNotFoundException e) {

	// TODO Auto-generated catch block

	e.printStackTrace();

	}

	}

	public static Connection getConnection(){

	if(con==null){

	try {

	con=DriverManager.getConnection(DBURL,DBUSER,DBPASSWORD);//建立连接,使用的参数就是上面我们所定义的字符串常量。

	} catch (SQLException e) {

	// TODO Auto-generated catch block

	e.printStackTrace();

	}

	}

	return con;

	}

}
	


