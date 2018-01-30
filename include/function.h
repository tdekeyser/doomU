#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef enum type {
    Void, Str, Num, Func
} Type;

typedef struct typed_value {
    Type type;
    char const *value;
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
TypedValue *new_TypedValue(Type type, char const *value);
void free_TypedValue(TypedValue *);

Arguments *new_Arguments(size_t, char**);
void free_Arguments(Arguments *);

Lambda *new_Lambda(Arguments *args, TypedValue *returnValue);
void free_Lambda(Lambda *);

Stream *new_Stream(char const *name, Lambda **, size_t n_lambdas);
void free_Stream(Stream *);


#endif /* DOOMU_FUNCTION_H */