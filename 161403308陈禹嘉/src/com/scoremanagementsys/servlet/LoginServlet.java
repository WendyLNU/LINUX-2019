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

public class LoginServlet extends HttpServlet {
    private AdminService adminService = new AdminService();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("userName");
        String password = request.getParameter("password");
        String return_url = request.getParameter("return_url");

        PrintWriter out = response.getWriter();
        JSONObject jsonObject = new JSONObject();
        String login_flag = null;

        if (name != null && name != "" && password != null && password != "") {
            Admin admin = new Admin();
            admin.setName(name);
            admin.setPassword(password);
            boolean bool = adminService.checkAdmin(admin);

            if (bool) {
                login_flag = "success";

                request.getSession().setAttribute("admin", admin);
                request.getSession().setAttribute("login_flag", login_flag);

                jsonObject.put("return_url", return_url);
                jsonObject.put("login_flag", login_flag);
                out.print(jsonObject);
                out.close();

            } else {
                login_flag = "error";

                request.getSession().setAttribute("login_flag", login_flag);
                jsonObject.put("login_flag", login_flag);
                out.print(jsonObject);
                out.close();
            }
        } else {
            login_flag = "error";
            jsonObject.put("login_flag", login_flag);
            out.print(jsonObject);
            out.close();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}
