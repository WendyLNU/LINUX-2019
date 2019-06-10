package com.scoremanagementsys.service;

import com.scoremanagementsys.dao.impl.ScoreDaoImpl;
import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.util.ConnectionFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ScoreService {
    private ScoreDaoImpl scoreDao = new ScoreDaoImpl();
    private Score_AllService score_allService = new Score_AllService();
    private Connection conn;

    private final String column_s_number = "s_number";
    private final String column_c_number = "c_number";
    private final String column_grade = "grade";

    public void add(Score score){
        conn = ConnectionFactory.getInstance().makeConnection();
        try {
            conn.setAutoCommit(false);
            scoreDao.add(conn,score);
            score_allService.addOrUpdateStudentScore(score);
            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                conn.rollback();
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    public Score getScoreBySnoAndCno(String studentNumber, String courseNumber){
        conn = ConnectionFactory.getInstance().makeConnection();
        Score score = new Score();

        try {
            ResultSet res = scoreDao.getScoreBySnoAndCno(conn,studentNumber, courseNumber);
            while (res.next()){
                score.setS_number(res.getString(column_s_number));
                score.setC_number(res.getString(column_c_number));
                score.setGrade(res.getInt(column_grade));
            }

            return score;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return score;
    }
    public List<Score> getScoresByStudentNumberWithPage(String studentNumber,int startIndex, int pageSize){
        conn = ConnectionFactory.getInstance().makeConnection();

        List<Score> scoreList = new ArrayList<>();
        try {
            ResultSet res = scoreDao.getScoresByStudentNumber(conn,studentNumber, startIndex, pageSize);
            while (res.next()){
                Score score = new Score();

                score.setS_number(res.getString(column_s_number));
                score.setC_number(res.getString(column_c_number));
                score.setGrade(res.getInt(column_grade));

                scoreList.add(score);
            }

            return scoreList;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return scoreList;
    }

    public List<Score> getScoresByCourseNumberWithPage(String courseNumber,int startIndex, int pageSize){
        conn = ConnectionFactory.getInstance().makeConnection();

        List<Score> scoreList = new ArrayList<>();
        try {
            ResultSet res = scoreDao.getScoresByCourseNumber(conn,courseNumber,startIndex, pageSize);

            while (res.next()){
                Score score = new Score();

                score.setS_number(res.getString(column_s_number));
                score.setC_number(res.getString(column_c_number));
                score.setGrade(res.getInt(column_grade));

                scoreList.add(score);
            }

            return scoreList;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return scoreList;
    }

    public void update(Score score){
        conn = ConnectionFactory.getInstance().makeConnection();
        try {
            conn.setAutoCommit(false);

            scoreDao.update(conn,score);
            score_allService.addOrUpdateStudentScore(score);

            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public void delete(String studentNumber){
        conn = ConnectionFactory.getInstance().makeConnection();
        try {
            conn.setAutoCommit(false);

            scoreDao.delete(conn,studentNumber);
            score_allService.deleteScores(studentNumber);

            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public List<Score> getAllWithPage( String searchContent, String order, int startIndex, int pageSize){
        conn = ConnectionFactory.getInstance().makeConnection();
        List<Score> scoreList = new ArrayList<>();

        try {
            ResultSet res = scoreDao.getAllWithPage(conn,searchContent,order,startIndex,pageSize);

            while (res.next()){
                Score score = new Score();

                score.setS_number(res.getString(column_s_number));
                score.setC_number(res.getString(column_c_number));
                score.setGrade(res.getInt(column_grade));

                scoreList.add(score);
            }

            return scoreList;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return scoreList;
    }

    public int getRowTotal(String searchContent){
        conn = ConnectionFactory.getInstance().makeConnection();
        int rowTotal = 0;

        try {

            ResultSet res = scoreDao.getRowTotal(conn, searchContent);

            if (res.next()){
                rowTotal = res.getInt(1);
            }

            return rowTotal;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rowTotal;
    }

    public int getRowTotalByStudentNumber(String studentNumber){
        conn = ConnectionFactory.getInstance().makeConnection();
        int rowTotal = 0;

        try {

            ResultSet res = scoreDao.getRowTotalByStudentNumber(conn, studentNumber);

            if (res.next()){
                rowTotal = res.getInt(1);
            }

            return rowTotal;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rowTotal;
    }

    public int getRowTotalByCourseNumber(String courseNumber){
        conn = ConnectionFactory.getInstance().makeConnection();
        int rowTotal = 0;

        try {

            ResultSet res = scoreDao.getRowTotalByCourseNumber(conn, courseNumber);

            if (res.next()){
                rowTotal = res.getInt(1);
            }

            return rowTotal;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rowTotal;
    }

    public boolean checkScore(String studentNumber, String courseNumber) {
        conn = ConnectionFactory.getInstance().makeConnection();
        boolean isExist = false;
        try {
            isExist = scoreDao.checkScore(conn,studentNumber,courseNumber);

            return isExist;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return isExist;
    }
}