package dao;

import java.util.ArrayList;
import java.util.List;

import entity.Food;

public class FoodDao {
	private List<Food> foodList;
	private List<String> typeList;
	private static FoodDao foodDao;

	public static FoodDao instance() {
		if (foodDao == null)
			foodDao = new FoodDao();
		return foodDao;
	}

	public FoodDao() {
		foodList = new ArrayList<Food>();
		typeList = new ArrayList<String>();
		addFood(new Food("������ơ��", "����", 5, 500));
		addFood(new Food("�ൺơ��", "����", 5, 500));
		addFood(new Food("�齭ơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));
		addFood(new Food("ϲ��ơ��", "����", 5, 500));
		addFood(new Food("�ྩơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));
		addFood(new Food("��ʿ��ơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));
		addFood(new Food("����ʿơ��", "����", 5, 500));
		addFood(new Food("����ơ��", "����", 5, 500));

		addFood(new Food("ƻ��", "ˮ��", 5, 500));
		addFood(new Food("ѩ��", "ˮ��", 5, 500));
		addFood(new Food("����", "ˮ��", 5, 500));
		addFood(new Food("�㽶 ", "ˮ��", 5, 500));
		addFood(new Food("���", "ˮ��", 5, 500));
		addFood(new Food("���", "ˮ��", 5, 500));
		addFood(new Food("���� ", "ˮ��", 5, 500));
		addFood(new Food("���ܹ�", "ˮ��", 5, 500));
		addFood(new Food("â��", "ˮ��", 5, 500));

		addFood(new Food("��֭", "����", 5, 500));
		addFood(new Food("����", "����", 5, 500));
		addFood(new Food("����ķ�̲�", "����", 5, 500));
		addFood(new Food("��ϲ", "����", 5, 500));
		addFood(new Food("������", "����", 5, 500));
		addFood(new Food("�ʳȶ�", "����", 5, 500));

		addFood(new Food("��������", "���", 10, 500));
		addFood(new Food("������ŵ", "���", 10, 500));
		addFood(new Food("Ҭ��Ȧ ", "���", 10, 500));
		addFood(new Food("�㽶��������", "���", 10, 500));
		addFood(new Food("Ĩ��춹", "���", 10, 500));

	}

	public List<Food> getFoodList() {
		return foodList;
	}

	public List<String> getTypeList() {
		return typeList;
	}

	public Food getFoodbyId(int id) {
		for (Food food : foodList) {
			if (food.getId() == id)
				return food;
		}
		return null;
	}

	public void addFood(Food food) {
		foodList.add(food);
		for (String type : typeList)
			if (food.getType().equals(type))
				return;
		typeList.add(food.getType());
	}

	public void removeFood(Food food) {
		foodList.remove(food);
	}

	public Object[][] getFoodsData() {
		Object[][] result = new Object[1][5];
		if (foodList.size() > 0) {
			result = new Object[foodList.size()][5];
			int i = 0;
			for (Food food : foodList) {
				result[i][0] = food.getId();
				result[i][1] = food.getName();
				result[i][2] = food.getType();
				result[i][3] = food.getPrice();
				result[i][4] = food.getNumRest();
				i++;
			}
		} else {
			result[0][0] = 0;
			result[0][1] = "û������";
			result[0][2] = "";
			result[0][3] = 0;
			result[0][4] = 0;
		}
		return result;
	}

}
