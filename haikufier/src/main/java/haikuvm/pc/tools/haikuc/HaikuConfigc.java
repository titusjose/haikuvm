package haikuvm.pc.tools.haikuc;

import haikuvm.pc.tools.Haikufy;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;

public class HaikuConfigc {

    private PrintStream out;

    private HaikuConfigc(File file) throws FileNotFoundException {
        out=new PrintStream(file);
    }

    public HaikuConfigc(String dir) throws FileNotFoundException {
        this(new File(dir+"/"+Haikufy.choice("haikuC")+"/haikuConfig.c"));
    }

    public void close() {
    }
}
