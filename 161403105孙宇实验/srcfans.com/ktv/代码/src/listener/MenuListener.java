package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import frame.MainPanel;

public class MenuListener implements ActionListener {

	private JButton jbtRoomsBooked, jbtRoomsTaken, jbtExpiredRooms, jbtRooms,
			jbtRoomTypes, jbtFoods;

	public MenuListener(JButton jbtRoomsBooked, JButton jbtRoomsTaken,
			JButton jbtExpiredRooms, JButton jbtRooms, JButton jbtRoomTypes,
			JButton jbtFoods) {
		this.jbtRoomsBooked = jbtRoomsBooked;
		this.jbtRoomsTaken = jbtRoomsTaken;
		this.jbtExpiredRooms = jbtExpiredRooms;
		this.jbtRooms = jbtRooms;
		this.jbtRoomTypes = jbtRoomTypes;
		this.jbtFoods = jbtFoods;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == jbtRoomsBooked) {
			MainPanel.instance().showRoomsBookedData();
		} else if (e.getSource() == jbtRoomsTaken) {
			MainPanel.instance().showRoomTakenData();
		} else if (e.getSource() == jbtExpiredRooms) {
			MainPanel.instance().showExpiredRoomsData();
		} else if (e.getSource() == jbtRooms) {
			MainPanel.instance().showAllRoomsData();
		} else if (e.getSource() == jbtRoomTypes) {
			MainPanel.instance().showRoomTypesData();
		} else if (e.getSource() == jbtFoods) {
			MainPanel.instance().showFoodsData();
		}
	}

}
