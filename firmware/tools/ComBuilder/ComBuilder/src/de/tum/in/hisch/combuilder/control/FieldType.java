package de.tum.in.hisch.combuilder.control;

public enum FieldType {

	alt_u8, alt_8, alt_u16, alt_16, alt_u32, alt_32;
	
	public int getByteSize()
	{
		switch(this)
		{
		case alt_u8:
		case alt_8:
			return 1;
			
		case alt_u16:
		case alt_16:
			return 2;
			
		case alt_u32:
		case alt_32:
			return 4;
			
		default:
			return 1;
		}
	}
	
	public static FieldType EnumFromString(String str)
	{
		if(str.equals("u8"))
			return alt_u8;
		else if(str.equals("8"))
			return alt_8;
		else if(str.equals("u16"))
			return alt_u16;
		else if(str.equals("16"))
			return alt_16;
		else if(str.equals("u32"))
			return alt_u32;
		else if(str.equals("32"))
			return alt_32;
		else
			return alt_u8;
	}
}
