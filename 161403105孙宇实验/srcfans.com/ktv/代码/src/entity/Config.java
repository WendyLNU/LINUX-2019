package entity;

import java.awt.Font;
import java.io.File;

import javax.swing.ImageIcon;

public class Config {
	private String name;
	private float discount;
	private int hoursTaken;
	private int hoursAdded;
	private Font font;
	private String copyright;
	private String background;
	private ImageIcon backgroundImage;

	public Config(String name, float discount, int hoursTaken, int hoursAdded) {
		this(name, discount, hoursTaken, hoursAdded, "", new Font("Î¢ÈíÑÅºÚ",
				Font.PLAIN, 14));
	}

	public Config(String name, float discount, int hoursTaken, int hoursAdded,
			String background) {
		this(name, discount, hoursTaken, hoursAdded, background, new Font(
				"Î¢ÈíÑÅºÚ", Font.PLAIN, 14));
	}

	public Config(String name, float discount, int hoursTaken, int hoursAdded,
			String background, Font font) {
		this.name = name;
		this.discount = discount;
		this.hoursTaken = hoursTaken;
		this.hoursAdded = hoursAdded;
		this.font = font;
		this.copyright = "¹Ø×¢Ç°ÑØ£¬×·Çó×¿Ô½¡£";
		this.background = background;
		File file = new File(background);
		if (file.exists()) {
			backgroundImage = new ImageIcon(background);
		} else {
			background = "";
			backgroundImage = new ImageIcon(this.getClass().getResource(
					"/images/bg.jpg"));
		}
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public float getDiscount() {
		return discount;
	}

	public void setDiscount(float discount) {
		this.discount = discount;
	}

	public int getHoursTaken() {
		return hoursTaken;
	}

	public void setHoursTaken(int hoursTaken) {
		this.hoursTaken = hoursTaken;
	}

	public int getHoursAdded() {
		return hoursAdded;
	}

	public void setHoursAdded(int hoursAdded) {
		this.hoursAdded = hoursAdded;
	}

	public Font getFont() {
		return font;
	}

	public void setFont(Font font) {
		this.font = font;
	}

	public String getBackground() {
		return background;
	}

	public void setBackground(String background) {
		File file = new File(background);
		if (file.exists()) {
			backgroundImage = new ImageIcon(background);
		} else {
			background = "";
			backgroundImage = new ImageIcon(this.getClass().getResource(
					"/images/bg.jpg"));
		}
		this.background = background;
	}

	public ImageIcon getBackgroundImage() {
		return backgroundImage;
	}

	public String getCopyright() {
		return copyright;
	}
}
