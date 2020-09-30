import Presentacion.*;
import java.io.*;
import Dominio.*;
//import GestionDatos.FileManager;

public class main {

    public static void main (String[] args) {

        Tablero tablero = new Tablero(0, 0);
        
        tablero.loadFromFile("kakuroExemple.txt");

        tablero.print();
    }
}