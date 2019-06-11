package com.scoremanagementsys.filter;

import javax.servlet.*;
import java.io.IOException;

public class EncodingFilter implements Filter {
    private String charEncoding = null;

    public void init(FilterConfig config) throws ServletException {

        //从配置文件中获取默认编码
        charEncoding = config.getInitParameter("encoding");
        if(charEncoding == null){
            throw new ServletException("EncodingFilter中的编码设置为空！！！");
        }
    }

    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain) throws ServletException, IOException {

        //        如果请求的编码与设置的默认编码不一致，则以默认设置的为准
        if(!charEncoding.equals(req.getCharacterEncoding())){
//            设置请求编码
            req.setCharacterEncoding(charEncoding);
        }
//        设置响应编码
        resp.setCharacterEncoding(charEncoding);

        chain.doFilter(req, resp);
    }

    public void destroy() {
    }

}
