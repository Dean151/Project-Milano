package pkginterface;

import java.util.ArrayList;

/**
 * Class where the frame's data are saved
 * @author Charles Brandon
 */
public class FrameData {
    private static String data="";
    
    /**
     * Save data of a frame in the good way
     * @param frame number of the frame in the video
     * @param lines list of text fields in the gui
     */
    public static void addFrame (int frame, ArrayList<Line> lines){
        data = data + "frame:\r\n"+frame+"\r\n"+"cam:\r\n";
        for(Line line : lines){
            if(isValid(line)){
                data = data+line.getField2Dx().getText()+" "+line.getField2Dy().getText()+"\r\n";
            }
        }
        data = data + "obj:\r\n";
        for(Line line : lines){
            if(isValid(line)){
                data = data+line.getField3Dx().getText()+" "+line.getField3Dy().getText()+" "+line.getField3Dz().getText()+"\r\n";
            }
        }
        data = data+"end\r\n\r\n";
    }
    
    /**
     * Make sure that the text in the text field is an int or a float
     * @param line a text field in the gui
     * @return true if the text is valid
     */
    public static Boolean isValid(Line line){
        try{
            Integer.parseInt(line.getField2Dx().getText());
            Integer.parseInt(line.getField2Dy().getText());
            Float.parseFloat(line.getField3Dx().getText());
            Float.parseFloat(line.getField3Dy().getText());
            Float.parseFloat(line.getField3Dz().getText());
        }
        catch(NumberFormatException e){
            return false;
        }
        return true;
    }

    /**
     * Getter method of "data"
     * @return frames' data
     */
    public static String getData() {
        return data;
    }
    
    
}
