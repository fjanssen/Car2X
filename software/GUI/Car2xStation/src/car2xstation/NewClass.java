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
public class NewClass {
    
    public static void main(String args[]) {
        int a= 124;
        byte c= (byte) a;
        byte d = (byte) (a/256);
        char e=(char)c;
        char f=(char)d;
        System.out.println(a);
        System.out.println(c);
        System.out.println(d);
        System.out.println(e);
        System.out.println(f);
        String ii="test: "+f+e;
        System.out.println(ii);
        
    }
    
}
