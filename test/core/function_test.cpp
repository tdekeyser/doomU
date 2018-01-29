#include "../Catch/catch.hpp"
#include "../../src/core/function.c"



TEST_CASE("get_type") {

    SECTION("checks type of input string") {
        REQUIRE(get_type("") == Void);
        REQUIRE(get_type("\"a string\"") == Str);
        REQUIRE(get_type("[20, -40, 300]") == Num);
        REQUIRE(get_type("print:a") == Func);
    }
}

