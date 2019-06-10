package frame;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.AddRoomListener;
import dao.RoomTypeDao;
import entity.RoomType;

public class AddRoomDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = -7228765492296653353L;
	private static AddRoomDialog addRoomDialog;
	private JComboBox jcbRoomType;
	private JTextField jtfRoomNumber, jtfEndNumber, jtbFloor;

	public static AddRoomDialog instance() {
		if (addRoomDialog == null)
			addRoomDialog = new AddRoomDialog();
		return addRoomDialog;
	}

	public AddRoomDialog() {
		super(MainFrame.instance(), "添加房间", true);
		setLayout(null);
		setSize(400, 300);
		setLocationRelativeTo(null);
		addRoomDialog = this;
		JLabel jlbRoomType = new JLabel("房间类型：");
		JLabel jlbRoomNumber = new JLabel("房间号码：");
		JLabel jlbFloor = new JLabel("房间楼层：");
		JLabel jlbto = new JLabel("—");
		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");
		jcbRoomType = new JComboBox();
		jtfRoomNumber = new JTextField();
		jtfEndNumber = new JTextField();
		jtbFloor = new JTextField();

		jlbto.setHorizontalAlignment(JLabel.CENTER);
		jlbRoomType.setBounds(60, 30, 85, 30);
		jlbRoomNumber.setBounds(60, 90, 85, 30);
		jlbFloor.setBounds(60, 150, 85, 30);
		jlbto.setBounds(210, 86, 30, 40);
		jcbRoomType.setBounds(130, 26, 190, 35);
		// jtfRoomNumber.setBounds(130, 86, 190, 40);
		jtfRoomNumber.setBounds(130, 86, 80, 40);
		jtfEndNumber.setBounds(240, 86, 80, 40);
		jtbFloor.setBounds(130, 146, 190, 40);
		ensure.setBounds(115, 205, 70, 40);
		cancel.setBounds(210, 205, 70, 40);

		for (RoomType item : RoomTypeDao.instance().getRoomTypeList()) {
			jcbRoomType.addItem(item);
		}

		AddRoomListener addRoomListener = new AddRoomListener(jcbRoomType,
				jtfRoomNumber, jtfEndNumber, jtbFloor, cancel);
		jtfRoomNumber.addActionListener(addRoomListener);
		jtfEndNumber.addActionListener(addRoomListener);
		jtbFloor.addActionListener(addRoomListener);
		ensure.addActionListener(addRoomListener);
		cancel.addActionListener(addRoomListener);

		add(jlbRoomType);
		add(jlbRoomNumber);
		add(jlbFloor);
		add(jcbRoomType);
		add(jtfRoomNumber);
		add(jtfEndNumber);
		add(jtbFloor);
		add(ensure);
		add(cancel);
		add(jlbto);
	}

	public void open(boolean batch) {
		if (batch) {
			jtfRoomNumber.setBounds(130, 86, 80, 40);
			jtfEndNumber.setBounds(240, 86, 80, 40);
			jtfEndNumber.setVisible(true);
		} else {
			jtfRoomNumber.setBounds(130, 86, 190, 40);
			jtfEndNumber.setVisible(false);
		}
		if (jcbRoomType.getItemCount() > 0)
			jcbRoomType.setSelectedIndex(0);
		jtfEndNumber.setText("0000");
		jtfRoomNumber.setText("0000");
		jtbFloor.setText("1");
		setVisible(true);
	}

}
