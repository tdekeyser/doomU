#include <assert.h>
#include <stdlib.h>

#include "../../include/function.h"
#include "../../include/str_utils.h"
#include "config.c"


Type get_type(string str) {
    assert(str != NULL);

    if (str[0] == SQUARE_BRACKET_OPEN)
        return Num;
    if (str[0] == QUOTE) {
        return Str;
    } else if (contains(str, COLON)) {
        return Func;
    }

    return Void;
}


TypedValue *new_TypedValue(Type type, char const *value) {
    assert(value != NULL);

    TypedValue *typedValue = (TypedValue *) malloc(sizeof(TypedValue));
    if (!typedValue) {
        fprintf(stderr, OOM);
        return NULL;
    }

    typedValue->type = type;
    typedValue->value = value;

    return typedValue;
}


Arguments *new_Arguments(size_t n_args, char **values) {
    assert(n_args <= ARG_LEN);
    assert(values != NULL);

    Arguments *arguments = (Arguments *) malloc(sizeof(Arguments));
    if (!arguments) {
        fprintf(stderr, OOM);
        return NULL;
    }

    arguments->n_args = n_args;
    arguments->values = values;

    return arguments;
}


Lambda *new_Lambda(Arguments *args, TypedValue *returnValue) {
    Lambda *lambda = (Lambda *) malloc(sizeof(Lambda));
    if (!lambda) {
        fprintf(stderr, OOM);
        return NULL;
    }

    lambda->args = args;
    lambda->returnValue = returnValue;

    return lambda;
}


Stream *new_Stream(char const *name, Lambda **lambdas, size_t n_lambdas) {
    Stream *stream = (Stream *) malloc(sizeof(Stream));
    if (!stream) {
        fprintf(stderr, OOM);
        return NULL;
    }

    stream->name = name;
    stream->n_lambdas = n_lambdas;
    stream->lambdas = lambdas;

    return stream;
}


void free_TypedValue(TypedValue *typedValue) {
    assert(typedValue != NULL);

    free(typedValue);
}


void free_Arguments(Arguments *arguments) {
    assert(arguments != NULL);

    if (arguments->values != NULL)
        free(arguments->values);

    free(arguments);
}

void free_Lambda(Lambda *lambda) {
    assert(lambda != NULL);

    if (lambda->args != NULL)
        free_Arguments(lambda->args);
    if (lambda->returnValue != NULL)
        free_TypedValue(lambda->returnValue);

    free(lambda);
}


void free_Stream(Stream *stream) {
    assert(stream != NULL);

    for (unsigned int i = 0; i < stream->n_lambdas; i++) {
        free_Lambda(stream->lambdas[i]);
    }
    free(stream);
}

