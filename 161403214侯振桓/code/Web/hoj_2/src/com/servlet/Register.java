package com.servlet;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dao.UserDao;
import com.dao.impl.UserDaoImpl;

/**
 * Servlet implementation class register
 */
@WebServlet("/Register")
public class Register extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		UserDao dao = new UserDaoImpl();
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
		String user_id = request.getParameter("user_id");
		String nick = request.getParameter("nick");
		String email = request.getParameter("email");
		String school = request.getParameter("school");
		String password = request.getParameter("password");
		try {
			String temp = dao.repeating(user_id, nick);
			if(temp!=null) response.getWriter().println(temp+" repeat !");
			else
			{
				
				if(dao.insertUser(user_id, nick, email, school, password))
				{
					response.getWriter().println("true");
				}
				else response.getWriter().println("似乎数据库出了点问题");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
