package Presentacion;

public class MainGUI implements Runnable {

	GUI gui = new GUI();
	public static void main(String[] args)
	{ 	
		new Thread(new MainGUI()).start();
	}
	@Override
	public void run() {
		while(true) {
			gui.repaint();
		}
	}

}
