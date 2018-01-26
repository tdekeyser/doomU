#define CATCH_CONFIG_MAIN


#include "../Catch/catch.hpp"
#include "../../src/core/function.c"
#include "../../src/core/lexer.c"


TEST_CASE("tokenize_lambda") {

    SECTION("splits a stripped string into a lambda") {
        char a_func_text[] = "(a,b):boo!)";

        Lambda *lambda = tokenize_lambda(a_func_text);

        REQUIRE(strcmp(lambda->returnValue, "boo!") == 0);
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
        string expected[] = { "" };

        char **args = tokenize_arguments(snip);

        REQUIRE(args[0] == NULL);
    }

}


TEST_CASE("tokenize_returnValue") {

    SECTION("parses return value from lambda") {
        char snip[] = "return this)";

        char *returnValue = tokenize_returnValue(snip);

        REQUIRE(strcmp(returnValue, "return this") == 0);
    }

}


TEST_CASE("lex") {

    SECTION("tokenizes a file as a stream of lambdas") {
        string filename = "../test/core/helloworld.du";

        Stream *actual = lex(filename);

        REQUIRE(strcmp(actual->name, "main") == 0);
        REQUIRE(actual->lambdas[0]->args[0] == NULL);
        REQUIRE(strcmp(actual->lambdas[0]->returnValue, "\"Hello world!\"") == 0);
        REQUIRE(actual->lambdas[1]->args[0] == NULL);
        REQUIRE(strcmp(actual->lambdas[1]->returnValue, "print") == 0);
        REQUIRE(actual->n_lambdas == 2);
    }

}
