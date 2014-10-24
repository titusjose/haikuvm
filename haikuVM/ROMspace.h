#if NO_MICRO

#define PROGMEM
#define strcpy_P strcpy
#define strlen_P strlen
#define memcpy_P memcpy
//#define pgm_read_byte(x) x
#define pgm_read_byteRef(x) ((char)x)
//#define pgm_read_word(x) x
#define pgm_read_wordRef(x) x
#define pgm_read_dwordRef(x) x
#define pgm_read_word(x) (*(x))

#else

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define pgm_read_byteRef(x) pgm_read_byte(&(x))
#define pgm_read_wordRef(x) pgm_read_word(&(x))
#define pgm_read_dwordRef(x) pgm_read_dword(&(x))

#endif



