#include <stdio.h>


typedef struct MapParameters {
    size_t len;
    long *values;
} MapParameters;

typedef long (* Operation) (MapParameters *);

typedef struct Function {
    char const *name;
    Operation operation;
} Function;

Operation lookup(char const *func_name);

// ###################
// BUILT-IN OPERATIONS
// ###################
long add(MapParameters *);
long subtract(MapParameters *);
long multiply(MapParameters *);
long mod(MapParameters *);

long printi(MapParameters *);
long prints(MapParameters *);