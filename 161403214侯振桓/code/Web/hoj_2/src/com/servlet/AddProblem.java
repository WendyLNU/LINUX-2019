package com.servlet;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dao.ProblemDao;
import com.dao.impl.ProblemDaoImpl;
import com.domain.Problem;


@WebServlet("/AddProblem")
public class AddProblem extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		Problem p = new Problem();
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
		p.setTitle(request.getParameter("title"));
		p.setDescription(request.getParameter("description"));
		p.setInput(request.getParameter("input"));
		p.setOutput(request.getParameter("output"));
		p.setSample_input(request.getParameter("sample_input"));
		p.setSample_output(request.getParameter("sample_output"));
		int timelimit=0,spacelimit=0;
		for(char c:request.getParameter("timelimit").toCharArray())
		{
			timelimit=timelimit*10+c-'0';
		}
		for(char c:request.getParameter("spacelimit").toCharArray())
		{
			spacelimit=spacelimit*10+c-'0';
		}
		p.setTimelimit(timelimit);
		p.setSpacelimit(spacelimit);
		
		ProblemDao dao = new ProblemDaoImpl();
		try {
			p.setProblem_id(1001+dao.findAlls());
			if(dao.insertProblem(p))
			{	
				response.sendRedirect("ProblemSet");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally{
			response.getWriter().println("database error !");
		}
	}

}
