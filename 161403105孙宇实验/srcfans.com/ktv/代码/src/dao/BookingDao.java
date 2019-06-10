package dao;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import entity.Booking;

public class BookingDao {
	private List<Booking> bookingList;
	private static BookingDao bookingDao;

	public static BookingDao instance() {
		if (bookingDao == null)
			bookingDao = new BookingDao();
		return bookingDao;
	}

	public BookingDao() {
		bookingList = new ArrayList<Booking>();
	}

	public void addBooking(Booking booking) {
		bookingList.add(booking);
	}

	private Object[] formatData(Booking booking) {
		Object[] result = new Object[5];
		result[0] = booking.getRoomNumber();
		result[1] = RoomTypeDao.instance().getNamebyId(
				RoomDao.instance().getRoom(booking.getRoomId()).getType());
		result[2] = booking.getPhoneNumber();
		result[3] = booking.getHours();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		result[4] = (booking.getBookTime() == null) ? "" : formatter
				.format(booking.getBookTime());
		return result;
	}

	public Object[][] getBookingsData() {
		Object[][] result = new Object[BookingDao.instance().getBookingList()
				.size()][5];
		int i = 0;
		for (Booking booking : bookingList) {
			result[i] = formatData(booking);
			i++;
		}
		return result;
	}

	public List<Booking> getBookingList() {
		return bookingList;
	}

	public Booking getBooking(String phoneNumber) {
		for (Booking booking : bookingList) {
			if (booking.getPhoneNumber().equals(phoneNumber)) {
				return booking;
			}
		}
		return null;
	}

	public void removeBooking(Booking booking) {
		RoomDao.instance().getRoom(booking.getRoomId()).setBooked(false);
		bookingList.remove(booking);
	}
}
