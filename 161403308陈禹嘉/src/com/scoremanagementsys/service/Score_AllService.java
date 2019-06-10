package com.scoremanagementsys.service;

import com.scoremanagementsys.dao.impl.Score_AllDaoImpl;
import com.scoremanagementsys.entity.Score;
import com.scoremanagementsys.entity.Score_All;
import com.scoremanagementsys.util.ConnectionFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * 学生成绩服务类
 */
public class Score_AllService {
    private Score_AllDaoImpl score_allDao = new Score_AllDaoImpl();
    private Connection conn;

    /**
     * 分页获取所有学生的所有成绩
     * @param searchContent
     * @param order
     * @param startIndex
     * @param pageSize
     * @return
     */
    public List<Score_All> getAllWithPage(String searchContent, String order, int startIndex, int pageSize){

        conn = ConnectionFactory.getInstance().makeConnection();
        List<Score_All> score_allList = new ArrayList<>();

        try {
            ResultSet res = score_allDao.getAllWithPage(conn,searchContent,order,startIndex,pageSize);

            while (res.next()){
                Score_All score_all = new Score_All();

                score_all.setId(res.getLong("id"));
                score_all.setS_number(res.getString("s_number"));
                score_all.setS_name(res.getString("s_name"));
                score_all.setS_gender(res.getString("s_gender"));
                score_all.setJava(res.getDouble("java"));
                score_all.setKotlin(res.getDouble("kotlin"));
                score_all.setPython(res.getDouble("python"));
                score_all.setPhp(res.getDouble("php"));
                score_all.setScore_sum(res.getDouble("score_sum"));
                score_all.setScore_avg(res.getDouble("score_avg"));

                score_allList.add(score_all);
            }

            return score_allList;

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return score_allList;
    }

    /**
     * 获取数据总数
     * @return
     */
    public int getRowTotal() {
        conn = ConnectionFactory.getInstance().makeConnection();

        int rowTotal = 0;

        try {
            ResultSet res = score_allDao.getRowTotal(conn);

            if(res.next()){
                rowTotal = res.getInt(1);
            }

            return rowTotal;

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return rowTotal;
    }

    /**
     * 添加或更新学生成绩
     * @param score
     */
    public void addOrUpdateStudentScore(Score score){
        conn = ConnectionFactory.getInstance().makeConnection();

        try {
            conn.setAutoCommit(false);
            score_allDao.addOrUpdateStudentScore(conn, score);
            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                conn.rollback();
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        }finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 删除学生成绩
     * @param studentNumber
     */
    public void deleteScores(String studentNumber){
        conn = ConnectionFactory.getInstance().makeConnection();

        try {
            score_allDao.deleteScores(conn, studentNumber);
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