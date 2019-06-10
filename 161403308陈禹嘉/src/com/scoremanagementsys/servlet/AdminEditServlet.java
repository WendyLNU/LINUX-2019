package com.scoremanagementsys.servlet;

import com.scoremanagementsys.entity.Admin;
import com.scoremanagementsys.service.AdminService;
import net.sf.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * 管理员修改密码
 */
public class AdminEditServlet extends HttpServlet {
    private AdminService adminService = new AdminService();
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String oldPassword = request.getParameter("oldPassword");
        String newPassword = request.getParameter("newPassword");

        int res = 0;
        JSONObject jsonObject = new JSONObject();

        if(name != null && !name.equals("")){
            Admin admin = new Admin();
            admin.setName(name);
            admin.setPassword(oldPassword);

            if (adminService.checkAdmin(admin)){
                admin.setPassword(newPassword);
                adminService.update(admin);

                res = 1;    //修改成功
            }else {
                res = 0;    //修改失败，密码错误！
            }
        }else {
            res = -1;   //修改失败，用户名为空！
        }
        //向前台页面输出
        jsonObject.put("res",res);
        PrintWriter out = response.getWriter();
        out.print(jsonObject);
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
