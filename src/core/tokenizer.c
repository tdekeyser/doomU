#include <stdio.h>
#include <assert.h>
#include "../../include/str_utils.h"
#include "../../include/tokenizer.h"
#include "config.c"


Func *newFunc(char **args, string returnValue) {
    Func *func = (Func*) malloc(sizeof(Func));
    if (!func)
        fprintf(stderr, OOM);

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

    char arg_str[VAR_LEN * ARG_LEN];
    char **args = (char**) malloc(ARG_LEN);
    if (!args)
        fprintf(stderr, OOM);

    slice_until(PAREN_CLOSED, buffer, arg_str);
    assert((length(buffer) > 0)); // Syntax error: no closing parentheses found
    
    split(COMMA, arg_str, args);
    return args;
}


char *tokenize_returnValue(char *buffer) {
    assert(buffer != NULL);

    char *returnValue = (char*) malloc(VAR_LEN);
    if (!returnValue)
        fprintf(stderr, OOM);

    slice_until(PAREN_CLOSED, buffer, returnValue);

    assert(length(returnValue) > 0);
    return returnValue;
}


// TODO fix memory leaks
Func *tokenize_function(char *buffer) {
    assert(buffer != NULL);
    assert(no_spaces(buffer));

    skip_until(PAREN_OPEN, buffer);
    char **args = tokenize_arguments(buffer);

    skip_until(COLON, buffer);
    char *returnVal = tokenize_returnValue(buffer);

    return newFunc(args, returnVal);
}


// TODO fails if file is larger than BUFFER
Func * lex(string filename) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {
        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
            strip(buffer);
            skip_until(PAREN_OPEN, buffer);
            return tokenize_function(buffer);
        }

        fclose(file);  
    } else {
        fprintf(stderr, "An error occurred while reading file with filename '%s'", filename);
    }

    return NULL;
}
