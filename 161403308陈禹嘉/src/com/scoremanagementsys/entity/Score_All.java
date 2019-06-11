package com.scoremanagementsys.entity;

public class Score_All extends IdEntity{
    private String s_number;
    private String s_name;
    private String s_gender;
    private double java;
    private double kotlin;
    private double python;
    private double php;
    private double score_sum;
    private double score_avg;

    public String getS_number() {
        return s_number;
    }

    public void setS_number(String s_number) {
        this.s_number = s_number;
    }

    public String getS_name() {
        return s_name;
    }

    public void setS_name(String s_name) {
        this.s_name = s_name;
    }

    public String getS_gender() {
        return s_gender;
    }

    public void setS_gender(String s_gender) {
        this.s_gender = s_gender;
    }

    public double getJava() {
        return java;
    }

    public void setJava(double java) {
        this.java = java;
    }

    public double getKotlin() {
        return kotlin;
    }

    public void setKotlin(double kotlin) {
        this.kotlin = kotlin;
    }

    public double getPython() {
        return python;
    }

    public void setPython(double python) {
        this.python = python;
    }

    public double getPhp() {
        return php;
    }

    public void setPhp(double php) {
        this.php = php;
    }

    public double getScore_sum() {
        return score_sum;
    }

    public void setScore_sum(double score_sum) {
        this.score_sum = score_sum;
    }

    public double getScore_avg() {
        return score_avg;
    }

    public void setScore_avg(double score_avg) {
        this.score_avg = score_avg;
    }

    @Override
    public String toString() {
        return "Score_All{" +
                "s_number='" + s_number + '\'' +
                ", s_name='" + s_name + '\'' +
                ", s_gender='" + s_gender + '\'' +
                ", java=" + java +
                ", kotlin=" + kotlin +
                ", python=" + python +
                ", php=" + php +
                ", score_sum=" + score_sum +
                ", score_avg=" + score_avg +
                ", id=" + id +
                '}';
    }
}