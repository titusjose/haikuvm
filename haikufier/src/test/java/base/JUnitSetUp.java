package base;

import haikuvm.pc.tools.HaikuVM;
import gnu.io.*;

import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

import communication.Communication;


public class JUnitSetUp
{

    private static String target = "arduino";
    private static String mode  = "16/32";

    public static void setTarget(String target) {
        JUnitSetUp.target=target;
    }
    
    public static void setMode(String mode) {
        JUnitSetUp.mode=mode;
    }
    
    /** */
    public static class SerialReader implements SerialPortEventListener 
    {
        private Vector<String> lines=new Vector<String>();
        private InputStreamReader in;
		private String line;
        private static long t0;
        private static long t1;
        private static int lasttime;

        public SerialReader ( InputStream in )
        {
			line = "";
            this.in = new InputStreamReader(in); 
        }

		@Override
		public void serialEvent(SerialPortEvent evt) {
			if (evt.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
				try {
					int c;
	                for ( int i=0; in.ready() && (c = in.read()) >0; i++ ) {
						if (c == '\n') {
							if (line.endsWith("\r"))
								line = line.substring(0, line.length() - 1);
							lines.add(line);
							line = "";
						} else {
							line += (char) c;
						}
	                }
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
        
        public String readLine() throws IOException {
            if (t0==0) t0=System.currentTimeMillis();
            for(int i=0; i<Math.max(50, 2*lasttime); i++) {
                if (lines.size()>0) {
                    t1=System.currentTimeMillis();
                    lasttime=(int)(t1-t0)/ 100;
                    t0=t1;
                    return lines.remove(0);
                }
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            return null;
            //throw new IOException("readLine() timeout");
        }
    }

    /** */
    public static class SerialWriter implements Runnable 
    {
        OutputStream out;
        private String cmd;
        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        public void run ()
        {
            try
            {                
                while ( true )
                {
                    byte[] buf = getCmd();
                    Thread.sleep(10);
                    for (int i = 0; i < buf.length; i++) {
                        out.write(buf[i]);
                        Thread.sleep(10);
                    }
                }                
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }            
        }

        private synchronized byte[] getCmd() throws InterruptedException {
            while(true) {
                if (cmd!=null) break; 
                wait();
            }
            byte[] res = cmd.getBytes();
            cmd=null;
            notifyAll();
            return res;
        }

        public synchronized void send(String cmd) throws InterruptedException {
            while(true) {
                if (this.cmd==null) break; 
                wait();
            }
            this.cmd=cmd;
            notifyAll();
        }
    }

    private static SerialWriter sw;
    private static SerialReader sr;
    private static Communication con;
    
    public static void write(String cmd) throws InterruptedException {
        sw.send(cmd);
    }
    
    public static String readLine() throws IOException {
        return sr.readLine();
    }


    
    public static void main ( String[] args ) throws Exception
    {
        setUpSerialSpezial();
        sw.send("!;");
        System.out.print(sr.readLine());
        System.out.print(sr.readLine());
        System.out.print(sr.readLine());
        System.out.print(sr.readLine());
        System.out.print(sr.readLine());
        
        System.out.println(getDouble("123, 10 / ? ;"));
        System.out.println(getDouble("123, 10 + ? ;"));
        System.out.println(getDouble("123, 10 - ? ;"));
        System.out.println(getDouble("dmax() ? ;"));
        System.out.println(getDouble("dmin() ? ;"));
        System.out.println(getDouble("fmax() ? ;"));
        System.out.println(getDouble("fmin() ? ;"));
        for (int i = 0; i < 10; i++) {
            System.out.println(getDouble(i+", 10 + ? ;"));
        }
        for (int i = 0; i < 10; i++) {
            System.out.println(getDouble(i+" sqrt() ? ;"));
        }
    }

    public static void setUpSerial() throws Exception, IOException, InterruptedException {
        if (con!=null) con.close();
        con = new Communication();
        con.connect("COM17", 57600);
        sw=new SerialWriter(con.getOutputStream());
        sr=new SerialReader(con.getInputStream());
        con.addEventListener(sr);
        Thread t0=new Thread(sw);
        t0.setDaemon(true);
        t0.start();
    }

    public static void setUpSerialSpezial() throws Exception, IOException, InterruptedException {
        setUpSerial();
        sr.readLine();
        sw.send("#;");
    }

    public static void tierDownSerial() throws Exception, IOException, InterruptedException {
        if (con!=null) con.close();
   }

    public static double getDouble(String cmd) throws InterruptedException, IOException {
        sw.send(cmd);
        String res=sr.readLine();
        res=res.replaceFirst(".+[;]", "");
        double d=Double.parseDouble(res);
        return d;
    }
    

    public static void testee(String clazz, String type) throws InterruptedException, Exception {
        System.setProperty("COMMAND_NAME", "haiku");
        Vector<String> output = HaikuVM.executeBlocking(new String[] {
                "src/test/resources/junit", 
                type, target, mode, "1",
                // "--bootclasspath",
                // "../bootstrap/bin;../haikuRT\bin;../lib/nxt/classes.jar",
                // "--classpath",
                // "../haikuBench/bin;../examples/bin;../gattaca/bin",
                clazz });
        
        String program="";
		String data="";
		for (String line : output) {
            if (line.startsWith("Program: ")) {
                program=line.replace("\r", "");;
            } else if (line.startsWith("Data: ")) {
                data=line.replace("\r", "");;
            }
		}



		PrintWriter junitOut;
        Date dt = new Date();
        SimpleDateFormat df = new SimpleDateFormat( "yyyy-MM-dd HH:mm:ss.S" );

        if (target.startsWith("unix") || target.startsWith("linux") || target.startsWith("pc")) {
            output = HaikuVM.executeBlocking(new String[] {
                    "src/test/resources/junit", 
                    "execute", target, mode, "1",
                    // "--bootclasspath",
                    // "../bootstrap/bin;../haikuRT\bin;../lib/nxt/classes.jar",
                    // "--classpath",
                    // "../haikuBench/bin;../examples/bin;../gattaca/bin",
                    clazz });
            output.remove(0); // execute linux32 32/64 1 haikuvm.bench.Fibonacci
            output.remove(0); // #
            output.remove(0); // #
            output.remove(0); // #
            output.remove(0); // #############################################################
            output.remove(0); // # upload file
            output.remove(0); // #############################################################
            output.remove(0); // ./Fibonacci
            output.remove(output.size()-1); // #############################################################
            output.remove(output.size()-1); // # upload done
            output.remove(output.size()-1); // #############################################################
            junitOut = new PrintWriter(new FileWriter("src/test/resources/junit_" + target + "_" + mode.replace('/', '_') + ".log", true));
            junitOut.println("##########  Date: " + df.format( dt ) );        // '2001-01-26 19:03:56.731'
            junitOut.println("##########  "+clazz);
            for (String line : output) {
				junitOut.println(line);
			}
        } else {
            setUpSerial();

            junitOut = new PrintWriter(new FileWriter("src/test/resources/junit_" + target + "_"
                    + mode.replace('/', '_') + ".log", true)) {
                public void println(String line) {
                    super.println(line);
                    System.out.println(line);
                }
            };    

            output = new Vector<String>();
            
            junitOut.println("##########  Date: " + df.format( dt ) );        // '2001-01-26 19:03:56.731'
            junitOut.println("##########  "+clazz);
            String line;
            long t0 = System.currentTimeMillis();
            long t1 = t0;
            for (int i = 0; (line = readLine()) != null; i++) {
                output.add(line);
                junitOut.println(line);
                t1 = System.currentTimeMillis();
            }
            junitOut.println("##########  elapsed time: " + (t1 - t0) + " ms");
            junitOut.println("##########  " + program);
            junitOut.println("##########  " + data);

            tierDownSerial();
        }
        junitOut.println("##########  end");
        junitOut.println();
        junitOut.println();
        junitOut.close();
        
        assertWithTemplate(clazz, output);
    }
    
    public static void testee(String clazz) throws InterruptedException, Exception {
        testee(clazz, "develop_link_upload");
    }

    /**
##########  HelloWorld
Hello World!
old ##########  11 msec
##########  elapsed time: 11 msec
##########  Program:    5950 bytes (18.2% Full)
##########  Data:       1566 bytes (76.5% Full)

     * 
     * @param clazz
     * @param output
     * @throws IOException
     */
    public static void assertWithTemplate(String clazz, Vector<String> output)
            throws IOException {
        String expected = "src/test/resources/valid_" + target + "_"
                + mode.replace('/', '_') + ".lst";
        MyJUnit ju = new MyJUnit(expected, clazz, output);
        ju.start();
    }

}
