package MainPackage;
import java.io.*;
import Presentacion.*;
import Dominio.*;
import GestionDatos.*;
//import GestionDatos.FileManager;

public class main {

    public static void main (String[] args) {
/*
        Tablero tablero = new Tablero(0, 0);
        tablero.loadFromFile("kakuroExemple.txt");
        tablero.print();

        FileManager newSave = new FileManager("saveTest.txt");
        newSave.removeFile();

        CtrlTablero.saveToFile(tablero, "saveTest.txt", true);

        Tablero tablero2 = new Tablero(0,0);
        tablero2.loadFromFile("saveTest.txt");
        tablero2.print();
*/
    	GUI gui = new GUI();
    	public static void main(String[] args)
    	{ 	
    		new Thread(new MainGUI()).start();
    	}
    	@Override
    	public void run() {
    		while(true) {
    			gui.repaint();
    		}
    	}
    }
}