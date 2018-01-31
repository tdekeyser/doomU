#include <cstring>

#include "../Catch/catch.hpp"
#include "../../include/function.h"
#include "../../src/core/parser.c"


TEST_CASE("tokenize_lambda") {

    SECTION("splits a stripped string into a lambda") {
        char a_func_text[] = "(a,b):\"boo!\")";

        Lambda *lambda = tokenize_lambda(a_func_text);

        REQUIRE(lambda->operation->type == Str);
        REQUIRE(strcmp(lambda->operation->value, "\"boo!\"") == 0);
        REQUIRE(strcmp(lambda->args->values[0], "a") == 0);
        REQUIRE(strcmp(lambda->args->values[1], "b") == 0);
    }

}


TEST_CASE("tokenize_arguments") {

    SECTION("splits a stripped string into a list of argument tokens") {
        char snip[] = "arg1,arg2):return";
        string expected[] = { "arg1", "arg2" };

        Arguments *args = tokenize_arguments(snip);

        for (unsigned int i = 0; i < args->n_args; i++) {
            REQUIRE(strcmp(args->values[i], expected[i]) == 0);
        }
        REQUIRE(args->n_args == 2);
    }

    SECTION("no arguments returns null") {
        char snip[] = "):return";

        Arguments *args = tokenize_arguments(snip);

        REQUIRE(args->values[0] == NULL);
        REQUIRE(args->n_args == 0);
    }

}


TEST_CASE("tokenize_returnValue") {

    SECTION("parses string return value from lambda") {
        char snip[] = "\"return this\")";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Str);
        REQUIRE(strcmp(returnValue->value, "\"return this\"") == 0);
    }

    SECTION("parses void return value from lambda") {
        char snip[] = ")";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Void);
        REQUIRE(strcmp(returnValue->value, "") == 0);
    }

    SECTION("parses list return value from lambda") {
        char snip[] = "[1,2,3,4])";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Num);
        REQUIRE(strcmp(returnValue->value, "[1,2,3,4]") == 0);
    }

    SECTION("parses function return value from lambda") {
        char snip[] = "print:a:b)";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Func);
        REQUIRE(strcmp(returnValue->value, "print:a:b") == 0);
    }

}


TEST_CASE("parse") {

    SECTION("tokenizes a file as a stream of lambdas") {
        string filename = "../test/core/helloworld.du";

        Stream *actual = parse(filename);

        REQUIRE(strcmp(actual->name, "main") == 0);
        REQUIRE(actual->lambdas[0]->args->values[0] == NULL);
        REQUIRE(strcmp(actual->lambdas[0]->operation->value, "\"Hello world!\"") == 0);
        REQUIRE(strcmp(actual->lambdas[1]->args->values[0], "a") == 0);
        REQUIRE(strcmp(actual->lambdas[1]->operation->value, "prints:a") == 0);
        REQUIRE(actual->n_lambdas == 2);
    }

}
