package main;

import java.awt.Font;
import java.util.Enumeration;
//www.srcfans.com
import javax.swing.UIManager;

import dao.ConfigDao;
import frame.LoadingFrame;
import frame.LoginFrame;
import frame.MainFrame;

public class Main {

	public static void main(String[] args) {
		new Thread(new LoadingFrame()).start();
		// …Ë÷√ƒ¨»œ◊÷ÃÂ
		Font font = ConfigDao.instance().getConfig().getFont();
		Enumeration<Object> keys = UIManager.getDefaults().keys();
		while (keys.hasMoreElements()) {
			Object key = keys.nextElement();
			Object value = UIManager.get(key);
			if (value instanceof javax.swing.plaf.FontUIResource)
				UIManager.put(key, font);
		}
		new Thread(new LoginFrame()).start();
		try {
			UIManager
					.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch (Exception e) {
		}
		new Thread(new MainFrame()).start();
	}
}
