/*
 * simpleOS.cpp
 *
 *  Created on: 22.08.2011
 *      Author: genom2
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if NO_MICRO

#if defined(WIN32)
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <stddef.h>

#endif
#include "haikuJ2C.h"
#include "simpleOS.h"


#if _DEBUG
static char buf[80];

#undef jprintf
extern int jprintf(const char * format, ...);

#endif

#if NO_MICRO
FILE * tracefile=NULL;

#if _DEBUG || defined(WIN32)
int jprintf(const char * format, ...) {
	char buf[280]; // nicht globaler buf !!
	int err;
	va_list list;
	va_start(list, format);
	vsprintf(buf, format, list);
	err=printf(buf);
	if (tracefile) vfprintf(tracefile, format, list);
	va_end(list);
	return err;
}
#endif

julong millis() {
#if defined(WIN32)
	return clock();
#else
	struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec*1000+t.tv_usec/1000;
#endif
}

void delay(unsigned long ms)
{
#if defined(WIN32)
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

#else

#include <avr/interrupt.h>

#if defined(HAIKU_TimerInterrupt)

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )

/****************************************************************************
  \brief
  Counter fuer 36kHz.

  \see
  Interruptfunktion SIGNAL (SIG_OVERFLOW2) in asuro.c\n
  Gettime(), Sleep() in time.c
*****************************************************************************/
volatile unsigned char count36kHz;

//NOT static!
//because it my be a nice experiment to play with
//direct memory access via:
// @NativeCVariable
// volatile static long timer0_interrupts;
volatile jmillis timer0_interrupts = 0;

#if defined(HAIKU_AsuroTiming)
/****************************************************************************
  \brief
  Interrupt-Funktion fuer Timer-2-Ueberlauf.

  \see
  count36kHz, timebase

  \par
  Der zum Timer gehoerende Zaehler TCNT2 wird so justiert, dass damit die\n
  gewuenschten 36 kHz erreicht werden.\n
  Fuer die Zeitfunktionen werden die globalen Variablen count36kHz und\n
  timebase hochgezaehlt.

*****************************************************************************/
ISR(HAIKU_TimerInterrupt)
{
  TCNT2 += 0x25;
  count36kHz ++;
  if (!count36kHz)
	  timer0_interrupts ++;
}

#else
ISR(HAIKU_TimerInterrupt)
{
	timer0_interrupts++;
}
#endif

julong millis()
{
	jmillis m;
	uint8_t oldSREG = SREG;

	// timer 0 prescale factor is 64 and the timer overflows at 256

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of the timer0_millis++)
	cli();
	m = timer0_interrupts;
	SREG = oldSREG;

#if defined(HAIKU_AsuroTiming)
    return ((m * 256) + count36kHz) / 36;
	//return m * (clockCyclesPerMicrosecond() * 1000UL)/(64UL * 256UL);
#else
	return m * HAIKU_MillisDividend / HAIKU_MillisDivisor;
#endif
}

#endif


#if _DEBUG
FILE * fopen(char * file, char * mode) {
	return 0;
}

int jprintf(const char * format, ...) {
	char buf[80]; // nicht globaler buf !!
	char *p=buf;
	int err;
	va_list list;
	va_start(list, format);
	err=vsprintf(buf, format, list);
	  while (*p)
		  write(*p++);
	if (*--p=='\n') write('\r');
	va_end(list);
	return err;
}
#endif

#endif

