package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.filechooser.FileNameExtensionFilter;

import dao.ConfigDao;
import entity.Config;
import frame.ConfigDialog;

public class ConfigListener implements ActionListener {
	private JTextField jtfName, jtfDiscount, jtfHours, jtfHoursAdded, jtfBg;
	private JButton choose, cancel;

	public ConfigListener(JTextField jtfName, JTextField jtfDiscount,
			JTextField jtfHours, JTextField jtfHoursAdded, JTextField jtfBg,
			JButton choose, JButton cancel) {
		super();
		this.jtfName = jtfName;
		this.jtfDiscount = jtfDiscount;
		this.jtfHours = jtfHours;
		this.jtfHoursAdded = jtfHoursAdded;
		this.jtfBg = jtfBg;
		this.choose = choose;
		this.cancel = cancel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == cancel) {
			ConfigDialog.instance().dispose();
		} else if (e.getSource() == choose) {
			JFileChooser filechooser = new JFileChooser(jtfBg.getText().equals(
					"") ? "./images/" : jtfBg.getText());
			FileNameExtensionFilter filter = new FileNameExtensionFilter(
					"图片文件", "jpg", "jpeg", "gif", "bmp", "png");
			filechooser.setFileFilter(filter);
			if (filechooser.showOpenDialog(ConfigDialog.instance()) == JFileChooser.OPEN_DIALOG) {
				jtfBg.setText(filechooser.getSelectedFile().getAbsolutePath());
			}
		} else {
			if (jtfName.getText().equals("")
					|| jtfDiscount.getText().equals("")
					|| jtfHours.getText().equals("")
					|| jtfHoursAdded.getText().equals("")) {
				JOptionPane.showMessageDialog(null, "请将信息填写完整！");
				return;
			}
			Config config = new Config(jtfName.getText(),
					Float.parseFloat(jtfDiscount.getText()),
					Integer.parseInt(jtfHours.getText()),
					Integer.parseInt(jtfHoursAdded.getText()), jtfBg.getText());
			ConfigDao.instance().setConfig(config);
			ConfigDialog.instance().dispose();
			JOptionPane.showMessageDialog(null, "设置成功！");
		}
	}
}
