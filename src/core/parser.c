#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../../include/str_utils.h"
#include "../../include/parser.h"
#include "../../include/config.h"


Arguments *tokenize_arguments(char *buffer) {
    assert(buffer != NULL);

    char arg_str[VAR_LEN * ARG_LEN];
    char **args = (char **) malloc(ARG_LEN);
    MEM_ERROR(args);

    slice_until(PAREN_CLOSED, buffer, arg_str);
    SYNTAX_ERROR((length(buffer) <= 0), "No closing parentheses found.");

    size_t n_args = split(COMMA, arg_str, args);

    return new_Arguments(n_args, args);
}


TypedValue *tokenize_returnValue(char *buffer) {
    assert(buffer != NULL);

    char *value = (char *) malloc(VAR_LEN);
    MEM_ERROR(value);
    slice_until(PAREN_CLOSED, buffer, value);

    return new_TypedValue(get_type(value), value);
}


Lambda *tokenize_lambda(char *buffer) {
    assert(buffer != NULL);

    skip_until(PAREN_OPEN, buffer);
    Arguments *args = tokenize_arguments(buffer);

    skip_until(COLON, buffer);
    TypedValue *returnVal = tokenize_returnValue(buffer);

    return new_Lambda(args, returnVal);
}


Stream *tokenize_stream(char *buffer) {
    Lambda **lambdas = (Lambda **) malloc(sizeof(Lambda) * 5);

    skip_until(PAREN_OPEN, buffer);
    size_t i = 0;
    while (*buffer != PAREN_CLOSED) {
        skip_until(PAREN_OPEN, buffer);
        lambdas[i++] = tokenize_lambda(buffer);
    }

    return new_Stream((char *) "main", lambdas, i);
}


// TODO fails if file is larger than BUFFER
Stream *parse(FILE *file) {
    assert(file != NULL);

    char buffer[BUFFER + 1];
    fread(buffer, sizeof(char), BUFFER, file);
    strip_leave_quotes(buffer);
    return tokenize_stream(buffer);
}
