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

public class DeleteStudentServlet extends HttpServlet {
    private StudentService studentService = new StudentService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");

        JSONObject jsonObject = new JSONObject();
        int res = 0;
        if(studentService.checkStudentByNumber(studentNumber)){
            Student student = studentService.getStudentByStudentNumber(studentNumber);

            studentService.delete(student);

            res = 1;
        }else {
            res = 0;
        }
        jsonObject.put("res" ,res);
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
