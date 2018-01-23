#include <stdio.h>
#include <assert.h>
#include "../../include/str_utils.h"
#include "../../include/tokenizer.h"
#include "config.c"




int lex(string filename, Func *func) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {
        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
            strip(buffer);
            // do something!
        }

        fclose(file);  
    } 
    
    if (ferror(file)) {
        fprintf(stderr, "An error occurred with filename %s", filename);
    }

    return 0;
}


void tokenize_arguments(char *buffer, char **args) {
    assert(buffer != NULL);
    assert(args != NULL);

    char arg_str[VAR_LEN * ARG_LEN];

    slice_until(PAREN_CLOSED, buffer, arg_str);

    split(COMMA, arg_str, args);

}

