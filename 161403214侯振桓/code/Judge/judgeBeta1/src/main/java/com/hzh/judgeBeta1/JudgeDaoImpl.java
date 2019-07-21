package com.hzh.judgeBeta1;



import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.domain.Judge;


public class JudgeDaoImpl implements JudgeDao{
	private static String TABLE_FILED = " judge_id,problem_id,user_id,judge_date,status,code,language ";

	public void update(Judge judge) {
		
		String temp = "update judge2 set status = ?,time = ?,space = ? where judge_id = ?";
		QueryRunner runner = new QueryRunner(JDBCUtil.getDataSource());
		try {
			runner.update(temp,judge.getStatus(),judge.getTime(),judge.getSpace(),judge.getJudge_id());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
	}

}
