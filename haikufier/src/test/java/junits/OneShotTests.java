package junits;

import java.io.IOException;

import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;

import base.JUnitSetUp;

import static base.JUnitSetUp.*;

public class OneShotTests {
   
    @BeforeClass
    public static void beforeTests() throws IOException, InterruptedException, Exception {
        //JUnitSetUp.setTarget("junit.cygwin");
        JUnitSetUp.setMode("16/32");
    }

    @After
    public void tierDown() throws IOException, InterruptedException, Exception {
        base.JUnitSetUp.tierDownSerial();        
    }
    
    //@Test
    public void test090_JNINativeLIBC() throws Exception {
        testee("arduino.tutorial.JNINativeLIBC");
    }

    //@Test
    public void test090_Threads1() throws Exception {
        testee("haikuvm.bench.Clone");
    }

    //@Test
    public void test090_SynchronizedThreads3() throws Exception {
        testee("haikuvm.bench.SynchronizedThreads3");
    }

    @Test
    public void oneShot() throws Exception {
        testee("haikuvm.bench.PrimitivFieldsTest");
        //testee("arduino.tutorial.NativeCVariableEnhanced");
        //testee("haikuvm.bench.ArrayFieldsTest");
        //testee("haikuvm.bench.ClassMethods");
    }
    
    //@Test
    public void test090_ExceptionTest() throws Exception {
        testee("haikuvm.bench.ExceptionTest");
    }

    //@Test
    public void test090() throws Exception {
        testee("haikuvm.bench.MemoryOverflow2", "link_upload_PanicSupport");
    }
}
