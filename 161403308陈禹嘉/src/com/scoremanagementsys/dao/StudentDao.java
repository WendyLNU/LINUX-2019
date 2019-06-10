package com.scoremanagementsys.dao;

import com.scoremanagementsys.entity.IdEntity;
import com.scoremanagementsys.entity.Student;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface StudentDao {
    public boolean checkStudentByNumber(Connection conn, String studentName) throws SQLException;
    public void add(Connection conn, Student student) throws SQLException;
    public void update(Connection conn, Student student) throws SQLException;
    public void delete(Connection conn, Student student) throws SQLException;
    public ResultSet getStudentById(Connection conn, long id) throws SQLException;
    public ResultSet getStudentByStudentNumber(Connection conn, String studentNumber) throws SQLException;

    public ResultSet getAllWithPage(Connection conn, String searchContent, int startIndex, int pageSize) throws SQLException;
    public ResultSet getRowTotal(Connection conn) throws SQLException;
}