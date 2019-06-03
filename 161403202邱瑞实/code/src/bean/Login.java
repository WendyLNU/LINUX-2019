package bean;
import java.sql.*;
import bean.LoginCheck;
 public class Login {
	 private String username = null;
	    private String password = null;
	    public String getUsername() {
	        return username;
	    }
	    public void setUsername(String username) {
	        this.username = username;
	    }
	    public String getPassword() {
	        return password;
	    }
	    public void setPassword(String password) {
	        this.password = password;
	    }
	    public Login() {
	        super();
	        // TODO Auto-generated constructor stub
	    }


public String check() {
	String message="";
	System.out.println(getUsername());             
	System.out.println(getPassword());
	try{
		if(username!=null &&password!=null) {
			Connection conn=LoginCheck.getConnection();
			Statement stmt=LoginCheck.GetStatement(conn);
			String sql="select count(0)from user where user";
			sql+="id='"+username+"'and password";
			sql+="='"+password+"'";
			ResultSet rs =stmt.executeQuery(sql);
			if(rs.next()) {
				//int isUser=rs.getInt(1);
				//if(0==isUser) {message="not ok";}
				message="ok";
			
		}}else {
			
			message="sb";}
	}catch(Exception e) {
		e.printStackTrace();
	}
	return message;
}
}
