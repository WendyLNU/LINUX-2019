package entity;

public class RoomType {
	private int id;
	private String name;
	private int price;
	private int priceAdded;
	private static int autoIdId;

	public RoomType(String name, int price, int priceAdded) {
		this.id = ++autoIdId;
		this.name = name;
		this.price = price;
		this.priceAdded = priceAdded;
	}

	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getPrice() {
		return price;
	}

	public void setPrice(int price) {
		this.price = price;
	}

	public int getPriceAdded() {
		return priceAdded;
	}

	public void setPriceAdded(int priceAdded) {
		this.priceAdded = priceAdded;
	}

	@Override
	public String toString() {
		return name;
	}
}
