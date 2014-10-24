package haikuvm.pc.tools.haikuc;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.Formatter;

public class HaikuJava2File extends PrintOnChange {
    private static File dir;

    public HaikuJava2File(File file) {
        super(file);
    }

    public static boolean isSingleFile() {
        return dir!=null;
    }

    public static void setDir(File dir1) {
        dir=dir1;
    }

    public static File getDir() {
        return dir;
    }
}
