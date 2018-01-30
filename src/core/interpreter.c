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
    assert(false);
    return NULL;
}

// TODO to parser??
size_t parse_list(char*buffer, size_t len_buffer, char **elements) {
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
StreamElement *read_as_stream(TypedValue *init_return_value) {
    if (init_return_value->type == Str)
        return read_string_as_stream((char *) init_return_value->value);
    if (init_return_value->type == Num)
        return read_num_as_stream((char *) init_return_value->value);

    return NULL;
}


int map(StreamElement *input, Lambda *lambda) {
    // change input by applying lambda on it
    // returns OK or NOT OK
    return 0;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    // first read the output of the first lambda as streamcontent

    // then map the streamcontent according to the following lambdas

    free_Stream(stream);
    return 0;
}
