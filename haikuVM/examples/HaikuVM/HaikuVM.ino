/*
 *  HaikuVM 
 */

#include "haikuJ2C.h"

/*
 * Setup the Haiku JAVA VM
 * and start main(String[]) of the MicroKernel
 */
void setup()
{
  setupHaikuVM();
}


/*
 * Interprete for ever 
 * one JAVA byte code per loop call
 */
void loop(void) {
  interpretNextByteCode();
}