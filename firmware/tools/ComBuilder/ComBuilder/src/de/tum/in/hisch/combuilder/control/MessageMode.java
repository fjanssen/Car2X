package de.tum.in.hisch.combuilder.control;

public enum MessageMode {
	polling, startup;
	
	public static MessageMode EnumFromString(String str)
	{
		if(str.equals("polling"))
			return polling;
		else if(str.equals("startup"))
			return startup;
			return polling;
	}
}
