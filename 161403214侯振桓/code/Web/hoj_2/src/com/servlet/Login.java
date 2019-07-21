package com.servlet;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.dao.UserDao;
import com.dao.impl.UserDaoImpl;
import com.domain.User;

/**
 * Servlet implementation class Login
 */
@WebServlet("/Login")
public class Login extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		UserDao dao = new UserDaoImpl();
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
		
			try {
				User user = dao.findUser(request.getParameter("user_id"), request.getParameter("password"));
				if(user==null)
				{
					response.getWriter().println("false");
				}
				else
				{
					HttpSession session = request.getSession();
					session.setAttribute("user_id", request.getParameter("user_id"));
					response.getWriter().println("true");
					
				}
			} catch (SQLException e) {
				
				e.printStackTrace();
			}
	
		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
