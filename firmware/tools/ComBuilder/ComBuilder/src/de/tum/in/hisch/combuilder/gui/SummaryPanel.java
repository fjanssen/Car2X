package de.tum.in.hisch.combuilder.gui;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.factories.FormFactory;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.RowSpec;

import de.tum.in.hisch.combuilder.control.DataBase;
import java.awt.Font;

public class SummaryPanel extends JPanel {
	private JTextArea taDescription;
	
	/**
	 * Create the panel.
	 */
	public SummaryPanel() {
		
		
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
				RowSpec.decode("7px"),}));
		
		JLabel lblSummary = new JLabel("Summary:");
		add(lblSummary, "2, 2");
		
		JButton btnGenerate = new JButton("Generate");
		btnGenerate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				WizardFrame.getDataBase().generate();
				
			}
		});
		add(btnGenerate, "8, 2");
		
		JScrollPane scrollPane = new JScrollPane();
		add(scrollPane, "2, 4, 7, 9, fill, fill");
		
		taDescription = new JTextArea();
		taDescription.setFont(new Font("Consolas", Font.PLAIN, 13));
		taDescription.setEditable(false);
		scrollPane.setViewportView(taDescription);
		
	}
	
	public void updateFromDataBase(DataBase dataBase)
	{
		taDescription.setText(dataBase.toString());
	}
	
	
}
