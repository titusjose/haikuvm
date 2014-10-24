package haikuvm.pc.tools.haikuc;

import haikuvm.pc.tools.Haikufy;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;

public class HaikuConfigh {

    private PrintStream out;

    private HaikuConfigh(File file) throws FileNotFoundException {
        out=new PrintStream(file);

    }

    public HaikuConfigh(String dir) throws FileNotFoundException {
        this(new File(dir+"/"+Haikufy.choice("haikuC")+"/haikuConfig.h"));
    }

    public void close() {
    }
}
