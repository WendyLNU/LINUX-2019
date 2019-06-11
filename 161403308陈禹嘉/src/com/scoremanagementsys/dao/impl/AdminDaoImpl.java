package com.scoremanagementsys.dao.impl;

import com.scoremanagementsys.dao.AdminDao;
import com.scoremanagementsys.entity.Admin;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class AdminDaoImpl implements AdminDao {
    @Override
    public boolean checkAdmin(Connection conn, Admin admin) throws SQLException {
        String sql = " Select * From admin Where name = ? And password = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);

        ps.setString(1, admin.getName());
        ps.setString(2, admin.getPassword());

        ResultSet res = ps.executeQuery();
        if (res.next()) {
            return true;
        }
        return false;
    }

    @Override
    public void update(Connection conn, Admin admin) throws SQLException {
        String sql = " Update admin Set password = ? Where name = ? ";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, admin.getPassword());
        ps.setString(2, admin.getName());
        ps.execute();
    }

    @Override
    public ResultSet getAdminByName(Connection conn, String name) throws SQLException {
        String sql = " Select * From admin Where name = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, name);

        return ps.executeQuery();
    }

    @Override
    public ResultSet getAdminById(Connection conn, long id) throws SQLException {
        String sql = " Select * From admin Where name = ? ;";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setLong(1, id);

        return ps.executeQuery();
    }
}