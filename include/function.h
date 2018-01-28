#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef struct anonymous_function_declaration {
    char **args;
    char const *returnValue;
} Lambda;

typedef struct stream_declaration {
    char const *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;


Lambda *newLambda(char **args, char const *returnValue);
void freeLambda(Lambda *);

Stream *newStream(char const *name, Lambda **, size_t n_lambdas);
void freeStream(Stream *);


#endif /* DOOMU_FUNCTION_H */