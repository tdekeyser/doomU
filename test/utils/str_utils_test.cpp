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


TEST_CASE("contains") {

    SECTION("returns true if char is in string") {
        REQUIRE(contains((string) "this is a string with a, comma", COMMA) == true);
        REQUIRE(contains((string) "here is the a", 'a') == true);        
    }

    SECTION("false if char not in string") {
        REQUIRE_FALSE(contains((string) "no comma here", COMMA));
        REQUIRE_FALSE(contains((string) "neither a colon there", COLON));        
    }

}


TEST_CASE("no_spaces") {

    SECTION("is true if string contains no whitespace") {
        REQUIRE(no_spaces("thiscontainsnospaces!") == true);
    }

    SECTION("is false if string contains whitespace") {
        REQUIRE_FALSE(no_spaces("space\nhere :"));
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

        printf("%s", arguments);

        REQUIRE(strcmp(slice, "argument1, argument2") == 0);
        REQUIRE(strcmp(arguments, "") == 0);
    }

    SECTION("changes input buffer") {
        char arguments[] = "argument1, argument2";
        char slice[64];

        slice_until(COMMA, arguments, slice);

        REQUIRE(strcmp(arguments, " argument2") == 0);
    }

    SECTION("handles empty string") {
        char arg[] = "";
        char slice[64];

        slice_until(COMMA, arg, slice);

        REQUIRE(strcmp(arg, "") == 0);
        REQUIRE(strcmp(slice, "") == 0);
    }

}


TEST_CASE("skip_until") {

    SECTION("skips chars until limit is reached") {
        char a_string[] = "a string, this is";

        skip_until(COMMA, a_string);

        REQUIRE(strcmp(a_string, " this is") == 0);
    }

    SECTION("returns empty if limit not in string") {
        char a_string[] = "no limit can be found here!";

        skip_until(COMMA, a_string);

        REQUIRE(strcmp(a_string, "") == 0);
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

    SECTION("handles empty string") {
        char empty[] = "";
        char *actual[3];

        split(COMMA, empty, actual);

        REQUIRE(strcmp(empty, "") == 0);
        REQUIRE(actual[0] == NULL);
    }

}


TEST_CASE("strip") {

    SECTION("removes space and newline characters from string") {
        char a_string[] = "    full\nof\r whitespace! ";
        char another[] = " arg2";
        
        strip(a_string);
        strip(another);

        REQUIRE(strcmp(a_string, "fullofwhitespace!") == 0);
        REQUIRE(strcmp(another, "arg2") == 0);
    }

    SECTION("leaves string same if no whitespace") {
        char another_string[] = "nowhitespace!";
        
        strip(another_string);

        REQUIRE(strcmp(another_string, "nowhitespace!") == 0);
    }

}


TEST_CASE("strip_leave_quotes") {

    SECTION("removes whitespace but not inside quotation marks") {
        char a_string[] = " full\n \"but don't touch this\"! ";
        char another[] = "\"don't touch this\"! But remove space ";

        strip_leave_quotes(a_string);
        strip_leave_quotes(another);

        REQUIRE(strcmp(a_string, "full\"but don't touch this\"!") == 0);
        REQUIRE(strcmp(another, "\"don't touch this\"!Butremovespace") == 0);
    }

    SECTION("empty string remains empty") {
        char empty[] = "";

        strip_leave_quotes(empty);
        
        REQUIRE(strcmp(empty, "") == 0);
    }

}

