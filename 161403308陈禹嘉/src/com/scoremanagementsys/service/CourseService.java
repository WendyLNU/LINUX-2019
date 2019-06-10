package com.scoremanagementsys.service;

import com.scoremanagementsys.dao.impl.CourseDaoImpl;
import com.scoremanagementsys.entity.Course;
import com.scoremanagementsys.util.ConnectionFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CourseService {
    private CourseDaoImpl courseDao = new CourseDaoImpl();

    private final String column_id = "id";
    private final String column_number = "number";
    private final String column_name = "name";

    private Connection conn = null;

    /**
     * 验证课程号是否已存在
     * @param courseNumber
     * @return
     */
    public boolean checkCourseByNumber(String courseNumber) {

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            return courseDao.checkCourseByNumber(conn, courseNumber);

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
     * 添加课程
     * @param course
     */
    public void add(Course course) {
        try {
            conn = ConnectionFactory.getInstance().makeConnection();
            courseDao.add(conn, course);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 更新课程信息
     * @param course
     */
    public void update(Course course) {
        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            courseDao.update(conn, course);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 删除课程
     * @param course
     */
    public void delete(Course course) {
        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            courseDao.delete(conn, course);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 获取课程对象，id
     * @param id
     * @return
     */
    public Course getCourseById(long id) {
        Course course = new Course();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = courseDao.getCourseById(conn, id);
            while (res.next()) {
                course.setId(res.getLong(column_id));
                course.setName(res.getString(column_name));
                course.setNumber(res.getString(column_number));
            }
            return course;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return course;
    }
    /**
     * 获取课程对象，通过name
     * @return
     */
    public Course getCourseByName(String courseName) {
        Course course = new Course();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = courseDao.getCourseByName(conn, courseName);
            while (res.next()) {
                course.setId(res.getLong(column_id));
                course.setName(res.getString(column_name));
                course.setNumber(res.getString(column_number));
            }
            return course;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return course;
    }

    /**
     * 获取课程，课程号
     * @param courseNumber
     * @return
     */
    public Course getCourseByNumber(String courseNumber) {
        Course course = new Course();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = courseDao.getCourseByNumber(conn, courseNumber);
            while (res.next()) {
                course.setId(res.getLong(column_id));
                course.setName(res.getString(column_name));
                course.setNumber(res.getString(column_number));
            }
            return course;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return course;
    }

    /**
     * 分页获取所有课程
     * @param startIndex
     * @param pageSize
     * @return
     */
    public List<Course> getAllWithPage(int startIndex, int pageSize) {
        List<Course> courseList = new ArrayList<>();

        try {
            conn = ConnectionFactory.getInstance().makeConnection();

            ResultSet res = courseDao.getAllWithPage(conn, startIndex, pageSize);

            while (res.next()) {
                Course course = new Course();

                course.setId(res.getLong(column_id));
                course.setName(res.getString(column_name));
                course.setNumber(res.getString(column_number));

                courseList.add(course);
            }

            return courseList;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return courseList;
    }

    /**
     * 获取课程总数
     * @return
     */
    public int getRowTotal() {
        conn = ConnectionFactory.getInstance().makeConnection();
        int rowTotal = 0;

        try {

            ResultSet res = courseDao.getRowTotal(conn);

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