package Presentacion;
import Dominio.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.MouseInputAdapter;

public class TableroPanel extends JPanel {
    
    private Tablero tablero;
    private Dimension size;


    public TableroPanel(Tablero tablero)
    {
        this.size = (new Dimension(540,450));
        this.tablero = tablero;

    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        int casillaWidth = this.size.width / tablero.getNumColumnas();
        int casillaHeight = this.size.height / tablero.getNumFilas();
        
        Graphics2D g2d = (Graphics2D)g;
    }
}
