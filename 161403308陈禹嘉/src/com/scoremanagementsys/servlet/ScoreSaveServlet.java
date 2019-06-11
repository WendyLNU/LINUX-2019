package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.service.CourseService;
import com.scoremanagementsys.service.ScoreService;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class ScoreSaveServlet extends HttpServlet {
    private ScoreService scoreService = new ScoreService();
    private StudentService studentService = new StudentService();
    private CourseService courseService = new CourseService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");
        String courseNumber = request.getParameter("courseNumber");

        double grade = Double.valueOf(request.getParameter("grade"));

        JSONObject jsonObject = new JSONObject();
        PrintWriter out = response.getWriter();

        if(studentNumber != null && courseNumber != null){
            if(studentService.checkStudentByNumber(studentNumber)
                    && courseService.checkCourseByNumber(courseNumber)){
                Score score = new Score();
                score.setS_number(studentNumber);
                score.setC_number(courseNumber);
                score.setGrade(grade);

                scoreService.add(score);

                jsonObject.put("res",1);    //添加成功
            }else {
                jsonObject.put("res",0);    //添加失败：学生或是课程不存在
            }

        }else {
            jsonObject.put("res",-1);    //添加失败：学号或是课程号为空
        }
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
