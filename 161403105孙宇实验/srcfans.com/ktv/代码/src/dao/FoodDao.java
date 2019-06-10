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
		addFood(new Food("哈尔滨啤酒", "酒类", 5, 500));
		addFood(new Food("青岛啤酒", "酒类", 5, 500));
		addFood(new Food("珠江啤酒", "酒类", 5, 500));
		addFood(new Food("纯生啤酒", "酒类", 5, 500));
		addFood(new Food("百威啤酒", "酒类", 5, 500));
		addFood(new Food("喜力啤酒", "酒类", 5, 500));
		addFood(new Food("燕京啤酒", "酒类", 5, 500));
		addFood(new Food("金威啤酒", "酒类", 5, 500));
		addFood(new Food("重庆啤酒", "酒类", 5, 500));
		addFood(new Food("嘉士伯啤酒", "酒类", 5, 500));
		addFood(new Food("蓝带啤酒", "酒类", 5, 500));
		addFood(new Food("健力士啤酒", "酒类", 5, 500));
		addFood(new Food("蓝妹啤酒", "酒类", 5, 500));

		addFood(new Food("苹果", "水果", 5, 500));
		addFood(new Food("雪梨", "水果", 5, 500));
		addFood(new Food("槟榔", "水果", 5, 500));
		addFood(new Food("香蕉 ", "水果", 5, 500));
		addFood(new Food("酸橙", "水果", 5, 500));
		addFood(new Food("金桔", "水果", 5, 500));
		addFood(new Food("葡萄 ", "水果", 5, 500));
		addFood(new Food("哈密瓜", "水果", 5, 500));
		addFood(new Food("芒果", "水果", 5, 500));

		addFood(new Food("橙汁", "饮料", 5, 500));
		addFood(new Food("可乐", "饮料", 5, 500));
		addFood(new Food("阿萨姆奶茶", "饮料", 5, 500));
		addFood(new Food("七喜", "饮料", 5, 500));
		addFood(new Food("果粒橙", "饮料", 5, 500));
		addFood(new Food("鲜橙多", "饮料", 5, 500));

		addFood(new Food("提拉米苏", "甜点", 10, 500));
		addFood(new Food("卡布奇诺", "甜点", 10, 500));
		addFood(new Food("椰子圈 ", "甜点", 10, 500));
		addFood(new Food("香蕉布丁蛋糕", "甜点", 10, 500));
		addFood(new Food("抹茶红豆", "甜点", 10, 500));

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
			result[0][1] = "没有数据";
			result[0][2] = "";
			result[0][3] = 0;
			result[0][4] = 0;
		}
		return result;
	}

}
