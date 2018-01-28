#include <assert.h>
#include <stdlib.h>

#include "../../include/function.h"
#include "config.c"


Lambda *newLambda(char **args, char const *returnValue) {
    Lambda *lambda = (Lambda*) malloc(sizeof(Lambda));
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
        free((void *) lambda->returnValue);

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

