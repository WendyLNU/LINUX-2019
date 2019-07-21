package com.demo.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.demo.bean.User;
import com.demo.datacon.datacon;

public class UserDAO {
	public  User  login(String name,String password) {
		   User u=null;
		   Connection connection =null;
		   PreparedStatement pstmt=null;
		   ResultSet resultSet=null;
	 
		  //赋值
		  try {
			connection=datacon.getConnection();
			  //静态sql语句
			String sql = "select * from user where name=? and password=?"; 
		    pstmt = (PreparedStatement) connection.prepareStatement(sql);
			pstmt.setString(1, name);
			pstmt.setString(2, password);  
			resultSet = pstmt.executeQuery();
			if(resultSet.next()){
				u=new User();
				u.setName(resultSet.getString("name"));
				u.setPassword(resultSet.getString("password"));
				System.out.println("登录成功！");
			}else{
				System.out.println("用户名或者密码错误！");
			}  
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {	
		   datacon.close(pstmt, connection);	
		}
		 return u;
	 
	}
		public void addUser(User user) {
			Connection connection = null;
			PreparedStatement psmt = null;
			String sql  ="insert into user(id,name,password)values(?,?,?);";
			try {
				 connection = datacon.getConnection();				 
				 psmt = (PreparedStatement) connection.prepareStatement(sql);
				 psmt.setInt(1, user.getId());
				 psmt.setString(2, user.getName());
				 psmt.setString(3,user.getPassword());			 
				 psmt.executeUpdate();		 
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				 datacon.close(psmt, connection);
			}
		}	
		}




