package com.scoremanagementsys.dao.impl;

import com.scoremanagementsys.dao.Score_AllDao;
import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.service.ScoreService;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Score_AllDaoImpl implements Score_AllDao {
    private static final String javaNumber = "1001";
    private static final String kotlinNumber = "1002";
    private static final String pythonNumber = "1003";
    private static final String phpNumber = "1004";
    private ScoreService scoreService;

    @Override
    public ResultSet getRowTotal(Connection conn) throws SQLException {
        String sql = " Select Count(*) From score_all ";

        PreparedStatement ps = conn.prepareStatement(sql);

        return ps.executeQuery();
    }

    @Override
    public void addStudentInfo(Connection conn, Student student) throws SQLException {
        String sql = " Insert Into score_all (s_number, s_name, s_gender) Values (?,?,?) ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, student.getNumber());
        ps.setString(2, student.getName());
        ps.setString(3, student.getGender());

        ps.execute();
    }

    @Override
    public void addOrUpdateStudentScore(Connection conn, Score score) throws SQLException {
        String sql = " Update score_all Set java = ?, kotlin = ?, python = ?, php = ?, score_sum = ?, score_avg = ? " +
                " Where s_number = ?";
        PreparedStatement ps = conn.prepareStatement(sql);

        double javaGrade = 0;
        double kotlinGrade = 0;
        double pythonGrade = 0;
        double phpGrade = 0;
        double sum;
        double avg;
        scoreService = new ScoreService();

        if (score.getC_number().equals(javaNumber) ){
            javaGrade = score.getGrade();
        }else {
            javaGrade = scoreService.getScoreBySnoAndCno(score.getS_number(),javaNumber).getGrade();
        }

        if (score.getC_number().equals(kotlinNumber)){
            kotlinGrade = score.getGrade();
        }else {
            kotlinGrade = scoreService.getScoreBySnoAndCno(score.getS_number(),kotlinNumber).getGrade();
        }

        if (score.getC_number().equals(pythonNumber)){
            pythonGrade = score.getGrade();
        }else {
            pythonGrade = scoreService.getScoreBySnoAndCno(score.getS_number(),pythonNumber).getGrade();
        }

        if (score.getC_number().equals(phpNumber)){
            phpGrade = score.getGrade();
        }else {
            phpGrade = scoreService.getScoreBySnoAndCno(score.getS_number(),phpNumber).getGrade();
        }

        sum = javaGrade + kotlinGrade + pythonGrade + phpGrade;
        avg = (javaGrade + kotlinGrade + pythonGrade + phpGrade ) / 4;

        ps.setDouble(1, javaGrade);
        ps.setDouble(2, kotlinGrade);
        ps.setDouble(3, pythonGrade);
        ps.setDouble(4, phpGrade);
        ps.setDouble(5, sum);
        ps.setDouble(6, avg);
        ps.setString(7, score.getS_number());

        ps.execute();
    }

    @Override
    public ResultSet getAllWithPage(Connection conn, String searchContent, String order,int startIndex, int pageSize) throws SQLException {
        String sql = " Select * From score_all Where 1=1 ";

        if(searchContent != null && !searchContent.equals("")){
            sql += " And ( s_number Like '%"+searchContent+"%'  Or s_name Like '%" +searchContent+ "%' " +
                    " Or java Like '%"+searchContent+"%' Or kotlin Like '%"+searchContent+"%'  Or python Like '%"+searchContent+"%' " +
                    " Or php Like '%"+searchContent+"%' ) ";
        }
        if(order != null && !order.equals("")){

            if(order.equals("s_number")){
                sql += " Order By " + order;
            }else {
                sql += " Order By " + order + " Desc";
            }
        }else {
            sql += " Order By s_number";
        }
        sql += " limit ?, ?";

        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setInt(1, startIndex);
        ps.setInt(2, pageSize);

        return ps.executeQuery();
    }
    @Override
    public void updateStudentInfo(Connection conn, Student student) throws SQLException {
        String sql = " Update score_all Set s_name = ?, s_gender = ? Where s_number = ? ";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, student.getName());
        ps.setString(2, student.getGender());
        ps.setString(3, student.getNumber());

        ps.execute();
    }
    @Override
    public void delete(Connection conn, Student student) throws SQLException {
        String sql = " Delete From score_all Where s_number = ?";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, student.getNumber());

        ps.execute();
    }

    @Override
    public void deleteScores(Connection conn, String studentNumber) throws SQLException {
        String sql = " Update score_all Set java = 0, kotlin = 0," +
                " python = 0, php = 0, score_sum = 0, score_avg = 0 Where s_number = ?";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, studentNumber);

        ps.execute();
    }
}