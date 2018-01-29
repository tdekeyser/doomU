
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../include/interpreter.h"
#include "../../include/str_utils.h"
#include "config.c"


typedef struct function_parameters {
    size_t n_values;
    void **values;
    Type type;
} Parameters;


int add(Parameters *p) {
    assert(p->n_values == 2);

    return (*(int *) p->values[0]) + (*(int *) p->values[1]);
}

int print(Parameters *p) {
    assert(p->n_values == 1);

    if (p->type == List) {
        printf("%i", *(int *) p->values[0]);
    } else if (p->type == Str) {
        printf("hello");
        printf("%s", (char *) p->values[0]);
    }

    return * (int *) p->values[0];
}


typedef int (* func) (Parameters *);

typedef struct function {
    string name;
    func operation;
} Function;


Function const addF = (Function) { .name="add", .operation=add };
Function const printF = (Function) { .name="print", .operation=print };


func lookup(string func_name) {
    if (strcmp(func_name, addF.name) == 0) {
        return addF.operation;
    } else if (strcmp(func_name, printF.name) == 0) {
        return printF.operation;
    }
    return NULL;
}


TypedValue *interpret_lambda(Lambda *lambda, TypedValue *input) {
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

        if (lambda->args->n_args == 1) {

            char inputVal;
            int *result = (int *) strdup(input->value);
            int i = 0;
            while ((inputVal = input->value[i++]) != STR_NULL) {
                if ((inputVal == COMMA) || (inputVal == SQUARE_BRACKET_OPEN) || (inputVal == SQUARE_BRACKET_CLOSED))
                    continue;

                printf("%c", inputVal);

                void **paramVals = (void **) malloc(n_split);
                for (unsigned int i=0; i<n_split; i++) {
                    if (strcmp(params[i], lambda->args->values[0]) == 0) {
                        paramVals[i] = &inputVal;
                    } else if (isdigit(params[i][0])) {
                        paramVals[i] = params[i];
                    }
                }

                Parameters parameters = (Parameters) { .n_values=n_split, .values=paramVals, .type=List };
                func f = lookup(func_name);
                *result++ = f(&parameters);
            }

            printf("%s", (char *) result);

            return newTypedValue(List, (char *) result);
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

