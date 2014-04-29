package de.tum.in.hisch.combuilder.control;

import java.util.LinkedList;

public class SensorField {

	public String name;
	public FieldType type;
	public FieldMode mode;
	public int count;
	public String description;
	
	
	public SensorField(String name, String type, String mode, int count, String description) 
	{
		this.name = name;
		this.type = FieldType.EnumFromString(type);
		this.mode = FieldMode.EnumFromString(mode);
		this.count = count;
		if(this.mode == FieldMode.none || this.mode == FieldMode.pointer)
			count = 1;
		this.description = description;
	}
	
	public String[] getBytesOfField()
	{
		String[] bytes = new String[count * type.getByteSize()];
		String currentElement = "";
		
		
		for(int i = 0; i < count; i++ )
		{
			if(count > 1)
				currentElement = name + "[" + i + "]";
			else
				currentElement = name;
			
			if(type.getByteSize() > 1)
			{
				for(int j = 0; j < type.getByteSize(); j++ )
				{
					bytes[i*type.getByteSize() + j] = currentElement + "[" + j + "]";
				}
			}
			else
				bytes[i] = currentElement;	
		}

				
		return bytes;
	}
	
	public String getInfo()
	{
		String help;
		switch(mode)
		{
		case none:
			help =  type.toString() + " m_" + name + ";";
			break;
		case pointer:
			help =  type.toString() + " *m_p" + name + ";";
			break;
		case array:
			help =  type.toString() + " m_" + name + "[" + count + "];";
			break;
		case list:
			help =  "std::vector<" + type.toString() + "> "  + "m_" + name +";";
			break;
		default:
			help = "";
		}
		
		if(description != null && !description.isEmpty())
			help = help + " // " + description;
		
		return help;
	}
	
	public String getInfoSmall()
	{
		String help;
		switch(mode)
		{
		case none:
			help =  type.toString() + " " + name;
			break;
		case pointer:
			help =  type.toString() + " *p" + name;
			break;
		case array:
			help =  type.toString() + " " + name + "[]";
			break;
		case list:
			help =  "std::vector<" + type.toString() + "> "  + name;
			break;
		default:
			help = "";
		}		
		return help;
	}	
	
}
