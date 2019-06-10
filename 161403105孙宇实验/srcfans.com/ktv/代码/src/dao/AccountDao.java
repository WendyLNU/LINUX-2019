package dao;

import java.util.ArrayList;
import java.util.List;

import entity.Account;

public class AccountDao {

	private List<Account> accountList;

	private static AccountDao accountDao;

	public static AccountDao instance() {
		if (accountDao == null) {
			accountDao = new AccountDao();
		}
		return accountDao;
	}

	public List<Account> getAccountList() {
		return accountList;
	}

	private AccountDao() {
		accountList = new ArrayList<Account>();
		accountList.add(new Account("admin", "admin"));
	}

	public boolean check(String userName, String password) {
		for (Account account : accountList) {
			if (account.getUserName().equals(userName)
					&& account.getPassword().equals(password)) {
				return true;
			}
		}
		return false;
	}

	public Object[][] getUserList() {
		Object[][] result = new Object[accountList.size()][2];

		Account account;
		for (int i = 0; i < accountList.size(); i++) {
			account = accountList.get(i);
			result[i][0] = account.getUserName();
			result[i][1] = account.getPassword();
		}

		return result;
	}

	public void addUser(String userName, String password) {
		accountList.add(new Account(userName, password));
	}
}
