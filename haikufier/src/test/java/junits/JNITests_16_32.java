package junits;

import java.io.IOException;

import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;

import base.JUnitSetUp;

import static base.JUnitSetUp.*;

public class JNITests_16_32 extends JNITests {

    @BeforeClass
    public static void beforeTests() throws IOException, InterruptedException,
            Exception {
        JUnitSetUp.setTarget("arduino");
        JUnitSetUp.setMode("16/32");
    }
}
