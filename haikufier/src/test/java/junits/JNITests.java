package junits;

import java.io.IOException;

import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;

import static base.JUnitSetUp.*;

public class JNITests {
    @After
    public void tierDown() throws IOException, InterruptedException, Exception {
        base.JUnitSetUp.tierDownSerial();
    }

    @Test
    public void test010_JNIsimple() throws Exception {
        testee("arduino.tutorial.JNIsimple");
    }

    @Test
    public void test020_JNIenhanced() throws Exception {
        testee("arduino.tutorial.JNIenhanced");
    }

    @Test
    public void test030_NativeCVariableSimple() throws Exception {
        testee("arduino.tutorial.NativeCVariableSimple");
    }

    @Test
    public void test040_NativeCVariableEnhanced() throws Exception {
        testee("arduino.tutorial.NativeCVariableEnhanced");
    }
}
