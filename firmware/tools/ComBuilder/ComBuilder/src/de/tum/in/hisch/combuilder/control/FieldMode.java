package de.tum.in.hisch.combuilder.control;

public enum FieldMode {
	none, pointer, array, list;
	
	public static FieldMode EnumFromString(String str)
	{
		if(str.equals(""))
			return none;
		else if(str.equals("pointer"))
			return pointer;
		else if(str.equals("array"))
			return array;
		else if(str.equals("list"))
			return list;
		else
			return none;
	}
}
