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

/**
 * Servlet implementation class ProblemPage
 */
@WebServlet("/ProblemPage")
public class ProblemPage extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String pid = request.getParameter("pid");
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
		if(pid!=null)
		{	ProblemDao dao = new ProblemDaoImpl();
			try {
				Problem p = dao.findProblem(pid);
				request.setAttribute("problem", p);
				request.getRequestDispatcher("problem.jsp").forward(request, response);
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}


	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
