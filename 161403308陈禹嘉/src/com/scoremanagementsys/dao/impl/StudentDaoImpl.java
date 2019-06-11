package com.scoremanagementsys.dao.impl;

import com.scoremanagementsys.dao.StudentDao;
import com.scoremanagementsys.entity.Score_All;
import com.scoremanagementsys.entity.Student;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class StudentDaoImpl implements StudentDao {
    Score_AllDaoImpl score_allDao = new Score_AllDaoImpl();

    @Override
    public boolean checkStudentByNumber(Connection conn, String studentNumber) throws SQLException {
        String sql = " Select * From student Where number = ?; ";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, studentNumber);

        ResultSet res = ps.executeQuery();

        if (res.next()){
            return true;
        }
        return false;
    }

    @Override
    public void add(Connection conn, Student student) throws SQLException {
        String sql = " Insert Into student (number, name, gender) Values (?,?,?); ";
        PreparedStatement ps = conn.prepareCall(sql);

        ps.setString(1, student.getNumber());
        ps.setString(2, student.getName());
        ps.setString(3, student.getGender());

        ps.execute();

        //为主表添加数据
        score_allDao.addStudentInfo(conn, student);

    }

    @Override
    public void update(Connection conn, Student student) throws SQLException {
        String sql = " Update student Set name = ?, gender = ? Where number = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, student.getName());
        ps.setString(2, student.getGender());
        ps.setString(3, student.getNumber());

        ps.execute();

        //更新主表数据
        score_allDao.updateStudentInfo(conn, student);
    }

    @Override
    public void delete(Connection conn, Student student) throws SQLException {
        String sql = " Delete From student Where number = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, student.getNumber());

        //删除主表数据
        score_allDao.delete(conn, student);
        ps.execute();
    }

    @Override
    public ResultSet getStudentById(Connection conn, long id) throws SQLException {
        String sql = " Select * From student Where id = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setLong(1, id);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getStudentByStudentNumber(Connection conn, String studentNumber) throws SQLException {
        String sql = " Select * From student Where number = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, studentNumber);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getAllWithPage(Connection conn, String searchContent, int startIndex, int pageSize) throws SQLException {
        String sql = " Select * From student Where 1=1 ";
        if (searchContent != null && !searchContent.equals("")){
            sql += " And ( number Like '%"+searchContent+"%' Or name Like '%"+searchContent+"%' Or gender Like '%"+searchContent+"%')";
        }
        sql += "  Order By number limit ?,? ";

        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setInt(1, startIndex);
        ps.setInt(2, pageSize);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getRowTotal(Connection conn) throws SQLException {
        String sql = " Select Count(*) From student ";
        PreparedStatement ps = conn.prepareStatement(sql);

        return ps.executeQuery();
    }
}