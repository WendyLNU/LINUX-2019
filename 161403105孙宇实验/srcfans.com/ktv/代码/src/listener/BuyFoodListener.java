package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

import dao.FoodDao;
import dao.RoomDao;
import entity.Food;
import entity.Room;
import frame.BuyFoodDialog;
import frame.DataTable;
import frame.MainPanel;

public class BuyFoodListener implements ActionListener, ItemListener {
	private JComboBox jcbType, jcbFood;
	private JTextField jtfNums;
	private JButton cancel;

	public BuyFoodListener(JComboBox jcbType, JComboBox jcbFood,
			JTextField jtfNums, JButton cancel) {
		this.jcbType = jcbType;
		this.jcbFood = jcbFood;
		this.jtfNums = jtfNums;
		this.cancel = cancel;
	}

	@Override
	public void itemStateChanged(ItemEvent e) {
		jcbFood.removeAllItems();
		List<Food> foodList = FoodDao.instance().getFoodList();
		for (Food food : foodList) {
			if (food.getType().equals(jcbType.getSelectedItem())) {
				jcbFood.addItem(food);
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == cancel) {
			BuyFoodDialog.instance().dispose();
		} else {
			if (jtfNums.getText().equals("")) {
				JOptionPane.showMessageDialog(null, "请将填写购买数量！");
				return;
			}
			Food food = (Food) jcbFood.getSelectedItem();
			DataTable table = MainPanel.instance().getTable();
			String tmpStr = table.getValueAt(table.getSelectedRow(), 0)
					.toString();
			if (tmpStr == null)
				return;
			DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
			Room room = RoomDao.instance().getRoom(Integer.parseInt(tmpStr));
			room.buyFood(food, Integer.parseInt(jtfNums.getText()));
			tableModel.setValueAt(room.getMoney(), table.getSelectedRow(), 2);
			BuyFoodDialog.instance().dispose();
			JOptionPane.showMessageDialog(null, "<html>添加酒水成功！共花费  <b><font size=8>" + food.getPrice()
					* Integer.parseInt(jtfNums.getText()) + "</font></b> 元。");
		}
	}
}
