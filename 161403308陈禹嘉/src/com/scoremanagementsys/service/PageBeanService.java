package com.scoremanagementsys.service;

import com.scoremanagementsys.util.PageBean;
import net.sf.json.JSONObject;

public class PageBeanService {
    private static StudentService studentService = new StudentService();
    private static CourseService courseService = new CourseService();
    private static ScoreService scoreService = new ScoreService();
    private static Score_AllService score_allService = new Score_AllService();

    public JSONObject getStudentWithPage(String searchContent,int thisPage, int pageSize) {

        int dataTotal = studentService.getRowTotal();
//        有了三个初始数据便可创建pageBean对象了
        PageBean pb = new PageBean(thisPage, pageSize, dataTotal);

        int startIndex = pb.getStartIndex();
        pb.setList(studentService.getAllWithPage(searchContent,startIndex, pageSize));

        JSONObject jsonObject = JSONObject.fromObject(pb);

        return jsonObject;
    }

    public JSONObject getScore_AllWithPage(String searchContent, String order, int thisPage, int pageSize){
        int dataTotal = score_allService.getRowTotal();

//        有了三个初始数据便可创建pageBean对象了
        PageBean pb = new PageBean(thisPage, pageSize, dataTotal);

        int startIndex = pb.getStartIndex();
        pb.setList(score_allService.getAllWithPage(searchContent,order,startIndex, pageSize));

        JSONObject jsonObject = JSONObject.fromObject(pb);

        return jsonObject;
    }

    public JSONObject getScoresByStudentNumberWithPage(String studentNumber, String order, int thisPage, int pageSize){
        int dataTotal = scoreService.getRowTotalByStudentNumber(studentNumber);

//        有了三个初始数据便可创建pageBean对象了
        PageBean pb = new PageBean(thisPage, pageSize, dataTotal);

        int startIndex = pb.getStartIndex();
        pb.setList(scoreService.getScoresByStudentNumberWithPage(studentNumber,startIndex, pageSize));

        JSONObject jsonObject = JSONObject.fromObject(pb);

        return jsonObject;
    }

    public JSONObject getScoresByCourseNumberWithPage(String courseNumber, String order, int thisPage, int pageSize){
        int dataTotal = scoreService.getRowTotalByCourseNumber(courseNumber);

//        有了三个初始数据便可创建pageBean对象了
        PageBean pb = new PageBean(thisPage, pageSize, dataTotal);

        int startIndex = pb.getStartIndex();
        pb.setList(scoreService.getScoresByCourseNumberWithPage(courseNumber,startIndex, pageSize));

        JSONObject jsonObject = JSONObject.fromObject(pb);

        return jsonObject;
    }

    public JSONObject getCourseWithPage(int thisPage, int pageSize) {

        int dataTotal = courseService.getRowTotal();
//        有了三个初始数据便可创建pageBean对象了
        PageBean pb = new PageBean(thisPage, pageSize, dataTotal);

        int startIndex = pb.getStartIndex();
        pb.setList(courseService.getAllWithPage(startIndex, pageSize));

        JSONObject jsonObject = JSONObject.fromObject(pb);

        return jsonObject;
    }
}