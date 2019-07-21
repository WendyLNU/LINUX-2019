package com.servlet;

import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.domain.hzhContext;

/**
 * Servlet implementation class DeleteData
 */
@WebServlet("/DeleteData")
public class DeleteData extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		if(request.getParameter("pid")==null || request.getParameter("fileName")==null)
		{
			response.getWriter().println("error");
			return ;
		}
		if(request.getParameter("pid").equals("null")||request.getParameter("fileName").equals("null"))
		{
			response.getWriter().println("error");
			return ;
		}
		String inPath = hzhContext.DataPath+"\\"+request.getParameter("pid")+"\\"+request.getParameter("fileName")+".in";
		String outPath = hzhContext.DataPath+"\\"+request.getParameter("pid")+"\\"+request.getParameter("fileName")+".out";
		File inFile = new File(inPath);
		File outFile = new File(outPath);
		if(inFile.exists())
		{
			inFile.delete();
		}
		if(outFile.exists())
		{
			outFile.delete();
		}
		response.sendRedirect("ManData?pid="+request.getParameter("pid"));
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
