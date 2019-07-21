package com.dao;

import java.sql.SQLException;
import java.util.List;

import com.domain.Judge;

public interface JudgeDao {

	public void insertJudge(Judge judge);
	public List<Judge> findAll();
	public int findAlls()throws SQLException;
	public Integer findSubmited(int pid);
	public Integer findAc(int pid);
}
