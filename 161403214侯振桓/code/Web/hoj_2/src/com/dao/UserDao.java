package com.dao;

import java.sql.SQLException;

import com.domain.User;

public interface UserDao {
	public User findUser(String user_id,String password)throws SQLException;
	public String repeating(String user_id,String nick)throws SQLException;
	public boolean insertUser(String user_id,String nick,String email,String school,String password)throws SQLException;
}
