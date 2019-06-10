package frame;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Toolkit;

import javax.swing.JPanel;

import dao.ConfigDao;

public class BackgroundPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5419654428856923445L;

	public BackgroundPanel() {
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds(0, 0, (int) screenSize.getWidth(),
				(int) screenSize.getHeight());
	}

	public void paint(Graphics g) {
		super.paint(g);
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds(0, 0, (int) screenSize.getWidth(),
				(int) screenSize.getHeight());
		String copyright = ConfigDao.instance().getConfig().getCopyright();
		g.drawImage(ConfigDao.instance().getConfig().getBackgroundImage()
				.getImage(), 0, 0, getWidth(), getHeight(), this);
		g.setFont(new Font("ºÚÌå", Font.PLAIN, 16));
		g.setColor(Color.GRAY);
		g.drawString(copyright, 10, getHeight() - 10);
		MainFrame.instance().repaint();
	}
}
