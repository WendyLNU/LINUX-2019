package com.scoremanagementsys.servlet;

import com.scoremanagementsys.service.PageBeanService;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class GetStudentsServlet extends HttpServlet {
    private PageBeanService pageBeanService = new PageBeanService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String searchContent = request.getParameter("searchContent");
        int thisPage = Integer.valueOf(request.getParameter("thisPage"));
        int pageSize = Integer.valueOf(request.getParameter("pageSize"));

        JSONObject studentObj = pageBeanService.getStudentWithPage(searchContent,thisPage,pageSize);

        //向前台的页面输出结果
        PrintWriter out = response.getWriter();
        out.print(studentObj);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
