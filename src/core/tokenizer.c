#include <stdio.h>
#include "../../include/str_utils.h"
#include "../../include/tokenizer.h"
#include "config.c"




int lex(string filename, Func *func) {
    char buffer[BUFFER + 1];
    FILE *file = fopen(filename, "r");

    if (file) {
        size_t n_read;
        while ((n_read = fread(buffer, sizeof(char), BUFFER, file)) > 0) {
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
    size_t numArgs = 0;

    while (*buffer++ != PAREN_CLOSED) {
        char arg[VAR_LEN];
        slice_until(COMMA, buffer, arg);
    }
}



//int main() {
//    char **args = (char **) malloc(sizeof(void *) *BUFFER);
//    char test[] = "(argument1, argument2)";
//
//    tokenize_arguments(test, args);
//
//    printf("%s", args[0]);
//}
