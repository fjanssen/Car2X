package de.tum.in.hisch.combuilder.gui;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeSupport;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import com.jgoodies.forms.factories.FormFactory;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.RowSpec;

import de.tum.in.hisch.combuilder.control.DataBase;
import de.tum.in.hisch.combuilder.control.SensorField;

public class FieldsPanel extends JPanel {
	private String[] fileList;
	
	private boolean pathValid, nameValid, allValid;
	private PropertyChangeSupport changes;
	private JTable table;
	
	/**
	 * Create the panel.
	 */
	public FieldsPanel() {
		
		changes = new PropertyChangeSupport( this );
		
		setBorder(new LineBorder(new Color(0, 0, 0)));
		setLayout(new FormLayout(new ColumnSpec[] {
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("106px:grow"),
				FormFactory.LABEL_COMPONENT_GAP_COLSPEC,
				ColumnSpec.decode("max(38dlu;default)"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("max(91dlu;pref):grow"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("121px"),
				FormFactory.LABEL_COMPONENT_GAP_COLSPEC,
				ColumnSpec.decode("max(2dlu;default)"),},
			new RowSpec[] {
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("27px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("19px:grow"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("29px"),
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,}));
		
		JLabel lblSensorFields = new JLabel("Sensor Fields:");
		add(lblSensorFields, "2, 2");
		
		table = new JTable();
		table.setModel(new DefaultTableModel(
			new Object[][] {
				{null, null, null, null, null},
				{null, null, null, null, null},
				{null, null, null, null, null},
				{null, null, null, null, null},
			},
			new String[] {
				"Name", "Type", "Mode", "Count", "Description"
			}
		));
		table.setCellSelectionEnabled(true);
		
		
		TableColumn column = table.getColumnModel().getColumn(1);
		JComboBox<String> comboBox = new JComboBox(new String[] {"u8", "8", "u16", "16", "u32", "32"});
		column.setCellEditor(new ComboBoxCellEditor(comboBox));
		column = table.getColumnModel().getColumn(2);
		comboBox = new JComboBox(new String[] {"", "pointer", "array", "list" });
		column.setCellEditor(new ComboBoxCellEditor(comboBox));
		
		add(new JScrollPane(table), "2, 4, 5, 13, fill, fill");
		
		JButton btnAddField = new JButton("Add field");
		btnAddField.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				int idx = table.getSelectedRow();
				if(idx == -1)
					((DefaultTableModel) table.getModel()).addRow(new Object[] {null, null, null, null, null});
				else
					((DefaultTableModel) table.getModel()).insertRow(idx, new Object[] {null, null, null, null, null});
			}
		});
		add(btnAddField, "8, 4");
		
		JButton btnRemoveField = new JButton("Remove field");
		btnRemoveField.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRows[] = table.getSelectedRows();
				if(selectedRows.length == 0 && ((DefaultTableModel) table.getModel()).getRowCount() > 0)
				{
					((DefaultTableModel) table.getModel()).removeRow(((DefaultTableModel) table.getModel()).getRowCount()-1);
				}
				else
				{
					for(int i = selectedRows.length-1; i >= 0; i--)
						((DefaultTableModel) table.getModel()).removeRow(selectedRows[i]);
				}
			}
		});
		add(btnRemoveField, "8, 6");
		
		JButton btnUp = new JButton("Up");
		btnUp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRows[] = table.getSelectedRows();
				if(selectedRows.length > 0)
				{
					if(selectedRows[0] > 0)
					{
						((DefaultTableModel) table.getModel()).moveRow(selectedRows[0], selectedRows[selectedRows.length-1], selectedRows[0]-1);
						table.setRowSelectionInterval(selectedRows[0]-1, selectedRows[selectedRows.length-1]-1);
					}
				}
				
			}
		});
		add(btnUp, "8, 8");
		
		JButton btnDown = new JButton("Down");
		btnDown.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRows[] = table.getSelectedRows();
				if(selectedRows.length > 0)
				{
					if(selectedRows[selectedRows.length-1] < ((DefaultTableModel) table.getModel()).getRowCount()-1)
					{
						((DefaultTableModel) table.getModel()).moveRow(selectedRows[0], selectedRows[selectedRows.length-1], selectedRows[0]+1);
						table.setRowSelectionInterval(selectedRows[0]+1, selectedRows[selectedRows.length-1]+1);
					}
				}
			}
		});
		add(btnDown, "8, 10");
		
		pathValid = nameValid = allValid = false;
		
		
	}
	
	public void updateDataBase(DataBase dataBase)
	{
		dataBase.fieldList.clear();
		
		for(int i = 0; i < table.getRowCount(); i++)
		{
			if(table.getValueAt(i, 0) == null || table.getValueAt(i, 0).toString().isEmpty())
			continue;
			
			int count = 1;
			try{
				count = Integer.valueOf(table.getValueAt(i, 3)+"");
			}catch(java.lang.NumberFormatException e)
			{
				count = 1; 
			}
			dataBase.fieldList.add(new SensorField(table.getValueAt(i, 0)+"", table.getValueAt(i, 1)+"", table.getValueAt(i, 2)+"", count, table.getValueAt(i, 4)+""));
		}
	}
	
}