package com.dao.impl;

import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.dao.JudgeDao;
import com.domain.Control;
import com.domain.Judge;
import com.domain.Problem;
import com.util.JDBCUtil;

public class JudgeDaoImpl implements JudgeDao{
	private static String TABLE_FILED = " judge_id,problem_id,user_id,judge_date,status,code,language ";
	@Override
	public void insertJudge(Judge judge) {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		String temp = "insert into judge2("+TABLE_FILED+") values(?,?,?,?,?,?,?)";
		try {
			runner.update(temp,judge.getJudge_id(),judge.getProblem_id(),judge.getUser_id(),new java.sql.Date(new java.util.Date().getTime()),
					judge.getStatus(),judge.getCode(),judge.getLanguage()
					
					);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	@Override
	public List<Judge> findAll() {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		
		try {
			return runner.query("select * from judge2 order by judge_id desc",new BeanListHandler<Judge>(Judge.class));
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	@Override
	public int findAlls() throws SQLException {
		
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		Control s = runner.query("select count(*) as total from judge2",new BeanHandler<Control>(Control.class));
		return s.getTotal();
	}

	@Override
	public Integer findSubmited(int pid) {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		try {
			Control s = runner.query("select count(*) as total from judge2 where problem_id = ?",new BeanHandler<Control>(Control.class),pid);
			return s.getTotal();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;
	}

	@Override
	public Integer findAc(int pid) {
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		try {
			Control s = runner.query("select count(*) as total from judge2 where status = 1 and problem_id = ?",new BeanHandler<Control>(Control.class),pid);
			return s.getTotal();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;
	}
	

}
