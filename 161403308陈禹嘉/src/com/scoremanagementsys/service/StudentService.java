package com.scoremanagementsys.service;

import com.scoremanagementsys.dao.impl.StudentDaoImpl;
import com.scoremanagementsys.entity.Score_All;
import com.scoremanagementsys.entity.Student;
import com.scoremanagementsys.util.ConnectionFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * 学生服务类
 */
public class StudentService {
    private StudentDaoImpl studentDao = new StudentDaoImpl();
    private Score_AllService score_allService = new Score_AllService();

    private final String column_id = "id";
    private final String column_number = "number";
    private final String column_name = "name";
    private final String column_gender = "gender";

    private Connection conn;

    /**
     * 通过学号验证学生
     * @param studentNumber
     * @return
     */
    public boolean checkStudentByNumber(String studentNumber) {
        conn = ConnectionFactory.getInstance().makeConnection();

        try {
            return studentDao.checkStudentByNumber(conn, studentNumber);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return false;
    }

    /**
     * 添加学生
     * @param student
     */
    public void add(Student student) {

        if (!checkStudentByNumber(student.getNumber())) {
            conn = ConnectionFactory.getInstance().makeConnection();

            try {
                conn.setAutoCommit(false);

                studentDao.add(conn, student);

                conn.commit();
            } catch (SQLException e) {
                e.printStackTrace();
                try {
                    conn.rollback();
                } catch (SQLException e1) {
                    e1.printStackTrace();
                }
            } finally {
                try {
                    conn.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * 更新学生信息
     * @param student
     */
    public void update(Student student) {
        conn = ConnectionFactory.getInstance().makeConnection();
        try {
            conn.setAutoCommit(false);
            studentDao.update(conn, student);
            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                conn.rollback();
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 删除学生
     * @param student
     */
    public void delete(Student student) {
        conn = ConnectionFactory.getInstance().makeConnection();
        try {
            conn.setAutoCommit(false);
            studentDao.delete(conn, student);
            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                conn.rollback();
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 通过id获取学生对象
     * @param id
     * @return
     */
    public Student getStudentById(long id) {
        conn = ConnectionFactory.getInstance().makeConnection();
        Student student = new Student();

        try {
            ResultSet res = studentDao.getStudentById(conn, id);

            while (res.next()) {
                student.setId(res.getLong(column_id));
                student.setNumber(res.getString(column_number));
                student.setName(res.getString(column_name));
                student.setGender(res.getString(column_gender));
            }

            return student;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return student;
    }

    /**
     * 通过学号获取学生对象
     * @param studentNumber
     * @return
     */
    public Student getStudentByStudentNumber(String studentNumber) {
        conn = ConnectionFactory.getInstance().makeConnection();
        Student student = new Student();

        try {
            ResultSet res = studentDao.getStudentByStudentNumber(conn, studentNumber);

            while (res.next()) {

                student.setId(res.getLong(column_id));
                student.setNumber(res.getString(column_number));
                student.setName(res.getString(column_name));
                student.setGender(res.getString(column_gender));
            }

            return student;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return student;
    }

    /**
     * 分页获取所有学生
     * @param searchContent
     * @param startIndex
     * @param pageSize
     * @return
     */
    public List<Student> getAllWithPage(String searchContent, int startIndex, int pageSize) {
        conn = ConnectionFactory.getInstance().makeConnection();
        List<Student> studentList = new ArrayList<>();

        try {
            ResultSet res = studentDao.getAllWithPage(conn,searchContent, startIndex, pageSize);

            while (res.next()) {
                Student student = new Student();

                student.setId(res.getLong(column_id));
                student.setNumber(res.getString(column_number));
                student.setName(res.getString(column_name));
                student.setGender(res.getString(column_gender));

                studentList.add(student);
            }

            return studentList;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return studentList;
    }

    /**
     * 获取学生总数
     * @return
     */
    public int getRowTotal() {
        conn = ConnectionFactory.getInstance().makeConnection();
        int rowTotal = 0;

        try {

            ResultSet res = studentDao.getRowTotal(conn);

            if (res.next()){
                rowTotal = res.getInt(1);
            }

            return rowTotal;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rowTotal;
    }
} 