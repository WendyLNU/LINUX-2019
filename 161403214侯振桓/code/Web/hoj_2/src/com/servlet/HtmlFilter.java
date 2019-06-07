package com.servlet;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet Filter implementation class HtmlFilter
 */
@WebFilter(filterName="/HtmlFilter",urlPatterns="/*")
public class HtmlFilter implements Filter {

    /**
     * Default constructor. 
     */
    public HtmlFilter() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest req, ServletResponse res,
			FilterChain chain) throws IOException, ServletException {
			HttpServletRequest request;
			HttpServletResponse response;

			try {
			request = (HttpServletRequest) req;
			response = (HttpServletResponse) res;
			} catch (ClassCastException e) {
			throw new ServletException("non-HTTP request or response");
			}
			HtmlHttpServletRequest hrequest = new HtmlHttpServletRequest(request);
			chain.doFilter(hrequest, response);
}


	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
		System.out.println("filter start!!");
	}

}
class HtmlHttpServletRequest extends HttpServletRequestWrapper{
	
	public HtmlHttpServletRequest(HttpServletRequest request) {
			super(request);
	}
	public String getParameter(String name) {
		String value = super.getParameter(name);
		if(value==null)
		return value;
		value = filter(value);
		return value;
	}
	public String getParameterNoFilter(String name){
		return super.getParameter(name);
	}
	private String filter(String message) {
	if (message == null) return (null);
	
	char content[] = new char[message.length()];
	message.getChars(0, message.length(), content, 0);
	StringBuffer result = new StringBuffer(content.length + 50);
	for (int i = 0; i < content.length; i++) {
	switch (content[i]) {
	case '<':
	result.append("&lt;");
	break;
	case '>':
	result.append("&gt;");
	break;
	case '&':
	result.append("&amp;");
	break;
	case '"':
	result.append("&quot;");
	break;
	default:
	result.append(content[i]);
	}
	}
	return (result.toString());
	}
}
