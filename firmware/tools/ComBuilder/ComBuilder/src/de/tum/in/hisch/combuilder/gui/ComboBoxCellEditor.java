package de.tum.in.hisch.combuilder.gui;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.AbstractCellEditor;
import javax.swing.DefaultCellEditor;
import javax.swing.JComboBox;
import javax.swing.JTable;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableModel;

public class ComboBoxCellEditor extends DefaultCellEditor
{

    public ComboBoxCellEditor( JComboBox component )
    {
        super( component );
     
        component.addActionListener( new ActionListener()
        {
          @Override
          public void actionPerformed( ActionEvent e )
          {
            stopCellEditing();
          }
        } );
      }
     
      @Override
      public Component getTableCellEditorComponent( JTable table, Object value, boolean isSelected, int row,
                                                    int column )
      {
        JComboBox editor = (JComboBox) super.getTableCellEditorComponent( table, value, isSelected, row, column );
     
        editor.setSelectedItem( value );
     
        return editor;
      }
     
      @Override
      public Object getCellEditorValue()
      {
        return ((JComboBox) getComponent()).getSelectedItem();
      }
}