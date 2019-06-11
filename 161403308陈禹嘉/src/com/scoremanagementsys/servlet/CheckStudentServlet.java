package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class CheckStudentServlet extends HttpServlet {
    private StudentService studentService = new StudentService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");

        if(studentNumber != null && !studentNumber.equals("")){
            boolean isExist = studentService.checkStudentByNumber(studentNumber);

            JSONObject jsonObject = new JSONObject();
            if (isExist){
                Student student = studentService.getStudentByStudentNumber(studentNumber);

                jsonObject.put("student",student);
                jsonObject.put("isExist",1);
            }else {
                jsonObject.put("isExist",0);
            }

            //向前台的页面输出结果
            PrintWriter out = response.getWriter();
            out.print(jsonObject);
            out.close();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
