#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../include/tokenizer.h"

#define BUFFER 1024
#define VAR_LEN 64
#define ARG_LEN 3

#define PAREN_OPEN 40 // "("
#define PAREN_CLOSED 41 // ")"
#define COLON 158 // ":"
#define COMMA 44 // ","


int slice_until(int limit, const char *buffer, char *slice);


int lex(string filename, Func *func) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {
        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
            // do something!
        }

        fclose(file);  
    } 
    
    if (ferror(file)) {
        fprintf(stderr, "An error occurred with filename %s", filename);
    }

    return 0;
}


void tokenize_arguments(char *buffer, char **args) {
    size_t numArgs = 0;

    char c;
    while ((c=*buffer++) != PAREN_CLOSED) {
        char arg[VAR_LEN];
        int i = slice_until(COMMA, buffer, arg);
        *(args + numArgs) = arg;
        numArgs++;
        buffer += i;
    }
}


int slice_until(int limit, const char *buffer, char *slice) {
    size_t i = 0;
    while ((buffer[i] != limit) && (buffer[i] != '\0')) {
        slice[i] = buffer[i];
        i++;
    }
    slice[i] = '\0';
    return i;
}


int main() {
    char **args = (char **) malloc(sizeof(void *) *BUFFER);
    char test[] = "(argument1, argument2)";
    
    tokenize_arguments(test, args);

    printf("%s", args[0]);
}
