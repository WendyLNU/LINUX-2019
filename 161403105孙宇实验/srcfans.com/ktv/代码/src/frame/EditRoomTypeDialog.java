package frame;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.EditRoomTypeListener;
import entity.RoomType;

public class EditRoomTypeDialog extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5213823654951559181L;
	private static EditRoomTypeDialog editRoomTypeDialog;
	private JTextField jtfTypeId, jtfRoomType, jtfRoomPrice, jtfPriceAdded;

	public static EditRoomTypeDialog instance() {
		if (editRoomTypeDialog == null)
			editRoomTypeDialog = new EditRoomTypeDialog();
		return editRoomTypeDialog;
	}

	public EditRoomTypeDialog() {
		super(MainFrame.instance(), "编辑房间类型", true);
		setLayout(null);
		setSize(400, 300);
		setLocationRelativeTo(null);
		editRoomTypeDialog = this;
		JLabel jlbRoomType = new JLabel("类型名称：");
		JLabel jlbRoomPrice = new JLabel("房间价格 ：");
		JLabel jlbAddHour = new JLabel("加钟价格 ：");
		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");
		jtfTypeId = new JTextField();
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

		EditRoomTypeListener editRoomTypeListener = new EditRoomTypeListener(
				jtfTypeId, jtfRoomType, jtfRoomPrice, jtfPriceAdded, cancel);
		jtfRoomType.addActionListener(editRoomTypeListener);
		jtfRoomPrice.addActionListener(editRoomTypeListener);
		jtfPriceAdded.addActionListener(editRoomTypeListener);
		ensure.addActionListener(editRoomTypeListener);
		cancel.addActionListener(editRoomTypeListener);

		add(jlbRoomType);
		add(jlbRoomPrice);
		add(jlbAddHour);
		add(jtfRoomType);
		add(jtfRoomPrice);
		add(jtfPriceAdded);
		add(ensure);
		add(cancel);
	}

	public void open(RoomType roomType) {
		jtfTypeId.setText(String.valueOf(roomType.getId()));
		jtfRoomType.setText(roomType.getName());
		jtfRoomPrice.setText(String.valueOf(roomType.getPrice()));
		jtfPriceAdded.setText(String.valueOf(roomType.getPriceAdded()));
		setVisible(true);
	}

}
