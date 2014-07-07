/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package car2xstation;

import java.util.ArrayList;
import java.io.IOException;

/**
 *
 * @author HS
 */
class sendingUnit {
  
    //Attr
    ArrayList<Messages> myMsgs=new ArrayList<>();
   
    //Constr
    public sendingUnit(){
        String file_name="src/Car2xStation/COMM_CarProtocol/CarProtocol.cpp";
        try{
            readFile file = new readFile(file_name);
            String[] aryLines = file.OpenFile();
            int i1, i2, start=0;
            
            for(int i=0;i<aryLines.length;i++){
                
                if(start==1){
                    i1=aryLines[i].indexOf("C");
                    i2=aryLines[i].indexOf(".h")+2;
                if(i1>-1&&aryLines[i].indexOf("#include")>-1){
                    System.out.println(aryLines[i]);
                    myMsgs.add(new Messages(aryLines[i].substring(i1, i2)));
                }
                else{
                    break;
                };                       
                }
                if(aryLines[i].contains("//Car2X Message imports")) start=1;
            }
            
        }catch(IOException e){
            System.out.println(e.getMessage());
        }       
    }
    
    //Meth
    public ubyte[] sendMessage(int id,String text,ubyte[] header){
        ubyte[] out=myMsgs.get(id).touBytesMsg(text,header);
        return out;        
    }
    
    public String[] getStrings(){
        String[] out=new String[myMsgs.size()];
        int j=0;
        for(Messages i:myMsgs){
            out[j]=i.getName();
            j++;
        }
        return out;
    }

    public ubyte[] doRC(String text, ubyte[] header) {
        Messages cMsg=null;
                for(Messages m:myMsgs){
                    if(m.getName().equals("CControlMessage")){
                    cMsg=m;  
                    break;
                    }
                }
        if(cMsg==null) return null;
        else{
            //evaluate msg payload from pressed keys TODO
            
            return cMsg.touBytesMsg(text,header);
        }
    }

    ubyte[] getRC(ubyte[] header, boolean b) {
        Messages cMsg=null;
                for(Messages m:myMsgs){
                    if(m.getName().equals("CRemoteControlMessage")){
                    cMsg=m;  
                    break;
                    }
                }
        if(cMsg==null) return null;
        else{
            String text="00000000";
            if(b){
                text=car2xstation.myIP0x;   //own ip
            }
            return cMsg.touBytesMsg(text,header);
        }
    }
    
}
