#include <stdio.h>
#include <assert.h>
#include "../../include/str_utils.h"
#include "../../include/tokenizer.h"
#include "config.c"


Func *newFunc(char **args, string returnValue) {
    Func *func = (Func*) malloc(sizeof(Func));
    func->args = args;
    func->returnValue = returnValue;
    return func;
}


void freeFunc(Func *func) {
    assert(func != NULL);

    if (func->args != NULL) {
        free(func->args);
    }

    free(func);
}


char **tokenize_arguments(char *buffer) {
    assert(buffer != NULL);
    assert(no_spaces(buffer));

    char **args = (char**) malloc(ARG_LEN);
    char arg_str[VAR_LEN * ARG_LEN];
    slice_until(PAREN_CLOSED, buffer, arg_str);
    assert((length(buffer) > 0)); // Syntax error: no closing parentheses found

    split(COMMA, arg_str, args);

    return args;
}


// TODO fix memory leaks
Func *tokenize_function(char *buffer) {
    assert(buffer != NULL);
    assert(no_spaces(buffer));

    skip_until(PAREN_OPEN, buffer);
    char **args = tokenize_arguments(buffer);

    skip_until(COLON, buffer);
    char *returnVal = (char*) malloc(VAR_LEN);
    slice_until(PAREN_CLOSED, buffer, returnVal);

    return newFunc(args, returnVal);
}


int lex(string filename) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {
        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
            strip(buffer);
            skip_until(PAREN_OPEN, buffer);

            Func *func = tokenize_function(buffer);
        }
        fclose(file);  
    } 
    
    if (ferror(file)) {
        fprintf(stderr, "An error occurred with filename %s", filename);
    }

    return 0;
}
