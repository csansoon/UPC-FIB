package GestionDatos;
import java.io.FileNotFoundException;

import javax.lang.model.util.ElementScanner6;

import Dominio.Casilla;
import Dominio.CasillaBlanca;
import Dominio.CasillaNegra;

public class CtrlTablero {

    public static Casilla[][] loadFromFile(String filename)
    {
        FileManager file = new FileManager("kakuros/" + filename);
        if (file.fileExists() == false) 
        {
            System.out.println("[ERROR]: El archivo \"" + filename + "\" no existe.");
            return null;
        }

        String line = file.readNextLine();
        int pointer = 0;
        while (line.charAt(pointer) != ',') ++pointer;
        int filas =     Integer.parseInt(line.substring(0,pointer));
        int columnas =  Integer.parseInt(line.substring(pointer+1, line.length()));

        String[][] textoCasilla = new String[filas][columnas];

        int startPointer = 0;
        int finalPointer = 0;
        for (int i = 0; i < filas; ++i)
        {
            line = file.readNextLine();
            startPointer = 0;
            for (int j = 0; j < columnas; ++j)
            {
                finalPointer = startPointer;
                while (finalPointer < line.length() && line.charAt(finalPointer) != ',') ++finalPointer;
                textoCasilla[i][j] = line.substring(startPointer,finalPointer);
                startPointer = finalPointer + 1;
            }
        }

        Casilla[][] casilla = new Casilla[filas][columnas];
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                Casilla c;
                String texto = textoCasilla[i][j];
                        if (texto == "*") c = new CasillaNegra();
                else    if (texto == "?") c = new CasillaBlanca();
                else
                {
                    if (texto.charAt(0) >= '0' && texto.charAt(0) <= '9') // Si es un dígito
                    {
                        pointer = 0;
                        while (pointer < texto.length() && texto.charAt(pointer) >= '0' && texto.charAt(pointer) <= '9')
                        ++pointer;
                        c = new CasillaBlanca(Integer.parseInt(texto.substring(0,pointer))); // Casilla blanca con el valor del número
                    }

                    else
                    {
                        pointer = 0;
                        startPointer = 0;
                        finalPointer = 0;
                        int ncolumnas = 0;
                        int nfilas = 0;
                        while (pointer < texto.length())
                        {
                            char id = texto.charAt(pointer);
                            startPointer = pointer + 1;
                            finalPointer = startPointer;
                            while (finalPointer < texto.length() && texto.charAt(finalPointer) >= '0' && texto.charAt(finalPointer) <= '9')
                            ++finalPointer;
                            int value = Integer.parseInt(texto.substring(startPointer, finalPointer));

                            if (id == 'C') ncolumnas = value;
                            else if (id == 'F') nfilas = value;
                            pointer = finalPointer;
                        }
                        c = new CasillaNegra(ncolumnas, nfilas);
                    }
                }
                casilla[i][j] = c;
            }
        }
        return casilla;
    }
/*
    public static Casilla[][] loadFromFile (String filename)
    {
        FileManager file = new FileManager("kakuros/" + filename);
        if (file.fileExists() == false)
        {
            System.out.println("[debug]: El archivo no existe.");
            return null;
        }
        
        String line;
        line = file.readNextLine();

        String sColumnas = new String();
        String sFilas = new String();

        int l = 0;
        while (l < line.length() && line.charAt(l) != ',')
        {
            sFilas = sFilas + line.charAt(l);
            ++l;
        }
        ++l;
        while (l < line.length() && line.charAt(l) != ',')
        {
            sColumnas = sColumnas + line.charAt(l);
            ++l;
        }

        int filas, columnas;

        try { filas = Integer.parseInt(sFilas); }
        catch (NumberFormatException e) {
            System.out.println("Error: Formato de filas incorrecto.");
            return null;
        }

        try { columnas = Integer.parseInt(sColumnas);}
        catch (NumberFormatException e) {
            System.out.println("Error: Formato de columnas incorrecto.");
            return null;
        }

        Casilla[][] tablero = new Casilla[filas][columnas];

        int start, end;
        for (int i = 0; i < filas; ++i)
        {
            line = file.readNextLine();
            start = 0;
            for (int j = 0; j < columnas; ++j)
            {
                Casilla c;

                end = start;
                while(end < line.length() && line.charAt(end) != ',') ++end;

                String cell = line.substring(start,end);
                if (cell == null) return null;

                else if (cell.charAt(0) == '?') c = new CasillaBlanca(0);
                else if (cell.charAt(0) == '*') c = new CasillaNegra(0,0);

                else
                {
                    int index = 0;
                    int nfilas = 0;
                    int ncolumnas = 0;
                    while (index < cell.length())
                    {
                        char id = cell.charAt(index);
                        String value = "";
                        ++index;
                        while (index < cell.length() && cell.charAt(index) >= '0' && cell.charAt(index) <= '9' )
                        {
                            value = value + cell.charAt(index);
                            ++index;
                        }

                        if (id == 'C')
                        {
                            try { ncolumnas = Integer.parseInt(value); }
                            catch (NumberFormatException e) { ncolumnas = 0; }
                        }
                        else if (id == 'F')
                        {
                            try { nfilas = Integer.parseInt(value); }
                            catch (NumberFormatException e) { nfilas = 0; }
                        }
                    }
                    c = new CasillaNegra(ncolumnas, nfilas);
                }

                tablero[i][j] = c;
                //tablero.setCasilla(i, j, c);
                start = end + 1;
            }
        }
        return tablero;
    }
    */
}
