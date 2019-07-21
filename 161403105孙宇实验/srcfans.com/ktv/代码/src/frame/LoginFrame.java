package frame;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Toolkit;

import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import listener.LoginListener;

import com.sun.awt.AWTUtilities;

public class LoginFrame extends JFrame implements Runnable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7635382088464340846L;
	private static LoginFrame loginFrame;
	private static JDialog loginDialog;
	private JTextField jtfUserName;
	private JPasswordField jpfPassword;

	public static LoginFrame instance() {
		if (loginFrame == null)
			loginFrame = new LoginFrame();
		return loginFrame;
	}

	public static JDialog getLoginDialog() {
		if (loginDialog == null)
			loginDialog = new JDialog();
		return loginDialog;
	}

	public LoginFrame() {
		super("µÇÂ½ÏµÍ³");

		loginFrame = this;

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		loginDialog = new JDialog(this);
		jtfUserName = new JTextField();
		jpfPassword = new JPasswordField();
		final ImageButton ensure = new ImageButton("ensure");
		final ImageButton cancel = new ImageButton("cancel");

		loginDialog.setSize(420, 380);
		loginDialog.setLayout(null);
		loginDialog.setUndecorated(true);
		loginDialog.setLocationRelativeTo(null);

		JLabel loginBg = new JLabel(new ImageIcon(this.getClass().getResource(
				"/images/login.png")));
		loginBg.setBounds(0, 0, (int) loginDialog.getWidth(),
				(int) loginDialog.getHeight());
		loginDialog.add(jtfUserName);
		loginDialog.add(jpfPassword);
		loginDialog.add(ensure);
		loginDialog.add(cancel);
		loginDialog.add(loginBg);
		AWTUtilities.setWindowOpaque(loginDialog, false);

		jtfUserName.setBorder(null);
		jtfUserName.setOpaque(false);
		jtfUserName.setForeground(Color.LIGHT_GRAY);
		jpfPassword.setBorder(null);
		jpfPassword.setOpaque(false);
		jpfPassword.setForeground(Color.LIGHT_GRAY);

		jtfUserName.setBounds(40, 110, 340, 50);
		jpfPassword.setBounds(40, 210, 340, 50);
		ensure.setBounds(75, 290, 110, 45);
		cancel.setBounds(235, 290, 110, 45);

		jtfUserName.setSelectionColor(Color.GRAY);
		jpfPassword.setSelectionColor(Color.GRAY);
		jtfUserName.setFont(new Font("Î¢ÈíÑÅºÚ", Font.PLAIN, 24));
		jpfPassword.setFont(new Font("Î¢ÈíÑÅºÚ", Font.PLAIN, 24));

		LoginListener loginListener = new LoginListener(jtfUserName,
				jpfPassword, ensure, cancel);
		jtfUserName.addActionListener(loginListener);
		jpfPassword.addActionListener(loginListener);
		ensure.addActionListener(loginListener);
		cancel.addActionListener(loginListener);

		((JPanel) this.getContentPane()).setOpaque(false);
		BackgroundPanel background = new BackgroundPanel();
		getLayeredPane().add(background, new Integer(Integer.MIN_VALUE));

		setSize(screenSize);
		setUndecorated(true);
		setBackground(Color.BLACK);
		setLocationRelativeTo(null);
		setExtendedState(Frame.MAXIMIZED_BOTH);
		setMinimumSize(new Dimension(1024, 768));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setIconImage(new ImageIcon(this.getClass().getResource(
				"/images/icon.png")).getImage());
	}

	public void open() {
		jtfUserName.setText("");
		jpfPassword.setText("");
		jtfUserName.requestFocus();

		setVisible(true);
		loginDialog.setVisible(true);
		if(LoadingFrame.instance().isVisible())
			LoadingFrame.instance().dispose();
	}

	public void easeOpacity(float opacity) {
		if (opacity <= 0) {
			opacity = 0;
			return;
		} else if (opacity > 1) {
			opacity = 1;
		}
		AWTUtilities.setWindowOpacity(loginDialog, opacity);
	}

	public void showMainFrame() {
		MainFrame.instance().open();
	}

	public void exit() {
		System.exit(0);
	}

	@Override
	public void run() {
		instance().open();
	}
}
