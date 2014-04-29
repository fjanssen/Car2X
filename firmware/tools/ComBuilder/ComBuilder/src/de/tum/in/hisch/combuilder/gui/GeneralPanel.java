package de.tum.in.hisch.combuilder.gui;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JSeparator;
import javax.swing.JButton;
import javax.swing.JSpinner;
import javax.swing.JTextArea;
import javax.swing.JList;

import java.awt.GridLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

import net.miginfocom.swing.MigLayout;

import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.factories.FormFactory;
import com.jgoodies.forms.layout.RowSpec;

import de.tum.in.hisch.combuilder.control.DataBase;

import javax.swing.border.LineBorder;

import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.io.File;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeSupport;

import javax.swing.JScrollPane;
import javax.swing.AbstractListModel;

public class GeneralPanel extends JPanel {
	private JTextField tfSensorName;
	private JTextField tfPath;
	private JSpinner spType;
	private JTextArea taDescription;
	private JList listGeneratedFiles;
	private String[] fileList;
	
	private boolean pathValid, nameValid, allValid;
	private PropertyChangeSupport changes;
	
	/**
	 * Create the panel.
	 */
	public GeneralPanel() {
		
		changes = new PropertyChangeSupport( this );
		
		setBorder(new LineBorder(new Color(0, 0, 0)));
		setLayout(new FormLayout(new ColumnSpec[] {
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("106px:grow"),
				FormFactory.LABEL_COMPONENT_GAP_COLSPEC,
				ColumnSpec.decode("max(38dlu;default)"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("max(101dlu;pref):grow"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("90px"),
				FormFactory.LABEL_COMPONENT_GAP_COLSPEC,
				ColumnSpec.decode("max(2dlu;default)"),},
			new RowSpec[] {
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("27px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("9px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("121px:grow"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("7px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("28px"),
				FormFactory.NARROW_LINE_GAP_ROWSPEC,
				RowSpec.decode("102px:grow"),
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,}));
		
		pathValid = nameValid = allValid = false;
		
		listGeneratedFiles = new JList();
		JScrollPane scrollPane_1 = new JScrollPane();
		add(scrollPane_1, "2, 18, 7, 1, fill, fill");
		scrollPane_1.setViewportView(listGeneratedFiles);
		
		JLabel lblPath = new JLabel("Workspace Path:");
		add(lblPath, "2, 2, fill, fill");
		
		tfPath = new JTextField();
		tfPath.addKeyListener(new KeyAdapter() {
			@Override
			public void keyReleased(KeyEvent arg0) {
				if(arg0.getKeyCode() == KeyEvent.VK_ENTER)
				{
					updatePath();
				}
			}
		});
		tfPath.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent arg0) {
				updatePath();				
			}
		});
		tfPath.setColumns(10);
		add(tfPath, "4, 2, 3, 1, fill, fill");
		
		JButton btnBrowse = new JButton("Browse");
		btnBrowse.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				JFileChooser j = new JFileChooser();
				j.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				int opt = j.showSaveDialog(null);

				if(opt == JFileChooser.APPROVE_OPTION)
				{
					tfPath.setText(j.getSelectedFile().getAbsolutePath());
					updatePath();
				}			
			}
		});
		add(btnBrowse, "8, 2, fill, fill");
		
		JSeparator separator = new JSeparator();
		add(separator, "2, 4, 7, 1, fill, fill");
		
		JLabel lblSensorName = new JLabel("Sensor Name:");
		add(lblSensorName, "2, 6, fill, fill");
		
		tfSensorName = new JTextField();
		tfSensorName.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent arg0) {
				updateSensorName();
				updateFileList();				
				
			}
		});
		tfSensorName.addKeyListener(new KeyAdapter() {
			@Override
			public void keyReleased(KeyEvent e) {
				if(e.getKeyCode() == KeyEvent.VK_ENTER)
					updateSensorName();
				updateFileList();
			}
		});
		add(tfSensorName, "4, 6, 3, 1, fill, fill");
		tfSensorName.setColumns(10);
		
		JLabel lblSensorType = new JLabel("Sensor Type:");
		add(lblSensorType, "2, 8, fill, fill");
		
		spType = new JSpinner();
		add(spType, "4, 8, fill, fill");
		
		JLabel lblSensorDescription = new JLabel("Description:");
		add(lblSensorDescription, "2, 10, fill, fill");
		
		JScrollPane scrollPane = new JScrollPane();
		add(scrollPane, "2, 12, 7, 1, fill, fill");
		
		taDescription = new JTextArea();
		scrollPane.setViewportView(taDescription);
		
		JSeparator separator_1 = new JSeparator();
		add(separator_1, "2, 14, 7, 1, fill, fill");
		
		JLabel lblGeneratedFiles = new JLabel("Generated Files:");
		add(lblGeneratedFiles, "2, 16, fill, fill");
		
		
	}
	
	public String getSensorName()
	{
		return tfSensorName.getText();
	}
	
	
	private void updatePath()
	{
		File f = new File(tfPath.getText());
		if(!f.exists() || !f.isDirectory()) 
		{
			tfPath.setBorder(new LineBorder(Color.red));
			pathValid = false;
		}
		else
		{
			tfPath.setBorder(new LineBorder(Color.GRAY));
			pathValid = true;
		}
	}
	
	private void updateSensorName()
	{
		tfSensorName.setText(tfSensorName.getText().replaceAll("\\s+", "_"));
		if(tfSensorName.getText().length() < 3)
			tfSensorName.setBorder(new LineBorder(Color.red));
		else
			tfSensorName.setBorder(new LineBorder(Color.GRAY));
	}
	
	private void updateFileList()
	{
		String currentSensorName = tfSensorName.getText().replaceAll("\\s+", "_");
		fileList = new String[4];
		fileList[0] = "." + File.separatorChar + "networking" + File.separatorChar + currentSensorName + "Messages.h";
		fileList[1] = "." + File.separatorChar + "networking" + File.separatorChar + currentSensorName + "Messages.cpp";
		fileList[2] = "." + File.separatorChar + "sensors" + File.separatorChar + currentSensorName + "Sensor.h";
		fileList[3] = "." + File.separatorChar + "sensors" + File.separatorChar + currentSensorName + "Sensor.cpp";
		
		AbstractListModel list = new AbstractListModel() {
			String[] values = fileList;
			public int getSize() {
				return values.length;
			}
			public Object getElementAt(int index) {
				return values[index];
			}
			
		};				
		listGeneratedFiles.setModel(list);
		
		// Call to parent only if becomes valid
		nameValid = (currentSensorName.length() > 2);
		firePropertyChange("valid", allValid + "", (nameValid && pathValid) + "");	
		allValid = nameValid && pathValid;
		
	}
	
	public void updateDataBase(DataBase dataBase)
	{
		dataBase.workspacePath = tfPath.getText();
		dataBase.sensorName = tfSensorName.getText();
		dataBase.sensorType = (int) spType.getValue();
		dataBase.description = taDescription.getText();
	}
}
