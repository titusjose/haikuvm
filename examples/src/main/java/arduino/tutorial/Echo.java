package arduino.tutorial;

import static haiku.avr.lib.arduino.WProgram.*;
/**
 */
public class Echo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		init();
	    Serial.begin(57600);
        Serial.println("Please start typing");

	    for(int i=0; ;i++) {
	       	int c;
            while((c=Serial.read())<0) ;
            Serial.println(i+": "+(char)c);
	    }
	}

}
