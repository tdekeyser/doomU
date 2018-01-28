
#include <string.h>
#include <assert.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"


char *interpret_lambda(Lambda *lambda, string previous_return_value) {
    assert(lambda != NULL);

    char *returnVal = (char *) lambda->returnValue;

    if (contains(returnVal, COLON)) {
        char func_name[VAR_LEN];
        slice_until(COLON, returnVal, func_name);

        if (strcmp(func_name, "print") == 0) {
            printf("%s\n", previous_return_value);
            returnVal = (char *) "";
        }
    }

    return returnVal;
}


int interpret(Stream *stream) {
    assert(stream != NULL);

    char *returnVal = NULL;
    for (unsigned int i = 0; i < stream->n_lambdas; i++) {
        returnVal = interpret_lambda(stream->lambdas[i], returnVal);
    }

    freeStream(stream);
    return 0;
}

