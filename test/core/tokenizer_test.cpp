#define CATCH_CONFIG_MAIN

#include "../Catch/catch.hpp"
#include "../../src/core/tokenizer.c"


TEST_CASE("tokenize_function") {

    SECTION("splits a stripped string into a function") {
        char a_func_text[] = "((a,b):boo!)";
        char *arg[3];
        char returnVal[64];
        Func func = { .args=arg, .returnValue=returnVal };

        tokenize_function(a_func_text, &func);

        REQUIRE(strcmp(func.returnValue, "boo!") == 0);
        REQUIRE(strcmp(func.args[0], "a") == 0);
        REQUIRE(strcmp(func.args[1], "b") == 0);
    }

}


TEST_CASE("tokenize_arguments") {

    SECTION("splits a stripped string into a list of argument tokens") {
        char snip[] = "arg1,arg2):return";
        char *args[3];
        string expected[] = { "arg1", "arg2" };

        tokenize_arguments(snip, args);

        for (int i = 0; i < 2; i++) {
            REQUIRE(strcmp(args[i], expected[i]) == 0);
        }
    }

}
