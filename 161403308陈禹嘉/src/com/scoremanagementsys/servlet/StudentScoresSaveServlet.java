package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.service.ScoreService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class StudentScoresSaveServlet extends HttpServlet {
    private ScoreService scoreService = new ScoreService();
    private static final String javaNumber = "1001";
    private static final String kotlinNumber = "1002";
    private static final String pythonNumber = "1003";
    private static final String phpNumber = "1004";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String studentNumber = request.getParameter("studentNumber");
        double java = Double.valueOf(request.getParameter("java"));
        double kotlin = Double.valueOf(request.getParameter("kotlin"));
        double python = Double.valueOf(request.getParameter("python"));
        double php = Double.valueOf(request.getParameter("php"));

        int  res = 0;
        JSONObject jsonObject = new JSONObject();
        Score score;

        if (studentNumber != null){
            if (java >= 0 && java <= 100){
                if( scoreService.checkScore(studentNumber,javaNumber)){
                    score = scoreService.getScoreBySnoAndCno(studentNumber,javaNumber);
                    score.setGrade(java);
                    scoreService.update(score);
                }else {
                    score = new Score();

                    score.setS_number(studentNumber);
                    score.setC_number(javaNumber);
                    score.setGrade(java);

                    scoreService.add(score);
                }
            }
            if (kotlin >= 0 && kotlin <= 100){
                if (scoreService.checkScore(studentNumber,kotlinNumber)){
                    score = scoreService.getScoreBySnoAndCno(studentNumber,kotlinNumber);
                    score.setGrade(kotlin);
                    scoreService.update(score);
                }else {
                    score = new Score();

                    score.setS_number(studentNumber);
                    score.setC_number(kotlinNumber);
                    score.setGrade(kotlin);

                    scoreService.add(score);
                }

            }
            if (python >= 0 && python <= 100){

                if (scoreService.checkScore(studentNumber,pythonNumber)){
                    score = scoreService.getScoreBySnoAndCno(studentNumber,pythonNumber);
                    score.setGrade(python);
                    scoreService.update(score);
                }else {
                    score = new Score();
                    score.setS_number(studentNumber);
                    score.setC_number(pythonNumber);
                    score.setGrade(python);

                    scoreService.add(score);
                }

            }
            if (java >= 0 && php <= 100){

                if(scoreService.checkScore(studentNumber,phpNumber)){
                    score = scoreService.getScoreBySnoAndCno(studentNumber,phpNumber);
                    score.setGrade(php);
                    scoreService.update(score);
                }else {
                    score = new Score();
                    score.setS_number(studentNumber);
                    score.setC_number(phpNumber);
                    score.setGrade(php);

                    scoreService.add(score);
                }
            }
            res = 1;      //保存成功！
            jsonObject.put("res", res);
        }else {
            res = 0;    //学生不存在或已被删除！
            jsonObject.put("res", res);
        }

        //向前台的页面输出结果
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
