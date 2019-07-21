package com.jxal.servlet;
import bean.LoginCheck;
import java.sql.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import java.text.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class UserRegister
 */
@WebServlet("/UserRegister")
public class UserRegister extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public UserRegister() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doPost(request,response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String userid=request.getParameter("registerUsername");
				String usermail=request.getParameter("registerEmail");
				String userpass=request.getParameter("registerPassword");
				Date dtime=new Date();
				DateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				String nowTime=df.format(dtime);

				try {
					Connection conn=LoginCheck.getConnection();
					Statement stmt=conn.createStatement();
					 String sql="select*FROM user where userid='"+userid+"';";
					ResultSet rs=stmt.executeQuery(sql);
					if(rs.next()!=false) {
						PrintWriter out = response.getWriter();
						out.print("<script>alert('User name already exists!');window.location.href='register.jsp'</script>");
						
					}
				else {
					sql="insert into user(userid,password,mail,regtime,logintime)";
					sql+="values('"+userid+"','"+userpass+"','"+usermail+"','"+nowTime+"','"+nowTime+"')";
					
					
					int cnt=stmt.executeUpdate(sql);
					if(cnt>0) {
						PrintWriter out = response.getWriter();
						out.print("<script>alert('Login was successful!');window.location.href='login.jsp'</script>");
						
					}
					else {
						PrintWriter out = response.getWriter();
						out.print("<script>alert('Login was failed!');window.location.href='register.jsp'</script>");
					}
				}
				
	}catch(Exception e) {
		e.printStackTrace();
		response.sendRedirect("award.jsp");
	}
	}
}
