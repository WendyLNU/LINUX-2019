package frame;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.BuyFoodListener;

import dao.FoodDao;

public class BuyFoodDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = -7228765492296653353L;
	private static BuyFoodDialog addRoomDialog;
	private JComboBox jcbType, jcbFood;
	private JTextField jtfNums;

	public static BuyFoodDialog instance() {
		if (addRoomDialog == null)
			addRoomDialog = new BuyFoodDialog();
		return addRoomDialog;
	}

	public BuyFoodDialog() {
		super(MainFrame.instance(), "添加酒水", true);
		setLayout(null);
		setSize(400, 300);
		setLocationRelativeTo(null);
		addRoomDialog = this;
		JLabel jlbType = new JLabel("种类：");
		JLabel jlbFood = new JLabel("食品：");
		JLabel jlbNums = new JLabel("数量：");
		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");
		jcbType = new JComboBox();
		jcbFood = new JComboBox();
		jtfNums = new JTextField();
		
		jlbType.setBounds(70, 30, 85, 30);
		jlbFood.setBounds(70, 90, 85, 30);
		jlbNums.setBounds(70, 150, 85, 30);
		jcbType.setBounds(130, 26, 190, 40);
		jcbFood.setBounds(130, 86, 190, 40);
		jtfNums.setBounds(130, 146, 190, 35);
		ensure.setBounds(100, 205, 90, 40);
		cancel.setBounds(210, 205, 90, 40);
		
		BuyFoodListener buyFoodListener = new BuyFoodListener(jcbType, jcbFood, jtfNums, cancel);
		jcbType.addItemListener(buyFoodListener);
		jtfNums.addActionListener(buyFoodListener);
		ensure.addActionListener(buyFoodListener);
		cancel.addActionListener(buyFoodListener);

		add(jlbType);
		add(jlbFood);
		add(jlbNums);
		add(jcbType);
		add(jcbFood);
		add(jtfNums);
		add(ensure);
		add(cancel);
	}
	
	public void open(){
		jcbType.removeAllItems();
		for (String item : FoodDao.instance().getTypeList()) {
			jcbType.addItem(item);
		}
		jtfNums.setText("1");
		setVisible(true);
	}
}
