#ifndef OPTIONS
#define OPTIONS

struct OptStruct {
  char *input;
  char *source;
  long long byteOutputSize;
};

int ProcessOptions(int argc, char **argv, struct OptStruct *ptr_opts, long long *nBytes);
#endif
