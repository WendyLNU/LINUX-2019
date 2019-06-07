package com.domain;

import java.io.Serializable;
import java.sql.Date;

public class Judge implements Serializable{
	private int judge_id;
	private int problem_id;
	private String user_id;
	private int time;
	private int space;
	private Date judge_date;
	private int status;
	private String code;
	private int language;
	public int getJudge_id() {
		return judge_id;
	}
	public void setJudge_id(int judge_id) {
		this.judge_id = judge_id;
	}
	public int getProblem_id() {
		return problem_id;
	}
	public void setProblem_id(int problem_id) {
		this.problem_id = problem_id;
	}
	public String getUser_id() {
		return user_id;
	}
	public void setUser_id(String user_id) {
		this.user_id = user_id;
	}
	public int getTime() {
		return time;
	}
	public void setTime(int time) {
		this.time = time;
	}
	public int getSpace() {
		return space;
	}
	public void setSpace(int space) {
		this.space = space;
	}
	public Date getJudge_date() {
		return judge_date;
	}
	public void setJudge_date(Date judge_date) {
		this.judge_date = judge_date;
	}
	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	public int getLanguage() {
		return language;
	}
	public void setLanguage(int language) {
		this.language = language;
	}
	
	
	


}
