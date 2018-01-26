
#include <string.h>
#include <assert.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"


char *interpret_lamda(Lambda *lambda, const char* previous_return_value) {
    assert(lambda != NULL);

    char* returnVal = (char *) lambda->returnValue;

    if (contains(returnVal, COLON)) {
        char *func_name;
        slice_until(COLON, returnVal, func_name);

        if (strcmp(func_name, "print") == 0)
            printf("%s", previous_return_value);
    }

    return returnVal;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    char *returnVal;
    for (int i = 0; i < stream->n_lambdas; i++) {
        returnVal = interpret_lamda(stream->lambdas[i], returnVal);
    }

    // assert(returnVal == STR_NULL);
    
    freeStream(stream);
    return 0;
}

