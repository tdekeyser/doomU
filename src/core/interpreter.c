
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"



void print(TypedValue *value) {
    assert(value->type == Str);
    printf("%s\n", value->value);
}


TypedValue *execute(TypedValue* input, char **arguments, string func_name, char **parameters) {

    return newTypedValue(Void, "");
}


TypedValue *interpret_lambda(Lambda *lambda, TypedValue *previous_return) {
    assert(lambda != NULL);

    TypedValue *returnVal = lambda->returnValue;

    if (returnVal->type == Func) {

        // TODO move to parser ----------
        char *buffer = strdup(returnVal->value);
        char func_name[VAR_LEN];

        // get func name
        slice_until(COLON, buffer, func_name);

        // get func params
        char **params = (char **) malloc(ARG_LEN);
        if (!params) {
            fprintf(stderr, OOM);
            return NULL;
        }
        size_t n_split = split(COLON, buffer, params);
        // TODO--------------------------

        if (strcmp(func_name, "print") == 0) {
            print(previous_return);
            return newTypedValue(Void, "");
        }

        //return execute(previous_return, lambda->args, func_name, params);
    }

    return returnVal;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    TypedValue *returnVal = newTypedValue(Void, "");
    for (unsigned int i = 0; i < stream->n_lambdas; i++) {
        returnVal = interpret_lambda(stream->lambdas[i], returnVal);
    }

    freeTypedValue(returnVal);
    freeStream(stream);
    return 0;
}

