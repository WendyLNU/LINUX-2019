package com.servlet;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URLEncoder;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.domain.hzhContext;

/**
 * Servlet implementation class DownLoadData
 */
@WebServlet("/DownLoadData")
public class DownLoadData extends HttpServlet {
	
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
		String inPath = hzhContext.DataPath+"/"+request.getParameter("pid")+"/"+request.getParameter("fileName")+".in";
		File inFile = new File(inPath);
		if(!inFile.exists())
		{
			response.getWriter().println("error");
			return ;
		}
		response.setHeader("content-disposition", "attachment;filename=" + URLEncoder.encode(request.getParameter("fileName")+".in", "UTF-8"));
		
		FileInputStream in = new FileInputStream(inPath);
		OutputStream out = response.getOutputStream();
		
        byte buffer[] = new byte[1024];
        int len = 0;
        //循环将输入流中的内容读取到缓冲区当中
        while((len=in.read(buffer))>0){
            //输出缓冲区的内容到浏览器，实现文件下载
            out.write(buffer, 0, len);
        }
        //关闭文件输入流
        in.close();
        //关闭输出流
        out.close();	
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
