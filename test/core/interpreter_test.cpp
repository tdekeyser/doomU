
#include "../Catch/catch.hpp"
#include "../../include/parser.h"
#include "../../src/core/interpreter.c"


TEST_CASE("interpret_lambda") {

    SECTION("can return a string value in a non-arg lambda") {
        auto **args = (char**) malloc(ARG_LEN);
        char hello[] = "\"Hello world!\"";
        Lambda *lambda = newLambda(args, hello);

        const char *actual = interpret_lambda(lambda, (char *) "");

        REQUIRE(strcmp(actual, hello) == 0);
    }

    SECTION("can print a value from a lambda") {
        auto **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char print[] = "print:a";
        char hello[] = "\"Hello world!\"";
        Lambda *lambda = newLambda(args, print);

        const char *actual = interpret_lambda(lambda, hello);

        REQUIRE(strcmp(actual, "") == 0);
    }

}


TEST_CASE("interpret") {

    SECTION("executes a lambda stream") {
        Stream *stream = parse("../test/core/helloworld.du");

        REQUIRE(interpret(stream) == 0);
    }

}