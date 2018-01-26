#include <assert.h>
#include <stdlib.h>

#include "../../include/function.h"
#include "config.c"


Lambda *newLambda(char **args, const char *returnValue) {
    Lambda *lambda = (Lambda*) malloc(sizeof(Lambda));
    if (!lambda)
        fprintf(stderr, OOM);

    lambda->args = args;
    lambda->returnValue = returnValue;

    return lambda;
}


void freeLambda(Lambda *lambda) {
    assert(lambda != NULL);

    // TODO cannot be freed correctly because you don't know how many there are...
    if (lambda->args != NULL)
        free(lambda->args);
    free(lambda);
}


Stream *newStream(char *name, Lambda **lambdas, size_t n_lambdas) {
    Stream *stream = (Stream *) malloc(sizeof(Stream));
    if (!stream)
        fprintf(stderr, OOM);
    
    stream->name = name;
    stream->n_lambdas = n_lambdas;
    stream->lambdas = lambdas;
    
    return stream;
}


void freeStream(Stream *stream) {
    assert(stream != NULL);

    for (int i = 0; i < stream->n_lambdas; i++) {
        free(stream->lambdas[i]);
    }   
    free(stream);
}

