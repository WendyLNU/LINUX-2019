package com.scoremanagementsys.test;

import com.scoremanagementsys.entity.Course;
import com.scoremanagementsys.service.CourseService;

public class CourseServiceTest {
    private static CourseService courseService = new CourseService();

    public static void main(String[] args) {
//        add();
    }

    public static void add(){

        String number = "1004";
        String name = "php";

        if ( !courseService.checkCourseByNumber(number)){
            Course course = new Course();
            course.setNumber(number);
            course.setName(name);

            courseService.add(course);
            System.out.println("添加成功！");
        }else {
            System.out.println("该课程已存在！");
        }

    }
} 