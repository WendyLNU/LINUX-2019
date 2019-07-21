package bean;
import java.sql.*;
public class LoginCheck {
     public static Connection getConnection() {
    	
    	
    		    String url="jdbc:mysql://localhost:3306/base1?serverTimezone=GMT%2B8&useUnicode=true&characterEncoding=utf-8";  //JDBC��URL  
    		    //����DriverManager�����getConnection()���������һ��Connection����
    		    Connection conn=null;
    		    try {
    		    	 Class.forName("com.mysql.cj.jdbc.Driver");
    		      conn = DriverManager.getConnection(url,  "root","www.lsl.com");
    		      //����һ��Statement����
    		
    		      System.out.print("�ɹ����ӵ����ݿ⣡");
    		    
    		    } catch (Exception e){
    		      e.printStackTrace();
    		    }
    		    
    		    return conn;
    		    
    		  }
    		public static Statement GetStatement(Connection conn) {
    			Statement stmt=null;
    			try {
    				if(conn!=null) {
    					stmt=conn.createStatement();
    				}
    			}catch(Exception e) {
    				e.printStackTrace();
    			}
    			return stmt;
    		}
    	 public static ResultSet getResultSet(Statement stmt,String sql) {
    		 ResultSet rs=null;
    		 try {
    			 if(stmt!=null) {
    				 rs=stmt.executeQuery(sql);
    			 }
    		 }catch(Exception e) {
    			 e.printStackTrace();
    		 }
    		 return rs;
    	 }
public static void closeConn(Connection conn) {

	try {
		if(conn!=null) {
			conn.close();
			conn=null;
		}
	}catch(Exception e) {
		e.printStackTrace();
	}
}
public static void closeStmt(Statement stmt) {
	try {
		if(stmt!=null) {
			stmt.close();
			stmt=null;
		}
	}catch(Exception e) {
		e.printStackTrace();
	}
	
}
public static void closeRs(ResultSet rs) {
	try {
		if(rs!=null) {
			rs.close();
			rs=null;
		}
	}catch(Exception e) {
		e.printStackTrace();
	}
}
     }
     
