package com.scoremanagementsys.entity;

public class Score extends IdEntity{
    private String s_number;
    private String c_number;
    private double grade;

    public String getS_number() {
        return s_number;
    }

    public void setS_number(String s_number) {
        this.s_number = s_number;
    }

    public String getC_number() {
        return c_number;
    }

    public void setC_number(String c_number) {
        this.c_number = c_number;
    }

    public double getGrade() {
        return grade;
    }

    public void setGrade(double grade) {
        this.grade = grade;
    }

    @Override
    public String toString() {
        return "Score{" +
                "s_number='" + s_number + '\'' +
                ", c_number='" + c_number + '\'' +
                ", grade=" + grade +
                ", id=" + id +
                '}';
    }
}