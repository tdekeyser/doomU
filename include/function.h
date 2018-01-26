/**
* A tokenizer cuts a sequence of inputs into a series of statments/words
* that are labeled.
*/
#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef struct anonymous_function_declaration {
    char **args;
    const char *returnValue;
} Lambda;


Lambda *newLambda(char **args, const char *returnValue);
void freeFunc(Lambda *);


typedef struct stream_declaration {
    const char *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;


Stream *newStream(char *name, Lambda **, size_t n_lambdas);
void freeStream(Stream *);


#endif /* DOOMU_FUNCTION_H */