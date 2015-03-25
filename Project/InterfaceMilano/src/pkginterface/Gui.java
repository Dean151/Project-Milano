package pkginterface;

import java.awt.GridLayout;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

/**
 * Main gui of the program. It allows you to choose the coordinates in a frame 
 * and to match them to the 3D coordinates
 * @author Charles Brandon
 */
public class Gui extends javax.swing.JFrame {

    /**
     * Creates new form gui
     */
    public Gui() {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {               
                initComponents();
                settingUp();
            }
        });
    }
    
    /**
     * Init basic components
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        imagePanel = new javax.swing.JPanel();
        imageLabel = new javax.swing.JLabel();
        dataPanel = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        imagePanel.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        javax.swing.GroupLayout imagePanelLayout = new javax.swing.GroupLayout(imagePanel);
        imagePanel.setLayout(imagePanelLayout);
        imagePanelLayout.setHorizontalGroup(
            imagePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(imagePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(imageLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 528, Short.MAX_VALUE)
                .addContainerGap())
        );
        imagePanelLayout.setVerticalGroup(
            imagePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(imagePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(imageLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 459, Short.MAX_VALUE)
                .addContainerGap())
        );

        dataPanel.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        javax.swing.GroupLayout dataPanelLayout = new javax.swing.GroupLayout(dataPanel);
        dataPanel.setLayout(dataPanelLayout);
        dataPanelLayout.setHorizontalGroup(
            dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 346, Short.MAX_VALUE)
        );
        dataPanelLayout.setVerticalGroup(
            dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 567, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(imagePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(dataPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(dataPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(imagePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
   
    /**
     * Init secondary components
     */
    public void settingUp(){
        nextFrame.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                nextFrameMouseClicked(evt);
            }
        });
        
        done.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                doneMouseClicked(evt);
            }
        });
        
        imageLabel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                labelImageMouseClicked(evt);
            }
        });
        
        dataPanel.setLayout(new GridLayout(16,6));
        dataPanel.add(label2Dx);
        dataPanel.add(label2Dy);
        dataPanel.add(new javax.swing.JLabel());
        dataPanel.add(label3Dx);
        dataPanel.add(label3Dy);
        dataPanel.add(label3Dz);
        
        for(int j=1;j<=15;j++){
            if(j<=nbLines){
            Line line = new Line();
            lines.add(line);
            
            dataPanel.add(line.getField2Dx());
            dataPanel.add(line.getField2Dy());
            dataPanel.add(line.getVide());
            dataPanel.add(line.getField3Dx());
            dataPanel.add(line.getField3Dy());
            dataPanel.add(line.getField3Dz());
            }
            else if(j!=15){
                for(int k=0;k<6;k++){
                    dataPanel.add(new javax.swing.JLabel());
                }
            }
            if(j==15){
                for(int k=0;k<4;k++){
                    dataPanel.add(new javax.swing.JLabel());
                }
                dataPanel.add(nextFrame);
                dataPanel.add(done);
            }
            
        }
    }
    
    /**
     * Add a frame to the left panel
     * @param path Path of the frame's file
     */
    public void setImage(String path){
        Image img = null;
        try{
            img = ImageIO.read(new File(path));
        }
        catch(IOException e){
            System.out.println("Frame not found");
        }
        
        imageLabel.setIcon(new javax.swing.ImageIcon(path));
        imageLabel.setSize(img.getWidth(null), img.getWidth(null));
    }
    
    /**
     * Set the number of the frame in the video
     * @param frame number of the frame in the video
     */
    public void setFrame(int frame) {
        this.frame = frame;
    } 
    
    /**
     * Setting up the gui to work with the next file
     */
    public void nextFrame(){
        for(Line ligne : lines){
            ligne.getField2Dx().setText("");
            ligne.getField2Dy().setText("");
        }
        focus =0;
        new ChooseFrame(this).setVisible(true);
    }
    
    /**
     * Method to save current data in text fields and prepare the gui for the
     * next frame
     * @param evt Event when you click on the "+" button
     */
    private void nextFrameMouseClicked(java.awt.event.MouseEvent evt){
        FrameData.addFrame(frame,lines);
        nextFrame();
    }
    
    /**
     * Save the last frame's data and close the program
     * @param evt Event when you click on the "ok" button
     */
    private void doneMouseClicked(java.awt.event.MouseEvent evt){
        FrameData.addFrame(frame,lines);
        Save.Enregistrer(FrameData.getData());
        this.dispose();
        
    }
    
    /**
     * Add to the good text field the pixel's coordinates of the frame at the
     * location you click
     * @param evt Event when you click on a pixel of the frame
     */
    private void labelImageMouseClicked(java.awt.event.MouseEvent evt){
        
        int x = evt.getX();
        int y = evt.getY();
        lines.get(focus).getField2Dx().setText(Integer.toString(x));
        lines.get(focus).getField2Dy().setText(Integer.toString(y));
        if(focus<nbLines-1){
            focus++;
        }
        else focus=0;
        lines.get(focus).getField2Dx().requestFocus();
        
        
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel dataPanel;
    private javax.swing.JLabel imageLabel;
    private javax.swing.JPanel imagePanel;
    // End of variables declaration//GEN-END:variables
    private javax.swing.JLabel label2Dx=new javax.swing.JLabel("X");
    private javax.swing.JLabel label2Dy=new javax.swing.JLabel("Y");
    private javax.swing.JLabel label3Dx=new javax.swing.JLabel("x");
    private javax.swing.JLabel label3Dy=new javax.swing.JLabel("y");
    private javax.swing.JLabel label3Dz=new javax.swing.JLabel("z");
    
    private javax.swing.JButton nextFrame=new javax.swing.JButton("+");
    private javax.swing.JButton done=new javax.swing.JButton("ok");
    
    private ArrayList<Line> lines = new ArrayList<>();
    /**
     * Number of text field's line
     */
    private int nbLines = 14;
    /**
     * Number of the frame in the video
     */
    private int frame = 0;
    /**
     * Number of the frame focused
     */
    private int focus=0;
    
}
