package frame;

import java.awt.Component;
import java.awt.Graphics;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

import dao.ConfigDao;

public class DataTable extends JTable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -251519594436074037L;

	@SuppressWarnings("serial")
	public DataTable(final Object[][] data, Object[] head) {
		super(new DefaultTableModel(data, head) {
			public Class<?> getColumnClass(int column) {
				if (data.length > 0 && column < getRowCount() && getValueAt(0, column) != null)
					return getValueAt(0, column).getClass();
				return Object.class;
			}
		});
		setRowHeight(30);
		setOpaque(false);
		setRowSorter(new TableRowSorter<TableModel>(getModel()));
		setFont(ConfigDao.instance().getConfig().getFont());
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		getTableHeader().repaint();
		// 2 MainPanel.instance().repaint();
	}

	public Component prepareRenderer(TableCellRenderer renderer, int row,
			int column) {
		Component c = super.prepareRenderer(renderer, row, column);
		boolean selected = false;
		for (int i : getSelectedRows()) {
			if (row == i) {
				selected = true;
				break;
			}
		}
		if (c instanceof JComponent) {
			((JLabel) c).setHorizontalAlignment(JLabel.CENTER);
			((JComponent) c).setOpaque(false);
			if (selected) {
				((JComponent) c).setOpaque(true);
			}
		}
		return c;
	}

	public JTableHeader getTableHeader() {
		JTableHeader tableHeader = super.getTableHeader();
		DefaultTableCellRenderer hr = (DefaultTableCellRenderer) tableHeader
				.getDefaultRenderer();
		hr.setHorizontalAlignment(DefaultTableCellRenderer.CENTER);
		tableHeader.setFont(ConfigDao.instance().getConfig().getFont());
		return tableHeader;
	}

	public boolean isCellEditable(int row, int column) {
		return false;
	}
}