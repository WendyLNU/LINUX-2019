package com.scoremanagementsys.test;

import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.service.StudentService;

public class StudentServiceTest {
    private static StudentService studentService = new StudentService();

    public static void main(String[] args) {
//        addTest();
//        updateTest();
//        checkStudentTest();
    }

    public static void addTest(){
        String number = "1500170102";
        String name = "李思";
        String gender = "女";

        Student student = new Student();
        student.setNumber(number);
        student.setName(name);
        student.setGender(gender);

        studentService.add(student);
        System.out.println("添加成功！");
    }
    public static void updateTest(){
        Student student = studentService.getStudentById(1);
        student.setName("李四");
        studentService.update(student);
    }

    public static void checkStudentTest(){
        String number = "1500170101";
        if(studentService.checkStudentByNumber(number)){
            System.out.println("学生已存在！");
        }else {
            System.out.println("可以添加！");
        }
    }
} 