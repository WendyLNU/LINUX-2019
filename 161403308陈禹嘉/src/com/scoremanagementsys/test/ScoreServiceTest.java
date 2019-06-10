package com.scoremanagementsys.test;

import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.service.CourseService;
import com.scoremanagementsys.service.ScoreService;
import com.scoremanagementsys.service.StudentService;

public class ScoreServiceTest {
    private static ScoreService scoreService = new ScoreService();
    private static StudentService studentService = new StudentService();
    private static CourseService courseService = new CourseService();

    public static void main(String[] args) {

//        add();
    }
    public static void add(){
        String s_number = "1500170102";
        String c_number = "1003";
        int grade = 86;

        if( studentService.checkStudentByNumber(s_number) && courseService.checkCourseByNumber(c_number)){
            Score score = new Score();
            score.setS_number(s_number);
            score.setC_number(c_number);
            score.setGrade(grade);

            scoreService.add(score);

            System.out.println("添加成功！");
        }else {
            System.out.println("学生或是课程不存在！");
        }
    }
} 