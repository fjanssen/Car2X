package de.tum.in.hisch.combuilder.control;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.LinkedList;

public class DataBase {
	
	public String workspacePath;
	
	public String sensorName;
	public int sensorType;
	public String description;
	
	public LinkedList<SensorField> fieldList;
	
	public LinkedList<SubMessage> subMessageList;
	
	public DataBase()
	{
		fieldList = new LinkedList<SensorField>();
		subMessageList = new LinkedList<SubMessage>();
		
		workspacePath = "";
		sensorName = "";
		sensorType = 0;
		description = "";
	}
	
	public String[] getBytesOfFields()
	{
		LinkedList<String> byteList = new LinkedList<String>();
		
		for(int i = 0; i < fieldList.size(); i++)
		{
			byteList.addAll(Arrays.asList(fieldList.get(i).getBytesOfField()));
		}
		
		return byteList.toArray(new String[0]);
	}
	
	public String toString()
	{
		StringBuilder str = new StringBuilder();
		
		str.append("Summary generated on ");
		DateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
		Date date = new Date();
		str.append(dateFormat.format(date));
		str.append("\n\n\n");
		
		str.append("-----------------------------------------\n"
				+  "-- SECTION 1: GENERAL INFORMATION      --\n"
				+  "-----------------------------------------\n\n");
		
		str.append("Working Path: " + workspacePath + "\n");
		str.append("Sensor Name:  " + sensorName + "\n");
		str.append("Sensor Type:  " + sensorType + " (0x" + Integer.toHexString(sensorType) + ")\n\n\n");
		
		str.append("-----------------------------------------\n"
				+  "-- SECTION 2: SENSOR FIELDS            --\n"
				+  "-----------------------------------------\n\n");
		
		str.append("Number of fields: " + fieldList.size() + "\n");
		str.append("Field list:\n");
		for(int i = 0; i < fieldList.size(); i++)
			str.append("    " + fieldList.get(i).getInfo() + "\n");
		str.append("\n");

		String[] bytes = getBytesOfFields();
		str.append("Number of bytes: " + bytes.length + "\n\n");
		
		if(fieldListValid())
			str.append("FIELDS OK!\n\n\n");
		else
			str.append(">>>>>>>>>>> ERROR IN FIELDS! <<<<<<<<<<<\n\n\n");
		
		str.append("-----------------------------------------\n"
				+  "-- SECTION 3: SUB MESSAGES             --\n"
				+  "-----------------------------------------\n\n");
		
		str.append("Number of messages: " + subMessageList.size() + "\n");
		str.append("Message list:\n");
		for(int i = 0; i < subMessageList.size(); i++)
			str.append("    " + subMessageList.get(i).getInfo() + "\n");
		str.append("\n");
		
		if(subMessageListValid())
			str.append("MESSAGES OK!\n\n\n");
		else
			str.append(">>>>>>>>>>> ERROR IN MESSAGES! <<<<<<<<<<<\n\n\n");
		
		str.append("-----------------------------------------\n"
				+  "-- SECTION 4: SUGGESTION               --\n"
				+  "-----------------------------------------\n\n");
		
		if(subMessageListValid() && fieldListValid())
			str.append("Ready for generation!");
		else
			str.append("Generation may fail! Please review your inputs!!!");
		
		return str.toString();
	}
	
	public boolean fieldListValid()
	{
		if(fieldList.size() < 0)
			return false;
		
		boolean duplicatedField = false;
		for(int i = 0; i < fieldList.size()-1; i++)
		{
			for(int j = i+1; j < fieldList.size(); j++)
			{
				duplicatedField |= (fieldList.get(i).name.equals(fieldList.get(j).name));
			}
		}
		return !duplicatedField;
	}
	
	public boolean subMessageListValid()
	{
		if(subMessageList.size() < 0)
			return false;
		
		boolean duplicatedField = false;
		for(int i = 0; i < subMessageList.size()-1; i++)
		{
			for(int j = i+1; j < subMessageList.size(); j++)
			{
				duplicatedField |= (subMessageList.get(i).name.equals(subMessageList.get(j).name));
				duplicatedField |= (subMessageList.get(i).subType ==  subMessageList.get(j).subType);
			}
		}
		return !duplicatedField;
	}

	public String getAnswerMessageString(int messageNumber)
	{
		StringBuilder str = new StringBuilder();
		
		if(subMessageList == null || subMessageList.size() <= messageNumber)
			return "";
		
		String[] usedFields = subMessageList.get(messageNumber).getFieldList();
		
		for(int i = 0; i < usedFields.length; i++ )
		{
			for(SensorField current : fieldList)
			{
				if(usedFields[i].equals(current.name))
				{
					str.append(current.getInfoSmall());
					str.append(", ");
					break;
				}
				
			}
		}
		
		if(str.length() > 1)
			str.delete(str.length()-2, str.length());
		return str.toString();
	}
	
	public String getMessageFieldsString(int messageNumber)
	{
		StringBuilder str = new StringBuilder();
		
		if(subMessageList == null || subMessageList.size() <= messageNumber)
			return "";
		
		String[] usedFields = subMessageList.get(messageNumber).getFieldList();
		
		for(int i = 0; i < usedFields.length; i++ )
		{
			for(SensorField current : fieldList)
			{
				if(usedFields[i].equals(current.name))
				{
					str.append("    ");
					str.append(current.getInfo());
					str.append("\n");
					break;
				}
				
			}
		}
		return str.toString();
	}
	
	
	public String getParseMessageString(int messageNumber)
	{
		StringBuilder str = new StringBuilder();
		if(subMessageList == null || subMessageList.size() <= messageNumber)
			return "";
		
		SubMessage message = subMessageList.get(messageNumber);
		
		
		str.append("    if(iLength < ");
		str.append(message.getLength());
		str.append(")\n");
		str.append("        return;\n\n");
		
		String[][] structure = message.structure;
		for(int i = 0; i < structure.length; i++)
		{
			for(int j = 0; j < structure[i].length; j++)
			{
				if(structure[i][j] != null && !structure[i][j].isEmpty() && !structure[i][j].matches("\\d*"))
				{
					if(structure[i][j].contains("["))
					{
						String help = structure[i][j].substring(0, structure[i][j].indexOf('['));
						int start = structure[i][j].indexOf('[');
						int end =  structure[i][j].indexOf(']');
						int idx = Integer.parseInt(structure[i][j].substring(start+1,end));
						
						str.append("    m_");
						str.append(help);
						str.append(" = ((alt_u32) pMessage[");
						str.append(i*4+j);
						str.append("]) << ");
						str.append(8 * idx);
						str.append(";\n");
						
						

					}
					else
					{
						str.append("    m_");
						str.append(structure[i][j]);
						str.append(" = pMessage[");
						str.append(i*4+j);
						str.append("];\n");
					}
				}
			}
		}
		
		str.append("\n    m_bValid = true;\n    // TODO: Add some more valid checks here\n");
		
		return str.toString();
	}
	
	public String getBytesString(int messageNumber)
	{
		StringBuilder str = new StringBuilder();
		SubMessage message = subMessageList.get(messageNumber);
		
		if(subMessageList == null || subMessageList.size() <= messageNumber)
			return "";
		
		str.append("    CCarMessage::getBytes(pMessage);\n\n");
		
		String[][] structure = message.structure;
		for(int i = 0; i < structure.length; i++)
		{
			for(int j = 0; j < structure[i].length; j++)
			{
				if(structure[i][j] != null && !structure[i][j].isEmpty() && !structure[i][j].matches("\\d*"))
				{
					
					if(structure[i][j].contains("["))
					{
						String help = structure[i][j].substring(0, structure[i][j].indexOf('['));
						int start = structure[i][j].indexOf('[');
						int end =  structure[i][j].indexOf(']');
						int idx = Integer.parseInt(structure[i][j].substring(start+1,end));
						
						str.append("    pMessage[");
						str.append(i*4+j+4);
						str.append("] = (m_");
						str.append(help);
						str.append(" >> ");
						str.append(8 * idx);
						str.append(") & 0xFF;\n");
					}
					else
					{
						str.append("    pMessage[");
						str.append(i*4+j+4);
						str.append("] = m_");
						str.append(structure[i][j]);
						str.append(";\n");
					}
				}
				else if(structure[i][j] != null && !structure[i][j].isEmpty())
				{
					str.append("    pMessage[");
					str.append(i*4+j+4);
					str.append("] = ");
					str.append(structure[i][j]);
					str.append(";\n");
				}
			}
		}
		
		str.append("    return m_bValid;\n");
		
		return str.toString();
	}
	
	public String getSetterString(int messageNumber)
	{
		StringBuilder str = new StringBuilder();
		SubMessage message = subMessageList.get(messageNumber);
		
		if(subMessageList == null || subMessageList.size() <= messageNumber)
			return "";		
		
		String[] usedFields = subMessageList.get(messageNumber).getFieldList();
		for(int i = 0; i < usedFields.length; i++ )
		{
			for(SensorField current : fieldList)
			{
				if(usedFields[i].equals(current.name))
				{
					str.append("    m_");
					str.append(current.name);
					str.append(" = ");
					str.append(current.name);
					str.append(";\n");
					break;
				}
				
			}
		}
		
		str.append("    m_uiFlags = m_uiFlags | 0x01; // Set response flag\n");
		
		return str.toString();
	}
	
	
	public void generate()
	{
		Generator.generate(this);
	}
	
}
