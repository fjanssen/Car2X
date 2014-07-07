/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package car2xstation;

import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
/**
 *
 * @author HS
 */
public class readFile {
    private String path;
    
    
    public readFile(String file_path){
        path=file_path;       
    }
    
    public String[] OpenFile() throws IOException{
        FileReader fr = new FileReader(path);
        BufferedReader textReader= new BufferedReader(fr);
        
        int numberOfLines=readLines();
        String[] textData=new String[numberOfLines];
        
        for(int i=0;i<numberOfLines;i++){
            textData[i]=textReader.readLine();
        }
        
        textReader.close();
        return textData;
    }
    
    int readLines() throws IOException{
        FileReader ftr = new FileReader(path);
        BufferedReader bf= new BufferedReader(ftr);
        String aLine;
        int numOfLines=0;
        
        while((aLine=bf.readLine())!=null){
            numOfLines++;
        }
        bf.close();
        return numOfLines;
    }
}
