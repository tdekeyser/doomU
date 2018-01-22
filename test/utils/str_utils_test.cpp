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
        string ab = "argument1, argument2";
        char a[64];

        size_t i = slice_until(COMMA, ab, a);

        REQUIRE(strcmp(a, "argument1") == 0);
        REQUIRE(strcmp(ab, "argument1, argument2") == 0);
        REQUIRE(i == 9);
    }

    SECTION("returns string if delimiter is not found") {
        string arguments = "argument1, argument2";
        char slice[64];

        size_t i = slice_until(COLON, arguments, slice);

        REQUIRE(strcmp(slice, "argument1, argument2") == 0);
        REQUIRE(strcmp(arguments, "argument1, argument2") == 0);
        REQUIRE(i == 20);
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

//    SECTION("returns one element if no delimiter in string") {
//        char another_string[] = "guitars are nice";
//        string another_split_string[] = {"guitars are nice"};
//
//        char *actual[1];
//
//        split(COMMA, another_string, actual);
//
//        REQUIRE(strcmp(actual[0], another_split_string[0]) == 0);
//    }

}

