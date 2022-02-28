#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int ProcessOptions(int argc, char **argv, struct OptStruct *ptr_opts, long long *nBytes) {
  int c;
  ptr_opts->byteOutputSize = -1;
  ptr_opts->input = "none";
  int err = 0;
  while ((c = getopt(argc, argv, "i:o:")) != -1) {
    switch(c) {
      case 'i':
	if (argc != 4 && argc != 6) {
          err = 1;
          break;
        }
        if (strcmp("rdrand", optarg) == 0) {
	  ptr_opts->input = "rdrand";
        }
        else if (strcmp("mrand48_r", optarg) == 0) {
	  ptr_opts->input = "mrand48_r";
        }
        else if (optarg[0] == '/') {
          ptr_opts->input = "/f";
          ptr_opts->source = optarg;
        }
        else {
	  err = 1;
        }
        break;
      
      case 'o':
	if (argc != 4 && argc != 6) {
          err = 2;
          break;
	}
        if (strcmp("stdio", optarg) != 0) {
	  ptr_opts->byteOutputSize = atoi(optarg);

          if (atoi(optarg) <= 0) {
            err = 3;
            break;
          }
        } 
        break;

      case ':':
        fprintf(stderr, "Option -%c needs an operand\n", optopt);

        if (optopt == 'i')
          err = 1;
        else
          err = 2;
        break;
      
      case '?':
        fprintf(stderr, "Unknown option: '-%c'\n", optopt);
        break;

      default:
        break;
    }
  }

  if (optind >= argc) {
    return err;
  }
  
  *nBytes = atol(argv[optind]);
  if (*nBytes < 0) {
    err = 3;
  }
  
  return err;
}

