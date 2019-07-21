package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import dao.BookingDao;
import dao.RoomDao;
import entity.Booking;
import entity.Room;
import entity.RoomType;
import frame.BookRoomDialog;
import frame.MainPanel;

public class BookRoomListener implements ActionListener {
	private JComboBox jtfType;
	private JTextField jtfPhoneNumber;
	private JTextField jlbDuration;
	private JCheckBox jcbTake;
	private JButton cancel;

	public BookRoomListener(JComboBox jtfType, JTextField jtfPhoneNumber,
			JTextField jlbDuration, JCheckBox jcbTake,
			JButton cancel) {
		this.jtfType = jtfType;
		this.jtfPhoneNumber = jtfPhoneNumber;
		this.jlbDuration = jlbDuration;
		this.jcbTake = jcbTake;
		this.cancel = cancel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == cancel) {
			BookRoomDialog.instance().dispose();
		} else {
			if (jtfType.getSelectedIndex() < 0) {
				JOptionPane.showMessageDialog(null, "请选择房间类型！");
				return;
			}
			int roomType = ((RoomType) jtfType.getSelectedItem()).getId();
			if (jcbTake.isSelected()) {
				List<Room> roomList = RoomDao.instance().getRoomList();
				for (int i = 0; i < roomList.size(); i++) {
					if (roomList.get(i).getType() == roomType
							&& !roomList.get(i).isBooked()
							&& roomList.get(i).getStartTime() == null) {
						BookRoomDialog.instance().dispose();
						roomList.get(i).take(
								Integer.parseInt(jlbDuration.getText()));
						MainPanel.instance().showRoomTakenData();
						JOptionPane.showMessageDialog(null,
								"<html>开房成功！房间号： <b><font size=8>"
										+ roomList.get(i).getNumber()
										+ "</font></b>");
						return;
					}
				}
				JOptionPane.showMessageDialog(null, "已没有该类型的空房！", "提示",
						JOptionPane.ERROR_MESSAGE);
			} else {
				if (jtfPhoneNumber.getText().equals("")) {
					JOptionPane.showMessageDialog(null, "请输入电话号码！");
					return;
				}
				List<Room> roomList = RoomDao.instance().getRoomList();
				for (int i = 0; i < roomList.size(); i++) {
					if (roomList.get(i).getType() == roomType
							&& !roomList.get(i).isBooked()
							&& roomList.get(i).getStartTime() == null) {
						if (BookingDao.instance().getBooking(
								jtfPhoneNumber.getText()) != null) {
							JOptionPane.showMessageDialog(null, "该号码已预订过房间！",
									"提示", JOptionPane.ERROR_MESSAGE);
							return;
						}
						BookRoomDialog.instance().dispose();
						roomList.get(i).book();
						Booking booking = new Booking(roomList.get(i).getId(),
								jtfPhoneNumber.getText(),
								Integer.parseInt(jlbDuration.getText()));
						BookingDao.instance().addBooking(booking);
						MainPanel.instance().showRoomsBookedData();
						JOptionPane.showMessageDialog(null,
								"<html>订房成功！房间号： <b><font size=8>"
										+ roomList.get(i).getNumber()
										+ "</font></b>");
						return;
					}
				}
				JOptionPane.showMessageDialog(null, "已没有该类型的空房！", "提示",
						JOptionPane.ERROR_MESSAGE);
			}
		}
	}
}
