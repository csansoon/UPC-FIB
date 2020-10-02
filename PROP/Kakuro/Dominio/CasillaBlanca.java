package Dominio;
public class CasillaBlanca extends Casilla {
    public CasillaBlanca()
    {
        this.value = 0;
    }
    public CasillaBlanca(int n)
    {
        this.value = n;
    }

    public int[] getValue()
    {
        int[] valueCasilla = { this.value };
        return valueCasilla;
    }
    public Boolean setValue(int n)
    {
        if (n < 0 || n > 9) return false;
        this.value = n;
        return true;
    }

    public void print()
    {
        /* Para imprimir igual que se lee:
        if (value == 0) System.out.print("?");
        else System.out.printf(Integer.toString(value));
        */
        System.out.printf("[");
        if (value == 0) System.out.printf("     ");
        else System.out.printf("  " + this.value + "  ");
        System.out.printf("]");
    }

    private int value;
}
