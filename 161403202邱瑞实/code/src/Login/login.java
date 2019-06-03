package Login;

public class login {
	private String LoginName;
	private String LoginPwd;
	public String getLoginName() {
		return LoginName;
	}
	public String getLoginPwd() {
		return LoginPwd;
	}
	public login(String loginName,String loginPwd) {
		super();
		LoginName=loginName;
		LoginPwd=loginPwd;
	}
	public login(String loginName) {
		super();
		LoginName = loginName;
	}
	public login() {
		super();
	}
	

}
