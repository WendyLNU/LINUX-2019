package com.dao;

import java.sql.SQLException;
import java.util.List;

import com.domain.Problem;

public interface ProblemDao {
	public List<Problem> findAll()throws SQLException;
	public List<Problem> findPage(int pageid)throws SQLException;
	public boolean insertProblem(Problem p)throws SQLException;
	public int findAlls()throws SQLException;
	public Problem findProblem(String pid) throws SQLException;
}
