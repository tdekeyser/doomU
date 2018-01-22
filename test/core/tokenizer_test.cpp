#define CATCH_CONFIG_MAIN

#include "../Catch/catch.hpp"
#include "../../src/core/tokenizer.c"


TEST_CASE("slice_until") {

    SECTION("returns string slice from buffer until limit is encountered") {
        const char ab[] = "argument1, argument2";
        char a[VAR_LEN];

        int i = slice_until(COMMA, ab, a);

        REQUIRE(strcmp(a, "argument1") == 0);
        REQUIRE(strcmp(ab, "argument1, argument2") == 0);
        REQUIRE(i == 9);
    }

    SECTION("returns string if delimiter is not found") {
        const char arguments[] = "argument1, argument2";
        char slice[VAR_LEN];

        int i = slice_until(COLON, arguments, slice);

        REQUIRE(strcmp(slice, "argument1, argument2") == 0);
        REQUIRE(strcmp(arguments, "argument1, argument2") == 0);
        REQUIRE(i == 20);
    }

}
