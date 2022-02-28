/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
randall    instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "output.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "options.h"
#include "mrand48r.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main program, which outputs N bytes of random data.  */
int main (int argc, char **argv)
{
  struct OptStruct opt;
  long long nBytes;

  int err = ProcessOptions(argc, argv, &opt, &nBytes);

  //deal with errors
  switch (err) {
    case 0:
      break;
      
    // -i
    case 1:
      fprintf(stderr, "%s: usage: %s -i <rdrand/mrand48_r/FILE> byteCount\n", argv[0], argv[0]);
      return 1;
      
    // -o
    case 2:
      fprintf(stderr, "%s: usage: %s -o <stdio/N> byteCount\n", argv[0], argv[0]);
      return 1;

    case 3:  
      fprintf(stderr, "%s: usage: %s missing option operand or wrong operand \n", argv[0], argv[0]);
      return 1;
  }
  
  /* If there's no work to do, don't worry about which library to use.  */
  if (nBytes == 0)
    return 0;

  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  //generate via hardware
  if (strcmp("rdrand", opt.input) == 0 || strcmp("none", opt.input) == 0) {
    if (rdrand_supported()) { 
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    } 
    else {
      fprintf(stderr, "Hardware random-number generation requires x86-64 processors.");
      return 1;
    }
  }

  //generate via GNU mrand48
  else if (strcmp("mrand48_r", opt.input) == 0)
  {
    initialize = mrand48r_init;
    rand64 = mrand48r;
    finalize = mrand48r_fini;
  }

  //generate via software
  else
  {
    if (strcmp("/f", opt.input) == 0) {
      software_rand64_setFile(opt.source);
    }

    else if (strcmp("rdrand", opt.input) == 0)
    {
      fprintf(stderr, "RDRAND not supported\n");
      return 1;
    }

    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }

  initialize ();

  unsigned long long x;
  int outbytes;
  int output_errno = 0;
  int wordsize = sizeof rand64();

  // output by -o option (N)
  if (opt.byteOutputSize > 0) {
    char *buffer = malloc(opt.byteOutputSize);
    if (buffer == NULL)
    {
      fprintf(stderr, "Null memory");
      return 1;
    }
    
    do 
    {
      outbytes = nBytes < opt.byteOutputSize ? nBytes : opt.byteOutputSize;
      for (int i = 0; i < outbytes; i++){
        x = rand64();
        buffer[i] = x;
      }
      int writtenBytes = write(1, buffer, outbytes);
      if (writtenBytes == -1) {
	output_errno = errno;
	break;
      }
      int decrement = outbytes >= wordsize ? wordsize : outbytes; 
      nBytes -= decrement;
    } while (0 < nBytes);

    free(buffer);
  }

  else //default output
  {
    do
    {
      x = rand64();
      outbytes = nBytes < wordsize ? nBytes : wordsize;
      if (!writebytes(x, outbytes))
      {
        output_errno = errno;
        break;
      }
      nBytes -= outbytes;
    } while (0 < nBytes);
  }

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  finalize ();
  return !!output_errno;
}
