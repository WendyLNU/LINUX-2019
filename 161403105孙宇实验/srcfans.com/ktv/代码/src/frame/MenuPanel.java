package frame;

import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JPanel;

import listener.MenuListener;

public class MenuPanel extends JPanel {
	/**
	 * MenuPanel
	 */
	private static final long serialVersionUID = -2703153422697822701L;
	private static MenuPanel menuPanel;

	public static MenuPanel instance() {
		if (menuPanel == null)
			menuPanel = new MenuPanel();
		return menuPanel;
	}

	public MenuPanel() {
		setOpaque(false);
		setLayout(new FlowLayout(FlowLayout.RIGHT, 0, 15));
		setPreferredSize(new Dimension(200, 600));

		ImageButton jbtRoomsBooked, jbtRoomsTaken, jbtExpiredRooms, jbtRooms, jbtRoomTypes, jbtFoods;
		jbtRoomsBooked = new ImageButton("menu", "已订房间", 16);
		jbtRoomsTaken = new ImageButton("menu", "已拿房间", 16);
		jbtExpiredRooms = new ImageButton("menu", "过期房间", 16);
		jbtRooms = new ImageButton("menu", "房间管理", 16);
		jbtRoomTypes = new ImageButton("menu", "房间类型", 16);
		jbtFoods = new ImageButton("menu", "食物管理", 16);

		jbtRoomsBooked.setPreferredSize(new Dimension(180, 50));
		jbtRoomsTaken.setPreferredSize(new Dimension(180, 50));
		jbtExpiredRooms.setPreferredSize(new Dimension(180, 50));
		jbtRooms.setPreferredSize(new Dimension(180, 50));
		jbtRoomTypes.setPreferredSize(new Dimension(180, 50));
		jbtFoods.setPreferredSize(new Dimension(180, 50));

		MenuListener menuListener = new MenuListener(jbtRoomsBooked,
				jbtRoomsTaken, jbtExpiredRooms, jbtRooms, jbtRoomTypes, jbtFoods);
		jbtRoomsBooked.addActionListener(menuListener);
		jbtRoomsTaken.addActionListener(menuListener);
		jbtExpiredRooms.addActionListener(menuListener);
		jbtRooms.addActionListener(menuListener);
		jbtRoomTypes.addActionListener(menuListener);
		jbtFoods.addActionListener(menuListener);

		add(jbtRoomsBooked);
		add(jbtRoomsTaken);
		add(jbtExpiredRooms);
		add(jbtRooms);
		add(jbtRoomTypes);
		add(jbtFoods);
	}
}