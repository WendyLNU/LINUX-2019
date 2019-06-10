package com.scoremanagementsys.util;

import java.util.List;

public class PageBean<obj> {
//    已知数据
    private int thisPage;   //当前页，从请求那边传过来的
    private int pageSize;   //每页显示的数据数目
    private int dataTotal;  //总的记录数，从数据库查询获取

//    需要计算的数据
    private int pageTotal;  //总的页数，通过dataTotal/pageDataCount获取
    private int startIndex; //查询开始的索引，配合pageSize可以得出每页需要查询哪些数据

//    将每页要显示的数据放在list集合中
    private List<obj> list;

//    分页导航显示的页数，如1,2,3,4,5页，start为1，end为5，通过计算得出
    private int start;
    private int end;

//    通过thisPage、pageSize、dataTotal计算得出pageTotal、tartIndex
//    在构造方法中直接计算获取
    public PageBean(int thisPage, int pageSize, int dataTotal){
        this.thisPage = thisPage;
        this.pageSize = pageSize;
        this.dataTotal = dataTotal;

//        计算总页数
        if( dataTotal % pageSize == 0){
//            正好整除，说明每页正好显示pageSize条数据，没有多余
            this.pageTotal = dataTotal / pageSize;
        }else {
//            不整除，说明有多余数据需要追加一页来显示
            this.pageTotal = dataTotal / pageSize + 1;
        }

//        计算开始查询的索引
        this.startIndex = (thisPage - 1)*pageSize;

//        默认显示前5页
        this.start = 1;
        this.end = 5;

        if ( pageTotal <= 5){
//            若总页数小于5，则end为总页数的值
            this.end = this.pageTotal;
        }else {
//            若总页数大于5，则需要根据当前页来判断start和end的值
            this.start = thisPage - 2;
            this.end = thisPage + 2;

//            不符合上述规则的情况，如 当前页为（倒数）第一页或（倒数）第二页
            if( this.start < 2){
                this.start = 1;
                this.end = 5;
            }

            if( this.end > this.pageTotal - 2){
                this.end = pageTotal;
                this.start = end - 5;
            }
        }
    }

    public int getThisPage() {
        return thisPage;
    }

    public void setThisPage(int thisPage) {
        this.thisPage = thisPage;
    }

    public int getPageSize() {
        return pageSize;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public int getDataTotal() {
        return dataTotal;
    }

    public void setDataTotal(int dataTotal) {
        this.dataTotal = dataTotal;
    }

    public int getPageTotal() {
        return pageTotal;
    }

    public void setPageTotal(int pageTotal) {
        this.pageTotal = pageTotal;
    }

    public int getStartIndex() {
        return startIndex;
    }

    public void setStartIndex(int startIndex) {
        this.startIndex = startIndex;
    }

    public List<obj> getList() {
        return list;
    }

    public void setList(List<obj> list) {
        this.list = list;
    }

    public int getStart() {
        return start;
    }

    public void setStart(int start) {
        this.start = start;
    }

    public int getEnd() {
        return end;
    }

    public void setEnd(int end) {
        this.end = end;
    }
}