package com.scoremanagementsys.servlet;

import com.scoremanagementsys.service.ScoreService;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class DeleteStudentScoreServlet extends HttpServlet {
    private ScoreService scoreService = new ScoreService();
    private StudentService studentService = new StudentService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");

        JSONObject jsonObject = new JSONObject();
        int res = 0;

        if(studentNumber != null && !studentNumber.equals("")){
            if(studentService.checkStudentByNumber(studentNumber)){

                scoreService.delete(studentNumber);

                res = 1;    //删除成功！
            }else {
                res = 0;    //删除失败，学生不存在！
            }
        }else {
            res = -1;   //删除失败，学号为空！
        }

        jsonObject.put("res",res);
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
