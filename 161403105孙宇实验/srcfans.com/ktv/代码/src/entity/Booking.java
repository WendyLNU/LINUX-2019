package entity;

import java.util.Date;

public class Booking {
	private int roomId;
	private String phoneNumber;
	private int hours;
	private Date bookTime;

	public Booking(int roomId, String phoneNumber, int hours) {
		this.roomId = roomId;
		this.phoneNumber = phoneNumber;
		this.hours = hours;
		this.bookTime = new Date();
	}

	public int getRoomId() {
		return roomId;
	}

	public String getRoomNumber() {
		String tmpStr = "0000"+roomId;
		return tmpStr.substring(tmpStr.length() - 4,tmpStr.length());
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public int getHours() {
		return hours;
	}

	public Date getBookTime() {
		return bookTime;
	}
}
