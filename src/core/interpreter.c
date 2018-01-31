#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"



/////// SHOULD BE MOVED TO FUNCTION_H

typedef struct StreamElement {
    Type type;
    long value;
    struct StreamElement *next;
} StreamElement;

StreamElement *new_StreamElement(Type type, long value) {
    StreamElement *element = (StreamElement *) malloc(sizeof(StreamElement));
    if (!element) {
        fprintf(stderr, OOM);
        return NULL;
    }

    element->type = type;
    element->value = value;
    element->next = NULL;
    return element;
}

void free_StreamElement(StreamElement *first) {
    assert(first != NULL);

    if (first->next != NULL)
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

/////////////////////////////

StreamElement *read_string_as_stream(char *value) {
    StreamElement *head = NULL;
    char c;
    while ((c = *value++) != STR_NULL) {
        if (c == QUOTE)
            continue;
        head = append(head, new_StreamElement(Str, (long) c));
    }
    return head;
}

// TODO to parser??
size_t parse_list(char *buffer, size_t len_buffer, char **elements) {
    assert(buffer != NULL);
    assert(len_buffer > 0);

    char tmp[len_buffer - 2];
    skip_until(SQUARE_BRACKET_OPEN, buffer);
    slice_until(SQUARE_BRACKET_CLOSED, buffer, tmp);
    return split(COMMA, tmp, elements);
}

StreamElement *read_num_as_stream(char *buffer) {
    assert(buffer != NULL);

    char *elements[length(buffer)];
    size_t n_elements = parse_list(buffer, length(buffer), elements);

    StreamElement *head = NULL;
    for (unsigned int i = 0; i < n_elements; i++) {
        head = append(head, new_StreamElement(Num, parse_long(elements[i])));
    }
    return head;
}


// Reads output of the first lambda as input for the stream.
StreamElement *read_as_stream(TypedValue *init_operation) {
    if (init_operation->type == Str)
        return read_string_as_stream((char *) init_operation->value);
    if (init_operation->type == Num)
        return read_num_as_stream((char *) init_operation->value);

    assert(false && "Input type not recognized.");
    return NULL;
}


// TODO move to parser ??
size_t parse_operation(char *buffer, char *func_name, char **params) {
    slice_until(COLON, buffer, func_name);
    return split(COLON, buffer, params);
}


typedef struct MapParameters {
    size_t len;
    long *values;
} MapParameters;


long add(MapParameters *parameters) {
    assert(parameters->len == 2);
    return parameters->values[0] + parameters->values[1];
}

long printi(MapParameters *parameters) {
    assert(parameters->len == 1);
    printf("%lu ", parameters->values[0]);
    return parameters->values[0];
}

long prints(MapParameters *parameters) {
    assert(parameters->len == 1);
    printf("%c", (char) parameters->values[0]);
    return parameters->values[0];
}


typedef long (* Operation) (MapParameters *);
typedef struct Function {
    char const *name;
    Operation operation;
} Function;


static Function const functions[] = {
    (Function) { .name="add", .operation=add },
    (Function) { .name="printi", .operation=printi },
    (Function) { .name="prints", .operation=prints },    
};

Operation lookup(string func_name) {
    int i = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (strcmp(functions[i].name, func_name) == 0)
            return functions[i].operation;
    }

    assert(false && "Function name not found.");
    return NULL;
}


int map(StreamElement *head, Lambda *lambda) {
    assert(head != NULL);
    assert(lambda != NULL);
    assert(lambda->operation->type == Func);

    char func_name[VAR_LEN];
    char *params[ARG_LEN];
    size_t n_params = parse_operation((char *) lambda->operation->value, func_name, params);

    StreamElement *tmp = head;
    do {

        long map_params[n_params];
        for (unsigned int i = 0; i < n_params; i++) {
            if (strcmp(params[i], lambda->args->values[0]) == 0) {
                // TODO this is a shortcut that prevents using multiple arguments in a lambda!!
                map_params[i] = tmp->value;
            } else if (isdigit(params[i][0])) {
                map_params[i] = parse_long(params[i]);
            }
        }

        MapParameters parameters = (MapParameters) { .len=n_params, .values=map_params };
        Operation operation = lookup(func_name);
        tmp->value = operation(&parameters);

    } while ((tmp = tmp->next) != NULL);

    return 0;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    // first read the output of the first lambda as streamcontent
    StreamElement *head = read_as_stream(stream->lambdas[0]->operation);

    // then map the streamcontent according to the following lambdas
    for (unsigned int i = 1; i < stream->n_lambdas; i++) {
        map(head, stream->lambdas[i]);
    }

    // free streamelements
    free_StreamElement(head);

    free_Stream(stream);
    return 0;
}
