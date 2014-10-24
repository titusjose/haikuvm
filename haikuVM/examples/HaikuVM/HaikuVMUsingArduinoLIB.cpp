// To access arduino clibs, it's important to have an extension of cpp.

#include <jni.h>

#if ARDUINO>105
/*
 * Only needed if newer ArduinoIDE is used
 */
#if !defined(HAIKU_TimerInterrupt) && isMICRO
#include <Arduino.h>

/*
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    read
 * Signature: ()I
 */
JNIEXPORT jint Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_read
  (JNIEnv *env, jclass obj)
{
    return Serial.read();
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION it is machine generated.
 *
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    read
 * Signature: ()I
 */
JNIEXPORT void native_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_read_I(void) {
    pushTop();    // Save variable top onto stack.
    {
        jclass     obj = NULL;
        JNIEnv     *env = NULL; // not used in HaikuVM
        top.s1.i = Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_read(env, obj);
    }
    // Variable top holds the return value.
}

/////////////////////////////////////////////////


/*
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    available
 * Signature: ()I
 */
JNIEXPORT jint Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_available
  (JNIEnv *env, jclass obj)
{
    return Serial.available();
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION it is machine generated.
 *
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    available
 * Signature: ()I
 */
JNIEXPORT void native_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_available_I(void) {
    pushTop();    // Save variable top onto stack.
    {
        jclass     obj = NULL;
        JNIEnv     *env = NULL; // not used in HaikuVM
        top.s1.i = Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_available(env, obj);
    }
    // Variable top holds the return value.
}

/////////////////////////////////////////////////


/*
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    begin
 * Signature: (J)V
 */
JNIEXPORT void Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_begin
  (JNIEnv *env, jclass obj, jlong arg1)
{
    Serial.begin(arg1);
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION it is machine generated.
 *
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    begin
 * Signature: (J)V
 */
JNIEXPORT void native_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_begin_JV(void) {
    pushTop();    // Save variable top onto stack.
    {
        jlong    arg1 = popp2()->j;
        jclass     obj = NULL;
        JNIEnv     *env = NULL; // not used in HaikuVM
        Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_begin(env, obj, arg1);
    }
    popTop();
}

/////////////////////////////////////////////////


/*
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    write
 * Signature: (B)B
 */
JNIEXPORT jbyte Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_write
  (JNIEnv *env, jclass obj, jbyte arg1)
{
    return Serial.write((uint8_t) arg1);
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION it is machine generated.
 *
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    write
 * Signature: (B)B
 */
JNIEXPORT void native_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_write_BB(void) {
    pushTop();    // Save variable top onto stack.
    {
        jbyte    arg1 = pop()->b;
        jclass     obj = NULL;
        JNIEnv     *env = NULL; // not used in HaikuVM
        top.s1.b = Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_write(env, obj, arg1);
    }
    // Variable top holds the return value.
}

/////////////////////////////////////////////////


/*
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    isOpen
 * Signature: ()Z
 */
JNIEXPORT jboolean Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_isOpen
  (JNIEnv *env, jclass obj)
{
    return Serial;
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION it is machine generated.
 *
 * Class:     processing.hardware.arduino.cores.arduino.HardwareSerialImpl
 * Method:    isOpen
 * Signature: ()Z
 */
JNIEXPORT void native_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_isOpen_Z(void) {
    pushTop();    // Save variable top onto stack.
    {
        jclass     obj = NULL;
        JNIEnv     *env = NULL; // not used in HaikuVM
        top.s1.z = Java_processing_hardware_arduino_cores_arduino_HardwareSerialImpl_isOpen(env, obj);
    }
    // Variable top holds the return value.
}
/////////////////////////////////////////////////
#endif
#endif
