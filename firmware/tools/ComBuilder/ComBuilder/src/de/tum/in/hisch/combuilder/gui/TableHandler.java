package de.tum.in.hisch.combuilder.gui;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.dnd.DnDConstants;

import javax.swing.JComponent;
import javax.swing.JTable;
import javax.swing.TransferHandler;


public class TableHandler extends TransferHandler
{
  JTable  myTable;

  public TableHandler(JTable table)
  {
    myTable = table;
    table.setTransferHandler(this);
    table.setDragEnabled(true);
  }

  public boolean canImport(JComponent comp, DataFlavor[] transferFlavors)
  {
    if (myTable != comp) return false;
    // eventuell DataFlavor noch prüfen
    return true;
  }

  protected Transferable createTransferable(JComponent c)
  {
    if (c == myTable)
    {
      int row = myTable.getSelectedRow();
      int col = myTable.getSelectedColumn();
      Object value = myTable.getModel().getValueAt(row, col);

      // Hier ein entsprechendes Transferable benutzen
      return new ObjectTransferable(value);
    }
    else
    {
      return super.createTransferable(c);
    }
  }

  public boolean importData(JComponent comp, Transferable t)
  {
    if (comp == myTable)
    {
      try
      {
        Object value = t.getTransferData(ObjectTransferable.FLAVOR);

        int row = myTable.getSelectedRow();
        int col = myTable.getSelectedColumn();
        myTable.getModel().setValueAt(value,row, col);
        return true;
      }
      catch (Exception e)
      {
      }
    }
    return super.importData(comp, t);
  }

  public int getSourceActions(JComponent c)
  {
    if (myTable == c) return DnDConstants.ACTION_COPY;
    else return super.getSourceActions(c);
  }

}