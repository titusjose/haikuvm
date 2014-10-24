
Debug(static int GCinc);

static int GCtransaction=0;
static char * write_barrier;

__attribute__((noinline)) void setMarkBit(jobject obj) {
	if ( !(obj==NULL || isMarked(obj))) {
		setMarkFlag(obj);
		if (write_barrier>obj) write_barrier=obj;
	}
}

/**
 * Incremental Conservative
 */
void incrementalGC(int incremental) {
#define ROOT 0
#define MARK 1
#define SWEEP 2
    static int GCtransactionSave;
	static int gcPhase=ROOT;
	static char* ptr;
	char* p;
	jheapsize len;
	jheapsize i;
	jobject h;

	Debug(GCinc++);
	if (gcPhase==ROOT && GCtransactionSave!=GCtransaction && stack!=NULL) {
		GCtransactionSave=GCtransaction;

		memset(dataSp, 0, ((int)&stack->stack[stack->length]-(int)dataSp)); // just good for GC
		for(i=0; i<STATIC_ROOTS; i++) {
			if(allStatics.gcRoots[i]) MarkBit(allStatics.gcRoots[i]);
		}
		setMark(top.s1.a);
		gcPhase=MARK;
		write_barrier=HEAP2OBJ(&heapmem);
		if (--incremental<=0) return;
	}
	if (gcPhase==MARK) {
		// Mark (short but slow -> O(N*N) maybe O(N*N*N) because of indirect use of isPointer(..) in setMark(..))
rescan:
		while((len=getObjLength(write_barrier))) {
			if (isMarked(write_barrier)) {
				// scan this specific heap alloc block (which starts at ptr)
				for(i=0; i+sizeof(void*)+sizeof(heap_t)-1<len; i++) {
					h=*(jobject*)(write_barrier+i);
					if (setMark(h) && h < write_barrier) {
						write_barrier=h;
						if (--incremental<=0) return;
						goto rescan; // only if we marked something befor ptr. setMark(h) garanties that h points to a heap alloc block.
					}
				}

			}
			write_barrier+=len;
			if (--incremental<=0) return;
		}
		ptr=HEAP2OBJ(&heapmem);
		gcPhase=SWEEP;
	}
	if (gcPhase==SWEEP) {
		// Sweep Version 1
		while((len=getObjLength(ptr))) {
			if(!isMarked(ptr)) {
				for(p=ptr; (i=getObjLength(p)) && !isMarked(p); p+=i) {
					// noop: just feed forward to next marked element
				}
				len=p-ptr;
				setClass(ptr, FREE);
			}
			setAllocsize(ptr, len); // (re-)set len and unMark

			ptr+=len;
			if (--incremental<=0) return;
		}
		gcPhase=ROOT;

		Debug(GCcount++);
		Debug(jprintf("\nGC #################### %d/%d\n", GCinc, GCcount));

		Debug(haikuHeapWalk("heap", 1);)
		Debug(haikuHeapWalk("free", 0);)
	}
}

void native_java_lang_System_gc_V() {
	incrementalGC(0x7fff);
	incrementalGC(0x7fff);
}

jheap GCalloc(jclass clazz, jint size) {
	int rec;
	jobject ptr=NULL;

	for(rec=0; ptr==NULL && rec<2; rec++) {
	    GCtransaction++;
		if (rec>0) incrementalGC(0x7fff);
		ptr=Reuse(size+sizeof(heap_t));
	}
	if (ptr) {
		memset(ptr, 0, size);
		setClass(ptr, clazz);
		setAllocsize(ptr, size+sizeof(heap_t));
		MarkBit(ptr); // no write_barrier shift needed
	} else {
#if NO_MICRO
		jprintf("needed %d (+%d if reuse) more bytes for %s\n", size+sizeof(heap_t), sizeof(heap_t), findClass(clazz));
#endif
		//fatal("heap overflow");
		panic(OutOfMemoryError, size);
	}
	return ptr;
}
