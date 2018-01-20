/**
* A tokenizer cuts a sequence of inputs into a series of statments/words
* that are labeled.
*/
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "utils.h"
#include <stdlib.h>

typedef struct key_value {
    string key;
    void *value;
} KVPair;


typedef struct function_arguments {
    size_t num;
    KVPair args[];
} Args;








#endif /* TOKENIZER_H */