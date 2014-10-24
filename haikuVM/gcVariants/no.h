void native_java_lang_System_gc_V() {
}

jobject GCalloc(jclass clazz, jint size) {
	jobject ptr;

	ptr=Reuse(size+sizeof(heap_t));
	if (ptr) {
		memset(ptr, 0, size);
		setClass(ptr, clazz);
		setAllocsize(ptr, size+sizeof(heap_t));
	} else {
#if NO_MICRO
		jprintf("needed %d (+%d if reuse) more bytes\n", size, sizeof(heap_t));
#endif
		//fatal("heap overflow");
		panic(OutOfMemoryError, size);
	}
	return ptr;
}
