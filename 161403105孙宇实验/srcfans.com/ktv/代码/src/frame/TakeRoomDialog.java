package frame;

import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JTextField;

import listener.TakeRoomListener;
import dao.ConfigDao;

public class TakeRoomDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = -1116388016863724023L;
	private static TakeRoomDialog takeRoomDialog;
	private JTextField jtfPhoneNumber;

	public static TakeRoomDialog instance() {
		if (takeRoomDialog == null)
			takeRoomDialog = new TakeRoomDialog();
		return takeRoomDialog;
	}

	public TakeRoomDialog() {
		super(MainFrame.instance(), "拿房", true);
		setLayout(null);
		setResizable(false);
		setSize(400, 300);
		setLocationRelativeTo(null);

		takeRoomDialog = this;
		
		jtfPhoneNumber = new JTextField();
		jtfPhoneNumber.setBounds(50, 60, 300, 80);
		jtfPhoneNumber.setFont(new Font(ConfigDao.instance().getConfig().getFont()
				.getName(), Font.PLAIN, 30));

		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");
		ensure.setBounds(100, 180, 90, 40);
		cancel.setBounds(210, 180, 90, 40);

		TakeRoomListener getRoomListener = new TakeRoomListener(this, jtfPhoneNumber, ensure, cancel);
		ensure.addActionListener(getRoomListener);
		cancel.addActionListener(getRoomListener);
		jtfPhoneNumber.addActionListener(getRoomListener);
		
		add(jtfPhoneNumber);
		add(ensure);
		add(cancel);
	}

	public void open() {
		jtfPhoneNumber.setText("电话号码");
		jtfPhoneNumber.selectAll();
		setVisible(true);
	}
}
