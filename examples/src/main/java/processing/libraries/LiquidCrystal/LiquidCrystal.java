package processing.libraries.LiquidCrystal;

import haiku.vm.NativeCppMethod;
import processing.hardware.arduino.cores.arduino.Print;

public class LiquidCrystal extends Print {

    private Object cobject;

    public LiquidCrystal(int rs, int enable, int d0, int d1, int d2, int d3) {
        cobject=cConstructor(rs, enable, d0, d1, d2, d3);
    }

    
    @NativeCppMethod
    private native static Object cConstructor(int rs, int enable, int d0, int d1, int d2, int d3);
    private native Object getCObject();

    @Override
    @NativeCppMethod
    public native byte write(byte c);

    @NativeCppMethod
    public native void begin(int i, int j);

    @NativeCppMethod
    public native void setCursor(int i, int j);

}
