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

	Class.forName(DBDRIVER);//�õ�DriverManager�������潨������ʱʹ��

	} catch (ClassNotFoundException e) {

	// TODO Auto-generated catch block

	e.printStackTrace();

	}

	}

	public static Connection getConnection(){

	if(con==null){

	try {

	con=DriverManager.getConnection(DBURL,DBUSER,DBPASSWORD);//��������,ʹ�õĲ�����������������������ַ���������

	} catch (SQLException e) {

	// TODO Auto-generated catch block

	e.printStackTrace();

	}

	}

	return con;

	}

}
	


