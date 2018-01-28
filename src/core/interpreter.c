
#include <string.h>
#include <assert.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"


TypedValue *interpret_lambda(Lambda *lambda, TypedValue *previous) {
    assert(lambda != NULL);

    TypedValue *returnVal = lambda->returnValue;

    if (contains(returnVal->value, COLON)) {
        char func_name[VAR_LEN];
        slice_until(COLON, (char *) returnVal->value, func_name);

        if (strcmp(func_name, "print") == 0) {
            assert(previous->type == Str);
            printf("%s\n", previous->value);
            returnVal = newTypedValue(Void, "");
        }
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

