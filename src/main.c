
#include <assert.h>

#include "../include/lexer.h"
#include "../include/interpreter.h"


int main(int argc, char *argv[]) {
    assert(argc > 0);

    Stream *stream = lex(argv[1]);
    return interpret(stream);
}