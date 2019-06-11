package com.scoremanagementsys.service;

import com.scoremanagementsys.dao.impl.AdminDaoImpl;
import com.scoremanagementsys.entity.Admin;
import com.scoremanagementsys.util.ConnectionFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * 管理员服务类
 */
public class AdminService {
    private final String column_id = "id";
    private final String column_name = "name";
    private final String column_password = "password";

    private AdminDaoImpl adminDao = new AdminDaoImpl();

    /**
     * 验证管理员
     * @param admin
     * @return
     */
    public boolean checkAdmin(Admin admin){
        Connection conn = null;
        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            return adminDao.checkAdmin(conn,admin);

        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return false;
    }

    /**
     * 通过Id获取管理员
     * @param id
     * @return
     */
    public Admin getAdminById(long id){
        Connection conn = null;
        Admin admin = new Admin();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = adminDao.getAdminById(conn, id);

            while (res.next()){
                admin.setId(res.getLong(column_id));
                admin.setName(column_name);
                admin.setPassword(column_password);
            }

            return admin;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return admin;
    }

    /**
     * 通过账号获取管理员
     * @param name
     * @return
     */
    public Admin getAdminByName(String name){
        Connection conn = null;
        Admin admin = new Admin();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = adminDao.getAdminByName(conn, name);

            while (res.next()){
                admin.setId(res.getLong(column_id));
                admin.setName(column_name);
                admin.setPassword(column_password);
            }

            return admin;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return admin;
    }

    /**
     * 更新管理员信息
     * @param admin
     */
    public void update(Admin admin){
        Connection conn = null;
        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            adminDao.update(conn,admin);

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
} 