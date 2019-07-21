package com.dao.impl;

import java.sql.SQLException;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import com.dao.UserDao;
import com.domain.User;
import com.util.JDBCUtil;

public class UserDaoImpl implements UserDao{

	@Override
	public User findUser(String user_id, String password) throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		String temp="select * from user where user_id = ? and password = ?";
		return runner.query(temp,new BeanHandler<User>(User.class),user_id,password );
	}

	@Override
	public String repeating(String user_id, String nick) throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		String temp="select * from user where user_id = ?";
		User user = runner.query(temp,new BeanHandler<User>(User.class),user_id);
		if(user!=null) return "user_id";
		temp="select * from user where nick = ?";
		user = runner.query(temp,new BeanHandler<User>(User.class),nick);
		if(user!=null) return "nick";
		return null;
	}

	@Override
	public boolean insertUser(String user_id, String nick, String email, String school, String password)
			throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		String temp = "insert into user(user_id,nick,email,address,password) values(?,?,?,?,?)";
		int rows = runner.update(temp,user_id,nick,email,school,password);
		if(rows==0) return false;
		return true;
	}

}
