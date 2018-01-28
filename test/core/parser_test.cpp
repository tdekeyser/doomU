#define CATCH_CONFIG_MAIN


#include "../Catch/catch.hpp"
#include "../../include/function.h"
#include "../../src/core/parser.c"


TEST_CASE("tokenize_lambda") {

    SECTION("splits a stripped string into a lambda") {
        char a_func_text[] = "(a,b):\"boo!\")";

        Lambda *lambda = tokenize_lambda(a_func_text);

        REQUIRE(lambda->returnValue->type == Str);
        REQUIRE(strcmp(lambda->returnValue->value, "\"boo!\"") == 0);
        REQUIRE(strcmp(lambda->args[0], "a") == 0);
        REQUIRE(strcmp(lambda->args[1], "b") == 0);
    }

}


TEST_CASE("tokenize_arguments") {

    SECTION("splits a stripped string into a list of argument tokens") {
        char snip[] = "arg1,arg2):return";
        string expected[] = { "arg1", "arg2" };

        char **args = tokenize_arguments(snip);

        for (int i = 0; i < 2; i++) {
            REQUIRE(strcmp(args[i], expected[i]) == 0);
        }
    }

    SECTION("no arguments returns null") {
        char snip[] = "):return";

        char **args = tokenize_arguments(snip);

        REQUIRE(args[0] == NULL);
    }

}


TEST_CASE("tokenize_returnValue") {

    SECTION("parses string return value from lambda") {
        char snip[] = "\"return this\")";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Str);
        REQUIRE(strcmp(returnValue->value, "\"return this\"") == 0);
    }

    SECTION("parses int return value from lambda") {
        char snip[] = "45)";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == Int);
        REQUIRE(strcmp(returnValue->value, "45") == 0);
    }

    SECTION("parses list return value from lambda") {
        char snip[] = "[1,2,3,4])";

        TypedValue *returnValue = tokenize_returnValue(snip);

        REQUIRE(returnValue->type == List);
        REQUIRE(strcmp(returnValue->value, "[1,2,3,4]") == 0);
    }

}


TEST_CASE("parse") {

    SECTION("tokenizes a file as a stream of lambdas") {
        string filename = "../test/core/helloworld.du";

        Stream *actual = parse(filename);

        REQUIRE(strcmp(actual->name, "main") == 0);
        REQUIRE(actual->lambdas[0]->args[0] == NULL);
        REQUIRE(strcmp(actual->lambdas[0]->returnValue->value, "\"Hello world!\"") == 0);
        REQUIRE(strcmp(actual->lambdas[1]->args[0], "a") == 0);     
        REQUIRE(strcmp(actual->lambdas[1]->returnValue->value, "print:a") == 0);
        REQUIRE(actual->n_lambdas == 2);
    }

}
