#include "../Catch/catch.hpp"

#include "../../src/core/operation.c"


TEST_CASE("operations") {

    SECTION("add") {
        long values[] = { 10l, 30l };
        MapParameters params = (MapParameters) { 2, values };

        REQUIRE(add(&params) == 40l);
    }

    SECTION("subtract") {
        long values[] = { 450l, 10l };
        MapParameters params = (MapParameters) { 2, values };

        REQUIRE(subtract(&params) == 440l);
    }

    SECTION("subtract: negative values") {
        long values[] = { 10l, 450l };
        MapParameters params = (MapParameters) { 2, values };

        REQUIRE(subtract(&params) == -440l);
    }

    SECTION("multiply") {
        long values[] = { 100l, 4l };
        MapParameters params = (MapParameters) { 2, values };

        REQUIRE(multiply(&params) == 400l);
    }

    SECTION("mod") {
        long values[] = { 23l, 5l };
        MapParameters params = (MapParameters) { 2, values };

        REQUIRE(mod(&params) == 3l);
    }

}

