package de.tum.in.hisch.combuilder.gui;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

import javax.swing.DropMode;
import javax.swing.JButton;
import javax.swing.JComponent;
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
import de.tum.in.hisch.combuilder.control.SubMessage;

import javax.swing.JList;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;
import javax.swing.AbstractListModel;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeSupport;

public class MessagePanel extends JPanel {

	private JLabel lblMessageName;
	private JLabel lblSubtype;
	
	private JTable table;
	private JList list;
	private String[] allValues;
	private String[] unusedValues;
	private int size, allSize;
	
	/**
	 * Create the panel.
	 */
	public MessagePanel() {
		
		allValues = new String[128];
		unusedValues = new String[128];
		size = 0;
		allSize = 0;
		
		setBorder(new LineBorder(new Color(0, 0, 0)));
		setLayout(new FormLayout(new ColumnSpec[] {
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("106px:grow"),
				FormFactory.RELATED_GAP_COLSPEC,
				FormFactory.DEFAULT_COLSPEC,
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("110dlu"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("max(5dlu;default)"),},
			new RowSpec[] {
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("27px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("max(2dlu;default)"),
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px:grow"),
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("19px"),
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("19px"),
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("max(5dlu;default)"),}));
		
		lblMessageName = new JLabel("Message Name: ");
		add(lblMessageName, "2, 2");
		
		lblSubtype = new JLabel("SubType: ");
		add(lblSubtype, "6, 2");
		
		JSeparator separator_1 = new JSeparator();
		add(separator_1, "2, 4, 5, 1");
		
		JSeparator separator = new JSeparator();
		separator.setOrientation(SwingConstants.VERTICAL);
		add(separator, "4, 5, 1, 10");
		
		JLabel lblMessageStructure = new JLabel("Message structure:");
		add(lblMessageStructure, "2, 6");
		
		JLabel lblUnusedSensorFields = new JLabel("Unused sensor fields:");
		add(lblUnusedSensorFields, "6, 6");
		
		JScrollPane scrollPane = new JScrollPane();
		add(scrollPane, "2, 8, 1, 5, fill, fill");
		
		table = new JTable();
		table.setCellSelectionEnabled(true);
		scrollPane.setViewportView(table);
		table.setModel(new DefaultTableModel(
			new Object[][] {
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
				{null, null, null, null},
			},
			new String[] {
				"0 - 7", "8 - 15", "16 - 23", "24 - 31"
			}
		));
		
		JScrollPane scrollPane_1 = new JScrollPane();
		add(scrollPane_1, "6, 8, fill, fill");
		
		list = new JList();
		list.setModel(new AbstractListModel() {
			String[] values = unusedValues;
			public int getSize() {
				return size;
			}
			public Object getElementAt(int index) {
				return unusedValues[index];
			}
		});
		scrollPane_1.setViewportView(list);
		
		JButton button_1 = new JButton("< 0 Padding");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				insertInTable(0);
				
			}
		});
		add(button_1, "6, 10");
		
		JButton button = new JButton("< 1 Padding");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				insertInTable(1);
			}
		});
		add(button, "6, 12");
		
		JButton btnFree = new JButton("Free >");
		btnFree.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				insertInTable("");
			}
		});
		add(btnFree, "2, 14");
		
		JButton buttonAllocate = new JButton("<    Allocate");
		buttonAllocate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
								
				if(size > 0)
					insertInTable(list.getSelectedValue());
				
				updateListAndTable();
			}
		});
		add(buttonAllocate, "6, 14");
		
		list.setSelectedIndex(0);
		updateListAndTable();
	}
	
	
	
	
	private void insertInTable(Object obj)
	{
		int selectedColumn = table.getSelectedColumn();
		int selectedRow = table.getSelectedRow();
		
		if(selectedColumn < 0 || selectedRow < 0)
		{
			selectedColumn = 0;
			selectedRow = 0;
		}
		
		table.setValueAt(obj, selectedRow, selectedColumn);
		
		if(selectedColumn < 3)
			selectedColumn++;
		else
		{
			selectedColumn = 0;
			selectedRow++;
		}
		table.setRowSelectionInterval(selectedRow, selectedRow);
		table.setColumnSelectionInterval(selectedColumn, selectedColumn);
		
		updateListAndTable();
	}
	
	private void updateListAndTable()
	{
		ArrayList<String> usedElements = new ArrayList<String>();
		ArrayList<String> unusedElements = new ArrayList<String>();
		//boolean fail = false;
		
		for(int i = 0; i < table.getColumnCount(); i++)
		{
			for(int j = 0; j < table.getRowCount(); j++)
			{
				if(table.getValueAt(j, i) == null || table.getValueAt(j, i).toString().isEmpty() || 
						table.getValueAt(j, i).toString().equals("null") || 
							table.getValueAt(j, i).toString().matches("\\d+"))
					continue;
				else
				{
					usedElements.add(table.getValueAt(j, i).toString());						
				}
			}
		}
		
		for(int x = 0; x < allSize; x++)
		{
			int y = 0;
			for(y = 0; y < usedElements.size(); y++)
			{
				if(allValues[x].equals(usedElements.get(y)))
					break;
			}
			
			if(y == usedElements.size())
				unusedElements.add(allValues[x]);
		}
		
		Object[] help = unusedElements.toArray();
		System.arraycopy(help, 0, unusedValues, 0, help.length);
		size = help.length;
		
		list.updateUI();
		
		/*if(fail)
			table.setBorder(new LineBorder(Color.red));
		else
			table.setBorder(new LineBorder(Color.gray));
			*/

	}
	
	public String[] getUnusedFields()
	{
		return unusedValues;
	}
	
	public int getRestSize()
	{
		return size;
	}
	
	public void setRestSize(int restSize)
	{
		allSize = restSize;
	}
	
	public void updateFromSubMessage(SubMessage subMessage, String[] unusedFields, int restSize)
	{
		lblMessageName.setText("Message Name: " + subMessage.name);
		lblSubtype.setText("SubType: " + subMessage.subType);
		
		boolean equal = true;
		if(restSize == allSize)
		{
			if(allSize <= restSize)
				for(int i = 0; i < allSize; i++)
					equal &= (allValues[i] == unusedFields[i]);
			else
				for(int i = 0; i < restSize; i++)
					equal &= (allValues[i] == unusedFields[i]);
		}
		else
			equal = false;
		
		if(!equal)
		{
			for(int i = 0; i < table.getColumnCount(); i++)
			{
				for(int j = 0; j < table.getRowCount(); j++)
				{
					table.setValueAt("", j, i);
				}
			}
		}
		
		allValues = unusedFields;
		allSize = restSize;
		
		updateListAndTable();
	}
	
	public void updateDataBase(DataBase dataBase, int idx)
	{
		int lastRow = -1;
		// Find last row
		for(int j = table.getRowCount()-1; j >= 0; j--)
		{
			for(int i = 0; i < table.getColumnCount(); i++)
			{
				if(table.getValueAt(j, i) != null && !table.getValueAt(j, i).toString().isEmpty())
				{
					lastRow = j;
					break;
				}
					
			}
			if(lastRow > -1)
				break;
		}
		
		if(lastRow < 0) // Then completly empty
			dataBase.subMessageList.get(idx).structure = new String[0][0];
		else
		{
			String[][] structure = new String[lastRow+1][4];
			for(int j = 0; j <= lastRow; j++)
			{
				for(int i = 0; i < table.getColumnCount(); i++)
				{
					if(table.getValueAt(j, i) == null || table.getValueAt(j, i).toString().isEmpty())
						structure[j][i] = "0";
					else
						structure[j][i] = table.getValueAt(j, i).toString();		
					System.out.print(structure[j][i] + ", ");
				}
				System.out.println();
			}
			
			dataBase.subMessageList.get(idx).structure = structure;
			
		}
	}
	
}