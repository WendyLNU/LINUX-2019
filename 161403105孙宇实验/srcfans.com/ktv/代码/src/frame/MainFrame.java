package frame;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainFrame extends JFrame implements Runnable {
	/**
	 * MainFrame
	 */
	private static final long serialVersionUID = -5988513125942516733L;
	private static MainFrame mainFrame;

	public static MainFrame instance() {
		if (mainFrame == null)
			mainFrame = new MainFrame();
		return mainFrame;
	}

	public MainFrame() {
		setTitle("KTV管理系统");
		mainFrame = this;
		setUndecorated(true);
		// setAlwaysOnTop(true);
		setSize(Toolkit.getDefaultToolkit().getScreenSize());
		setMinimumSize(new Dimension(1024, 768));

		Container container = getContentPane();
		container.setLayout(new BorderLayout());
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		container.add(new OptionPanel(), BorderLayout.NORTH);
		container.add(new MenuPanel(), BorderLayout.WEST);
		container.add(new MainPanel(), BorderLayout.CENTER);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setIconImage(new ImageIcon(this.getClass().getResource(
				"/images/icon.png")).getImage());

		((JPanel) this.getContentPane()).setOpaque(false);
		BackgroundPanel background = new BackgroundPanel();
		getLayeredPane().add(background, new Integer(Integer.MIN_VALUE));
	}

	public void open() {
		setVisible(true);
		LoginFrame.instance().setVisible(false);
		LoginFrame.getLoginDialog().setVisible(false);
	}

	@Override
	public void run() {
		instance();
	}
}
