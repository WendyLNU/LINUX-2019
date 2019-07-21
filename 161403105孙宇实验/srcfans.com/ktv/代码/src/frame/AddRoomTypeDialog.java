package frame;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.AddRoomTypeListener;

public class AddRoomTypeDialog extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5213823654951559181L;
	private static AddRoomTypeDialog addRoomTypeDialog;
	private JTextField jtfRoomType, jtfRoomPrice, jtfPriceAdded;

	public static AddRoomTypeDialog instance() {
		if (addRoomTypeDialog == null)
			addRoomTypeDialog = new AddRoomTypeDialog();
		return addRoomTypeDialog;
	}

	public AddRoomTypeDialog() {
		super(MainFrame.instance(), "添加房间类型", true);
		setLayout(null);
		setSize(400, 300);
		setLocationRelativeTo(null);
		addRoomTypeDialog = this;
		JLabel jlbRoomType = new JLabel("类型名称：");
		JLabel jlbRoomPrice = new JLabel("房间价格 ：");
		JLabel jlbAddHour = new JLabel("加钟价格 ：");
		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");
		jtfRoomType = new JTextField();
		jtfRoomPrice = new JTextField();
		jtfPriceAdded = new JTextField();

		jlbRoomType.setBounds(60, 30, 85, 30);
		jlbRoomPrice.setBounds(60, 90, 85, 30);
		jlbAddHour.setBounds(60, 150, 85, 30);
		jtfRoomType.setBounds(130, 26, 190, 40);
		jtfRoomPrice.setBounds(130, 86, 190, 40);
		jtfPriceAdded.setBounds(130, 146, 190, 40);
		ensure.setBounds(115, 200, 70, 40);
		cancel.setBounds(210, 200, 70, 40);

		AddRoomTypeListener addRoomTypeListener = new AddRoomTypeListener(
				jtfRoomType, jtfRoomPrice, jtfPriceAdded, cancel);
		jtfRoomType.addActionListener(addRoomTypeListener);
		jtfRoomPrice.addActionListener(addRoomTypeListener);
		jtfPriceAdded.addActionListener(addRoomTypeListener);
		ensure.addActionListener(addRoomTypeListener);
		cancel.addActionListener(addRoomTypeListener);

		add(jlbRoomType);
		add(jlbRoomPrice);
		add(jlbAddHour);
		add(jtfRoomType);
		add(jtfRoomPrice);
		add(jtfPriceAdded);
		add(ensure);
		add(cancel);
	}

	public void open() {
		jtfRoomType.setText("");
		jtfRoomPrice.setText("0");
		jtfPriceAdded.setText("0");
		setVisible(true);
	}

}
