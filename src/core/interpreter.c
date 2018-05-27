#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "../../include/interpreter.h"
#include "../../include/operation.h"
#include "../../include/str_utils.h"
#include "../../include/config.h"



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

    TYPE_ERROR(true, "Type error: Input type not recognized: %i", init_operation->type);
}


// TODO move to parser ??
size_t parse_operation(char *buffer, char *func_name, char **params) {
    slice_until(COLON, buffer, func_name);
    return split(COLON, buffer, params);
}


int map(StreamElement *head, Lambda *lambda) {
    assert(head != NULL);
    assert(lambda != NULL);
    TYPE_ERROR(lambda->operation->type != Func, "Type error: Lambda operation must be of type Func: %s", lambda->operation->value);

    char func_name[VAR_LEN];
    char *params[ARG_LEN];
    size_t n_params = parse_operation((char *) lambda->operation->value, func_name, params);

    StreamElement *tmp = head;
    do {

        long map_params[n_params];
        for (int i = 0; i < n_params; i++) {
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

    for (int i = 0; i < n_params; i++)
        free(params[i]);
    return 0;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    StreamElement *head = read_as_stream(stream->lambdas[0]->operation);

    for (unsigned int i = 1; i < stream->n_lambdas; i++) {
        map(head, stream->lambdas[i]);
    }

    free_StreamElement(head);
    return 0;
}
