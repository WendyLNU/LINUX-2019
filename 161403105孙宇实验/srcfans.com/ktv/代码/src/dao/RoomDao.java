package dao;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import entity.Room;

public class RoomDao {
	private List<Room> roomList;
	private static RoomDao roomDao;

	public static RoomDao instance() {
		if (roomDao == null)
			roomDao = new RoomDao();
		return roomDao;
	}

	public RoomDao() {
		roomList = new ArrayList<Room>();
		for (int i = 0; i < 10; i++)
			addRoom(new Room(1101 + i, 0, 1));
		for (int i = 0; i < 20; i++)
			addRoom(new Room(2101 + i, 0, 2));
		for (int i = 0; i < 30; i++)
			addRoom(new Room(3201 + i, 1, 3));
		for (int i = 0; i < 20; i++)
			addRoom(new Room(4301 + i, 2, 4));
		for (int i = 0; i < 10; i++)
			addRoom(new Room(5301 + i, 2, 5));
	}

	public Room getRoom(int id) {
		for (Room room : roomList) {
			if (room.getId() == id) {
				return room;
			}
		}
		return null;
	}

	public void addRoom(Room room) {
		roomList.add(room);
	}

	public void removeRoom(Room room) {
		roomList.remove(room);
	}

	public List<Room> getRoomList() {
		return roomList;
	}

	private int getNumsTaken() {
		int nums = 0;
		for (Room room : roomList) {
			if (room.getStartTime() != null)
				++nums;
		}
		return nums;
	}

	private int getNumsExpired() {
		int nums = 0;
		for (Room room : roomList) {
			if (room.getEndTime() != null
					&& room.getEndTime().before(new Date()))
				++nums;
		}
		return nums;
	}

	public Object[][] getRoomsData() {
		Object[][] result = new Object[1][5];
		if (roomList.size() > 0) {
			result = new Object[roomList.size()][5];
			Room room;
			for (int i = 0; i < roomList.size(); i++) {
				room = roomList.get(i);
				result[i] = formatData(room);
			}
		} else {
			result[0][0] = 0;
			result[0][1] = "没有数据";
			result[0][2] = 0;
			result[0][3] = 0;
			result[0][4] = 0;
		}
		return result;
	}

	public Object[][] getRoomsTakenData() {
		Object[][] result = new Object[getNumsTaken()][5];
		int i = 0;
		for (Room room : roomList) {
			if (room.getStartTime() != null) {
				result[i] = formatTakenData(room);
				i++;
			}
		}
		return result;
	}

	public Object[][] getExpiredRoomsData() {
		Object[][] result = new Object[getNumsExpired()][5];
		int i = 0;
		for (Room room : roomList) {
			if (room.getEndTime() != null
					&& room.getEndTime().before(new Date())) {
				result[i] = formatTakenData(room);
				i++;
			}
		}
		return result;
	}

	private Object[] formatData(Room room) {
		Object[] result = new Object[5];
		result[0] = room.getNumber();
		result[1] = RoomTypeDao.instance().getNamebyId(room.getType());
		result[2] = room.getFloor() + 1;
		result[3] = room.getPrice();
		result[4] = room.getPriceAdded();
		return result;
	}

	private Object[] formatTakenData(Room room) {
		Object[] result = new Object[5];
		result[0] = room.getNumber();
		result[1] = RoomTypeDao.instance().getNamebyId(room.getType());
		result[2] = room.getMoney();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		result[3] = (room.getStartTime() == null) ? "" : formatter.format(room
				.getStartTime());
		result[4] = (room.getEndTime() == null) ? "" : formatter.format(room
				.getEndTime());
		return result;
	}
}
