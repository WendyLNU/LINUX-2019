package com.jxal.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import bean.LoginCheck;

/**
 * Servlet implementation class UserLogin
 */
@WebServlet("/UserLogin")
public class UserLogin extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public UserLogin() {
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
		String username=request.getParameter("username");
		String userpass=request.getParameter("password");
		String usercode=request.getParameter("code");
		String message="";
		HttpSession session=request.getSession();
		if(usercode==session.getAttribute("code")) {
			
			System.out.print("ok");
		}
		else System.out.println("false");
		try{
			if(username!=null ) {
				Connection conn=LoginCheck.getConnection();
				Statement stmt=LoginCheck.GetStatement(conn);
				String sql="select count(0)from user where user";
				sql+="id='"+username+"'and password";
				sql+="='"+userpass+"'";
				ResultSet rs =stmt.executeQuery(sql);
				if(rs.next()) {
					//int isUser=rs.getInt(1);
					//if(0==isUser) {message="not ok";}
					message="ok";
					
					session.setAttribute("isLogin", true);
					session.setAttribute("userid", username);
					Date dtime=new Date();
					DateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					String nowTime=df.format(dtime);
					 sql ="update user SET logintime='"+nowTime+"' where userid='"+username+"'";
					 stmt.execute(sql);
					PrintWriter out = response.getWriter();
					out.print("<script>alert('login successful!');window.location.href='manager.jsp'</script>");
					
			}
				else {
					PrintWriter out = response.getWriter();
					out.print("<script>alert('Incorrect username or password!');window.location.href='login.jsp'</script>");
					
					
				}
			}else {
				PrintWriter out = response.getWriter();
				out.print("<script>alert('User name cannot be empty!');window.location.href='login.jsp'</script>");
				
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		System.out.print(message);
	}

}
