#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../../include/operation.h"


static Function const functions[] = {
    (Function) { .name="add", .operation=add },
    (Function) { .name="printi", .operation=printi },
    (Function) { .name="prints", .operation=prints },    
};

// TODO get length of function list
Operation lookup(char const *func_name) {
    int i = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (strcmp(functions[i].name, func_name) == 0)
            return functions[i].operation;
    }

    assert(false && "Function name not found.");
    return NULL;
}


// ###################
// BUILT-IN OPERATIONS
// ###################
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

