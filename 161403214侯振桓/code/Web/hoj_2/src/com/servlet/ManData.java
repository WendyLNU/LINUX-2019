package com.servlet;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.domain.hzhContext;

/**
 * Servlet implementation class ManData
 */
@WebServlet("/ManData")
public class ManData extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		if(request.getParameter("pid")==null||request.getParameter("pid").equals("null"))
		{
			response.getWriter().println("error");
			return ;
		}
		String FilePath = hzhContext.DataPath+request.getParameter("pid")+"/";; 
		Map<String,String> fileNameMap = new HashMap<String,String>();
		listfile(new File(FilePath),fileNameMap);
		request.setAttribute("fileMap", fileNameMap);
		
		request.getRequestDispatcher("ManData.jsp").forward(request, response);
		
	}
    public void listfile(File file,Map<String,String> map){
        //如果file代表的不是一个文件，而是一个目录
        if(!file.isFile()&&file.isDirectory()){
            //列出该目录下的所有文件和目录
            File files[] = file.listFiles();
            //遍历files[]数组
            for(File f : files){
                //递归
                listfile(f,map);
            }
        }else{
  
            
            map.put(file.getName(), file.length()+"B");
            //System.out.println(file.getAbsolutePath()+"。。。"+file.length());
        }
    }
	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
