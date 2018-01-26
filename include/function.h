/**
* Function structures that are used to define processes
* in the language.
*/
#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef struct anonymous_function_declaration {
    char **args;
    const char *returnValue;
} Lambda;

typedef struct stream_declaration {
    const char *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;


Lambda *newLambda(char **args, const char *returnValue);
void freeLambda(Lambda *);

Stream *newStream(char *name, Lambda **, size_t n_lambdas);
void freeStream(Stream *);


#endif /* DOOMU_FUNCTION_H */