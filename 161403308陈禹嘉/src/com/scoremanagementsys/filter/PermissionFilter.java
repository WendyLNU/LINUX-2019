package com.scoremanagementsys.filter;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class PermissionFilter implements Filter {

    public void init(FilterConfig config) throws ServletException {

    }

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws ServletException, IOException {

        HttpServletRequest req = (HttpServletRequest) request;
        HttpServletResponse resp = (HttpServletResponse) response;

        String servletPath = req.getServletPath();      //获取servlet的地址
        HttpSession session = req.getSession();         //获取session对象
        String login_flag = (String) session.getAttribute("login_flag");    //获取session对象的值
        StringBuffer server = req.getRequestURL();      //获取请求RUL

            //  放行样式文件和js文件
            if (servletPath != null &&  servletPath.equals("/login.jsp") || servletPath.equals("/loginServlet")
                    || server.toString().endsWith(".js") || server.toString().endsWith(".imgs")
                    || server.toString().endsWith(".css")|| server.toString().contains("fonts")
                    ) {

            chain.doFilter(req, resp);
        } else {
            if (login_flag != null && login_flag.equals("success")) {
                chain.doFilter(req, resp);
            } else if (login_flag != null && login_flag.equals("error")) {
                RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
                rd.forward(req, resp);
            } else {

                RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
                rd.forward(req, resp);
            }
        }
    }

    public void destroy() {
    }

}
