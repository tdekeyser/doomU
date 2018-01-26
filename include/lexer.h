/**
* A tokenizer cuts a sequence of inputs into a series of statments/words
* that are labeled.
*/
#ifndef DOOMU_TOKENIZER_H
#define DOOMU_TOKENIZER_H

#include "str_utils.h"
#include <stdlib.h>


typedef struct function_declaration {
    char **args;
    string returnValue;
} Func;


Func * lex(string filename);


#endif /* DOOMU_TOKENIZER_H */