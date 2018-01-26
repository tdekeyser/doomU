
#include "../Catch/catch.hpp"
#include "../../src/core/interpreter.c"


TEST_CASE("interpret_lambda") {

    SECTION("can return a string value in a non-arg lambda") {
        char **args = (char**) malloc(ARG_LEN);
        char hello[] = "\"Hello world!\"";
        Lambda *lambda = newLambda(args, hello);

        const char *actual = interpret_lamda(lambda, (char *) "");

        REQUIRE(strcmp(actual, hello) == 0);
    }

    SECTION("can print a value from a lambda") {
        char **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char print[] = "print:a";
        char hello[] = "\"Hello world!\"";
        Lambda *lambda = newLambda(args, print);

        const char *actual = interpret_lamda(lambda, hello);

        REQUIRE(strcmp(actual, (char *) "") == 0);
    }

}