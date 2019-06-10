package listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

import frame.BookRoomDialog;
import frame.ConfigDialog;
import frame.LoginFrame;
import frame.MainFrame;
import frame.MainPanel;
import frame.TakeRoomDialog;

public class OptionListener implements ActionListener{
	JButton jbtBookRoom;
	JButton jbtTakeRoom;
	JButton jbtRefresh;
	JButton jbtConfig;
	JButton jbtLock;
	JButton jbtExit;

	public OptionListener(JButton jbtBookRoom, JButton jbtTakeRoom,
			JButton jbtRefresh, JButton jbtConfig, JButton jbtLock,
			JButton jbtExit) {
		super();
		this.jbtBookRoom = jbtBookRoom;
		this.jbtTakeRoom = jbtTakeRoom;
		this.jbtRefresh = jbtRefresh;
		this.jbtConfig = jbtConfig;
		this.jbtLock = jbtLock;
		this.jbtExit = jbtExit;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == jbtBookRoom){
			BookRoomDialog.instance().open();
		}else if(e.getSource() == jbtTakeRoom){
			TakeRoomDialog.instance().open();
		}else if(e.getSource() == jbtRefresh){
			MainPanel.instance().refresh();
		}else if(e.getSource() == jbtConfig){
			ConfigDialog.instance().open();
		}else if(e.getSource() == jbtLock){
			LoginFrame.instance().open();
			MainFrame.instance().dispose();
		}else if(e.getSource() == jbtExit){
			System.exit(0);
		}
	}
}
