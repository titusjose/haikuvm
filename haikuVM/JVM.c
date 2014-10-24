#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "haikuJ2C.h"
#include "utility/haikuConfig.h"
#include "simpleOS.h"

uint8_t bc;
int8_t t;


extern const ByteCode main_YLjava_lang_String;
extern const class_t java_lang_Thread__class;


void unimplemented() {
	panic(VirtualMachineError, 0); //unimplemented byte code
}

void unused() {
	panic(VirtualMachineError, 1); //(normaly) unused byte code
}

__attribute__((noinline)) int32_t GETCODEDWORD2() {
	int32_t codei=pgm_read_dwordRef(*((int32_t*)pc));
	pc+=4;
	return codei;
}

#if NO_MICRO
__attribute__((noinline)) void* GETCODEADR2() {
	void* codei=pgm_read_dwordRef(*((void**)pc));
	pc+=sizeof(void*);
	return codei;
}
#endif

__attribute__((noinline)) int16_t GETCODEWORD2() {
	int16_t codei=pgm_read_wordRef(*((int16_t*)pc));
	pc+=2;
	return codei;
}

__attribute__((noinline)) int GETCODEBYTE2() {
	uint8_t codei=pgm_read_byteRef(*pc);
	pc+=1;
	return codei;
}

void switchThread() {
	// Task switch
#if TRACEING
	void *save=currentThread;
#endif
#if HAIKU_Threads
	*dataSp=top.s1;
	currentThread->programcounter=pc;
	currentThread->stackpointer=dataSp;
	currentThread->stackframe=lsp;
	currentThread->stack=stack;
#endif
	while(1) {
		incrementalGC(HAIKU_IncrementalGCSlice);
		allStatics.statics.java_lang_Thread_currentThread = (jobject) currentThread->next;

			// restart if state is IDLE or YIELD
		if (currentThread->state<=YIELD ||
			// restart if state is WAITING and waiting time is over (see sleep(..) and wait(..))
		    (currentThread->state==WAITING && (julong)(currentThread->waitUntil)<=millis())) break;
#if NO_MICRO
		if (currentThread->state==STOPPED && currentThread->next == currentThread ) {
#if	_DEBUG
			getc(stdin);
#endif
			exit(0);
		}
#endif
	}

	currentThread->state=IDLE;
#if HAIKU_Threads
	pc=(unsigned char*)currentThread->programcounter;
	dataSp=currentThread->stackpointer;
	lsp=currentThread->stackframe;
	stack=currentThread->stack;
	top.s1=*dataSp;
#endif
#if TRACEING
	if (save!=currentThread) {
		jprintf("################################# next Thread %p\n", currentThread);
	}
#endif
}

#if NO_MICRO

#define	LABEL(x)	BC_##x

#define SWITCH(x)	switch(*(bytecodeLabels+x)) {
#define BEGCODE(x)    case BC_##x: {
#define ENDCODE       }; break;
#define ENDSWITCH	default: unused(); }

//#define PUSHTOP0()	goto loopTop0
#define PUSHTOP0()	pushTop0();
#define LOOP_THREAD() goto loopThread
typedef int label_t;

#else

#define	LABEL(x)	&&OPL_##x
#define SWITCH(x)	goto *(label_t)pgm_read_wordRef(*(bytecodeLabels+x));

#define BEGCODE(x)  OPL_##x: {
#define ENDCODE     }; goto loop;

#define ENDSWITCH
//#define PUSHTOP0()	goto loopTop0
#define PUSHTOP0()	pushTop0();
#define LOOP_THREAD() goto loopThread

typedef void * label_t;

#endif

#pragma GCC diagnostic ignored "-Wunused-label"

heapmem_t heapmem; // ={HEAPSIZE, FREE};

void setupHaikuVM() {
	// init Java heap
	heapmem.heapControl.xallocsize = HEAPSIZE;

	// must be the following order to save Mark(stack) in java_lang_System_gc_V()
	// setup main thread
	allStatics.statics.java_lang_Thread_currentThread = newInstance(
			(class_t*) &java_lang_Thread__class);
	// setup first stack frame
	stack = (stackFrame4Debug_t*) newStack(HAIKU_InitialMainThreadStackSize);
	dataSp = &stack->stack[0];

	// init main thread
	currentThread->next = currentThread;
	currentThread->stack = stack;

	// prepare first method to run
	invoke(&main_YLjava_lang_String);
}

#ifdef ARDUINO
//slow (but needed for Arduino IDE)
void interpretNextByteCode(){
#include "utility/bytecodeDispatcher.h"

	bc=pgm_read_byteRef((*pc));
	pc++;

	SWITCH(bc)
#include "Bytecodes.h"
	ENDSWITCH;
	return;

loopThread:
	t++;
#if HAIKU_Threads!=0
		if ((t++&0x3)==0) {
			switchThread();
		}
#endif

loop:
	;
}
#else
/**
 * fast
 * But for some unkonwn reason it is included into the hex file
 * if compiled with ArduinoIDE but shoudn't. See interpretNextByteCode() instead.
 * This is why we need #ifndef ARDUINO. This saves space.
 *
 * setup JVM and interpret main_YLjava_lang_String for ever (which is not over and over again)
 */
void startJVM() {
#include "utility/bytecodeDispatcher.h"

#if defined(ARDUINO_SAM_DUE)
#else
#if defined(USBCON)
    USBCON &= 127; // CLEAR BIT 7 -> disable USB interrupt
#endif
#endif

    setupHaikuVM();

	sei();

loopThread:
#if HAIKU_Threads!=0
	if ((t++&0x3)==0) {
		switchThread();
	}
#endif

loop:
	bc=pgm_read_byteRef((*pc));
	pc++;

	SWITCH(bc)
#include "Bytecodes.h"
	ENDSWITCH;

	goto loop;
}
#endif

