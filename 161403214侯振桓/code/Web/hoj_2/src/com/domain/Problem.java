package com.domain;

public class Problem {
	private int problem_id;
	private String title;
	private String description;
	private String input;

	private String  output;
	private String sample_input;
	private String sample_output;
	private int submit;
	private int accept;
	private int timelimit;
	private int spacelimit;
	
	public int getSubmit() {
		return submit;
	}
	public void setSubmit(int submit) {
		this.submit = submit;
	}
	public int getAccept() {
		return accept;
	}
	public void setAccept(int accept) {
		this.accept = accept;
	}
	public int getTimelimit() {
		return timelimit;
	}
	public void setTimelimit(int timelimit) {
		this.timelimit = timelimit;
	}
	public int getSpacelimit() {
		return spacelimit;
	}
	public void setSpacelimit(int spacelimit) {
		this.spacelimit = spacelimit;
	}
	public int getProblem_id() {
		return problem_id;
	}
	public void setProblem_id(int problem_id) {
		this.problem_id = problem_id;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getInput() {
		return input;
	}
	public void setInput(String input) {
		this.input = input;
	}
	public String getOutput() {
		return output;
	}
	public void setOutput(String output) {
		this.output = output;
	}
	public String getSample_input() {
		return sample_input;
	}
	public void setSample_input(String sample_input) {
		this.sample_input = sample_input;
	}
	public String getSample_output() {
		return sample_output;
	}
	public void setSample_output(String sample_output) {
		this.sample_output = sample_output;
	}
	
}
