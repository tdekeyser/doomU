#include <assert.h>

#include "../include/parser.h"
#include "../include/interpreter.h"


int main(int argc, char *argv[]) {
    assert(argc > 0);

    Stream *stream = parse(argv[1]);
    int success = interpret(stream);

    free_Stream(stream);
    return success;
}