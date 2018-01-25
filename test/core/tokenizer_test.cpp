#define CATCH_CONFIG_MAIN

#include <unistd.h>
#include "../Catch/catch.hpp"
#include "../../src/core/tokenizer.c"


TEST_CASE("tokenize_function") {

    SECTION("splits a stripped string into a function") {
        char a_func_text[] = "(a,b):boo!)";

        Func *func = tokenize_function(a_func_text);

        REQUIRE(strcmp(func->returnValue, "boo!") == 0);
        REQUIRE(strcmp(func->args[0], "a") == 0);
        REQUIRE(strcmp(func->args[1], "b") == 0);
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
        string expected[] = { "" };

        char **args = tokenize_arguments(snip);

        REQUIRE(args[0] == NULL);
    }

}


TEST_CASE("tokenize_returnValue") {

    SECTION("parses return value from function") {
        char snip[] = "return this)";

        char *returnValue = tokenize_returnValue(snip);

        REQUIRE(strcmp(returnValue, "return this") == 0);
    }

}

// TODO strip also removes whitespace from literals (strings)
TEST_CASE("lex") {

    SECTION("tokenizes a file as a function") {
        string filename = "../test/core/helloworld.du";

        Func *actual = lex(filename);

        REQUIRE(actual->args[0] == NULL);
        REQUIRE(strcmp(actual->returnValue, "\"Helloworld!\"") == 0);
    }

}
