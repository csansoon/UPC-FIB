package Dominio;

public abstract class Casilla {
    public abstract int[] getValue();
    public void print()
    {
        //System.out.println("[debug]: Entra en Casilla");
        System.out.printf("!");
    }
}
