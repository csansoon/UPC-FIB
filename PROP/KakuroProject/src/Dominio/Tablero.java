package Dominio;
import java.sql.Time;

import GestionDatos.*;

public class Tablero {
    
    public Tablero(int x, int y)
    {
        this.modificarTamaño(x, y);
    }

    public Boolean loadFromFile(String filename)
    {
        Tablero newTablero = CtrlTablero.loadFromFile(filename);
        if (newTablero == null) return false;

        this.setCasillas(newTablero.getCasillas());
        this.setTime(newTablero.getTime());

        return true;
    }

    public int[] getValue(int x, int y)
    {
        return casilla[x][y].getValue();
    }

    public int[] getTamaño()
    {
        int[] tamaño = {this.filas, this.columnas};
        return tamaño;
    }

    public Boolean setCasilla(int x, int y, Casilla newCasilla)
    {
        if (filaCorrecta(x) && columnaCorrecta(y))
        {
            this.casilla[x][y] = newCasilla;
            return true;
        }
        return false;
    }
    
    public Casilla[][] getCasillas()
    {
        return this.casilla;
    }

    public Boolean setCasillas(Casilla[][] casillas)
    {
        this.casilla = casillas;
        this.filas = casillas.length;
        if (this.filas > 0) this.columnas = casillas[0].length;
        else columnas = 0;
        
        return true;
    }

    public Boolean setTime(Time newTime)
    {
        this.time = newTime;
        return true;
    }

    public Time getTime()
    {
        return this.time;
    }

    private Boolean filaCorrecta(int x) { return (x >= 0 && x < filas); }
    private Boolean columnaCorrecta(int y) { return (y >= 0 && y < columnas); }

    private Boolean modificarTamaño(int x, int y)
    {
        if (x < 0) return false;
        if (y < 0) return false;

        this.filas = x;
        this.columnas = y;
        this.casilla = new Casilla[x][y];

        this.initialize();
        return true;
    }

    private void initialize()
    {
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                casilla[i][j] = new CasillaNegra();
            }
        }
    }

    public void print()
    {
        /* Para imprimir igual que se lee:
        System.out.println(Integer.toString(filas) + "," + Integer.toString(columnas));
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                //System.out.println("[debug]: aqui llega, i = " + i + " j = " + j);
                this.casilla[i][j].print();
                if (j < columnas - 1) System.out.printf(",");
            }
            System.out.println();
        }
        */
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                this.casilla[i][j].print();
            }
            System.out.println();
        }
    }

    private int filas;
    private int columnas;
    private Casilla[][] casilla; 
    private Time time;
}
