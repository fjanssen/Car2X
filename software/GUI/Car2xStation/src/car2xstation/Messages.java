/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package car2xstation;

import java.io.IOException;

/**
 *
 * @author HS
 */
class Messages {
    //Attr
    String type="00",length,subtype,flags,payload,name;
    int payloadlength;
    
    Boolean staticMsg=false;
   //Constr
   public Messages(String msgName){
       name=msgName.substring(0,msgName.length()-2);
       System.out.println(name);
       try{
            readFile file = new readFile("src/Car2xStation/COMM_CarProtocol/headers/"+msgName);
            String[] aryLines = file.OpenFile();
            
            for(int i=0;i<aryLines.length;i++){
                if(aryLines[i].indexOf("//struct for GUI:")>-1){
                    System.out.println(aryLines[i]);
                    type=aryLines[i].substring(19,21);
                    length=aryLines[i].substring(21,23);
                    subtype=aryLines[i].substring(23,25);
                    flags=aryLines[i].substring(25,27);
                    payloadlength=Integer.parseInt(length)-4;
                    break;
                }
            }
            if(type.equals("00")){
                System.out.println("message import failed!");
            }
            else{
                System.out.println(this.toString());
            }
            if(payloadlength==0) staticMsg=true;
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
       
       
       
   } 
    
   //Meth
    public ubyte[] touBytesMsg(String text,ubyte[] header){
        if(!staticMsg){
         while(payloadlength>(text.length()/2)){
            text+="0"; 
         }
            text=text.substring(0,payloadlength*2);
        }
        //System.out.println(text);
        int len=Integer.parseInt(length);
        ubyte[] out=new ubyte[8+len];
        //package header
        out[0]=header[0];//C
        out[1]=header[1];//A
        out[2]=header[2];//R
        out[3]=header[3];//X
        out[4]=header[4];//pckgnumber
        out[5]=header[5];//pckgnumber
        out[6]=new ubyte(len/256);//pckglenght
        out[7]=new ubyte(len);//pckglength
        //msg header
        out[8]=new ubyte(Integer.parseInt(type,16));//type
        out[9]=new ubyte(len);//length
        out[10]=new ubyte(Integer.parseInt(subtype,16));//subtype
        out[11]=new ubyte(Integer.parseInt(flags,16));//flags
        //payload
        for(int i=4;i<len;i++){
            
            out[8+i]=new ubyte(Integer.parseInt(text.substring(2*(i-4), 2*(i-4)+2),16));
        }
        return out;
    }
    
    public String getName(){        
        return name;
    }
    
    public String toString(){
        return "Msg: "+name+" type: "+type+" length: "+length+" subtype: "+subtype+" flags: "+flags;
    }
}
