package frame;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import listener.ConfigListener;
import dao.ConfigDao;
import entity.Config;

public class ConfigDialog extends JDialog {
	private static final long serialVersionUID = 5016876596940564305L;
	private static ConfigDialog configDialog;
	private JTextField jtfName, jtfDiscount, jtfHours, jtfHoursAdded, jtfBg;

	public static ConfigDialog instance() {
		if (configDialog == null)
			configDialog = new ConfigDialog();
		return configDialog;
	}

	public ConfigDialog() {
		super(MainFrame.instance(), "系统设置", true);
		setLayout(null);
		setSize(400, 420);
		setLocationRelativeTo(null);
		configDialog = this;
		JLabel jlbName = new JLabel("KTV名称：");
		JLabel jlbDiscount = new JLabel("折　　扣：");
		JLabel jlbHoursAdded = new JLabel("开房时长：");
		JLabel jlbHours = new JLabel("加钟时长：");
		JLabel jlbBg = new JLabel("背景图片：");
		JButton choose = new JButton("浏览");
		JButton ensure = new JButton("确定");
		JButton cancel = new JButton("取消");

		jtfName = new JTextField();
		jtfDiscount = new JTextField();
		jtfHours = new JTextField();
		jtfHoursAdded = new JTextField();
		jtfBg = new JTextField();

		jlbName.setBounds(60, 30, 85, 30);
		jlbDiscount.setBounds(60, 90, 85, 30);
		jlbHours.setBounds(60, 150, 85, 30);
		jlbHoursAdded.setBounds(60, 215, 85, 30);
		jlbBg.setBounds(60, 275, 85, 30);
		jtfName.setBounds(130, 26, 190, 40);
		jtfDiscount.setBounds(130, 86, 190, 40);
		jtfHours.setBounds(130, 146, 190, 40);
		jtfHoursAdded.setBounds(130, 206, 190, 40);
		jtfBg.setBounds(130, 266, 130, 40);
		choose.setBounds(260, 266, 60, 40);
		ensure.setBounds(115, 320, 70, 40);
		cancel.setBounds(210, 320, 70, 40);

		ConfigListener configListener = new ConfigListener(jtfName,
				jtfDiscount, jtfHours, jtfHoursAdded, jtfBg, choose, cancel);
		jtfName.addActionListener(configListener);
		jtfDiscount.addActionListener(configListener);
		jtfHours.addActionListener(configListener);
		jtfHoursAdded.addActionListener(configListener);
		jtfBg.addActionListener(configListener);
		choose.addActionListener(configListener);
		ensure.addActionListener(configListener);
		cancel.addActionListener(configListener);

		add(jlbName);
		add(jlbDiscount);
		add(jlbHours);
		add(jlbHoursAdded);
		add(jlbBg);
		add(jtfName);
		add(jtfDiscount);
		add(jtfHours);
		add(jtfHoursAdded);
		add(jtfBg);
		add(choose);
		add(ensure);
		add(cancel);
	}

	public void open() {
		Config config = ConfigDao.instance().getConfig();
		jtfName.setText(config.getName());
		jtfDiscount.setText(String.valueOf(config.getDiscount()));
		jtfHours.setText(String.valueOf(config.getHoursTaken()));
		jtfHoursAdded.setText(String.valueOf(config.getHoursAdded()));
		jtfBg.setText(config.getBackground());
		setVisible(true);
	}
}
