/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkginterface;

import java.io.File;
import java.io.FileWriter;

/**
 *
 * @author Charles
 */
public class Enregistrement {
    public static void Enregistrer(String str){
        try{
            File ff=new File("Frame.txt"); 
            ff.createNewFile();
            FileWriter ffw=new FileWriter(ff);
            ffw.write(str);  
            ffw.close(); 
        } catch (Exception e) {
            e.printStackTrace();
        }
        
    }
}
