package Dominio;
import GestionDatos.*;

public class Tablero {
    
    public Tablero(int x, int y)
    {
        this.modificarTamaño(x, y);
    }

    public Boolean loadFromFile(String filename)
    {
        this.casilla = CtrlTablero.loadFromFile(filename);
        if (this.casilla == null) return false;
        this.filas = casilla.length;
        if (filas > 0) this.columnas = casilla[0].length;
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

        //System.out.println();
        //System.out.printf("[debug]: Tamaño de tablero: ");
        //System.out.printf(Integer.toString(casilla.length));
        //System.out.printf("x");
        //System.out.printf(Integer.toString(casilla[0].length));
        //System.out.println();
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
                //System.out.printf(" ");
            }
            System.out.println();
            //System.out.println();
        }
    }

    private int filas;
    private int columnas;
    private Casilla[][] casilla; 
}
