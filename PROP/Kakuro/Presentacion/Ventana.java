package Presentacion;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
//import java.awt.Toolkit;

public class Ventana {
    
    public void setDefaultParameters()
    {
        initializeNewFrame("Nueva Ventana");
        
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int width = (int)(screenSize.getWidth() / 4);
        int height = (int)(screenSize.getHeight() / 4);

        f.setBounds(width, height, width * 2, height * 2);
         
        final JTextField tf=new JTextField();  
        tf.setBounds(50,50, 150,20);  
        JButton b=new JButton("Click Here");  
        b.setBounds(50,100,95,30);
        ActionListener al = new ActionListener()
        {
            public void actionPerformed(ActionEvent e){  
                tf.setText("Welcome to Javatpoint.");  
            }
        };
        b.addActionListener(al);
        f.add(b);f.add(tf);  
        f.setLayout(null);  
        f.setVisible(true);   

    } 

    private void initializeNewFrame(String title)
    {
        if (f == null) f = new JFrame(title);
        else f.setTitle(title);
    }

    public Ventana()
    {
        setDefaultParameters();
    }

    public void update(Ventana newWindow)
    {
        f = newWindow.f;
        f.setTitle("Test3");
    }

    private JFrame f;
}
