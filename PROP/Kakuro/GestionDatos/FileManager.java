package GestionDatos;
import java.io.*;

public class FileManager {

    public FileManager (String filename)
    {
        this.file = new File(filename);
    }

    public Boolean fileExists()
    {
        //Devuelve TRUE si y sólo si el path existe y es un archivo.
        return (this.file.exists() && this.file.isFile());
    }

    public String readNextLine()
    {
        if (reader == null)
        {
            if (this.fileExists() == false) return null;
            try { reader = new BufferedReader(new FileReader(this.file)); }
            catch (FileNotFoundException fe) { return null; }
        }
        try
        {
            String line = reader.readLine();
            //while (line) // Aqui queria poner que ignorara las líneas que empiezan por "#"
            return line;
        }
        catch (IOException e)
        {
            return null;
        }
    }
    
    public static void readFileLineByLine (String path) throws Exception 
    { 
        // path = ""C:\\Users\\pankaj\\Desktop\\test.txt"
        File file = new File(path); 
  
        BufferedReader br = new BufferedReader(new FileReader(file)); 
  
        String st; 
        while ((st = br.readLine()) != null) 
        System.out.println(st);
    } 

    public static void readFileCharByChar (String path) throws Exception 
    { 
        // path = "C:\\Users\\pankaj\\Desktop\\test.txt"
        FileReader fr = new FileReader(path); 
  
        int i; 
        while ((i=fr.read()) != -1) 
        System.out.print((char) i); 
    }

    public static void writeFileLineByLine (String filename, String[] text) throws Exception
    {
        PrintWriter writer = new PrintWriter("filename", "UTF-8");
        for (int i = 0; i < text.length; ++i)
        {
            writer.println(text[i]);    
        }
        writer.close();
    }

    public static void listFiles (String directory)
    {
        File f = new File(directory);

        String[] filesInTheFolder = f.list();

        for (int i = 0; i < filesInTheFolder.length; ++i)
        {
            System.out.println(filesInTheFolder[i]);
        }

    }


    private File file;
    private BufferedReader reader;

}
