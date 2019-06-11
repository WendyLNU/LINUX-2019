package com.scoremanagementsys.dao.impl;

import com.scoremanagementsys.dao.ScoreDao;
import com.scoremanagementsys.dao.Score_AllDao;
import com.scoremanagementsys.entity.Score;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ScoreDaoImpl implements ScoreDao {
    private Score_AllDao score_allDao = new Score_AllDaoImpl();

    @Override
    public boolean checkScore(Connection conn, String s_number, String c_number) throws SQLException {
        String sql = " Select * From score Where s_number = ? And c_number = ? ";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, s_number);
        ps.setString(2, c_number);

        ResultSet res = ps.executeQuery();

        while (res.next()) {
            return true;
        }
        return false;
    }

    @Override
    public void add(Connection conn, Score score) throws SQLException {
        if (checkScore(conn, score.getS_number(), score.getC_number())) {
            update(conn, score);
        } else {
            String sql = " Insert Into score (s_number, c_number, grade) " +
                    " Values (?,?,?) ; ";
            PreparedStatement ps = conn.prepareCall(sql);
            ps.setString(1, score.getS_number());
            ps.setString(2, score.getC_number());
            ps.setDouble(3, score.getGrade());

            ps.execute();
        }
    }

    @Override
    public ResultSet getScoresByStudentNumber(Connection conn, String studentNumber, int startIndex, int pageSize) throws SQLException {
        String sql = " Select * From score Where s_number = ? Order By grade limit ?,? ";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, studentNumber);
        ps.setInt(2, startIndex);
        ps.setInt(3, pageSize);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getScoresByCourseNumber(Connection conn, String courseNumber, int startIndex, int pageSize) throws SQLException {
        String sql = " Select * From score Where c_number = ? Order By s_number limit ?,? ";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, courseNumber);
        ps.setInt(2, startIndex);
        ps.setInt(3, pageSize);

        return ps.executeQuery();
    }

    @Override
    public void update(Connection conn, Score score) throws SQLException {
        String sql = " Update score Set grade = ? Where s_number = ? And c_number = ?; ";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setDouble(1, score.getGrade());
        ps.setString(2, score.getS_number());
        ps.setString(3, score.getC_number());

        ps.execute();
    }

    @Override
    public void delete(Connection conn, String studentNumber) throws SQLException {
        String sql = " Update score Set grade = 0 Where s_number = ? ";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, studentNumber);

        ps.execute();
    }

    public ResultSet getAllWithPage(Connection conn, String searchContent, String order, int startIndex, int pageSize) throws SQLException {
        String sql = " Select * From score ";

        if (searchContent != null && !searchContent.equals("")) {
            sql += " Where s_number Like '%" + searchContent + "%' or c_number Like '%" + searchContent + "%' ";
        }

        if (order != null && !order.equals("")) {

            if( !order.equals("s_number")){
                sql += " Order By " + order + " desc";
            }else {
                sql += " Order By " + order;
            }
        } else {
            sql += " Order By grade desc, s_number, c_number ";
        }

        sql += " limit ?, ? ";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setInt(1, startIndex);
        ps.setInt(2, pageSize);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getRowTotal(Connection conn, String searchContent) throws SQLException {
        String sql = " Select Count(*) From score ";

        PreparedStatement ps = conn.prepareStatement(sql);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getRowTotalByStudentNumber(Connection conn, String studentNumber) throws SQLException {
        String sql = " Select Count(*) From score Where s_number = ?";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, studentNumber);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getRowTotalByCourseNumber(Connection conn, String courseNumber) throws SQLException {
        String sql = " Select Count(*) From score Where c_number = ?";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, courseNumber);

        return ps.executeQuery();
    }

    public ResultSet getScoreBySnoAndCno(Connection conn, String studentNumber, String courseNumber) throws SQLException {
        String sql = " Select * From score Where s_number = ? And c_number = ?";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, studentNumber);
        ps.setString(2, courseNumber);

        return ps.executeQuery();
    }
}