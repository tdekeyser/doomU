#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef enum type {
    Void, Int, Str, List, Func
} Type;


typedef struct typed_value {
    Type type;
    char const *value;
} TypedValue;

typedef struct anonymous_function_declaration {
    char **args;
    TypedValue *returnValue;
} Lambda;

typedef struct stream_declaration {
    char const *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;


Type get_type(char const *str);
TypedValue *newTypedValue(Type type, char const *value);
void freeTypedValue(TypedValue *);

Lambda *newLambda(char **args, TypedValue *returnValue);
void freeLambda(Lambda *);

Stream *newStream(char const *name, Lambda **, size_t n_lambdas);
void freeStream(Stream *);


#endif /* DOOMU_FUNCTION_H */