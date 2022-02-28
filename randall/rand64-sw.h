#ifndef RAND64_SW
#define RAND64_SW
#include <stdio.h>
#include <stdlib.h>

void
software_rand64_setFile (char *file);

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (void);

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void);

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void);

#endif
