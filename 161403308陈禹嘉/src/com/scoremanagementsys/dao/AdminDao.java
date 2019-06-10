package com.scoremanagementsys.dao;

import com.scoremanagementsys.entity.Admin;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface AdminDao {
    public boolean checkAdmin(Connection conn, Admin admin) throws SQLException;
    public void update(Connection conn, Admin admin) throws SQLException;
    public ResultSet getAdminByName(Connection conn, String name) throws SQLException;
    public ResultSet getAdminById(Connection conn, long id) throws SQLException;
} 