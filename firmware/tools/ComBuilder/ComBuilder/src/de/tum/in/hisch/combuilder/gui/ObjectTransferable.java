package de.tum.in.hisch.combuilder.gui;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

public class ObjectTransferable implements Transferable
{
  public static final DataFlavor FLAVOR=new DataFlavor(Object.class,"Object");

  Object myValue;

  public ObjectTransferable(Object value)
  {
    myValue=value;
  }

  public DataFlavor[] getTransferDataFlavors()
  {
    return new DataFlavor[]{FLAVOR};
  }

  public boolean isDataFlavorSupported(DataFlavor flavor)
  {
    return flavor==FLAVOR;
  }

  public Object getTransferData(DataFlavor flavor) throws
         UnsupportedFlavorException, IOException
  {
    if(flavor==FLAVOR) return myValue;
    else throw new UnsupportedFlavorException(flavor);
  }    

}