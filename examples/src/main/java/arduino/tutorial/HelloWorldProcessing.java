package arduino.tutorial;

import static haiku.arduino.api.Arduino.*;

/**
 */
public class HelloWorldProcessing {

    /**
     * @param args
     */
    public static void main(String[] args) {
        init();
        Serial.begin(57600);
        for (int i = 0; i < 10; i++) {
            Serial.println("Hello World "+i+", "+sq(i)+", "+random(1000));
        }
    }
}
