#include <stdio.h>
#include <assert.h>
#include "../../include/function.h"


//typedef struct function_parameters {
//    size_t n_values;
//    void **values;
//    Type type;
//} Parameters;
//
//
//int add(Parameters *p) {
//    assert(p->n_values == 2);
//
//    return (*(int *) p->values[0]) + (*(int *) p->values[1]);
//}
//
//int print(Parameters *p) {
//    assert(p->n_values == 1);
//
//    if (p->type == List) {
//        printf("%i", *(int *) p->values[0]);
//    } else if (p->type == Str) {
//        printf("hello");
//        printf("%s", (char *) p->values[0]);
//    }
//
//    return * (int *) p->values[0];
//}
