package com.servlet;

import java.io.IOException;
import java.sql.SQLException;

import javax.jms.MessageProducer;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.dao.JudgeDao;
import com.dao.ProblemDao;
import com.dao.impl.JudgeDaoImpl;
import com.dao.impl.ProblemDaoImpl;
import com.domain.Judge;
import com.domain.Problem;
import com.util.ActiveMqUtil;




/**
 * Servlet implementation class Status
 */
@WebServlet("/Status")
public class Status extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session = request.getSession();
		if(session.getAttribute("user_id")==null||session.getAttribute("user_id").equals("null"))
		{
			response.getWriter().println("Please login first !!!");
			return ;
		}
		ProblemDao pDao = new ProblemDaoImpl();
		JudgeDao jDao = new JudgeDaoImpl();
		try {
			Problem p = pDao.findProblem(request.getParameter("pid"));
			Judge judge = new Judge();
			judge.setCode(((HtmlHttpServletRequest)request).getParameterNoFilter("code"));
			judge.setLanguage(1);
			judge.setProblem_id(p.getProblem_id());
			judge.setStatus(0);
			judge.setUser_id((String)session.getAttribute("user_id"));
			judge.setJudge_id(1001+jDao.findAlls());
			jDao.insertJudge(judge);
			judge.setTime(p.getTimelimit());
			judge.setSpace(p.getSpacelimit());
			ActiveMqUtil MqUtil = new ActiveMqUtil();
			MqUtil.sendJudge(judge);
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		response.sendRedirect("StatusList");
		
	}

}
