#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../../include/str_utils.h"
#include "../../include/lexer.h"
#include "../../include/function.h"
#include "config.c"



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


Lambda *tokenize_lambda(char *buffer) {
    assert(buffer != NULL);

    skip_until(PAREN_OPEN, buffer);
    char **args = tokenize_arguments(buffer);

    skip_until(COLON, buffer);
    char *returnVal = tokenize_returnValue(buffer);

    return newLambda(args, returnVal);
}


Stream *tokenize_stream(char *buffer) {
    Lambda **lambdas = (Lambda **) malloc(sizeof(Lambda) * 5);

    skip_until(PAREN_OPEN, buffer);
    size_t i = 0;
    while (*buffer != PAREN_CLOSED) {
        skip_until(PAREN_OPEN, buffer);
        lambdas[i++] = tokenize_lambda(buffer);
    }

    return newStream("main", lambdas, i);
}


// TODO fails if file is larger than BUFFER
Stream *lex(string filename) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {

        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
            strip_leave_quotes(buffer);
            return tokenize_stream(buffer);
        }

        fclose(file);  
    } else {
        fprintf(stderr, "An error occurred while reading file with filename '%s'", filename);
    }

    return NULL;
}
