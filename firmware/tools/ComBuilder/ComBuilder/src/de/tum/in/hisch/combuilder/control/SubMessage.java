package de.tum.in.hisch.combuilder.control;

import java.util.LinkedList;

public class SubMessage {

	public String name;
	public int subType;
	public MessageMode mode;
	public int frequency;
	public String description;
	
	public String[][] structure;
	
	public SubMessage(String name, int subType, String mode, int frequency,	String description) 
	{
		this.name = name;
		this.subType = subType;
		this.mode = MessageMode.EnumFromString(mode);
		this.frequency = frequency;
		this.description = description;
	}
	
	public String getInfo()
	{
		StringBuilder str = new StringBuilder();
		str.append(name + "Message" + " of SubType " + subType + "\n    Works ");
		if(mode == MessageMode.startup)
			str.append("on startup.\n");
		else
			str.append("every " + frequency + " Message-Cycles.\n");
		str.append("    Message Structure:\n");
		str.append(getStructureString());
		return str.toString();
	}
	
	public String getStructureString()
	{
		StringBuilder str = new StringBuilder();
		for(int i = 0; i < structure.length; i++)
		{
			str.append(structure[i][0]);
			for(int j = 1; j < structure[i].length; j++)
			{
				str.append(" | " + structure[i][j]);
			}
			str.append("\n");
		}
		
		return str.toString();
	}
	
	public String[] getFieldList()
	{
		LinkedList<String> list = new LinkedList<String>();
		String help;
		
		for(int i = 0; i < structure.length; i++)
		{
			for(int j = 0; j < structure[i].length; j++)
			{
				if(structure[i][j] != null && !structure[i][j].isEmpty() && !structure[i][j].matches("\\d*"))
				{										
					if(structure[i][j].contains("["))					
						help = structure[i][j].substring(0, structure[i][j].indexOf('['));
					else
						help = structure[i][j];
					
					if(!list.contains(help))
						list.add(help);
				}
			}
		}
		
		return list.toArray(new String[0]);
	}
	
	public int getLength()
	{
		return 4 * structure.length;
	}
	
}
