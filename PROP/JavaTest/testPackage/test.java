package testPackage;
import java.io.*;

import javax.swing.JPanel;

public class test extends JPanel {
	public static void main (final String[] args) {
        if (args.length >= 1)
        {
            System.out.println("Hello world, my name is " + args[0]);
        }
        else
        {
            System.out.println("Hello world, I have no name");
        }
	}
}