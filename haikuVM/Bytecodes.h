
#ifndef BEGCODE
#define BEGCODE(bc) void OPF_##bc() {
#define ENDCODE };
#define PUSHTOP0()	pushTop0()
#define LOOP_THREAD()
#endif

/**
 * aaload (32) <br>
 *	arrayref, index ==> value<br>
 *	loads onto the stack a reference from an array<br>
 */
BEGCODE(AALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	setMarkBit(top.s1.a);
	if (checkIndex(adr, index)) top.s1.a=((jobjectArray)adr)->array[index];
ENDCODE

/**
 * aastore (53) <br>
 *	arrayref, index, value ==><br>
 *	stores into a reference in an array<br>
 */
BEGCODE(AASTORE)
	jobject value=top.s1.a;
	jint index=ipop();
	jobject adr=apop();
	setMarkBit(top.s1.a);
	popTop();
	if (checkIndex(adr, index))	((jobjectArray)adr)->array[index]=value;
ENDCODE

/**
 * aconst_null (01) <br>
 *	==> null<br>
 *	pushes a null reference onto the stack<br>
 */
BEGCODE(ACONST_NULL)
	pushTop();
	top.s1.a=NULL;
ENDCODE

/**
 * aload (19) 1: index<br>
 *	==> objectref<br>
 *	loads a reference onto the stack from a local variable #index<br>
 */
BEGCODE(ALOAD)	
	pushTop();
	top.s1=getLocal(GETCODEBYTE2())->s0;
	setMarkBit(top.s1.a);
ENDCODE

/**
 * aload_0 (2a) <br>
 *	==> objectref<br>
 *	loads a reference onto the stack from local variable 0<br>
 */
BEGCODE(ALOAD_0)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
	setMarkBit(top.s1.a);
ENDCODE

/**
 * aload_1 (2b) <br>
 *	==> objectref<br>
 *	loads a reference onto the stack from local variable 1<br>
 */
BEGCODE(ALOAD_1)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
	setMarkBit(top.s1.a);
ENDCODE

/**
 * aload_2 (2c) <br>
 *	==> objectref<br>
 *	loads a reference onto the stack from local variable 2<br>
 */
BEGCODE(ALOAD_2)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
	setMarkBit(top.s1.a);
ENDCODE

/**
 * aload_3 (2d) <br>
 *	==> objectref<br>
 *	loads a reference onto the stack from local variable 3<br>
 */
BEGCODE(ALOAD_3)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
	setMarkBit(top.s1.a);
ENDCODE

/**
 * anewarray (bd) 2: indexbyte1, indexbyte2<br>
 * HAIKU: anewarray (bd) 2: sizeindex<br>
 *	count ==> arrayref<br>
 *	creates a new array of references of length count and component type identified by the class reference index (indexbyte1 << 8 + indexbyte2) in the constant pool<br>
 */
BEGCODE(ANEWARRAY)
	void * mem = newarray(top.s1.i, GETCODEBYTE2());
	PanicAware(mem, top.s1.a=mem);
ENDCODE

/**
 * areturn (b0) <br>
 *	objectref ==> [empty]<br>
 *	returns a reference from a method<br>
 */
BEGCODE(ARETURN)
	areturn();
ENDCODE

/**
 * arraylength (be) <br>
 *	arrayref ==> length<br>
 *	gets the length of an array<br>
 */
BEGCODE(ARRAYLENGTH)
	top.s1.i=top.s1.ay->length;
ENDCODE

/**
 * astore (3a) 1: index<br>
 *	objectref ==><br>
 *	stores a reference into a local variable #index<br>
 */
BEGCODE(ASTORE)
	setLocal(GETCODEBYTE2(), &top.s1);
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

/**
 * astore_0 (4b) <br>
 *	objectref ==><br>
 *	stores a reference into local variable 0<br>
 */
BEGCODE(ASTORE_0)
	setLocal(bc&7, &top.s1);
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

/**
 * astore_1 (4c) <br>
 *	objectref ==><br>
 *	stores a reference into local variable 1<br>
 */
BEGCODE(ASTORE_1)
	setLocal(bc&7, &top.s1);
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

/**
 * astore_2 (4d) <br>
 *	objectref ==><br>
 *	stores a reference into local variable 2<br>
 */
BEGCODE(ASTORE_2)
	setLocal(bc&7, &top.s1);
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

/**
 * astore_3 (4e) <br>
 *	objectref ==><br>
 *	stores a reference into local variable 3<br>
 */
BEGCODE(ASTORE_3)
	setLocal(bc&7, &top.s1);
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

/**
 * athrow (bf) <br>
 *	objectref ==> [empty], objectref<br>
 *	throws an error or exception (notice that the rest of the stack is cleared, leaving only a reference to the Throwable)<br>
 */
BEGCODE(ATHROW)
	athrow(top.s1.a);
ENDCODE

/**
 * baload (33) <br>
 *	arrayref, index ==> value<br>
 *	loads a byte or Boolean value from an array<br>
 */
BEGCODE(BALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index))	top.s1.i=((jbyteArray)adr)->array[index];
ENDCODE

/**
 * bastore (54) <br>
 *	arrayref, index, value ==><br>
 *	stores a byte or Boolean value into an array<br>
 */
BEGCODE(BASTORE)
	jint value=top.s1.i;
	jint index=ipop();
	jobject adr=apop();
	popTop();
	if (checkIndex(adr, index))	((jbyteArray)adr)->array[index]=value;
ENDCODE

/**
 * bipush (10) 1: byte<br>
 *	==> value<br>
 *	pushes a byte onto the stack as an integer value<br>
 */
BEGCODE(BIPUSH)
	pushTop();
	top.s1.i=(int8_t)GETCODEBYTE2();
ENDCODE

/**
 * caload (34) <br>
 *	arrayref, index ==> value<br>
 *	loads a char from an array<br>
 */
BEGCODE(CALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index))	top.s1.c=((jchar8or16Array)adr)->array[index];
ENDCODE

/**
 * castore (55) <br>
 *	arrayref, index, value ==><br>
 *	stores a char into an array<br>
 */
BEGCODE(CASTORE)
	jchar value=top.s1.c;
	jint index=ipop();
	jobject adr=apop();
	popTop();
	if (checkIndex(adr, index))	((jchar8or16Array)adr)->array[index]=value;
ENDCODE

/**
 * checkcast (c0) 2: indexbyte1, indexbyte2<br>
 *	objectref ==> objectref<br>
 *	checks whether an objectref is of a certain type, the class reference of which is in the constant pool at index (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(CHECKCAST)	
	jclass clazz=(jclass)GETCODEADR2();
	if (top.s1.a!=NULL && clazz!=getClass(top.s1.a)) {
		panic(ClassCastException, (int)getClass(top.s1.a));
	}
ENDCODE

/**
 * d2f (90) <br>
 *	value ==> result<br>
 *	converts a double to a float<br>
 */
BEGCODE(D2F)
	popTop0();
	top.s1.f=FLOAT2TF(TD2DOUBLE(top.d));
ENDCODE

/**
 * d2i (8e) <br>
 *	value ==> result<br>
 *	converts a double to an int<br>
 */
BEGCODE(D2I)
	popTop0();
	top.s1.i=TD2DOUBLE(top.d);
ENDCODE

/**
 * d2l (8f) <br>
 *	value ==> result<br>
 *	converts a double to a long<br>
 */
BEGCODE(D2L)
	popTop0();
	top.j=TD2DOUBLE(top.d);
	PUSHTOP0();
ENDCODE

/**
 * dadd (63) <br>
 *	value1, value2 ==> result<br>
 *	adds two doubles<br>
 */
BEGCODE(DADD)
	popTop0();	
	top.d=DOUBLE2TD(TD2DOUBLE(top.d)+TD2DOUBLE(popp2()->d));
	PUSHTOP0();
ENDCODE

/**
 * daload (31) <br>
 *	arrayref, index ==> value<br>
 *	loads a double from an array<br>
 */
BEGCODE(DALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index))	top.d=((jdoubleArray)adr)->array[index];
	PUSHTOP0();
ENDCODE

/**
 * dastore (52) <br>
 *	arrayref, index, value ==><br>
 *	stores a double into an array<br>
 */
BEGCODE(DASTORE)
	jint index;
	jobject adr;
	jdouble d;
	popTop0();
	d=top.d;
	index=ipop();
	adr=apop();
	popTop();
	if (checkIndex(adr, index))	((jdoubleArray)adr)->array[index]=d;
ENDCODE

/**
 * dcmpg (98) <br>
 *	value1, value2 ==> result<br>
 *	compares two doubles<br>
 */
BEGCODE(DCMPG)
	double v2, v1;
	popTop0();
	v2=TD2DOUBLE(top.d);
	v1=TD2DOUBLE(popp2()->d);
	if (v2<v1) top.s1.i=1; 
	else if (v2>v1) top.s1.i=-1; 
	else if (v1!=v1 || v2!=v2) top.s1.i=1; 
	else top.s1.i=0; 
ENDCODE

/**
 * dcmpl (97) <br>
 *	value1, value2 ==> result<br>
 *	compares two doubles<br>
 */
BEGCODE(DCMPL)
	double v2, v1;
	popTop0();
	v2=TD2DOUBLE(top.d);
	v1=TD2DOUBLE(popp2()->d);
	if (v2<v1) top.s1.i=1; 
	else if (v2>v1) top.s1.i=-1; 
	else if (v1!=v1 || v2!=v2) top.s1.i=-1; 
	else top.s1.i=0; 
ENDCODE

/**
 * dconst_0 (0e) <br>
 *	==> 0.0<br>
 *	pushes the constant 0.0 onto the stack<br>
 */
BEGCODE(DCONST_0)
	pushTop();
	top.d=DOUBLE2TD(bc&7);
	PUSHTOP0();
ENDCODE

/**
 * dconst_1 (0f) <br>
 *	==> 1.0<br>
 *	pushes the constant 1.0 onto the stack<br>
 */
BEGCODE(DCONST_1)
	pushTop();
	top.d=DOUBLE2TD(bc&7);
	PUSHTOP0();
ENDCODE

/**
 * ddiv (6f) <br>
 *	value1, value2 ==> result<br>
 *	divides two doubles<br>
 */
BEGCODE(DDIV)
	popTop0();	
	top.d=DOUBLE2TD(TD2DOUBLE(popp2()->d)/TD2DOUBLE(top.d));
	PUSHTOP0();
ENDCODE

/**
 * dload (18) 1: index<br>
 *	==> value<br>
 *	loads a double value from a local variable #index<br>
 */
BEGCODE(DLOAD)
	pushTop();
	top.d= getLocal(GETCODEBYTE2())->d;
	PUSHTOP0();
ENDCODE

/**
 * dload_0 (26) <br>
 *	==> value<br>
 *	loads a double from local variable 0<br>
 */
BEGCODE(DLOAD_0)
	pushTop();
	top.d= getLocal(bc&7)->d;
	PUSHTOP0();
ENDCODE

/**
 * dload_1 (27) <br>
 *	==> value<br>
 *	loads a double from local variable 1<br>
 */
BEGCODE(DLOAD_1)
	pushTop();
	top.d= getLocal(bc&7)->d;
	PUSHTOP0();
ENDCODE

/**
 * dload_2 (28) <br>
 *	==> value<br>
 *	loads a double from local variable 2<br>
 */
BEGCODE(DLOAD_2)
	pushTop();
	top.d= getLocal(bc&7)->d;
	PUSHTOP0();
ENDCODE

/**
 * dload_3 (29) <br>
 *	==> value<br>
 *	loads a double from local variable 3<br>
 */
BEGCODE(DLOAD_3)
	pushTop();
	top.d= getLocal(bc&7)->d;
	PUSHTOP0();
ENDCODE

/**
 * dmul (6b) <br>
 *	value1, value2 ==> result<br>
 *	multiplies two doubles<br>
 */
BEGCODE(DMUL)
	popTop0();	
	top.d=DOUBLE2TD(TD2DOUBLE(popp2()->d)*TD2DOUBLE(top.d));
	PUSHTOP0();
ENDCODE

/**
 * dneg (77) <br>
 *	value ==> result<br>
 *	negates a double<br>
 */
BEGCODE(DNEG)
	popTop0();	
	top.d=DOUBLE2TD(-TD2DOUBLE(top.d));
	PUSHTOP0();
ENDCODE

/**
 * drem (73) <br>
 *	value1, value2 ==> result<br>
 *	gets the remainder from a division between two doubles<br>
 */
BEGCODE(DREM)
	double d0, d1;
	jlong j;
	popTop0();	
	d0=TD2DOUBLE(popp2()->d);
	d1= d0 / TD2DOUBLE(top.d);
	j=d1;
	top.d=DOUBLE2TD(d0-j*top.d);
	PUSHTOP0();
ENDCODE

/**
 * dreturn (af) <br>
 *	value ==> [empty]<br>
 *	returns a double from a method<br>
 */
BEGCODE(DRETURN)
	popTop0();
	areturn();
	PUSHTOP0();
ENDCODE

/**
 * dstore (39) 1: index<br>
 *	value ==><br>
 *	stores a double value into a local variable #index<br>
 */
BEGCODE(DSTORE)
	popTop0();
	getLocal(GETCODEBYTE2())->d=top.d;
	popTop();
ENDCODE

/**
 * dstore_0 (47) <br>
 *	value ==><br>
 *	stores a double into local variable 0<br>
 */
BEGCODE(DSTORE_0)
	popTop0();
	getLocal(bc&7)->d=top.d;
	popTop();
ENDCODE

/**
 * dstore_1 (48) <br>
 *	value ==><br>
 *	stores a double into local variable 1<br>
 */
BEGCODE(DSTORE_1)
	popTop0();
	getLocal(bc&7)->d=top.d;
	popTop();
ENDCODE

/**
 * dstore_2 (49) <br>
 *	value ==><br>
 *	stores a double into local variable 2<br>
 */
BEGCODE(DSTORE_2)
	popTop0();
	getLocal(bc&7)->d=top.d;
	popTop();
ENDCODE

/**
 * dstore_3 (4a) <br>
 *	value ==><br>
 *	stores a double into local variable 3<br>
 */
BEGCODE(DSTORE_3)
	popTop0();
	getLocal(bc&7)->d=top.d;
	popTop();
ENDCODE

/**
 * dsub (67) <br>
 *	value1, value2 ==> result<br>
 *	subtracts a double from another<br>
 */
BEGCODE(DSUB)
	popTop0();	
	top.d=DOUBLE2TD(TD2DOUBLE(popp2()->d)-TD2DOUBLE(top.d));
	PUSHTOP0();
ENDCODE

/**
 * dup (59) <br>
 *	value ==> value, value<br>
 *	duplicates the value on top of the stack<br>
 */
BEGCODE(DUP)
	pushTop();
ENDCODE

/**
 * dup_x1 (5a) <br>
 *	value2, value1 ==> value1, value2, value1<br>
 *	inserts a copy of the top value into the stack two values from the top.s1<br>
 */
BEGCODE(DUP_X1)
	popTop0();
	pushTop();
	pushTop0();
ENDCODE

/**
 * dup_x2 (5b) <br>
 *	value3, value2, value1 ==> value1, value3, value2, value1<br>
 *	inserts a copy of the top value into the stack two (if value2 is double or long it takes up the entry of value3, too) or three values (if value2 is neither double nor long) from the top.s1<br>
 */
BEGCODE(DUP_X2)
	stack_t value2= *pop();
	stack_t value3= *pop();

	pushTop();
	*push()=value3;
	*push()=value2;
ENDCODE

/**
 * dup2 (5c) <br>
 *	{value2, value1} ==> {value2, value1}, {value2, value1}<br>
 *	duplicate top.s1 two stack words (two values, if value1 is not double nor long; a single value, if value1 is double or long)<br>
 */
BEGCODE(DUP2)
	top.s0= *(dataSp-1);
	pushTop();
	pushTop0();
ENDCODE

/**
 * dup2_x1 (5d) <br>
 *	value3, {value2, value1} ==> {value2, value1}, value3, {value2, value1}<br>
 *	duplicate two words and insert beneath third word (see explanation above)<br>
 */
BEGCODE(DUP2_X1)
	stack_t value2= *pop();
	stack_t value3= *pop();

	*push()=value2;
	pushTop();

	*push()=value3;

	*push()=value2;
ENDCODE

/**
 * dup2_x2 (5e) <br>
 *	{value4, value3}, {value2, value1} ==> {value2, value1}, {value4, value3}, {value2, value1}<br>
 *	duplicate two words and insert beneath fourth word<br>
 */
BEGCODE(DUP2_X2)
	stack_t value2= *pop();
	stack_t value3= *pop();
	stack_t value4= *pop();

	*push()=value2;
	pushTop();

	*push()=value4;
	*push()=value3;

	*push()=value2;
ENDCODE

/**
 * f2d (8d) <br>
 *	value ==> result<br>
 *	converts a float to a double<br>
 */
BEGCODE(F2D)
	top.d=DOUBLE2TD(TF2FLOAT(top.s1.f));
	PUSHTOP0();
ENDCODE

/**
 * f2i (8b) <br>
 *	value ==> result<br>
 *	converts a float to an int<br>
 */
BEGCODE(F2I)
	top.s1.i=TF2FLOAT(top.s1.f);
ENDCODE

/**
 * f2l (8c) <br>
 *	value ==> result<br>
 *	converts a float to a long<br>
 */
BEGCODE(F2L)
	top.j=TF2FLOAT(top.s1.f);
	PUSHTOP0();
ENDCODE

/**
 * fadd (62) <br>
 *	value1, value2 ==> result<br>
 *	adds two floats<br>
 */
BEGCODE(FADD)
	top.s1.f=FLOAT2TF(TF2FLOAT(top.s1.f) + TF2FLOAT(fpop()));
ENDCODE

/**
 * faload (30) <br>
 *	arrayref, index ==> value<br>
 *	loads a float from an array<br>
 */
BEGCODE(FALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index))	top.s1.f=((jfloatArray)adr)->array[index];
ENDCODE

/**
 * fastore (51) <br>
 *	arrayref, index, value ==><br>
 *	stores a float in an array<br>
 */
BEGCODE(FASTORE)
	jfloat value=top.s1.f;
	jint index=ipop();
	jobject adr=apop();
	popTop();
	if (checkIndex(adr, index))	((jfloatArray)adr)->array[index]=value;
ENDCODE

/**
 * fcmpg (96) <br>
 *	value1, value2 ==> result<br>
 *	compares two floats<br>
 * If the two numbers are the same, the integer 0 is pushed onto the stack. 
 * If value2 is greater than value1, the integer 1 is pushed onto the stack. 
 * If value1 is greater than value2, the integer -1 is pushed onto the stack. 
 * If either number is NaN, the integer 1 is pushed onto the stack. +0.0 and -0.0 are treated as equal.
 */
BEGCODE(FCMPG)
	float f2=TF2FLOAT(top.s1.f);
	float f1=TF2FLOAT(fpop());
	if (f2<f1) top.s1.i=1; 
	else if (f2>f1) top.s1.i=-1; 
	else if (f1!=f1 || f2!=f2) top.s1.i=1; 
	else top.s1.i=0; 
ENDCODE

/**
 * fcmpl (95) <br>
 *	value1, value2 ==> result<br>
 *	compares two floats<br>
 * If the two numbers are the same, the integer 0 is pushed onto the stack. 
 If value2 is greater than value1, the integer 1 is pushed onto the stack. 
 If value1 is greater than value2, the integer -1 is pushed onto the stack. 
 If either number is NaN, the integer -1 is pushed onto the stack. +0.0 and -0.0 are treated as equal.


 */
BEGCODE(FCMPL)
	float f2=TF2FLOAT(top.s1.f);
	float f1=TF2FLOAT(fpop());
	if (f2<f1) top.s1.i=1; 
	else if (f2>f1) top.s1.i=-1; 
	else if (f1!=f1 || f2!=f2) top.s1.i=-1; 
	else top.s1.i=0; 
ENDCODE

/**
 * fconst_0 (0b) <br>
 *	==> 0.0f<br>
 *	pushes 0.0f on the stack<br>
 */
BEGCODE(FCONST_0)
	pushTop();
	top.s1.f=FLOAT2TF(bc&7);
ENDCODE

/**
 * fconst_1 (0c) <br>
 *	==> 1.0f<br>
 *	pushes 1.0f on the stack<br>
 */
BEGCODE(FCONST_1)
	pushTop();
	top.s1.f=FLOAT2TF(bc&7);
ENDCODE

/**
 * fconst_2 (0d) <br>
 *	==> 2.0f<br>
 *	pushes 2.0f on the stack<br>
 */
BEGCODE(FCONST_2)
	pushTop();
	top.s1.f=FLOAT2TF(bc&7);
ENDCODE

/**
 * fdiv (6e) <br>
 *	value1, value2 ==> result<br>
 *	divides two floats<br>
 */
BEGCODE(FDIV)
	top.s1.f=FLOAT2TF(TF2FLOAT(fpop()) / TF2FLOAT(top.s1.f));
ENDCODE

/**
 * fload (17) 1: index<br>
 *	==> value<br>
 *	loads a float value from a local variable #index<br>
 */
BEGCODE(FLOAD)
	pushTop();
	top.s1=getLocal(GETCODEBYTE2())->s0;
ENDCODE

/**
 * fload_0 (22) <br>
 *	==> value<br>
 *	loads a float value from local variable 0<br>
 */
BEGCODE(FLOAD_0)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
ENDCODE

/**
 * fload_1 (23) <br>
 *	==> value<br>
 *	loads a float value from local variable 1<br>
 */
BEGCODE(FLOAD_1)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
ENDCODE

/**
 * fload_2 (24) <br>
 *	==> value<br>
 *	loads a float value from local variable 2<br>
 */
BEGCODE(FLOAD_2)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
ENDCODE

/**
 * fload_3 (25) <br>
 *	==> value<br>
 *	loads a float value from local variable 3<br>
 */
BEGCODE(FLOAD_3)
	pushTop();
	top.s1=getLocal(bc&7)->s0;
ENDCODE

/**
 * fmul (6a) <br>
 *	value1, value2 ==> result<br>
 *	multiplies two floats<br>
 */
BEGCODE(FMUL)
	top.s1.f=FLOAT2TF(TF2FLOAT(top.s1.f) * TF2FLOAT(fpop()));
ENDCODE

/**
 * fneg (76) <br>
 *	value ==> result<br>
 *	negates a float<br>
 */
BEGCODE(FNEG)
	top.s1.f=FLOAT2TF(-TF2FLOAT(top.s1.f));
ENDCODE

/**
 * frem (72) <br>
 *	value1, value2 ==> result<br>
 *	gets the remainder from a division between two floats<br>
 */
BEGCODE(FREM)
	jfloat f0, f1;
	jint i;
	f0=TF2FLOAT(pop()->f);
	f1= f0 / TF2FLOAT(top.s1.f);
	i=f1;
	top.s1.f=FLOAT2TF(f0-i*top.s1.f);
ENDCODE

/**
 * freturn (ae) <br>
 *	value ==> [empty]<br>
 *	returns a float<br>
 */
BEGCODE(FRETURN)
	areturn();
ENDCODE

/**
 * fstore (38) 1: index<br>
 *	value ==><br>
 *	stores a float value into a local variable #index<br>
 */
BEGCODE(FSTORE)
	setLocal(GETCODEBYTE2(), &top.s1);
	popTop();
ENDCODE

/**
 * fstore_0 (43) <br>
 *	value ==><br>
 *	stores a float value into local variable 0<br>
 */
BEGCODE(FSTORE_0)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * fstore_1 (44) <br>
 *	value ==><br>
 *	stores a float value into local variable 1<br>
 */
BEGCODE(FSTORE_1)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * fstore_2 (45) <br>
 *	value ==><br>
 *	stores a float value into local variable 2<br>
 */
BEGCODE(FSTORE_2)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * fstore_3 (46) <br>
 *	value ==><br>
 *	stores a float value into local variable 3<br>
 */
BEGCODE(FSTORE_3)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * fsub (66) <br>
 *	value1, value2 ==> result<br>
 *	subtracts two floats<br>
 */
BEGCODE(FSUB)
	top.s1.f=FLOAT2TF(TF2FLOAT(fpop()) - TF2FLOAT(top.s1.f));
ENDCODE

/**
 * getfield (b4) 2: index1, index2<br>
 *	objectref ==> value<br>
 *	gets a field value of an object objectref, where the field is identified by field reference in the constant pool index (index1 << 8 + index2)<br>
 */
BEGCODE(GETFIELD_L)
#if	HAIKU_PanicExceptions & NullPointerException
	jobject* addr=(jobject*)getField();
	if (addr!=NULL) {
		top.s1.a=*addr;
		setMarkBit(top.s1.a);
	}
#else
	top.s1.a=*(jobject*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_B)
#if	HAIKU_PanicExceptions & NullPointerException
	jbyte* addr=(jbyte*)getField();
	if (addr!=NULL) top.s1.i=*addr;
#else
	top.s1.i=*(jbyte*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_C)
#if	HAIKU_PanicExceptions & NullPointerException
	jchar* addr=(jchar*)getField();
	if (addr!=NULL) top.s1.i=*addr;
#else
	top.s1.i=*(jchar*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_D)
#if	HAIKU_PanicExceptions & NullPointerException
	jdouble* addr=(jdouble*)getField();
	if (addr!=NULL) {
		top.d=*addr;
		PUSHTOP0();
	}
#else
	top.d=*(jdouble*)getField();
	PUSHTOP0();
#endif
ENDCODE

BEGCODE(GETFIELD_F)
#if	HAIKU_PanicExceptions & NullPointerException
	jfloat* addr=(jfloat*)getField();
	if (addr!=NULL) top.s1.f=*addr;
#else
	top.s1.f=*(jfloat*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_I)
#if	HAIKU_PanicExceptions & NullPointerException
	jint* addr=(jint*)getField();
	if (addr!=NULL) top.s1.i=*addr;
#else
	top.s1.i=*(jint*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_J)
#if	HAIKU_PanicExceptions & NullPointerException
	jlong* addr=(jlong*)getField();
	if (addr!=NULL) {
		top.j=*addr;
		PUSHTOP0();
	}
#else
	top.j=*(jlong*)getField();
	PUSHTOP0();
#endif
ENDCODE

BEGCODE(GETFIELD_S)
#if	HAIKU_PanicExceptions & NullPointerException
	jshort* addr=(jshort*)getField();
	if (addr!=NULL) top.s1.i=*addr;
#else
	top.s1.i=*(jshort*)getField();
#endif
ENDCODE

BEGCODE(GETFIELD_Z)
#if	HAIKU_PanicExceptions & NullPointerException
	jboolean* addr=(jboolean*)getField();
	if (addr!=NULL) top.s1.i=*addr;
#else
	top.s1.i=*(jboolean*)getField();
#endif
ENDCODE

/**
 * getstatic (b2) 2: index1, index2<br>
 *	==> value<br>
 *	gets a static field value of a class, where the field is identified by field reference in the constant pool index (index1 << 8 + index2)<br>
 */
BEGCODE(GETSTATIC_L)
	pushTop();
	top.s1.a=*(jobject*)GETCODEADR2();
	setMarkBit(top.s1.a);
ENDCODE

/**
 * getstatic (b2) 2: index1, index2<br>
 *	==> value<br>
 *	gets a native static C struct
 */
BEGCODE(GETSTATIC_N)
	pushTop();
	top.s1.a=(jobject*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_B)
	pushTop();
	top.s1.i=*(jbyte*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_C)
	pushTop();
	top.s1.i=*(jchar*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_D)
	pushTop();
	top.d=*(jdouble*)GETCODEADR2();
	PUSHTOP0();
ENDCODE

BEGCODE(GETSTATIC_F)
	pushTop();
	top.s1.f=*(jfloat*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_I)
	pushTop();
	top.s1.i=*(jint*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_J)
	pushTop();
	top.j=*(jlong*)GETCODEADR2();
	PUSHTOP0();
ENDCODE

BEGCODE(GETSTATIC_S)
	pushTop();
	top.s1.i=*(jshort*)GETCODEADR2();
ENDCODE

BEGCODE(GETSTATIC_Z)
	pushTop();
	top.s1.i=*(jboolean*)GETCODEADR2();
ENDCODE

/**
 * goto (a7) 2: branchbyte1, branchbyte2<br>
 *	[no change]<br>
 *	goes to another instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(GOTO)
	pc=(unsigned char *)GETCODEADR2();
	LOOP_THREAD();
ENDCODE

/**
 * goto_w (c8) 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4<br>
 *	[no change]<br>
 *	goes to another instruction at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 + branchbyte2 << 16 + branchbyte3 << 8 + branchbyte4)<br>
 */
BEGCODE(GOTO_W)
	unimplemented();
ENDCODE

/**
 * i2b (91) <br>
 *	value ==> result<br>
 *	converts an int into a byte<br>
 */
BEGCODE(I2B)
	top.s1.i=(jbyte)top.s1.i;
ENDCODE

/**
 * i2c (92) <br>
 *	value ==> result<br>
 *	converts an int into a character<br>
 */
BEGCODE(I2C)
	top.s1.c=top.s1.i;
ENDCODE

/**
 * i2d (87) <br>
 *	value ==> result<br>
 *	converts an int into a double<br>
 */
BEGCODE(I2D)
	top.d=DOUBLE2TD(top.s1.i);
	PUSHTOP0();
ENDCODE

/**
 * i2f (86) <br>
 *	value ==> result<br>
 *	converts an int into a float<br>
 */
BEGCODE(I2F)
	top.s1.f=FLOAT2TF(top.s1.i);
ENDCODE

/**
 * i2l (85) <br>
 *	value ==> result<br>
 *	converts an int into a long<br>
 */
BEGCODE(I2L)
	top.j=top.s1.i; // without this AVR GCC leaves high bytes dirty
	PUSHTOP0();
ENDCODE

/**
 * i2s (93) <br>
 *	value ==> result<br>
 *	converts an int into a short<br>
 */
BEGCODE(I2S)
	top.s1.i=(jshort)top.s1.i;
ENDCODE

/**
 * iadd (60) <br>
 *	value1, value2 ==> result<br>
 *	adds two ints together<br>
 */
BEGCODE(IADD)
	top.s1.i+=ipop();
ENDCODE

/**
 * iaload (2e) <br>
 *	arrayref, index ==> value<br>
 *	loads an int from an array<br>
 */
BEGCODE(IALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index))	top.s1.i=((jintArray)adr)->array[index];
ENDCODE

/**
 * iand (7e) <br>
 *	value1, value2 ==> result<br>
 *	performs a bitwise and on two integers<br>
 */
BEGCODE(IAND)
	top.s1.i&=ipop();
ENDCODE

/**
 * iastore (4f) <br>
 *	arrayref, index, value ==><br>
 *	stores an int into an array<br>
 */
BEGCODE(IASTORE)
	jint value=top.s1.i;
	jint index=ipop();
	jobject adr=apop();
	popTop();
	if (checkIndex(adr, index))	((jintArray)adr)->array[index]=value;
ENDCODE

/**
 * iconst_m1 (02) <br>
 *	==> -1<br>
 *	loads the int value -1 onto the stack<br>
 */
BEGCODE(ICONST_M1)
	pushTop();
	top.s1.i=-1;
ENDCODE

/**
 * iconst_0 (03) <br>
 *	==> 0<br>
 *	loads the int value 0 onto the stack<br>
 */
BEGCODE(ICONST_0)
	pushTop();
	top.s1.i=0;
ENDCODE

/**
 * iconst_1 (04) <br>
 *	==> 1<br>
 *	loads the int value 1 onto the stack<br>
 */
BEGCODE(ICONST_1)
	pushTop();
	top.s1.i=1;
ENDCODE

/**
 * iconst_2 (05) <br>
 *	==> 2<br>
 *	loads the int value 2 onto the stack<br>
 */
BEGCODE(ICONST_2)
	pushTop();
	top.s1.i=2;
ENDCODE

/**
 * iconst_3 (06) <br>
 *	==> 3<br>
 *	loads the int value 3 onto the stack<br>
 */
BEGCODE(ICONST_3)
	pushTop();
	top.s1.i=3;
ENDCODE

/**
 * iconst_4 (07) <br>
 *	==> 4<br>
 *	loads the int value 4 onto the stack<br>
 */
BEGCODE(ICONST_4)
	pushTop();
	top.s1.i=4;
ENDCODE

/**
 * iconst_5 (08) <br>
 *	==> 5<br>
 *	loads the int value 5 onto the stack<br>
 */
BEGCODE(ICONST_5)
	pushTop();
	top.s1.i=5;
ENDCODE

/**
 * idiv (6c) <br>
 *	value1, value2 ==> result<br>
 *	divides two integers<br>
 */
BEGCODE(IDIV)
#if	HAIKU_PanicExceptions & ArithmeticException
	if ( top.s1.i==0 ) {
		ipop();
		panic(ArithmeticException, 0);
	} else {
		top.s1.i=ipop()/top.s1.i;
	}
#else
#if NO_MICRO
	if ( top.s1.i==0 ) {
		ipop();
		top.s1.i=-1;
	} else {
		top.s1.i=ipop()/top.s1.i;
	}
#else
	top.s1.i=ipop()/top.s1.i;
#endif
#endif
ENDCODE

/**
 * if_acmpeq (a5) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if references are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ACMPEQ)
	jobject v1=apop(), v2=top.s1.a;
	compare(v1!=v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_acmpne (a6) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if references are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ACMPNE)
	jobject v1=apop(), v2=top.s1.a;
	compare(v1!=v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmpeq (9f) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if ints are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPEQ)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmpne (a0) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if ints are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPNE)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmplt (a1) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if value1 is less than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPLT)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmpge (a2) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if value1 is greater than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPGE)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmpgt (a3) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if value1 is greater than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPGT)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * if_icmple (a4) 2: branchbyte1, branchbyte2<br>
 *	value1, value2 ==><br>
 *	if value1 is less than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IF_ICMPLE)
	jint v1=ipop(), v2=top.s1.i;
	compare(v1-v2);
	LOOP_THREAD();
ENDCODE

/**
 * ifeq (99) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFEQ)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * ifne (9a) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is not 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFNE)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * iflt (9b) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is less than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFLT)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * ifge (9c) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is greater than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFGE)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * ifgt (9d) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is greater than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFGT)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * ifle (9e) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is less than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFLE)
	compare(top.s1.i);
	LOOP_THREAD();
ENDCODE

/**
 * ifnonnull (c7) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is not null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFNONNULL)
	compare((int)top.s1.a); // TODO 64 bit pointer vs. 32bit int
	LOOP_THREAD();
ENDCODE

/**
 * ifnull (c6) 2: branchbyte1, branchbyte2<br>
 *	value ==><br>
 *	if value is null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)<br>
 */
BEGCODE(IFNULL)
	compare((int)top.s1.a); // TODO 64 bit pointer vs. 32bit int
	LOOP_THREAD();
ENDCODE

/**
 * iinc (84) 2: index, const<br>
 *	[No change]<br>
 *	increment local variable #index by signed byte const<br>
 */
BEGCODE(IINC)
	jstack top_s1 =(jstack)getLocal(GETCODEBYTE2());
	top_s1->i+=(int8_t)GETCODEBYTE2();
ENDCODE

/**
 * HAIKU: iinc1 (84) 1: index<br>
 *	[No change]<br>
 *	increment local variable #index by 1<br>
 */
BEGCODE(IINC1)
	jstack top_s1 =(jstack)getLocal(GETCODEBYTE2());
	top_s1->i++;
ENDCODE

/**
 * iload (15) 1: index<br>
 *	==> value<br>
 *	loads an int value from a local variable #index<br>
 */
BEGCODE(ILOAD)
	pushTop();
	top.s1.i=getLocal(GETCODEBYTE2())->s0.i;
ENDCODE

/**
 * iload_0 (1a) <br>
 *	==> value<br>
 *	loads an int value from local variable 0<br>
 */
BEGCODE(ILOAD_0)
	pushTop();
	top.s1.i=lsp[0].i;
ENDCODE

/**
 * iload_1 (1b) <br>
 *	==> value<br>
 *	loads an int value from local variable 1<br>
 */
BEGCODE(ILOAD_1)
	pushTop();
	top.s1.i=lsp[1].i;
ENDCODE

/**
 * iload_2 (1c) <br>
 *	==> value<br>
 *	loads an int value from local variable 2<br>
 */
BEGCODE(ILOAD_2)
	pushTop();
	top.s1.i=lsp[2].i;
ENDCODE

/**
 * iload_3 (1d) <br>
 *	==> value<br>
 *	loads an int value from local variable 3<br>
 */
BEGCODE(ILOAD_3)
	pushTop();
	top.s1.i=lsp[3].i;
ENDCODE

/**
 * imul (68) <br>
 *	value1, value2 ==> result<br>
 *	multiply two integers<br>
 */
BEGCODE(IMUL)
	top.s1.i*=ipop();
ENDCODE

/**
 * ineg (74) <br>
 *	value ==> result<br>
 *	negate int<br>
 */
BEGCODE(INEG)
	top.s1.i=-top.s1.i;
ENDCODE

/**
 * instanceof (c1) 2: indexbyte1, indexbyte2<br>
 *	objectref ==> result<br>
 *	determines if an object objectref is of a given type, identified by class reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(INSTANCEOF)
	top.s1.i=instanceOf(top.s1.a, (jclass)GETCODEADR2());
ENDCODE

/**
 * invokeinterface (b9) 4: indexbyte1, indexbyte2, count, 0<br>
 *	objectref, [arg1, arg2, ...] ==><br>
 *	invokes an interface method on object objectref, where the interface method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(INVOKEINTERFACE)
	unsigned char * code;
	int pos=GETCODEBYTE2();
	int msg=GETCODEBYTE2();
	if (pos==0) code=top.s1.a; else code=(dataSp-pos)->a;
	pc+=2;
	code=getMethod(code, msg);
	invoke((ByteCode *)code);
ENDCODE

/**
 * invokespecial (b7) 2: indexbyte1, indexbyte2<br>
 *	objectref, [arg1, arg2, ...] ==><br>
 *	invoke instance method on object objectref, where the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(INVOKESPECIAL)
	invoke((ByteCode *)GETCODEADR2());
ENDCODE

BEGCODE(INVOKESHORT)
	invoke((ByteCode *)pgm_read_wordRef(*(functionTable+bc)));
ENDCODE

/**
 * invokestatic (b8) 2: indexbyte1, indexbyte2<br>
 *	[arg1, arg2, ...] ==><br>
 *	invoke a static method, where the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(INVOKESTATIC)
	invoke((ByteCode *)GETCODEADR2());
ENDCODE

/**
 * invokevirtual (b6) 2: indexbyte1, indexbyte2<br>
 *	objectref, [arg1, arg2, ...] ==><br>
 *	invoke virtual method on object objectref, where the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(INVOKEVIRTUAL)
	jobject code;
	ByteCode * bytecode;
	int pos=GETCODEBYTE2();
	int msg=GETCODEBYTE2();
	pushTop(); dataSp--;
	code=(dataSp-pos)->a;
	bytecode=getMethod(code, msg);
	invoke((ByteCode *)bytecode);
ENDCODE

/**
 * ior (80) <br>
 *	value1, value2 ==> result<br>
 *	bitwise int or<br>
 */
BEGCODE(IOR)
	top.s1.i|=ipop();
ENDCODE

/**
 * irem (70) <br>
 *	value1, value2 ==> result<br>
 *	logical int remainder<br>
 */
BEGCODE(IREM)
	top.s1.i=ipop()%top.s1.i;
ENDCODE

/**
 * ireturn (ac) <br>
 *	value ==> [empty]<br>
 *	returns an integer from a method<br>
 */
BEGCODE(IRETURN)
	areturn();
ENDCODE

/**
 * ishl (78) <br>
 *	value1, value2 ==> result<br>
 *	int shift left<br>
 */
BEGCODE(ISHL)
	top.s1.i=ipop()<<top.s1.i;
ENDCODE

/**
 * ishr (7a) <br>
 *	value1, value2 ==> result<br>
 *	int arithmetic shift right<br>
 */
BEGCODE(ISHR)
	top.s1.i=ipop()>>top.s1.i;
ENDCODE

/**
 * istore (36) 1: index<br>
 *	value ==><br>
 *	store int value into variable #index<br>
 */
BEGCODE(ISTORE)
	setLocal(GETCODEBYTE2(), &top.s1);
	popTop();
ENDCODE

/**
 * istore_0 (3b) <br>
 *	value ==><br>
 *	store int value into variable 0<br>
 */
BEGCODE(ISTORE_0)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * istore_1 (3c) <br>
 *	value ==><br>
 *	store int value into variable 1<br>
 */
BEGCODE(ISTORE_1)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * istore_2 (3d) <br>
 *	value ==><br>
 *	store int value into variable 2<br>
 */
BEGCODE(ISTORE_2)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * istore_3 (3e) <br>
 *	value ==><br>
 *	store int value into variable 3<br>
 */
BEGCODE(ISTORE_3)
	setLocal(bc&7, &top.s1);
	popTop();
ENDCODE

/**
 * isub (64) <br>
 *	value1, value2 ==> result<br>
 *	int subtract<br>
 */
BEGCODE(ISUB)
	top.s1.i=ipop()-top.s1.i;
ENDCODE

/**
 * iushr (7c) <br>
 *	value1, value2 ==> result<br>
 *	int logical shift right<br>
 */
BEGCODE(IUSHR)
	top.s1.i=((juint)ipop())>>top.s1.i;
ENDCODE

/**
 * ixor (82) <br>
 *	value1, value2 ==> result<br>
 *	int xor<br>
 */
BEGCODE(IXOR)
	top.s1.i^=ipop();
ENDCODE

/**
 * jsr (a8) 2: branchbyte1, branchbyte2<br>
 *	==> address<br>
 *	jump to subroutine at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2) and place the return address on the stack<br>
 */
BEGCODE(JSR)
	unimplemented();
ENDCODE

/**
 * jsr_w (c9) 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4<br>
 *	==> address<br>
 *	jump to subroutine at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 + branchbyte2 << 16 + branchbyte3 << 8 + branchbyte4) and place the return address on the stack<br>
 */
BEGCODE(JSR_W)
	unimplemented();
ENDCODE

/**
 * l2d (8a) <br>
 *	value ==> result<br>
 *	converts a long to a double<br>
 */
BEGCODE(L2D)
	popTop0();
	top.d=DOUBLE2TD(1.0*top.j);
	PUSHTOP0();
ENDCODE

/**
 * l2f (89) <br>
 *	value ==> result<br>
 *	converts a long to a float<br>
 */
BEGCODE(L2F)
	popTop0();
	top.s1.f=FLOAT2TF(top.j);
ENDCODE

/**
 * l2i (88) <br>
 *	value ==> result<br>
 *	converts a long to a int<br>
 */
BEGCODE(L2I)
	popTop0();
	top.s1.i=(jint)top.j;
ENDCODE

/**
 * ladd (61) <br>
 *	value1, value2 ==> result<br>
 *	add two longs<br>
 */
BEGCODE(LADD)
	popTop0();
	top.j+=popp2()->j;
	PUSHTOP0();
ENDCODE

/**
 * laload (2f) <br>
 *	arrayref, index ==> value<br>
 *	load a long from an array<br>
 */
BEGCODE(LALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index)) 	top.j=((jlongArray)adr)->array[index];
	PUSHTOP0();
ENDCODE

/**
 * land (7f) <br>
 *	value1, value2 ==> result<br>
 *	bitwise and of two longs<br>
 */
BEGCODE(LAND)
	popTop0();
	top.j&=popp2()->j;
	PUSHTOP0();
ENDCODE

/**
 * lastore (50) <br>
 *	arrayref, index, value ==><br>
 *	store a long to an array<br>
 */
BEGCODE(LASTORE)
	jint index;
	jobject adr;
	jlong j;
	popTop0();
	j=top.j;
	index=ipop();
	adr=apop();
	popTop();
	if (checkIndex(adr, index)) ((jlongArray)adr)->array[index]=j;
ENDCODE

/**
 * lcmp (94) <br>
 *	value1, value2 ==> result<br>
 *	compares two longs values<br>
 */
BEGCODE(LCMP)
	// it's wrong to write: top.s1.i=(int)(jpop()-top.s1.j); because high bytes are neglected
	jlong j;
	popTop0();
	j=popp2()->j-top.j;
	if (j>0) top.s1.i=1;
	else if (j<0) top.s1.i=-1;
	else top.s1.i=0;
ENDCODE

/**
 * lconst_0 (09) <br>
 *	==> 0L<br>
 *	pushes the long 0 onto the stack<br>
 */
BEGCODE(LCONST_0)
	pushTop();
	top.j=0;
	PUSHTOP0();
ENDCODE

/**
 * lconst_1 (0a) <br>
 *	==> 1L<br>
 *	pushes the long 1 onto the stack<br>
 */
BEGCODE(LCONST_1)
	pushTop();
	top.j=1;
	PUSHTOP0();
ENDCODE

/**
 * ldc (12) 1: index<br>
 *	==> value<br>
 *	pushes a constant #index from a constant pool (String, int or float) onto the stack<br>
 */
BEGCODE(LDC_S)
	ldc();
ENDCODE

BEGCODE(LDC_I)
	ldc();
ENDCODE

BEGCODE(LDC_C)
	pushTop();
	top.s1.a=(jobject)GETCODEADR2();
	//Todo setMarkBit(top.s1.a); but for now classes reside in flash only
ENDCODE

BEGCODE(LDC_F)
	ldc_jfloat_t c;
	pushTop();
	// Nur so top.s1.fl kriege ich beim AVR das richtige float Format aus dem ROM
	c.fl=pgm_read_dwordRef(((ldc_jfloat_t*)GETCODEADR2())->fl);
	top.s1.f=FLOAT2TF(c.f);
ENDCODE

BEGCODE(LDC_FX)
	float n=0.0;
	pushTop();
	top.s1.f=FLOAT2TF((GETCODEBYTE2()-1)/n);
ENDCODE

/**
 * ldc_w (13) 2: indexbyte1, indexbyte2<br>
 *	==> value<br>
 *	pushes a constant #index from a constant pool (String, int or float) onto the stack (wide index is constructed as indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(LDC_W_S)
	ldc();
ENDCODE

BEGCODE(LDC_W_I)
	ldc();
ENDCODE

BEGCODE(LDC_W_F)	
	ldc_jfloat_t c;
	pushTop();
	// Nur so top.s1.fl kriege ich beim AVR das richtige float Format aus dem ROM
	c.fl=pgm_read_dwordRef(((ldc_jfloat_t*)GETCODEADR2())->fl);
	top.s1.f=FLOAT2TF(c.f);
ENDCODE

BEGCODE(LDC_W_FX)
	float n=0.0;
	pushTop();
	top.s1.f=FLOAT2TF((GETCODEBYTE2()-1)/n);
ENDCODE


/**
 * ldc2_w (14) 2: indexbyte1, indexbyte2<br>
 *	==> value<br>
 *	pushes a constant #index from a constant pool (double or long) onto the stack (wide index is constructed as indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(LDC2_W_D)
	ldc_jdouble_t c;
	pushTop();
	// Nur so top.s1.dl kriege ich beim AVR das richtige double Format aus dem ROM
	c.dl=pgm_read_dwordRef(((ldc_jdouble_t*)GETCODEADR2())->dl);
	top.d=DOUBLE2TD(c.d);
	PUSHTOP0();
ENDCODE

BEGCODE(LDC2_W_DX)
	double n=0.0;
	pushTop();
	top.d=DOUBLE2TD((GETCODEBYTE2()-1)/n);
	PUSHTOP0();
ENDCODE

BEGCODE(LDC2_W_L)	
	ldc();
	PUSHTOP0();
ENDCODE

/**
 * ldiv (6d) <br>
 *	value1, value2 ==> result<br>
 *	divide two longs<br>
 */
BEGCODE(LDIV)
	popTop0();
#if	HAIKU_PanicExceptions & ArithmeticException
	if ( top.j==0 ) {
		popp2();
		PUSHTOP0();
		panic(ArithmeticException, 0);
	} else {
		top.j=popp2()->j/top.j;
		PUSHTOP0();
	}
#else
#if NO_MICRO
	if ( top.j==0 ) {
		popp2();
		top.j=-1;
	} else {
		top.j=popp2()->j/top.j;
	}
#else
	top.j=popp2()->j/top.j;
#endif
	PUSHTOP0();
#endif
ENDCODE

/**
 * lload (16) 1: index<br>
 *	==> value<br>
 *	load a long value from a local variable #index<br>
 */
BEGCODE(LLOAD)
	pushTop();
	top.j=getLocal(GETCODEBYTE2())->j;
	PUSHTOP0();
ENDCODE

/**
 * lload_0 (1e) <br>
 *	==> value<br>
 *	load a long value from a local variable 0<br>
 */
BEGCODE(LLOAD_0)
	pushTop();
	top.j=getLocal(bc&7)->j;
	PUSHTOP0();
ENDCODE

/**
 * lload_1 (1f) <br>
 *	==> value<br>
 *	load a long value from a local variable 1<br>
 */
BEGCODE(LLOAD_1)
	pushTop();
	top.j=getLocal(bc&7)->j;
	PUSHTOP0();
ENDCODE

/**
 * lload_2 (20) <br>
 *	==> value<br>
 *	load a long value from a local variable 2<br>
 */
BEGCODE(LLOAD_2)
	pushTop();
	top.j=getLocal(bc&7)->j;
	PUSHTOP0();
ENDCODE

/**
 * lload_3 (21) <br>
 *	==> value<br>
 *	load a long value from a local variable 3<br>
 */
BEGCODE(LLOAD_3)
	pushTop();
	top.j=getLocal(bc&7)->j;
	PUSHTOP0();
ENDCODE

/**
 * lmul (69) <br>
 *	value1, value2 ==> result<br>
 *	multiplies two longs<br>
 */
BEGCODE(LMUL)
	popTop0();
	top.j*=popp2()->j;
	PUSHTOP0();
ENDCODE

/**
 * lneg (75) <br>
 *	value ==> result<br>
 *	negates a long<br>
 */
BEGCODE(LNEG)
	popTop0();
	top.j= -top.j;
	PUSHTOP0();
ENDCODE

/**
 * lookupswitch (ab) 4+: <0-3 bytes padding>, defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, npairs1, npairs2, npairs3, npairs4, match-offset pairs...<br>
 *	key ==><br>
 *	a target address is looked up from a table using a key and execution continues from the instruction at that address<br>
 */
BEGCODE(LOOKUPSWITCH)
	int i;
	jint index=top.s1.i;
	void * dflt;
	int32_t npairs;
	popTop();

	dflt=(void*)GETCODEADR2();
	npairs=GETCODEDWORD2();
	for(i=0; i<npairs; i++) {
		if (index==(jint)GETCODEDWORD2()) {
			dflt=(void*)GETCODEADR2();
			break;
		} else {
			pc+=sizeof(void *);
		}
	}
	pc=dflt;
ENDCODE

/**
 * lor (81) <br>
 *	value1, value2 ==> result<br>
 *	bitwise or of two longs<br>
 */
BEGCODE(LOR)
	popTop0();
	top.j|=popp2()->j;
	PUSHTOP0();
ENDCODE

/**
 * lrem (71) <br>
 *	value1, value2 ==> result<br>
 *	remainder of division of two longs<br>
 */
BEGCODE(LREM)
	popTop0();
	top.j=popp2()->j%top.j;
	PUSHTOP0();
ENDCODE

/**
 * lreturn (ad) <br>
 *	value ==> [empty]<br>
 *	returns a long value<br>
 */
BEGCODE(LRETURN)
	popTop0();
	areturn();
	PUSHTOP0();
ENDCODE

/**
 * lshl (79) <br>
 *	value1, value2 ==> result<br>
 *	bitwise shift left of a long value1 by int value2 positions<br>
 */
BEGCODE(LSHL)
	top.j=popp2()->j<<top.s1.i;
	PUSHTOP0();
ENDCODE

/**
 * lshr (7b) <br>
 *	value1, value2 ==> result<br>
 *	bitwise shift right of a long value1 by int value2 positions<br>
 */
BEGCODE(LSHR)
	top.j=popp2()->j>>top.s1.i;
	PUSHTOP0();
ENDCODE

/**
 * lstore (37) 1: index<br>
 *	value ==><br>
 *	store a long value in a local variable #index<br>
 */
BEGCODE(LSTORE)
	popTop0();
	getLocal(GETCODEBYTE2())->j=top.j;
	popTop();
ENDCODE

/**
 * lstore_0 (3f) <br>
 *	value ==><br>
 *	store a long value in a local variable 0<br>
 */
BEGCODE(LSTORE_0)
	popTop0();
	getLocal(bc&7)->j=top.j;
	popTop();
ENDCODE

/**
 * lstore_1 (40) <br>
 *	value ==><br>
 *	store a long value in a local variable 1<br>
 */
BEGCODE(LSTORE_1)
	popTop0();
	getLocal(bc&7)->j=top.j;
	popTop();
ENDCODE

/**
 * lstore_2 (41) <br>
 *	value ==><br>
 *	store a long value in a local variable 2<br>
 */
BEGCODE(LSTORE_2)
	popTop0();
	getLocal(bc&7)->j=top.j;
	popTop();
ENDCODE

/**
 * lstore_3 (42) <br>
 *	value ==><br>
 *	store a long value in a local variable 3<br>
 */
BEGCODE(LSTORE_3)
	popTop0();
	getLocal(bc&7)->j=top.j;
	popTop();
ENDCODE

/**
 * lsub (65) <br>
 *	value1, value2 ==> result<br>
 *	subtract two longs<br>
 */
BEGCODE(LSUB)
	popTop0();
	top.j=popp2()->j-top.j;
	PUSHTOP0();
ENDCODE

/**
 * lushr (7d) <br>
 *	value1, value2 ==> result<br>
 *	bitwise shift right of a long value1 by int value2 positions, unsigned<br>
 */
BEGCODE(LUSHR)
	top.j=((julong)(popp2()->j))>>top.s1.i;
	PUSHTOP0();
ENDCODE

/**
 * lxor (83) <br>
 *	value1, value2 ==> result<br>
 *	bitwise exclusive or of two longs<br>
 */
BEGCODE(LXOR)
	popTop0();
	top.j^=popp2()->j;
	PUSHTOP0();
ENDCODE

/**
 * monitorenter (c2) <br>
 *	objectref ==><br>
 *	enter monitor for object ("grab the lock" - start of synchronized() section)<br>
 */
BEGCODE(MONITORENTER)
	monitorenter();
ENDCODE

/**
 * monitorexit (c3) <br>
 *	objectref ==><br>
 *	exit monitor for object ("release the lock" - end of synchronized() section)<br>
 */
BEGCODE(MONITOREXIT)
	monitorexit();
ENDCODE

/**
 * multianewarray (c5) 3: indexbyte1, indexbyte2, dimensions<br>
 * HAIKU: multianewarray (c5) 3: sizebyte, dimensions<br>
 *	count1, [count2,...] ==> arrayref<br>
 *	create a new array of dimensions dimensions with elements of type identified by class reference in constant pool index (indexbyte1 << 8 + indexbyte2); the sizes of each dimension is identified by count1, [count2, etc.]<br>
 */
BEGCODE(MULTIANEWARRAY)
	int size=GETCODEBYTE2(); // size of base type
	int dim= GETCODEBYTE2();

	pushTop();
	multiArray((jobjectArray*)&top.s1.a, dim, size);
	dataSp-=dim;
ENDCODE

/**
 * new (bb) 2: indexbyte1, indexbyte2<br>
 *	==> objectref<br>
 *	creates new object of type identified by class reference in constant pool index (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(NEW)
	pushTop();
	{
		void * mem = newInstance((jclass)GETCODEADR2());
		PanicAware(mem, top.s1.a=mem);
	}
ENDCODE

/**
 * newarray (bc) 1: atype<br>
 * HAIKU: newarray (bc) 1: sizeindex<br>
 *	count ==> arrayref<br>
 *	creates new array with count elements of primitive type identified by atype<br>
 */
BEGCODE(NEWARRAY)
	void * mem = newarray(top.s1.i, GETCODEBYTE2());
	PanicAware(mem, top.s1.a=mem);
ENDCODE

/**
 * nop (00) <br>
 *	[No change]<br>
 *	performs no operation<br>
 */
BEGCODE(NOP)
ENDCODE

/**
 * pop (57) <br>
 *	value ==><br>
 *	discards the top.s1 value on the stack<br>
 */
BEGCODE(POP)
	popTop();
ENDCODE

/**
 * pop2 (58) <br>
 *	{value2, value1} ==><br>
 *	discards the top.s1 two values on the stack (or one value, if it is a double or long)<br>
 */
BEGCODE(POP2)
	dataSp--;
	popTop();
ENDCODE

/**
 * putfield (b5) 2: indexbyte1, indexbyte2<br>
 *	objectref, value ==><br>
 *	set field to value in an object objectref, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(PUTFIELD_B)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jbyte*)(obj+GETCODEWORD2())=top.s1.b;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_C)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jchar*)(obj+GETCODEWORD2())=top.s1.c;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_D)
	char* obj;
	popTop0();
	obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jdouble*)(obj+GETCODEWORD2())=top.d;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_F)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jfloat*)(obj+GETCODEWORD2())=top.s1.f;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_I)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jint*)(obj+GETCODEWORD2())=top.s1.i;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_J)
	char* obj;
	popTop0();
	obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jlong*)(obj+GETCODEWORD2())=top.j;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_L)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jobject*)(obj+GETCODEWORD2())=top.s1.a;
	setMarkBit(top.s1.a);
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_S)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jshort*)(obj+GETCODEWORD2())=top.s1.s;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

BEGCODE(PUTFIELD_Z)
	char* obj=cppop();
#if	HAIKU_PanicExceptions & NullPointerException
	if (obj==NULL) {
		panic(NullPointerException, 0);
	} else {
#endif
	*(jboolean*)(obj+GETCODEWORD2())=top.s1.z;
	popTop();
#if	HAIKU_PanicExceptions & NullPointerException
	}
#endif
ENDCODE

/**
 * putstatic (b3) 2: indexbyte1, indexbyte2<br>
 *	value ==><br>
 *	set static field to value in a class, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 + indexbyte2)<br>
 */
BEGCODE(PUTSTATIC_B)
	*(jbyte*)GETCODEADR2()=top.s1.b;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_C)
	*(jchar*)GETCODEADR2()=top.s1.c;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_D)
	popTop0();
	*(jdouble*)GETCODEADR2()=top.d;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_F)
	*(jfloat*)GETCODEADR2()=top.s1.f;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_I)
	*(jint*)GETCODEADR2()=top.s1.i;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_J)
	popTop0();
	*(jlong*)GETCODEADR2()=top.j;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_L)
	*(jobject*)GETCODEADR2()=top.s1.a;
	setMarkBit(top.s1.a);
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_S)
	*(jshort*)GETCODEADR2()=top.s1.s;
	popTop();
ENDCODE

BEGCODE(PUTSTATIC_Z)
	*(jboolean*)GETCODEADR2()=top.s1.z;
	popTop();
ENDCODE

/**
 * ret (a9) 1: index<br>
 *	[No change]<br>
 *	continue execution from address taken from a local variable #index (the asymmetry with jsr is intentional)<br>
 */
BEGCODE(RET)
	unimplemented();
ENDCODE

/**
 * return (b1) <br>
 *	==> [empty]<br>
 *	return void from method<br>
 */
BEGCODE(RETURN)
	pushTop();
	areturn();
	popTop();
ENDCODE

/**
 * saload (35) <br>
 *	arrayref, index ==> value<br>
 *	load short from array<br>
 */
BEGCODE(SALOAD)
	jint index=top.s1.i;
	jobject adr=apop();
	if (checkIndex(adr, index)) top.s1.s=((jshortArray)adr)->array[index];
ENDCODE

/**
 * sastore (56) <br>
 *	arrayref, index, value ==><br>
 *	store short to array<br>
 */
BEGCODE(SASTORE)
	jlong value=top.s1.s;
	jint index=ipop();
	jobject adr=apop();
	popTop();
	if (checkIndex(adr, index)) 	((jshortArray)adr)->array[index]=value;
ENDCODE

/**
 * sipush (11) 2: byte1, byte2<br>
 *	==> value<br>
 *	pushes a short onto the stack<br>
 */
BEGCODE(SIPUSH)
	pushTop();
	top.s1.i=GETCODEWORD2();
ENDCODE

/**
 * swap (5f) <br>
 *	value2, value1 ==> value1, value2<br>
 *	swaps two top.s1 words on the stack (note that value1 and value2 must not be double or long)<br>
 */
BEGCODE(SWAP)
	popTop0();
	pushTop();
	top.s1=top.s0;
ENDCODE

/**
 * tableswitch (aa) 4+: [0-3 bytes padding], defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, lowbyte1, lowbyte2, lowbyte3, lowbyte4, highbyte1, highbyte2, highbyte3, highbyte4, jump offsets...<br>
 *	index ==><br>
 *	continue execution from an address in the table at offset index<br>
 */
BEGCODE(TABLESWITCH)
	jint index=top.s1.i;
	void * target;
	int32_t low, high;
	popTop();

	target=(void*)GETCODEADR2();
	low=GETCODEDWORD2();
	high=GETCODEDWORD2();
	if (low<=index && index<=high) {
		pc+=sizeof(void*)*(index-low);
		pc=(void*)GETCODEADR2();
	} else {
		pc=target;
	}
ENDCODE

/**
 * wide (c4) 3/5: opcode, indexbyte1, indexbyte2 or iinc, indexbyte1, indexbyte2, countbyte1, countbyte2<br>
 *	[same as for corresponding instructions]<br>
 *	execute opcode, where opcode is either iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or ret, but assume the index is 16 bit; or execute iinc, where the index is 16 bits and the constant to increment by is a signed 16 bit short<br>
 */
BEGCODE(WIDE)
	unimplemented();
ENDCODE

/**
 * HAIKU: wiinc (c4) 6: indexbyte1, indexbyte2, countbyte1, countbyte2<br>
 *	[No change]<br>
 *	increment local variable #index by signed byte const<br>
 */
BEGCODE(WIINC)
	jstack top_s1 =(jstack)getLocal(GETCODEWORD2());
	top_s1->i+=(int16_t)GETCODEWORD2();
ENDCODE



/**
 * breakpoint (ca) <br>
 *	<br>
 *	reserved for breakpoints in Java debuggers; should not appear in any class file<br>
 */
BEGCODE(BREAKPOINT)
	unimplemented();
ENDCODE

/**
 * impdep1 (fe) <br>
 *	<br>
 *	reserved for implementation-dependent operations within debuggers; should not appear in any class file<br>
 */
BEGCODE(IMPDEP1)
	unimplemented();
ENDCODE

/**
 * impdep2 (ff) <br>
 *	<br>
 *	reserved for implementation-dependent operations within debuggers; should not appear in any class file<br>
 */
BEGCODE(IMPDEP2)
	unimplemented();
ENDCODE

/**
 * xxxunusedxxx (ba) <br>
 *	<br>
 *	this opcode is reserved "for historical reasons"<br>
 */
BEGCODE(XXXUNUSEDXXX)
	unused();
ENDCODE

