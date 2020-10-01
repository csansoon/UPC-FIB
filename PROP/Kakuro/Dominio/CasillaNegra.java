package Dominio;
public class CasillaNegra extends Casilla {
    public CasillaNegra(int ncolumnas, int nfilas)
    {
        this.setValue(ncolumnas, nfilas);
    }
    public CasillaNegra()
    {
        this.setValue(0,0);
    }

    public Boolean setValue(int x, int y)
    {
        this.value = new int[] {x, y};
        return true; //Devolver true solo si X y Y son valores aceptados.
    }

    public Boolean setFilas (int nfilas)
    {
        this.value[1] = nfilas;
        return true;
    }

    public Boolean setColumnas (int ncolumnas)
    {
        this.value[0] = ncolumnas;
        return true;
    }

    public int[] getValue()
    {
        return value;
    }

    public void print()
    {
        /* Para imprimir igual que se lee:
        if (value[0] == 0 && value[1] == 0) System.out.printf("*");
        else
        {
            if (value[1] > 0) System.out.printf("C" + Integer.toString(value[1]));
            if (value[0] > 0) System.out.printf("F" + Integer.toString(value[0]));
        }
        */
        System.out.printf("[");
        if (value[0] == 0) System.out.printf("##");
        else 
        {
            if (value[0] < 10) System.out.printf(" ");
            System.out.print(value[0]);
        }
        System.out.printf("\\");
        if (value[1] == 0) System.out.printf("##");
        else 
        {
            if (value[1] < 10) System.out.printf(" ");
            System.out.print(value[1]);
        }
        System.out.printf("]");
    }
    
    private int[] value; //value[0] = columnas   value[1] = filas
}
