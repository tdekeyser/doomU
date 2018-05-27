#include <assert.h>
#include <stdlib.h>

#include "../../include/function.h"
#include "../../include/str_utils.h"
#include "../../include/config.h"


Type get_type(char const *str) {
    assert(str != NULL);

    if (str[0] == SQUARE_BRACKET_OPEN)
        return Num;
    if (str[0] == QUOTE) {
        return Str;
    } else if (contains(str, COLON)) {
        return Func;
    }

    return Void;
}

// ###########
// TYPED VALUE
// ###########
TypedValue *new_TypedValue(Type type, char const *value) {
    assert(value != NULL);

    TypedValue *typedValue = (TypedValue *) malloc(sizeof(TypedValue));
    ERROR_HANDLER(!typedValue, OOM);

    typedValue->type = type;
    typedValue->value = value;

    return typedValue;
}

void free_TypedValue(TypedValue *typedValue) {
    assert(typedValue != NULL);

    free((void *) typedValue->value);
    free(typedValue);
}

// #########
// ARGUMENTS
// #########
Arguments *new_Arguments(size_t n_args, char **values) {
    assert(n_args <= ARG_LEN);
    assert(values != NULL);

    Arguments *arguments = (Arguments *) malloc(sizeof(Arguments));
    ERROR_HANDLER(!arguments, OOM);

    arguments->n_args = n_args;
    arguments->values = values;

    return arguments;
}

void free_Arguments(Arguments *arguments) {
    assert(arguments != NULL);

    if (arguments->values != NULL) {
        for (int i = 0; i < arguments->n_args; i++)
            free(arguments->values[i]);
        free(arguments->values);
    }

    free(arguments);
}


// ######
// LAMBDA
// ######
Lambda *new_Lambda(Arguments *args, TypedValue *returnValue) {
    Lambda *lambda = (Lambda *) malloc(sizeof(Lambda));
    ERROR_HANDLER(!lambda, OOM);

    lambda->args = args;
    lambda->operation = returnValue;

    return lambda;
}

void free_Lambda(Lambda *lambda) {
    assert(lambda != NULL);

    if (lambda->args != NULL)
        free_Arguments(lambda->args);
    if (lambda->operation != NULL)
        free_TypedValue(lambda->operation);

    free(lambda);
}

// ######
// STREAM
// ######
Stream *new_Stream(char const *name, Lambda **lambdas, size_t n_lambdas) {
    Stream *stream = (Stream *) malloc(sizeof(Stream));
    ERROR_HANDLER(!stream, OOM);

    stream->name = name;
    stream->n_lambdas = n_lambdas;
    stream->lambdas = lambdas;

    return stream;
}

void free_Stream(Stream *stream) {
    assert(stream != NULL);

    for (unsigned int i = 0; i < stream->n_lambdas; i++)
        free_Lambda(stream->lambdas[i]);

    free(stream->lambdas);
    free(stream);
}


// ##############
// STREAM ELEMENT
// ##############
StreamElement *new_StreamElement(Type type, long value) {
    StreamElement *element = (StreamElement *) malloc(sizeof(StreamElement));
    ERROR_HANDLER(!element, OOM);

    element->type = type;
    element->value = value;
    element->next = NULL;
    return element;
}

void free_StreamElement(StreamElement *first) {
    assert(first != NULL);

    if (first->next)
        free_StreamElement(first->next);

    free(first);
}

StreamElement *append(StreamElement *head, StreamElement *element) {
    if (head == NULL) {
        head = element;
    } else {
        StreamElement *previous = head;
        while (previous->next != NULL)
            previous = previous->next;
        previous->next = element;
    }
    return head;
}

