#include <assert.h>

#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/config.h"


int main(int argc, char *argv[]) {
    assert(argc > 0);

    FILE *file = fopen(argv[1], "r");
    ERROR_HANDLER(!file, "An error occurred while reading file with filename '%s'", argv[1]);

    Stream *stream = parse(file);
    int success = interpret(stream);

    free_Stream(stream);
    fclose(file);
}
