package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.service.ScoreService;
import com.scoremanagementsys.service.Score_AllService;
import com.scoremanagementsys.service.StudentService;
import net.sf.json.JSONObject;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class EditScoresServlet extends HttpServlet {
    private ScoreService scoreService = new ScoreService();
    private StudentService studentService = new StudentService();

    private static final String javaNumber = "1001";
    private static final String kotlinNumber = "1002";
    private static final String pythonNumber = "1003";
    private static final String phpNumber = "1004";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");

        JSONObject studentScores = new JSONObject();

        Student student = studentService.getStudentByStudentNumber(studentNumber);

        String studentName = student.getName();
        double java = scoreService.getScoreBySnoAndCno(studentNumber,javaNumber).getGrade();
        double kotlin = scoreService.getScoreBySnoAndCno(studentNumber,kotlinNumber).getGrade();
        double python = scoreService.getScoreBySnoAndCno(studentNumber,pythonNumber).getGrade();
        double php = scoreService.getScoreBySnoAndCno(studentNumber,phpNumber).getGrade();

        studentScores.put("number",studentNumber);
        studentScores.put("name",studentName);
        studentScores.put("java",java);
        studentScores.put("kotlin",kotlin);
        studentScores.put("python",python);
        studentScores.put("php",php);

        request.setAttribute("studentScores",studentScores);
        String forward = "scores_edit.jsp";
        RequestDispatcher requestDispatcher = request.getRequestDispatcher(forward);
        requestDispatcher.forward(request,response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
