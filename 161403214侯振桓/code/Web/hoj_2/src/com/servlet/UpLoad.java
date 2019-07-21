package com.servlet;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import com.domain.hzhContext;

/**
 * Servlet implementation class UpLoad
 */
@WebServlet("/UpLoad")
public class UpLoad extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		if(request.getParameter("pid")==null||request.getParameter("pid").equals("null"))
		{
			response.getWriter().println("error");
			return ;
		}
		String savePath = hzhContext.DataPath+request.getParameter("pid")+"/";
        File file = new File(savePath);
        

       
        try{
            
            
            DiskFileItemFactory factory = new DiskFileItemFactory();
            
            ServletFileUpload upload = new ServletFileUpload(factory);
            
            upload.setHeaderEncoding("UTF-8"); 
            
            if(!ServletFileUpload.isMultipartContent(request)){
            	response.getWriter().println("error");
                return;
            }
            
            if (!file.exists() || !file.isDirectory()) {
                System.out.println(savePath+"目录不存在，需要创建");
               
                file.mkdirs();
            }
            upload.setFileSizeMax(10*1024*1024);
            //解析Request请求
            List<FileItem> list = (List<FileItem>)upload.parseRequest(request);  
          
            for(FileItem item : list){
            	
                if(item.isFormField()){
                    String name = item.getFieldName();
                    
                    
                    String value = item.getString("UTF-8");
                   
                    System.out.println(name + "=" + value);
                }else{
                   
                    String filename = item.getName();
                    System.out.println(filename);
                    if(filename==null || filename.trim().equals("")){
                        continue;
                    }
                    
                    filename = filename.substring(filename.lastIndexOf("/")+1);
                    
                    InputStream in = item.getInputStream();
                    
                    FileOutputStream out = new FileOutputStream(savePath + "/" + filename);
                    
                    byte buffer[] = new byte[1024];
                   
                    int len = 0;
                   
                    while((len=in.read(buffer))>0){
                       
                        out.write(buffer, 0, len);
                    }
                    
                    in.close();
                   
                    out.close();
                    
                    item.delete();
                    
                }
            }
        }catch (Exception e) {
            
            e.printStackTrace();
            
        }
        response.sendRedirect("ManData?pid="+request.getParameter("pid"));
		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request, response);
	}

}
