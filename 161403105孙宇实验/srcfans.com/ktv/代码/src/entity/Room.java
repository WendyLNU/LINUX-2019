package entity;

import java.util.Date;
import java.util.GregorianCalendar;

import dao.ConfigDao;
import dao.RoomTypeDao;

public class Room {
	private int id;
	private int floor;
	private int type;
	private int money = 0;
	private Date startTime;
	private Date endTime;
	private boolean booked = false;

	public Room(int id, int floor, int type) {
		this.id = id;
		this.floor = floor;
		this.type = type;
	}

	public void take(int hours) {
		booked = false;
		money = (int) (RoomTypeDao.instance().getPricebyId(type)
				* ConfigDao.instance().getConfig().getDiscount() / 10);
		startTime = new Date();
		GregorianCalendar date = new GregorianCalendar();
		date.setTime(startTime);
		date.add(GregorianCalendar.HOUR, hours);
		endTime = date.getTime();
	}

	public void addHours() {
		GregorianCalendar date = new GregorianCalendar();
		date.setTime(endTime);
		date.add(GregorianCalendar.HOUR, ConfigDao.instance().getConfig()
				.getHoursAdded());
		money += RoomTypeDao.instance().getPriceAddedbyId(type)
				* ConfigDao.instance().getConfig().getDiscount() / 10;
		endTime = date.getTime();
	}

	public void buyFood(Food food, int nums) {
		money += food.getPrice() * nums;
	}

	public void end() {
		money = 0;
		startTime = null;
		endTime = null;
	}

	public void book() {
		booked = true;
	}

	public int getId() {
		return id;
	}

	public String getNumber() {
		String tmpStr = "0000" + id;
		return tmpStr.substring(tmpStr.length() - 4, tmpStr.length());
	}

	public int getFloor() {
		return floor;
	}

	public void setFloor(int floor) {
		this.floor = floor;
	}

	public int getType() {
		return type;
	}

	public void setType(int size) {
		this.type = size;
	}

	public int getMoney() {
		return money;
	}

	public void setMoney(int money) {
		this.money = money;
	}

	public int getPrice() {
		return RoomTypeDao.instance().getPricebyId(type);
	}

	public int getPriceAdded() {
		return RoomTypeDao.instance().getPriceAddedbyId(type);
	}

	public Date getStartTime() {
		return startTime;
	}

	public void setStartTime(Date startTime) {
		this.startTime = startTime;
	}

	public Date getEndTime() {
		return endTime;
	}

	public void setEndTime(Date endTime) {
		this.endTime = endTime;
	}

	public boolean isBooked() {
		return booked;
	}

	public void setBooked(boolean booked) {
		this.booked = booked;
	}
}
