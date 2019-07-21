package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.SimpleDateFormat;

import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.table.DefaultTableModel;

import dao.BookingDao;
import dao.FoodDao;
import dao.RoomDao;
import dao.RoomTypeDao;
import entity.Booking;
import entity.Food;
import entity.Room;
import entity.RoomType;
import frame.AddFoodDialog;
import frame.AddRoomDialog;
import frame.AddRoomTypeDialog;
import frame.BuyFoodDialog;
import frame.DataTable;
import frame.EditRoomTypeDialog;
import frame.MainPanel;

public class TableListener extends MouseAdapter implements ActionListener {
	private DataTable table;
	private JPopupMenu menu;

	public TableListener(JPopupMenu menu) {
		this.table = MainPanel.instance().getTable();
		this.menu = menu;
	}

	public void mousePressed(MouseEvent e) {
		if (table.getSelectedRow() < 0) {
			int modifiers = e.getModifiers();
			modifiers -= MouseEvent.BUTTON3_MASK;
			modifiers |= MouseEvent.BUTTON1_MASK;
			MouseEvent ne = new MouseEvent(e.getComponent(), e.getID(),
					e.getWhen(), modifiers, e.getX(), e.getY(),
					e.getClickCount(), false);
			table.dispatchEvent(ne);
		}
	}

	public void mouseReleased(MouseEvent e) {
		if ((e.getModifiers() & MouseEvent.BUTTON3_MASK) != 0
				&& !e.isControlDown() && !e.isShiftDown()) {
			menu.show(table, e.getX(), e.getY());
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (table.getSelectedRow() < 0)
			return;
		String strAction = ((JMenuItem) e.getSource()).getText().trim();
		if (!isSure("<html>您确定要进行<b><font size=6> " + strAction
				+ " </font></b>操作吗？"))
			return;
		if (strAction.equals("添加酒水")) {
			BuyFoodDialog.instance().open();
			return;
		} else if (strAction.equals("房间结算")) {
			String tmpStr = getSelectedValue(0);
			if (tmpStr == null)
				return;
			Room room = RoomDao.instance().getRoom(Integer.parseInt(tmpStr));
			removeSelectedRow();
			JOptionPane.showMessageDialog(null,
					"<html>结算成功！总消费<b><font size=8>  " + room.getMoney()
							+ " </font></b>元。");
			room.end();
			return;
		} else if (strAction.equals("房间加钟")) {
			String tmpStr = getSelectedValue(0);
			if (tmpStr == null)
				return;
			DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
			Room room = RoomDao.instance().getRoom(Integer.parseInt(tmpStr));
			room.addHours();
			SimpleDateFormat formatter = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
			tableModel.setValueAt(room.getMoney(), table.getSelectedRow(), 2);
			tableModel.setValueAt(formatter.format(room.getEndTime()),
					table.getSelectedRow(), 4);
		} else if (strAction.equals("开通房间")) {
			String tmpStr = getSelectedValue(2);
			if (tmpStr == null)
				return;
			BookingDao bookingDao = BookingDao.instance();
			Booking booking = bookingDao.getBooking(tmpStr);
			RoomDao.instance().getRoom(booking.getRoomId())
					.take(booking.getHours());
			bookingDao.removeBooking(booking);
			removeSelectedRow();
			JOptionPane.showMessageDialog(
					null,
					"<html>开通房间成功！房间号：<b><font size=8>  "
							+ booking.getRoomNumber() + " </font></b>");
			return;
		} else if (strAction.equals("删除订单")) {
			BookingDao bookingDao = BookingDao.instance();
			for (int row : table.getSelectedRows()) {
				Booking booking = bookingDao.getBooking(getValue(row, 2));
				bookingDao.removeBooking(booking);
			}
			removeSelectedRows();
		} else if (strAction.equals("添加房间")) {
			AddRoomDialog.instance().open(false);
			return;
		} else if (strAction.equals("批量添加")) {
			AddRoomDialog.instance().open(true);
			return;
		} else if (strAction.equals("删除房间")) {
			RoomDao roomDao = RoomDao.instance();
			for (int row : table.getSelectedRows()) {
				Room room = roomDao.getRoom(Integer.parseInt(getValue(row, 0)));
				roomDao.removeRoom(room);
			}
			removeSelectedRows();
		} else if (strAction.equals("添加食品")) {
			AddFoodDialog.instance().open();
			return;
		} else if (strAction.equals("删除食品")) {
			FoodDao foodDao = FoodDao.instance();
			for (int row : table.getSelectedRows()) {
				Food food = foodDao.getFoodbyId(Integer.parseInt(getValue(row,
						0)));
				if (food == null)
					return;
				foodDao.removeFood(food);
			}
			removeSelectedRows();
		} else if (strAction.equals("添加类型")) {
			AddRoomTypeDialog.instance().open();
			return;
		} else if (strAction.equals("编辑类型")) {
			RoomTypeDao roomTypeDao = RoomTypeDao.instance();
			RoomType roomType = roomTypeDao.getRoomTypebyId(Integer
					.parseInt(getValue(table.getSelectedRow(), 0)));
			if (roomType == null)
				return;
			EditRoomTypeDialog.instance().open(roomType);
			return;
		} else if (strAction.equals("删除类型")) {
			RoomTypeDao roomTypeDao = RoomTypeDao.instance();
			for (int row : table.getSelectedRows()) {
				RoomType roomType = roomTypeDao.getRoomTypebyId(Integer
						.parseInt(getValue(row, 0)));
				if (roomType == null)
					return;
				roomTypeDao.removeRoomType(roomType);
			}
			removeSelectedRows();
		}
		JOptionPane.showMessageDialog(null, strAction + "成功！");
	}

	private boolean isSure(String msg) {
		return (JOptionPane.showConfirmDialog(null, msg, "消息",
				JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION);
	}

	private String getValue(int row, int column) {
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		return tableModel.getValueAt(row, column).toString();
	}

	private String getSelectedValue(int column) {
		if (table.getSelectedRow() < 0)
			return null;
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		return tableModel.getValueAt(table.getSelectedRow(), column).toString();
	}

	private void removeSelectedRow() {
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.removeRow(table.getSelectedRow());
	}

	private void removeSelectedRows() {
		if (table.getSelectedRow() < 0)
			return;
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		boolean isEndSelect = false;
		if (table.getSelectedRows()[table.getSelectedRows().length - 1] == tableModel
				.getRowCount() - 1) {
			isEndSelect = true;
		}
		while (table.getSelectedRow() >= 0) {
			tableModel.removeRow(table.getSelectedRow());
		}
		if (isEndSelect && tableModel.getRowCount() > 0) {
			tableModel.removeRow(tableModel.getRowCount() - 1);
		}
		if (tableModel.getRowCount() <= 0) {
			MainPanel.instance().refresh();
		}
	}
}
