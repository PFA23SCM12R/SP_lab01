#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>

int open_file(const char *filename);
void close_file();
int read_int(int *var);
int read_string(char *str, int max_len);
int read_float(float *var);

#endif // READFILE_H

