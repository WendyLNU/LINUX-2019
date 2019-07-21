package com.servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dao.JudgeDao;
import com.dao.impl.JudgeDaoImpl;
import com.domain.Judge;

/**
 * Servlet implementation class StatusList
 */
@WebServlet("/StatusList")
public class StatusList extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		JudgeDao dao = new JudgeDaoImpl();
		List<Judge> list = dao.findAll();
		request.setAttribute("list", list);
		request.getRequestDispatcher("status.jsp").forward(request, response);
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
