#include "readfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *file = NULL;

// Function to open a file
int open_file(const char *filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;  // File couldn't be opened
    }
    return 0; // Success
}

// Function to close the opened file
void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}

// Function to read an integer from the file
int read_int(int *var) {
    if (file == NULL || fscanf(file, "%d", var) != 1) {
        return -1; // Failed to read an integer
    }
    return 0; // Success
}

// Function to read a string from the file
int read_string(char *str, int max_len) {
    if (file == NULL || fscanf(file, "%s", str) != 1) {
        return -1; // Failed to read a string
    }
    // Ensure the string is null-terminated if it exceeds max_len
    str[max_len - 1] = '\0';
    return 0; // Success
}

// Function to read a float from the file
int read_float(float *var) {
    if (file == NULL || fscanf(file, "%f", var) != 1) {
        return -1; // Failed to read a float
    }
    return 0; // Success
}

