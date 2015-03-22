/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkginterface;

import java.util.ArrayList;

/**
 *
 * @author Charles
 */
public class DonneesFrame {
    private static String donnees="";
    
    public static void ajoutFrame (int frame, ArrayList<Ligne> lignes){
        donnees = donnees + "frame:\r\n"+frame+"\r\n"+"cam:\r\n";
        for(Ligne ligne : lignes){
            if(isValid(ligne)){
                donnees = donnees+ligne.getField2Dx().getText()+" "+ligne.getField2Dy().getText()+"\r\n";
            }
        }
        donnees = donnees + "obj:\r\n";
        for(Ligne ligne : lignes){
            if(isValid(ligne)){
                donnees = donnees+ligne.getField3Dx().getText()+" "+ligne.getField3Dy().getText()+" "+ligne.getField3Dz().getText()+"\r\n";
            }
        }
        donnees = donnees+"end\r\n\r\n";
        System.out.println(donnees);
    }
    
    public static Boolean isValid(Ligne ligne){
        try{
            Integer.parseInt(ligne.getField2Dx().getText());
            Integer.parseInt(ligne.getField2Dy().getText());
            Float.parseFloat(ligne.getField3Dx().getText());
            Float.parseFloat(ligne.getField3Dy().getText());
            Float.parseFloat(ligne.getField3Dz().getText());
        }
        catch(NumberFormatException e){
            return false;
        }
        return true;
    }

    public static String getDonnees() {
        return donnees;
    }
    
    
}
