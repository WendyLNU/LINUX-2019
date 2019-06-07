package com.dao.impl;

import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.dao.ProblemDao;
import com.domain.Control;
import com.domain.Problem;
import com.domain.User;
import com.util.JDBCUtil;

public class ProblemDaoImpl implements ProblemDao{
	private static int PAGE_SIZE = 10;

	@Override
	public List<Problem> findAll() throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		
		return runner.query("select * from problem",new BeanListHandler<Problem>(Problem.class));
	}

	@Override
	public boolean insertProblem(Problem p) throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		String temp = "insert into problem(problem_id,title,description,input,output,sample_input,sample_output,submit,accept,timelimit,spacelimit) values(?,?,?,?,?,?,?,?,?,?,?)";
		
		int rows = runner.update(temp,p.getProblem_id(),p.getTitle(),p.getDescription(),p.getInput(),p.getOutput(),p.getSample_input(),p.getSample_output(),0,0,p.getTimelimit(),p.getSpacelimit());
		if(rows==0) return false;
		return true;
	}

	@Override
	public List<Problem> findPage(int pageid) throws SQLException {
		int index = (pageid-1)*PAGE_SIZE;
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		
		return runner.query("select * from problem limit ?,?",new BeanListHandler<Problem>(Problem.class),index,PAGE_SIZE);
	}

	@Override
	public int findAlls() throws SQLException {
		
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		Control s = runner.query("select count(*) as total from problem",new BeanHandler<Control>(Control.class));
		return s.getTotal();
	}

	@Override
	public Problem findProblem(String pid) throws SQLException {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		int id=0;
		for(char c:pid.toCharArray()) id=id*10+c-'0';
		return runner.query("select * from problem where problem_id = ?",new BeanHandler<Problem>(Problem.class),id);
	}

}
