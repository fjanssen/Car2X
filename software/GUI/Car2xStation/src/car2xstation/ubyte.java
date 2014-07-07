/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package car2xstation;

/**
 *
 * @author HS
 */
class ubyte {
    //attr
    private int value;
    
    //constr
    public ubyte(byte b){
        //result: 0...255
        if(b>=0)value=(int)b;
        else{
            value=128+(int)b;
        }
    }
    
    public ubyte(int i){
        //result: 0...255
        if(i>=0)value=0xFF&i;
        else{
            value=0xFF&(-i);//not needed
        }
    }
    
    public ubyte(char c){
        //result: 0...255
        byte b=(byte)c;
        if(b>=0)value=(int)b;
        else{
            value=128+(int)b;
        }
    }
    
    //meth
    public byte tosByte(){
        return (byte) value;
    }
    
    @Override
    public String toString(){
        String out =Integer.toHexString(value);
        while(out.length()<2){
            out="0"+out;
        }
        return "x"+ out;
    }
}
