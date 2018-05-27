#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../../include/operation.h"
#include "../../include/config.h"


static size_t n_functions = 6;

static Function const functions[] = {
    (Function) { .name="add", .operation=add },
    (Function) { .name="subtract", .operation=subtract },
    (Function) { .name="multiply", .operation=multiply },
    (Function) { .name="mod", .operation=mod },
    
    (Function) { .name="printi", .operation=printi },
    (Function) { .name="prints", .operation=prints },  
};

// TODO get length of function list
Operation lookup(char const *func_name) {
    for (unsigned int i = 0; i < n_functions; i++) {
        if (strcmp(functions[i].name, func_name) == 0)
            return functions[i].operation;
    }

    ERROR_HANDLER(true, "Function name not found: %s", func_name);
    return NULL;
}


// ###################
// BUILT-IN OPERATIONS
// ###################
long add(MapParameters *params) {
    assert(params->len == 2);
    return params->values[0] + params->values[1];
}

long subtract(MapParameters *params) {
    assert(params->len == 2);
    return params->values[0] - params->values[1];
}

long multiply(MapParameters *params) {
    assert(params->len == 2);
    return params->values[0] * params->values[1];
}

long mod(MapParameters *params) {
    assert(params->len == 2);
    return params->values[0] % params->values[1];
}

long printi(MapParameters *params) {
    assert(params->len == 1);
    printf("%lu ", params->values[0]);
    return params->values[0];
}

long prints(MapParameters *params) {
    assert(params->len == 1);
    printf("%c", (char) params->values[0]);
    return params->values[0];
}

