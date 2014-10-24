/*
 * simpleOS.h
 *
 *  Created on: 22.08.2011
 *      Author: genom2
 */

#ifndef SIMPLEOS_H_
#define SIMPLEOS_H_

#if NO_MICRO
//#include <windows.h>
#include <time.h>
typedef char prog_char;
#define sei()


#else
#include <stdio.h>
#define CLOCKS_PER_SEC 1000

#endif



extern julong millis();
extern void delay(unsigned long ms);
extern void myinit();

#if _DEBUG || defined(WIN32)
extern int jprintf(const char * format, ...);
#else
#define jprintf printf
#endif

#endif /* SIMPLEOS_H_ */
