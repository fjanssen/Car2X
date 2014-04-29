package de.tum.in.hisch.combuilder.gui;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;

import java.awt.Color;

import javax.swing.JLabel;

import java.awt.FlowLayout;

import javax.swing.ImageIcon;

import java.awt.Font;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import de.tum.in.hisch.combuilder.control.DataBase;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import java.util.LinkedList;

public class WizardFrame extends JFrame {

	private JPanel contentPane;
	private JButton btnPrevious;
	private JButton btnNext;
	private JButton btnFinish;
	private JButton btnCancel;
	
	private int page = 0;
	private GeneralPanel generalPanel;
	private FieldsPanel fieldsPanel;
	private SubMessagesPanel subMessagesPanel;
	private LinkedList<MessagePanel> messagePanels;
	private SummaryPanel summaryPanel;
	
	private boolean generalPanelValid = false;
	private boolean messagePanelValid = false;
	
	private static WizardFrame frame;
	private static DataBase dataBase;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					frame = new WizardFrame();
					frame.setVisible(true);
					dataBase = new DataBase();
					
					/*
					dataBase.sensorName = "Test";
					dataBase.description = "This is a test for the code generator of the tool ComBuilder."
							+ "\nWe have to check if the line-style is working or not......"
							+ "\nWhat a nonsens ;)              "
							+ "\n 1231231234564 56 4564   567 89  7  87 9    8 7.";
					
					dataBase.sensorType = 100;
					dataBase.workspacePath = "C:\\Users\\Flo\\Documents\\Tests";
					
					dataBase.fieldList.add(new SensorField("distance", "16", "", 1, "Distance in 2-complement"));
					dataBase.fieldList.add(new SensorField("validFlags", "u8", "", 1, "Valid if not zero"));
					dataBase.fieldList.add(new SensorField("name", "u8", "array", 8, "Name of the sensor"));
					
					dataBase.subMessageList.add(new SubMessage("Main", 0, "startup", 0, "Message asks for the sensor name.\nOnly on startup."));
					dataBase.subMessageList.add(new SubMessage("Values", 1, "polling", 1, "Message asks for the current distance value.\nWorks on every cycle."));
					
					String[][] struct1 = {{"name[0]", "name[1]", "name[2]", "name[3]"}, {"name[4]", "name[5]", "name[6]", "name[7]"}};
					dataBase.subMessageList.get(0).structure = struct1;
				
					String[][] struct2 = {{"distance[0]", "distance[1]", "0", "validFlags"}};
					dataBase.subMessageList.get(1).structure = struct2;
					
					System.out.println(dataBase.getAnswerMessageString(0) + "\n");
					System.out.println(dataBase.getAnswerMessageString(1) + "\n");
					
					dataBase.generate();
					*/
					
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public static DataBase getDataBase()
	{
		return dataBase;
	}

	/**
	 * Create the frame.
	 */
	public WizardFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 564, 549);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		JPanel panelTitle = new JPanel();
		panelTitle.setBackground(Color.BLACK);
		contentPane.add(panelTitle, BorderLayout.NORTH);
		panelTitle.setLayout(new BorderLayout(0, 0));
		
		JLabel lblWizardForNew = new JLabel("  Wizard for new Sensor");
		lblWizardForNew.setFont(new Font("Arial Black", Font.BOLD, 16));
		lblWizardForNew.setForeground(Color.WHITE);
		panelTitle.add(lblWizardForNew, BorderLayout.WEST);
		
		JLabel label = new JLabel("");
		label.setIcon(new ImageIcon("C:\\Users\\Flo\\Desktop\\ComBuilder\\ComBuilder\\resources\\newfile2.jpg"));
		panelTitle.add(label, BorderLayout.EAST);
		
		JPanel panelBottom = new JPanel();
		contentPane.add(panelBottom, BorderLayout.SOUTH);
		panelBottom.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		btnPrevious = new JButton("< Back");
		btnPrevious.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(page == 1)		
				{
					contentPane.remove(fieldsPanel);
					contentPane.add(generalPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					btnPrevious.setEnabled(false);
					btnNext.setEnabled(true);
					page--;
				}
				else if(page == 2)		
				{
					contentPane.remove(subMessagesPanel);
					contentPane.add(fieldsPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					setTitle(generalPanel.getSensorName());
					page--;
				}
				else if(page == 3)		
				{
					contentPane.remove(messagePanels.getFirst());
					contentPane.add(subMessagesPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					setTitle(generalPanel.getSensorName());
					page--;
				}
				else if(page < 3+messagePanels.size())
				{
					contentPane.remove(messagePanels.get(page-3));
					contentPane.add(messagePanels.get(page-4), BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					page--;
				}
				else if(page == 3+messagePanels.size())
				{
					contentPane.remove(summaryPanel);
					contentPane.add(messagePanels.get(page-4), BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					btnNext.setEnabled(true);
					page--;
				}
			}
		});
		panelBottom.add(btnPrevious);
		
		btnNext = new JButton("Next >");
		btnNext.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(page == 0)		
				{
					generalPanel.updateDataBase(dataBase);
					contentPane.remove(generalPanel);
					contentPane.add(fieldsPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					btnPrevious.setEnabled(true);
					btnNext.setEnabled(true);
					setTitle(dataBase.sensorName);
					page++;
				}
				else if(page == 1)		
				{
					fieldsPanel.updateDataBase(dataBase);
					contentPane.remove(fieldsPanel);
					contentPane.add(subMessagesPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					btnNext.setEnabled(true);
					
					String[] help = dataBase.getBytesOfFields();
					for(int i = 0; i < help.length; i++)
					{
						System.out.print(help[i] + ", ");
					}
					System.out.println("\n---------------------------------------\n");
					
					
					
					page++;
				}
				else if(page == 2)		
				{
					subMessagesPanel.updateDataBase(dataBase);
					contentPane.remove(subMessagesPanel);
					
					generateMessagePanels();
					
					contentPane.add(messagePanels.getFirst(), BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					page++;
				}
				else if(page < 2+messagePanels.size())
				{
					messagePanels.get(page-3).updateDataBase(dataBase, page-3);
					contentPane.remove(messagePanels.get(page-3));
					contentPane.add(messagePanels.get(page-2), BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					messagePanels.get(page-2).updateFromSubMessage(dataBase.subMessageList.get(page-2), messagePanels.get(page-3).getUnusedFields(), messagePanels.get(page-3).getRestSize());
					messagePanels.get(page-2).setRestSize(messagePanels.get(page-3).getRestSize());
					page++;
				}
				else if(page == 2+messagePanels.size())
				{
					messagePanels.get(page-3).updateDataBase(dataBase, page-3);
					contentPane.remove(messagePanels.get(page-3));
					contentPane.add(summaryPanel, BorderLayout.CENTER);
					SwingUtilities.updateComponentTreeUI(frame);
					summaryPanel.updateFromDataBase(dataBase);
					btnNext.setEnabled(false);
					page++;
				}
			}
		});
		panelBottom.add(btnNext);
		
		btnFinish = new JButton("Finish");
		btnFinish.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
			}
		});
		panelBottom.add(btnFinish);
		
		btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(ABORT);
			}
		});
		panelBottom.add(btnCancel);
		
		
		btnFinish.setEnabled(false);
		btnPrevious.setEnabled(false);
		btnNext.setEnabled(false);	
		
		initPanels();
		contentPane.add(generalPanel, BorderLayout.CENTER);
		page = 0;
	
	}
	
	private void initPanels()
	{
		generalPanel = new GeneralPanel();
		generalPanel.addPropertyChangeListener(new PropertyChangeListener() {
			@Override
			public void propertyChange(PropertyChangeEvent arg0) {
				if(arg0.getNewValue() != null)
					generalPanelValid = (arg0.getNewValue().toString().compareTo("true") == 0);
				btnNext.setEnabled(generalPanelValid);
			}
		});	
		
		fieldsPanel = new FieldsPanel();
		
		
		subMessagesPanel = new SubMessagesPanel();
		
		messagePanels = new LinkedList<MessagePanel>();
		
		summaryPanel = new SummaryPanel();
		
	}
	
	private void generateMessagePanels()
	{
		messagePanels.clear();
		for(int i = 0; i < dataBase.subMessageList.size(); i++)
		{
			MessagePanel current = new MessagePanel();
			
			if(i == 0)
			{
				String[] data = dataBase.getBytesOfFields();
				current.updateFromSubMessage(dataBase.subMessageList.get(i), data, data.length);
			}
			else
				current.updateFromSubMessage(dataBase.subMessageList.get(i), messagePanels.getLast().getUnusedFields(), messagePanels.getLast().getRestSize());
			
			messagePanels.add(current);
		}
	}

}
