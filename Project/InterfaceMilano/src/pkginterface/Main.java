package pkginterface;

/**
 *
 * @author Charles
 */
public class Main {

    /**
     * Main class of the program
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Gui gui = new Gui();
        gui.setVisible(true);
        new ChooseFrame(gui).setVisible(true);
    }
    
    
}
