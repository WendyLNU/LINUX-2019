package frame;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.AddFoodListener;
import dao.FoodDao;

public class AddFoodDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7928002009191943965L;
	private static AddFoodDialog addFoodDialog;
	private JTextField jtfName, jtfPrice, jtfNumRest;
	private JComboBox jcbType;

	public static AddFoodDialog instance() {
		if (addFoodDialog == null)
			addFoodDialog = new AddFoodDialog();
		return addFoodDialog;
	}

	public AddFoodDialog() {
		super(MainFrame.instance(), "添加食品", true);
		setLayout(null);
		setSize(400, 350);
		setLocationRelativeTo(null);
		
		JLabel jlbName, jlbType, jlbPrice, jlbNumRest;
		JButton ensure, cancel;
		jlbName = new JLabel("食品名称：");
		jlbType = new JLabel("食品种类：");
		jlbPrice = new JLabel("食品单价：");
		jlbNumRest = new JLabel("剩余数量：");
		jtfName = new JTextField();
		jcbType = new JComboBox();
		jtfPrice = new JTextField();
		jtfNumRest = new JTextField();
		ensure = new JButton("确定");
		cancel = new JButton("取消");

		jcbType.setEditable(true);

		jlbName.setBounds(60, 25, 60, 35);
		jlbType.setBounds(60, 80, 60, 35);
		jlbPrice.setBounds(60, 135, 60, 35);
		jlbNumRest.setBounds(60, 190, 90, 35);
		jtfName.setBounds(130, 25, 190, 35);
		jcbType.setBounds(130, 80, 190, 35);
		jtfPrice.setBounds(130, 135, 190, 35);
		jtfNumRest.setBounds(130, 190, 190, 35);
		ensure.setBounds(100, 250, 90, 40);
		cancel.setBounds(210, 250, 90, 40);

		AddFoodListener addFoodListener = new AddFoodListener(jtfName, jcbType,
				jtfPrice, jtfNumRest, cancel);
		jtfName.addActionListener(addFoodListener);
		// jtfType.addActionListener(addFoodListener);
		jtfPrice.addActionListener(addFoodListener);
		jtfNumRest.addActionListener(addFoodListener);
		ensure.addActionListener(addFoodListener);
		cancel.addActionListener(addFoodListener);

		add(jlbName);
		add(jlbType);
		add(jlbPrice);
		add(jlbNumRest);
		add(jtfName);
		add(jcbType);
		add(jtfPrice);
		add(jtfNumRest);
		add(ensure);
		add(cancel);
	}

	public void open() {
		jtfName.setText("");
		jcbType.removeAllItems();
		jcbType.addItem("");
		for (String item : FoodDao.instance().getTypeList()) {
			jcbType.addItem(item);
		}
		jtfPrice.setText("");
		jtfNumRest.setText("");
		setVisible(true);
	}
}
