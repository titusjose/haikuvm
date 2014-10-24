#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#include "haikuJ2C.h"
#include "utility/haikuConfig.h"
#include "simpleOS.h"

#define Debug(x)

static int GCcalls=0;
/*
Heap layout:
typedef struct {
	jheapsize allocsize;
	jclass clazz;
	struct {
		field1;
		...
		fieldN;
	} user;
} Object1;
...
typedef struct {
	jheapsize allocsize;
	jclass clazz;
	struct {
		field1;
		...
		fieldN;
	} user;
} ObjectN;
...
typedef struct { // not realy a struct but used here to explain a FREE block
	jheapsize allocsize;
	jclass clazz; // is set with value FREE
	char free[allocsize/2]
} FreeBlock;
...
0;	//allocsize of 0 signals end of heap.

*/
static int isMarked(jobject obj) {
	return getMarkFlag(obj);
}

static int isFree(jobject obj) {
	return getClass(obj)==FREE;
}

static void MarkBit(jobject obj) {
	setMarkFlag(obj);
}

__attribute__((noinline)) jheapsize getObjLength(jobject obj) {
	return getAllocsize(obj);
}

#if _DEBUG || NO_MICRO
extern const char * findClass(jclass clazz);

static int	GCcount=0;
static jheapsize usedHeap=0;
/**
* mode=0 -> FREE
* mode=1 -> Used
*/
void haikuHeapWalk(char * msg, int mode) {
	char* ptr;
	jheapsize len;
	int i, sum=0, free=0;
	jprintf("  walk: %s [%p, %p] len=%d GCcount=%d usedHeap=%d\n", msg, (char*)&heapmem, ((char*)&heapmem)+HEAPSIZE, HEAPSIZE, GCcount, usedHeap);
	for(ptr=HEAP2OBJ(&heapmem), i=0; (len=getObjLength(ptr)); ptr+=len, i++) {
		if (ptr+len<((char*)&heapmem) || ((char*)HEAP2OBJ(&heapmem))+HEAPSIZE<ptr+len) {
			//heap is corrupt
			jprintf("  walk: heap is corrupt at %p (= %p + %d) with len %d and HEAPSIZE=%d\n", ptr, (char*)&heapmem, ptr-(char*)&heapmem, len, HEAPSIZE);
			return;
		}
	}
	for(ptr=HEAP2OBJ(&heapmem), i=0; (len=getObjLength(ptr)); ptr+=len, i++) {
		sum+=len;
		if (isFree(ptr)) {
			free+=len;
			jprintf("    %d\t%p\t%d\t%d\t%d\t%s\n", i, ptr, len, sum, free, findClass(getClass(ptr)));
		} else {
			jprintf("    %d\t%p\t%d\t%d\t  \t%s", i, ptr, len, sum,     findClass(getClass(ptr)));
			if (strcmp("java.lang.String", findClass(getClass(ptr)))==0) {
				int j;
				jstring str= (jstring)ptr;
				if (str->chars) {
					jprintf(" %2d = \"", str->chars->length);
					for(j=0; j<str->chars->length; j++) {
						if (str->chars->array[j]) {
							jprintf("\%c", str->chars->array[j]);
						} else {
							jprintf("\\0");
						}
					}
					jprintf("\"");
				} else {
					jprintf("   = null");
				}
			}
			jprintf("\n");
		}
	}
	jprintf("end\n");
}
#endif

void testHeap(void * test) {
	char* ptr=HEAP2OBJ(&heapmem);
	jheapsize len;

	for(; (len=getObjLength(ptr)); ptr+=len) {
		if (isMarked(ptr)) {
			MarkBit(ptr);
		} else {
			setAllocsize(ptr, len);
		}
	}
}

static int isPointer(jobject test) {
	char* ptr=HEAP2OBJ(&heapmem);
	jheapsize len;

	// true only if test is the begin of a heap alloc
	for(; (len=getObjLength(ptr)) && (char*)test!=ptr; ptr+=len) {
		// noop
	}
	return len;
}

static int setMark(jobject pObj) {
	char* ptr=HEAP2OBJ(&heapmem);
	if ((char*)pObj<ptr || ptr+sizeof(heapmem_t)<=(char*)pObj) return 0; // test is no heap pointer
	if ( !isMarked(pObj) && isPointer(pObj)) { // Marked returns the marked flag from object header
        MarkBit(pObj); // Marks the flag in obj header
		return 1;
	}
	return 0;
}

static jobject Reuse(jint size) {
	char* ptr;
	jheapsize len;
	for(ptr=HEAP2OBJ(&heapmem); (len=getObjLength(ptr)); ptr+=len) {
		if(isFree(ptr)) {
			if (size==len) break; // Perfect hit so don't allocate extra FREE block
			if (size+sizeof(heap_t)<=len) {
				jobject free=ptr;
#if _DEBUG
				usedHeap+=size;
#endif
				size=len-size;
				if (2*(ptr-(char*)(&heapmem))>HEAPSIZE-len) {
					ptr+=size;
				} else {
					free=(ptr+(len-size));
				}
				setAllocsize(free, size);
				setClass(free, FREE);
				break;
			}
		}
	}
	if (len==0) ptr=NULL;
	return (jobject)ptr;
}

///////////////////////////////////////////////////////////////
#if HAIKU_GC==HAIKU_NoGC
#include "gcVariants/no.h"
#elif HAIKU_GC==HAIKU_IncrementalGC
#include "gcVariants/incremental.h"
#elif HAIKU_GC==HAIKU_ConservativGC
#include "gcVariants/conservative.h"
#elif HAIKU_GC==HAIKU_CompactingGC
#include "gcVariants/compacting.h"
#else
#include "gcVariants/conservative.h"
#endif
///////////////////////////////////////////////////////////////

jobject newInstance(jclass clazz) {
	return GCalloc(clazz, pgm_read_wordRef(clazz->mem));
}

extern const class_t java_lang_Object__class PROGMEM;
extern const uint8_t defs[];

array_t * newarray(jint length, int size) {
	//Every array is an Object
	array_t * a=(array_t *)GCalloc((jclass)&java_lang_Object__class, sizeof(array_t)+length*pgm_read_byteRef(defs[size]));
#if	HAIKU_PanicExceptions & OutOfMemoryError
	if (a!=NULL) a->length=length;
#else
	a->length=length;
#endif
	return a;
	/*
	static const int size PROGMEM= (sizeof(jdouble)<<12)+(sizeof(jfloat)<<10)+(sizeof(jlong)<<8)+(sizeof(jint)<<6)+(sizeof(jchar)<<4)+(sizeof(jbyte)<<2)+sizeof(jobject);
	int s=pgm_read_wordRef(size);
	s>>=2*GETCODEBYTE2();
	newarray(s&0x3);
	*/
}

void multiArray(jobjectArray* GCroot, int d, int size) {
	jint length=(dataSp-d)->i;
	d--;
	if (d) {
		int i;
		jobjectArray a=(jobjectArray)newarray(length, 0);
#if	HAIKU_PanicExceptions & OutOfMemoryError
	    if (a==NULL) return;
#endif
		*GCroot=a;
		for (i=0; i<length; i++) {
			multiArray((jobjectArray*)&(a->array[i]), d, size);
		}
	} else {
		*GCroot=(jobjectArray)newarray(length, size);
	}
}

stackFrame_t* newStack(int length) {
	return (stackFrame_t *)newarray(length, 8);
}

