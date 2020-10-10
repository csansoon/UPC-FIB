package Presentacion;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*;

@SuppressWarnings("serial")
public class GUI extends JFrame {
	
	private final int spacing = 5;
	//test only
	private final int rows = 9;
	private final int columns = 9;
	private final int square = 70;
	private final int centerx = 1280/2 - (square*rows/2);
	private final int centery = 800/2 - (square*columns/2);
	private int mx = -100;
	private int my = -100;
	
	int[][] array = new int [rows][columns];
	
	JLabel label;
	JLabel number;
	private boolean listen = false;
	
	
	public GUI() {
		label = new JLabel("");
		number = new JLabel("");
		
		JPanel panel = new JPanel();
		panel.add(label);
		panel.add(number);
		this.setLayout(null);
		getContentPane().add(panel);
		this.setTitle("Kakuro");
		this.setSize(1286,829); //This is actually 1280x800
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		Board board = new Board();
		this.setContentPane(board);
		this.add(panel);

		Mouse mouse = new Mouse();
		this.addMouseListener(mouse);
		Keyboard key = new Keyboard();
		this.addKeyListener(key);
		this.setVisible(true);
	}
	
	public class Board extends JPanel{

		public void paintComponent(Graphics g) {
			g.setColor(Color.black);
			g.fillRect(0, 0, 1280, 800);
			
			for(int i = 0; i < rows ; ++i) {
				for(int j = 0; j < columns ; ++j) {
					g.setColor(Color.white);
					if(mx >= centerx+spacing+6 + i*square && mx < centerx+spacing+6 + i*square + square && my>= centery+spacing + j*square+26 && my < centery+spacing + j*square + square +26)
					{
						g.setColor(Color.yellow);
					}
					g.fillRect(centerx+ spacing + i*square,centery+spacing +j*square,square-spacing,square-spacing);
				}
			}
		}
	}
	
	public class Mouse implements MouseListener{

		@Override
		public void mouseClicked(MouseEvent e) {
			mx =e.getX();
			my =e.getY();
			if(inBoxX() != -1 && inBoxY() != -1)
			{
				updateLabel("You have selected box [" + inBoxX() + "," + inBoxY() + "]");
				listen = true;
			}
			else
			{
				listen = false;
			}
			//System.out.println("mouse click" + mx + my);
		}

		@Override
		public void mousePressed(MouseEvent e) {

		}

		@Override
		public void mouseReleased(MouseEvent e) {

		}

		@Override
		public void mouseEntered(MouseEvent e) {

		}

		@Override
		public void mouseExited(MouseEvent e) {

		}
		
	}
	
	public class Keyboard implements KeyListener{

		@Override
		public void keyTyped(KeyEvent e) {
			if(listen)
			{
				String input = Character.toString(e.getKeyChar());
				updateNumber(input);
			}
			else
			{
				updateNumber("");
			}
		}

		@Override
		public void keyPressed(KeyEvent e) {

		}

		@Override
		public void keyReleased(KeyEvent e) {

		}
		
	}
	public int inBoxX()
	{
		for(int i = 0; i < rows ; ++i) {
			for(int j = 0; j < columns ; ++j) {
				if(mx >= centerx+spacing+6 + i*square && mx < centerx+spacing+6 + i*square + square && my>= centery+spacing + j*square+26 && my < centery+spacing + j*square + square +26)
				{
					return i;
				}
			}
		}
		return -1;
	}
	public int inBoxY()
	{
		for(int i = 0; i < rows ; ++i) {
			for(int j = 0; j < columns ; ++j) {
				if(mx >= centerx+spacing+6 + i*square && mx < centerx+spacing+6 + i*square + square && my>= centery+spacing + j*square+26 && my < centery+spacing + j*square + square +26)
				{
					return j;
				}
			}
		}
		return -1;
	}
	
	public void updateLabel(String text)
	{
		label.setText(text);
	}
	public void updateNumber(String text)
	{
		number.setBounds(mx,my,100,100);
		if(text.equals("1") || text.equals("2") || text.equals("3") || text.equals("4") || text.equals("5") || text.equals("6") || text.equals("7") || text.equals("8") || text.equals("9"))
			number.setText(text);
	}
}
