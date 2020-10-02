package GestionDatos;
import java.sql.Time;
import Dominio.Tablero;
import Dominio.Casilla;
import Dominio.CasillaBlanca;
import Dominio.CasillaNegra;

public class CtrlTablero {

    public static Tablero loadFromFile(String filename)
    {

        // Abrir el archivo:
        FileManager file = new FileManager("kakuros/" + filename);
        if (file.fileExists() == false) 
        {
            System.out.println("[ERROR]: El archivo \"" + filename + "\" no existe.");
            return null;
        }

        // Leer el tamaño del tablero (primera línea):
        String line = file.readNextLine();
        int pointer = 0;
        while (line.charAt(pointer) != ',') ++pointer;
        int filas =     Integer.parseInt(line.substring(0,pointer));
        int columnas =  Integer.parseInt(line.substring(pointer+1, line.length()));


        //  Desgrupar el texto de cada casilla:
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

        // Traducir cada casilla:
        Casilla[][] casilla = new Casilla[filas][columnas];
        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                Casilla c;
                String texto = textoCasilla[i][j];
                        if (texto.equals("*")) c = new CasillaNegra();
                else    if (texto.equals("?")) c = new CasillaBlanca();
                else
                {
                    if (texto.charAt(0) >= '0' && texto.charAt(0) <= '9') // Si es un dígito, quiero leer el número completo:
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
        String timeString = file.readNextLine();
        long timeNumber = 0;
        if (timeString != null) timeNumber = Long.parseLong(timeString);
        
        Time time = new Time(timeNumber);

        // Devolver el tablero leído:
        file.close();
        Tablero tablero = new Tablero(filas, columnas);
        tablero.setCasillas(casilla);
        tablero.setTime(time);
        return tablero;
    }

    public static Boolean saveToFile(Tablero tablero, String filename, Boolean sobreescribir_archivo)
    {
        // Abrir el archivo limpio:
        FileManager file = new FileManager("kakuros/" + filename);
        if (file.fileExists() == true) 
        {
            if (sobreescribir_archivo == false)
            {
                System.out.println("[ERROR]: El archivo \"" + filename + "\" ya existe.");
                return false;
            }
            file.removeFile();
        }
        if (file.createFile() == false) return false;

        
        Casilla[][] casilla = tablero.getCasillas();
        int[] tamaño = tablero.getTamaño();

        // Imprimir tamaño:
        file.writeNextLine(tamaño[0] + "," + tamaño[1]);

        // Imprimir línea por línea:
        for (int i = 0; i < tamaño[0]; ++i)
        {
            for (int j = 0; j < tamaño[1]; ++j)
            {
                if (j > 0) file.write(",");
                int[] value = casilla[i][j].getValue();

                Class tipoCasilla = casilla[i][j].getClass();
                if (tipoCasilla == CasillaBlanca.class)
                {
                    if (value[0] == 0) file.write("?");
                    else file.write(Integer.toString(value[0]));
                }
                else
                {
                    if (value[0] == 0 && value[1] == 0) file.write("*");
                    else
                    {
                        if (value[0] > 0) file.write("C" + value[0]);
                        if (value[1] > 0) file.write("F" + value[1]);
                    }
                }

            }
            file.write("\n");
        }

        // Aqui faltaria añadir imprimir el tiempo:
        //  ...

        file.close();
        return true;
    }
}
