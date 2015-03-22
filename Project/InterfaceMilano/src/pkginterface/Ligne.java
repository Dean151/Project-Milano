/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkginterface;

import javax.swing.JLabel;
import javax.swing.JTextField;

/**
 *
 * @author Charles
 */
public class Ligne {
    private javax.swing.JTextField field2Dx;
    private javax.swing.JTextField field2Dy;
    
    private javax.swing.JLabel vide;
    
    private javax.swing.JTextField field3Dx;
    private javax.swing.JTextField field3Dy;
    private javax.swing.JTextField field3Dz;

    public Ligne() {
        this.field2Dx = new javax.swing.JTextField();
        this.field2Dy = new javax.swing.JTextField();
        
        this.vide = new javax.swing.JLabel();
        
        this.field3Dx = new javax.swing.JTextField();
        this.field3Dy = new javax.swing.JTextField();
        this.field3Dz = new javax.swing.JTextField();

    }

    public JTextField getField2Dx() {
        return field2Dx;
    }

    public JTextField getField2Dy() {
        return field2Dy;
    }

    public JLabel getVide() {
        return vide;
    }

    public JTextField getField3Dx() {
        return field3Dx;
    }

    public JTextField getField3Dy() {
        return field3Dy;
    }

    public JTextField getField3Dz() {
        return field3Dz;
    }
    
    
    
}
