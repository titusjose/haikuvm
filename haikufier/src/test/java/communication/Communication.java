package communication;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.TooManyListenersException;

import gnu.io.*;

public class Communication
{
    private SerialPort serialPort;

    public Communication()
    {
        super();
    }
    
    public void connect ( String portName, int speed) throws Exception
    {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        if ( portIdentifier.isCurrentlyOwned() )
        {
            throw new Exception("Error: Port is currently in use");
        }
        else
        {
            CommPort commPort = portIdentifier.open(this.getClass().getName(), 0);
            
            if ( commPort instanceof SerialPort )
            {
                serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(speed, SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
            }
            else
            {
                throw new Exception("Error: Only serial ports are handled by this example.");
            }
        }     
    }

    public OutputStream getOutputStream() throws IOException {
        return serialPort.getOutputStream();
    }
    
    public InputStream getInputStream() throws IOException {
        return serialPort.getInputStream();
    }

    public void close() {
        try {
            serialPort.getOutputStream().close();
            serialPort.getInputStream().close();
            serialPort.removeEventListener();
            serialPort.close();
        } catch (IOException e) {
            e.printStackTrace();
        }        
    }

    public void addEventListener(SerialPortEventListener sr) throws TooManyListenersException {
//      try {
//          serialPort.enableReceiveTimeout(1000);
//      } catch (UnsupportedCommOperationException e) {
//          // TODO Auto-generated catch block
//          e.printStackTrace();
//      }
        serialPort.addEventListener(sr);
        serialPort.notifyOnDataAvailable(true);
    }
    
}
