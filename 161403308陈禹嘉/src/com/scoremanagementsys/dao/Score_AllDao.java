package com.scoremanagementsys.dao;

import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.entity.Student;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface Score_AllDao {

    public ResultSet getRowTotal(Connection conn) throws SQLException;
    public void addStudentInfo(Connection conn, Student student) throws SQLException;
    public void addOrUpdateStudentScore(Connection conn, Score score) throws SQLException;
    public void updateStudentInfo(Connection conn, Student student) throws SQLException;
    public void delete(Connection conn, Student student) throws SQLException;
    public void deleteScores(Connection conn, String studentNumber) throws SQLException;
    public ResultSet getAllWithPage(Connection conn, String searchContent, String order,int startIndex, int pageSize) throws SQLException;
}