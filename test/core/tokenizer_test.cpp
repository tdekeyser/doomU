#define CATCH_CONFIG_MAIN

#include "../Catch/catch.hpp"
#include "../../src/core/tokenizer.c"


TEST_CASE("tokenize_arguments") {

    SECTION("splits a stripped string into a list of argument tokens") {
        char du_snip[] = "arg1,arg2):return";
        char *args[3];
        string expected[] = { "arg1", "arg2" };

        tokenize_arguments(du_snip, args);

        for (int i = 0; i < 2; i++) {
            REQUIRE(strcmp(args[i], expected[i]) == 0);
        }
    }

}
