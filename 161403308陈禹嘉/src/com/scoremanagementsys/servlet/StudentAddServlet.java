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

public class StudentAddServlet extends HttpServlet {
    private StudentService studentService = new StudentService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");
        String studentName = request.getParameter("studentName");
        String gender = request.getParameter("gender");

        JSONObject jsonObject = new JSONObject();
        int res = 0;

        if(studentNumber != null && !studentNumber.equals("")
                && studentName != null && !studentName.equals("")
                && gender != null && !gender.equals("")){
            boolean isExist = studentService.checkStudentByNumber(studentNumber);

            if( !isExist){
                Student student = new Student();
                student.setNumber(studentNumber);
                student.setName(studentName);
                student.setGender(gender);

                studentService.add(student);

                res = 1;  //添加成功！
            }else {
                Student thisStudent = studentService.getStudentByStudentNumber(studentNumber);
                thisStudent.setNumber(studentNumber);
                thisStudent.setName(studentName);
                thisStudent.setGender(gender);
                studentService.update(thisStudent);

                res = 0;   //学生已存在,更新学生信息
            }
        }else {
            res = -1;   //学号或姓名或性别为空！
        }
        jsonObject.put("res",res);

        //向前台输出数据
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
