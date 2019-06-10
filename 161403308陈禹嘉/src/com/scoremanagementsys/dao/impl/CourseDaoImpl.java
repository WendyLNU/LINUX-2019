package com.scoremanagementsys.dao.impl;

import com.scoremanagementsys.dao.CourseDao;
import com.scoremanagementsys.entity.Course;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CourseDaoImpl implements CourseDao {
    @Override
    public boolean checkCourseByNumber(Connection conn, String courseNumber) throws SQLException {
        String sql = " Select * From course Where number = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, courseNumber);

        ResultSet res = ps.executeQuery();
        if(res.next()){
            return true;
        }
        return false;
    }

    @Override
    public ResultSet getAllWithPage(Connection conn, int startIndex, int pageSize) throws SQLException {

        String sql = " Select * From course Order By number limit ?,? ;";

        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setInt(1, startIndex);
        ps.setInt(2, pageSize);

        return ps.executeQuery();
    }

    @Override
    public void add(Connection conn, Course course) throws SQLException {
        String sql = " Insert Into course ( number, name) Values (?, ?); ";
        PreparedStatement ps = conn.prepareCall(sql);
        ps.setString(1, course.getNumber());
        ps.setString(2, course.getName());

        ps.execute();
    }

    @Override
    public void update(Connection conn, Course course) throws SQLException {
        String sql = " Update course Set name = ?, number = ? Where id = ? ; ";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, course.getName());
        ps.setString(2, course.getNumber());
        ps.setLong(3, course.getId());

        ps.execute();
    }

    @Override
    public void delete(Connection conn, Course course) throws SQLException {
        String sql = " Delete From course Where id = ? ; ";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setLong(1, course.getId());

        ps.execute();
    }

    @Override
    public ResultSet getCourseById(Connection conn, long id) throws SQLException {
        String sql = " Select * From course Where id = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setLong(1, id);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getCourseByNumber(Connection conn, String courseNumber) throws SQLException {
        String sql = " Select * From course Where number = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, courseNumber);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getRowTotal(Connection conn) throws SQLException {
        String sql = " Select Count(*) From course ";
        PreparedStatement ps = conn.prepareStatement(sql);

        return ps.executeQuery();
    }

    public ResultSet getCourseByName(Connection conn, String courseName) throws SQLException {
        String sql = " Select * From course Where name = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, courseName);

        return ps.executeQuery();
    }
}