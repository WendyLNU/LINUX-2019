package com.scoremanagementsys.dao;

import com.scoremanagementsys.entity.Course;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface CourseDao {
    public boolean checkCourseByNumber(Connection conn, String courseNumber) throws SQLException;

    public ResultSet getRowTotal(Connection conn) throws SQLException;

    public ResultSet getAllWithPage(Connection conn, int startIndex, int pageSize) throws SQLException;
    public ResultSet getCourseById(Connection conn, long id) throws SQLException;
    public ResultSet getCourseByNumber(Connection conn, String courseNumber) throws SQLException;
    public ResultSet getCourseByName(Connection conn, String courseName) throws SQLException;

    public void add(Connection conn, Course course) throws SQLException;
    public void update(Connection conn, Course course) throws SQLException;
    public void delete(Connection conn, Course course) throws SQLException;
}