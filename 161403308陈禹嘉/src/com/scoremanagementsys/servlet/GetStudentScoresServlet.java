package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Course;
import com.scoremanagementsys.service.CourseService;
import com.scoremanagementsys.service.PageBeanService;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class GetStudentScoresServlet extends HttpServlet {
    private PageBeanService pageBeanService = new PageBeanService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String searchContent = request.getParameter("searchContent");
        String order = request.getParameter("order");

        int thisPage = Integer.valueOf(request.getParameter("thisPage"));
        int pageSize = Integer.valueOf(request.getParameter("pageSize"));

        JSONObject studentScore = pageBeanService.getScore_AllWithPage(searchContent,order,thisPage,pageSize);

        //向前台的页面输出结果
        PrintWriter out = response.getWriter();
        out.print(studentScore);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}
