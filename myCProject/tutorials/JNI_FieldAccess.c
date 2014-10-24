/*
 * Copyright (c) 1995-1997 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for NON-COMMERCIAL purposes and without
 * fee is hereby granted provided that this copyright notice
 * appears in all copies. Please refer to the file "copyright.html"
 * for further important copyright and licensing information.
 *
 * SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR
 * ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
 * DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 *
 * Adapted to HaikuVM from genom2
#include <stdio.h>
#include <jni.h>
#include "FieldAccess.h"

JNIEXPORT void JNICALL
Java_arduino_tutorial_JNI_FieldAccess_accessFields(JNIEnv *env, jobject obj)
{
  jclass cls = (*env)->GetObjectClass(env, obj);
  jfieldID fid;
  jstring jstr;
  const char *str;
  jint si;

  printf("In C:\n");

  fid = (*env)->GetStaticFieldID(env, cls, "si", "I");
  if (fid == 0)
    return;
  si = (*env)->GetStaticIntField(env, cls, fid);
  printf("  FieldAccess.si = %d\n", si);
  (*env)->SetStaticIntField(env, cls, fid, 200);

  fid = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;");
  if (fid == 0)
    return;
  jstr = (*env)->GetObjectField(env, obj, fid);
  str = (*env)->GetStringUTFChars(env, jstr, 0);
  printf("  c.s = \"%s\"\n", str);
  (*env)->ReleaseStringUTFChars(env, jstr, str);

  jstr = (*env)->NewStringUTF(env, "123");
  (*env)->SetObjectField(env, obj, fid, jstr);
}
 */

/*
 * Adapted for HaikuVM from genom2
 * assumes char is 1 byte long: Char = 8
 */
#include <stdio.h>
#include <jni.h>

#include "../HaikuVM/utility/haikuConfig.h"
#include "../HaikuVM/utility/haikuJava.h"

#ifdef SIZEOF_arduino_tutorial_JNI_FieldAccess

JNIEXPORT void
Java_arduino_tutorial_JNI_FieldAccess_accessFields(JNIEnv *env, jobject obj)
{
//  jclass cls = (*env)->GetObjectClass(env, obj);
  int fid;
  jstring jstr;
  char *str;
  jint si;

  printf("In C:\n");

//  fid = (*env)->GetStaticFieldID(env, cls, "si", "I");
  si = *(jint*)SADR(arduino_tutorial_JNI_FieldAccess_si);
  printf("  FieldAccess.si = %d\n", si);
//  (*env)->SetStaticIntField(env, cls, fid, 200);
  *(jint*)SADR(arduino_tutorial_JNI_FieldAccess_si) = 200;

//  fid = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;");
  fid = FIDX(arduino_tutorial_JNI_FieldAccess, s);
//  jstr = (*env)->GetObjectField(env, obj, fid);
  jstr = (jstring)*((void**)((char*)obj+fid));
//  str = (*env)->GetStringUTFChars(env, jstr, 0);
  {
    str = malloc(jstr->chars->length+1);
    memcpy(str, jstr->chars->array, jstr->chars->length);
    str[jstr->chars->length]=0;
  }
  printf("  c.s = \"%s\"\n", str);
//  (*env)->ReleaseStringUTFChars(env, jstr, str);
  free(str);

//  jstr = (*env)->NewStringUTF(env, "123");
  {
    int length = 3; // of String "123"
    ldc_String* nstr;

    nstr=(ldc_String*)GCalloc(&java_lang_String__class, sizeof(ldc_String)+length);
    nstr->chars=&(nstr->length);
    setAllocsize(nstr->chars, sizeof(heap_t)+sizeof(array_t)+length);
    nstr->chars->length=length;
    memcpy(nstr->chars->array, "123", length);
    jstr = nstr;
  }
//  (*env)->SetObjectField(env, obj, fid, jstr);
  *((void**)((char*)obj+fid)) = jstr;
}

/*
 * Proprietary HaikuVM stack to JNI interface function.
 * DO NOT EDIT THIS FUNCTION – it is machine generated.
 *
 * Class:     arduino.tutorial.JNIfields
 * Method:    add
 * Signature: ()V
 */
JNIEXPORT void native_arduino_tutorial_JNI_FieldAccess_accessFields_V(void) {
    pushTop();    // Save variable top onto stack.
    {
        jobject    obj = pop()->a;
        JNIEnv     *env = NULL; // not used in HaikuVM
        Java_arduino_tutorial_JNI_FieldAccess_accessFields(env, obj);
    }
    popTop();
}

/////////////////////////////////////////////////
#endif
