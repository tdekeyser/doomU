#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef enum type {
    Void, Str, Num, Func
} Type;

typedef struct typed_value {
    Type type;
    void *value;
} TypedValue;

typedef struct arguments {
    size_t n_args;
    char **values;
} Arguments;

typedef struct anonymous_function_declaration {
    Arguments *args;
    TypedValue *returnValue;
} Lambda;

typedef struct stream_declaration {
    char const *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;


Type get_type(char const *str);
TypedValue *newTypedValue(Type type, void *value);
void freeTypedValue(TypedValue *);

Arguments *newArguments(size_t, char**);
void freeArguments(Arguments *);

Lambda *newLambda(Arguments *args, TypedValue *returnValue);
void freeLambda(Lambda *);

Stream *newStream(char const *name, Lambda **, size_t n_lambdas);
void freeStream(Stream *);


#endif /* DOOMU_FUNCTION_H */