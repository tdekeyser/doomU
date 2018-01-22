/**
* A tokenizer cuts a sequence of inputs into a series of statments/words
* that are labeled.
*/
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "utils.h"
#include <stdlib.h>



typedef struct function_declaration {
    char **args;
    string returnValue;
} Func;


int lex(string filename, Func *func);




#endif /* TOKENIZER_H */