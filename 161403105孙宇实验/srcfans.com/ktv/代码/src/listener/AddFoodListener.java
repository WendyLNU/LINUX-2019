package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import dao.FoodDao;
import entity.Food;
import frame.AddFoodDialog;
import frame.MainPanel;

public class AddFoodListener implements ActionListener {

	private JTextField jtfName, jtfPrice, jtfNumRest;
	private JComboBox cbfType;
	private JButton cancel;

	public AddFoodListener(JTextField jtfName, JComboBox cbfType,
			JTextField jtfPrice, JTextField jtfNumRest, JButton cancel) {
		this.jtfName = jtfName;
		this.cbfType = cbfType;
		this.jtfPrice = jtfPrice;
		this.jtfNumRest = jtfNumRest;
		this.cancel = cancel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == cancel) {
			AddFoodDialog.instance().dispose();
		} else {
			if(jtfName.getText().equals("") || cbfType.getSelectedItem().toString().equals("") || jtfPrice.getText().equals("") || jtfNumRest.getText().equals("")){
				JOptionPane.showMessageDialog(null, "请将信息填写完整！");
				return;
			}
			FoodDao.instance().addFood(
					new Food(jtfName.getText(), cbfType.getSelectedItem()
							.toString(), Integer.parseInt(jtfPrice.getText()),
							Integer.parseInt(jtfNumRest.getText())));
			MainPanel.instance().refresh();
			AddFoodDialog.instance().dispose();
			JOptionPane.showMessageDialog(null, "添加成功！");
		}
	}
}
