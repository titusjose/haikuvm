import gnu.io.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class SyncTime
{
    public SyncTime()
    {
        super();
    }
    
    void connect ( String portName, int speed) throws Exception
    {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: Port is currently in use");
        }
        else
        {
            CommPort commPort = portIdentifier.open(this.getClass().getName(), 0);
            
            if ( commPort instanceof SerialPort )
            {
                SerialPort serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(speed, SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                
                InputStream in = serialPort.getInputStream();
                OutputStream out = serialPort.getOutputStream();
                
                (new Thread(new SerialReader(in))).start();
                (new Thread(new SerialWriter(out))).start();

            }
            else
            {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }     
    }
    
    /** */
    public static class SerialReader implements Runnable 
    {
    	BufferedReader in;
        
        public SerialReader ( InputStream in )
        {
            this.in = new BufferedReader(new InputStreamReader(in)); 
        }
        
        public void run ()
        {
            String line;
            try
            {
                for(int i=0; ( line = in.readLine()) != null && i<5; i++)
                {
                    System.out.println(line);
                }
                line = in.readLine();
            	long j0=System.currentTimeMillis();
                System.out.println(line);
                long h0=Integer.parseInt(line);
                System.out.printf("%s\t%d\n", line, j0);
                
                while ( ( line = in.readLine()) != null )
                {
                	long j1=System.currentTimeMillis();
                    try {
						long h1=Integer.parseInt(line);
						System.out.printf("%s\t%g\n", line, 1.0*(j1-j0)/(h1-h0));
					} catch (NumberFormatException e) {
						long h1=0;
						System.out.printf("%s\t%g\n", line, 1.0*(j1-j0)/(h1-h0));
					}
                }
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }            
        }
    }

    /** */
    public static class SerialWriter implements Runnable 
    {
        OutputStream out;
        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        public void run ()
        {
            try
            {                
                int c = 0;
                while ( ( c = System.in.read()) > -1 )
                {
                    this.out.write(c);
                }                
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }            
        }
    }
    
    public static void main ( String[] args )
    {
    	//System.out.println("hello "+System.getProperty("java.library.path"));
        try
        {
            (new SyncTime()).connect("COM17", 57600);
            (new SyncTime()).connect("COM19", 2400);
        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
