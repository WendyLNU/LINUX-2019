package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Course;
import com.scoremanagementsys.service.CourseService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class GetCoursesServlet extends HttpServlet {
    private CourseService courseService = new CourseService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        JSONObject jsonObject = new JSONObject();

        List<Course> courseList = courseService.getAllWithPage(0,100);

        jsonObject.put("courseList",courseList);

        //向前台的页面输出结果
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
