#include "../Catch/catch.hpp"
#include "../../src/utils/str_utils.c"

#include <cstring>


TEST_CASE("length") {

    SECTION("calculates the length of an array") {
        REQUIRE(length("hello there!") == 12);
    }

    SECTION("empty string returns zero") {
        REQUIRE(length("") == 0);
    }

}


TEST_CASE("slice_until") {

    SECTION("returns string slice from buffer until limit is encountered") {
        char ab[] = "argument1, argument2";
        char a[64];

        slice_until(COMMA, ab, a);

        REQUIRE(strcmp(a, "argument1") == 0);
    }

    SECTION("returns string if delimiter is not found") {
        char arguments[] = "argument1, argument2";
        char slice[64];

        slice_until(COLON, arguments, slice);

        REQUIRE(strcmp(slice, "argument1, argument2") == 0);
    }

    SECTION("changes input buffer") {
        char arguments[] = "argument1, argument2";
        char slice[64];

        slice_until(COMMA, arguments, slice);

        printf("%s", arguments);

        REQUIRE(strcmp(arguments, " argument2") == 0);
    }

}


TEST_CASE("split") {

    SECTION("splits a string on a delimiter") {
        char a_string[] = "guitar, drums, keyboards";
        string split_string[] = {"guitar", " drums", " keyboards"};

        char *actual[3];

        split(COMMA, a_string, actual);

        for (int i = 0; i < 3; i++) {
            REQUIRE(strcmp(actual[i], split_string[i]) == 0);
        }
    }

    SECTION("returns one element if no delimiter in string") {
        char another_string[] = "guitars are nice";
        string another_split_string[] = {"guitars are nice"};

        char *actual[1];

        split(COMMA, another_string, actual);

        REQUIRE(strcmp(actual[0], another_split_string[0]) == 0);
    }

    SECTION("returns number of split elements") {
        char a_string[] = "guitar, drums, keyboards";
        char *actual[3];

        size_t num_splits = split(COMMA, a_string, actual);

        REQUIRE(num_splits == 3);
    }

    SECTION("does not change input buffer value") {
        char a_string[] = "guitar, drums, keyboards";
        char a_duplicate[] = "guitar, drums, keyboards";
        char *actual[3];

        split(COMMA, a_string, actual);

        REQUIRE(strcmp(a_string, a_duplicate) == 0);
    }

}


TEST_CASE("strip") {

    SECTION("removes space and newline characters from string") {
        char a_string[] = "    full\nof\r whitespace! ";
        
        strip(a_string);

        REQUIRE(strcmp(a_string, "fullofwhitespace!") == 0);
    }

    SECTION("leaves string same if no whitespace") {
        char another_string[] = "nowhitespace!";
        
        strip(another_string);

        REQUIRE(strcmp(another_string, "nowhitespace!") == 0);
    }

}

