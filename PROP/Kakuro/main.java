//import Presentacion.*;
import java.io.*;
import GestionDatos.FileManager;
import Dominio.*;

public class main {

    public static void main (String[] args) {

        Tablero tablero = new Tablero(0, 0);
        
        tablero.loadFromFile("kakuroExemple.txt");

        tablero.print();
    }
}