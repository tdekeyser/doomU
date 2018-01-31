#ifndef DOOMU_FUNCTION_H
#define DOOMU_FUNCTION_H

#include <stdio.h>


typedef enum type {
    Void, Str, Num, Func
} Type;

Type get_type(char const *str);


typedef struct TypedValue {
    Type type;
    char const *value;
} TypedValue;

TypedValue *new_TypedValue(Type type, char const *value);
void free_TypedValue(TypedValue *);


typedef struct Arguments {
    size_t n_args;
    char **values;
} Arguments;

Arguments *new_Arguments(size_t, char**);
void free_Arguments(Arguments *);


typedef struct Lambda {
    Arguments *args;
    TypedValue *operation;
} Lambda;

Lambda *new_Lambda(Arguments *args, TypedValue *returnValue);
void free_Lambda(Lambda *);


typedef struct Stream {
    char const *name;
    size_t n_lambdas;
    Lambda **lambdas;
} Stream;

Stream *new_Stream(char const *name, Lambda **, size_t n_lambdas);
void free_Stream(Stream *);


/*
Stream element as a linked list
*/
typedef struct StreamElement {
    Type type;
    long value;
    struct StreamElement *next;
} StreamElement;

StreamElement *new_StreamElement(Type type, long value);
void free_StreamElement(StreamElement *first);
StreamElement *append(StreamElement *head, StreamElement *element);


#endif /* DOOMU_FUNCTION_H */