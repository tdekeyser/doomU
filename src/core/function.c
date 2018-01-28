#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../include/function.h"
#include "../../include/str_utils.h"
#include "config.c"


Type get_type(string str) {
    assert(str != NULL);

    if (isdigit(str[0]))
        return Int;
    if (str[0] == SQUARE_BRACKET_OPEN)
        return List;
    if (str[0] == QUOTE) {
        return Str;
    } else if (contains(str, COLON)) {
        return Func;
    }

    return Void;
}


TypedValue *newTypedValue(Type type, char const *value) {
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


void freeTypedValue(TypedValue *typedValue) {
    assert(typedValue != NULL);

    free(typedValue);
}


Lambda *newLambda(char **args, TypedValue *returnValue) {
    Lambda *lambda = (Lambda *) malloc(sizeof(Lambda));
    if (!lambda) {
        fprintf(stderr, OOM);
        return NULL;
    }

    lambda->args = args;
    lambda->returnValue = returnValue;

    return lambda;
}


void freeLambda(Lambda *lambda) {
    assert(lambda != NULL);

    if (lambda->args != NULL)
        free(lambda->args);
    if (lambda->returnValue != NULL)
        freeTypedValue(lambda->returnValue);

    free(lambda);
}


Stream *newStream(char const *name, Lambda **lambdas, size_t n_lambdas) {
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


void freeStream(Stream *stream) {
    assert(stream != NULL);

    for (unsigned int i = 0; i < stream->n_lambdas; i++) {
        freeLambda(stream->lambdas[i]);
    }
    free(stream);
}

