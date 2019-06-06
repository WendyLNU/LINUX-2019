package com.demo.registerServlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.demo.bean.User;
import com.demo.dao.UserDAO;

/**
 * Servlet implementation class registerservlet
 */
@WebServlet("/registerservlet")
public class registerservlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public registerservlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPut(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	//	request.setCharacterEncoding("utf-8");
	//	response.setContentType("text/html;charset=utf-8");	
	//	request.setCharacterEncoding("utf-8");  
		int id=Integer.valueOf(request.getParameter("id")); 
         String name=request.getParameter("name");  
         String password=request.getParameter("password");
        
         User user=new User();
         user.setId(id);
         user.setName(name);
         user.setPassword(password);
        
         UserDAO userDAO=new UserDAO(); 
         userDAO.addUser(user);
         System.out.println("×¢²á³É¹¦");
         request.getRequestDispatcher("login.jsp").forward(request, response);
	}
}
