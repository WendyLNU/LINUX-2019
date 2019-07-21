package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import dao.BookingDao;
import dao.RoomDao;
import entity.Booking;
import entity.Room;
import frame.MainPanel;

public class TakeRoomListener implements ActionListener {
	private JDialog takeRoomDialog;
	private JTextField jtfPhoneNumber;
	private JButton ensure;
	private JButton cancel;

	public TakeRoomListener(JDialog getRoomDialog, JTextField jtfPhoneNumber,
			JButton ensure, JButton cancel) {
		super();
		this.takeRoomDialog = getRoomDialog;
		this.jtfPhoneNumber = jtfPhoneNumber;
		this.ensure = ensure;
		this.cancel = cancel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == ensure || e.getSource() == jtfPhoneNumber) {
			if (jtfPhoneNumber.getText().equals("")) {
				JOptionPane.showMessageDialog(null, "请输入电话号码！");
				return;
			}
			Booking booking = BookingDao.instance().getBooking(
					jtfPhoneNumber.getText().trim());
			if (booking != null) {
				Room room = RoomDao.instance().getRoom(booking.getRoomId());
				if(room != null){
					room.take(booking.getHours());
				}
				takeRoomDialog.dispose();
				BookingDao.instance().removeBooking(booking);
				MainPanel.instance().showRoomTakenData();
				JOptionPane.showMessageDialog(null,
						"<html>拿房成功！房间号： <b><font size=8>" + booking.getRoomNumber() + "</font></b>");
			} else {
				JOptionPane.showMessageDialog(null, "该号码未订房，请确认！", "提示",
						JOptionPane.ERROR_MESSAGE);
			}
		} else if (e.getSource() == cancel)
			takeRoomDialog.dispose();
	}
}
