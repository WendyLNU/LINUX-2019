package entity;

public class Food {
	private int id;
	private String name;
	private String type;
	private int price;
	private int numRest;
	private static int autoId;

	public Food(String name, String type, int price, int numRest) {
		this.id = ++autoId;
		this.name = name;
		this.type = type;
		this.price = price;
		this.numRest = numRest;
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

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public int getPrice() {
		return price;
	}

	public void setPrice(int price) {
		this.price = price;
	}

	public int getNumRest() {
		return numRest;
	}

	public void setNumRest(int numRest) {
		this.numRest = numRest;
	}

	@Override
	public String toString() {
		return name + " (µ¥¼Û " + price + " Ôª)";
	}
}