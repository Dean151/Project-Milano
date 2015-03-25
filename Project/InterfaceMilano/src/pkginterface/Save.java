package pkginterface;

import java.io.File;
import java.io.FileWriter;

/**
 * Class to save frame's data in a text file
 * @author Charles Brandon
 */
public class Save {
    
    /**
     * Save frame's data in a text file
     * @param str Frame's data
     */
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
