package com.jxal.servlet;

import java.awt.Color;
import java.awt.Font;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.sun.prism.Graphics;

/**
 * Servlet implementation class Code
 */
@WebServlet("/Code")
public class Code extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Code() {
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
	public  Color getRandColor(int fc,int bc){  
	    Random random = new Random();  
	    if(fc>255) fc=255;  
	    if(bc>255) bc=255;  
	    int r = fc + random.nextInt(bc - fc);  
	    int g = fc + random.nextInt(bc - fc);  
	    int b = fc + random.nextInt(bc - fc);  
	    return new Color(r,g,b);  
	    }  
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		 response.setHeader("Pragma", "No-cache");  
		    response.setHeader("Cache-Control", "no-cache");     
		    response.setDateHeader("Expires", 0);  
		    //���ڴ��д���ͼ��  
		    int width = 60;  
		    int height = 20;  
		    BufferedImage image = new BufferedImage(width,height,BufferedImage.TYPE_INT_RGB);  
		    //��ȡͼ��������  
		    Graphics g = (Graphics) image.getGraphics();  
		    //�����  
		    Random random = new Random();  
		    //�趨����  
		     ((java.awt.Graphics) g).setColor(getRandColor(200, 250));  
		    g.fillRect(0, 0, width, height);  
		    //�趨����  
		    ((java.awt.Graphics) g).setFont(new Font("Times New Roman",Font.PLAIN,18));  
		   //�������������  
		   ((java.awt.Graphics) g).setColor(getRandColor(160, 200));     
		   for (int i = 0; i < 100; i++) {     
		        int x = random.nextInt(width);     
		        int y = random.nextInt(height);     
		        int xl = random.nextInt(12);     
		        int yl = random.nextInt(12);     
		        g.drawLine(x, y, x + xl, y + yl);     
		   }   
		   //�������4λ��֤��  
		   String[] codes = {"2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","J","K","L","M","N","P","Q","R","S","T","U","V","W","X","Y","Z"};  
		   String code = "";  
		   for(int i=0;i<4;i++){  
		       String str = codes[random.nextInt(codes.length)];  
		       code += str;  
		       // ����֤����ʾ��ͼ����  
		       ((java.awt.Graphics) g).setColor(new Color(20 + random.nextInt(110), 20 + random.nextInt(110), 20 + random.nextInt(110)));  
		       //���ú�����������ɫ��ͬ����������Ϊ����̫�ӽ�������ֻ��ֱ������     
		       ((java.awt.Graphics) g).drawString(str, 13 * i + 6, 16);     
		   }  
		    // ����֤�����SESSION     
		   HttpSession session=request.getSession();
		   session.setAttribute("code", code);  
		   // ͼ����Ч     
		   ((java.awt.Graphics) g).dispose();     
		   // ���ͼ��ҳ��     
		   ImageIO.write(image, "JPEG", response.getOutputStream());  
		   //�����������,����ʱ�Ų������java.lang.IllegalStateException: getOutputStream() has already been called ..........���쳣  
		   response.getOutputStream().flush();    
		   response.getOutputStream().close();    
		   response.flushBuffer(); 
		   
		 
	}

}
