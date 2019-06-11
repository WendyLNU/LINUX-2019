package com.scoremanagementsys.dao;

import com.scoremanagementsys.entity.Score;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface ScoreDao {
    public void add(Connection conn, Score score) throws SQLException;
    public boolean checkScore(Connection conn, String s_number, String c_number) throws SQLException;
    public ResultSet getRowTotal(Connection conn, String searchContent) throws SQLException;
    public ResultSet getRowTotalByStudentNumber(Connection conn, String studentNumber) throws SQLException;
    public ResultSet getRowTotalByCourseNumber(Connection conn, String courseNumber) throws SQLException;

    public ResultSet getScoresByStudentNumber(Connection conn, String studentNumber, int startIndex, int pageSize) throws SQLException;

    public ResultSet getScoresByCourseNumber(Connection conn, String courseNumber, int startIndex, int pageSize) throws SQLException;

    public ResultSet getScoreBySnoAndCno(Connection conn, String studentNumber, String courseNumber) throws SQLException;

    public void update(Connection conn, Score score) throws SQLException;

    public void delete(Connection conn, String studentNumber) throws SQLException;
}