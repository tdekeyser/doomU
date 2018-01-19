#define CATCH_CONFIG_MAIN

#include "../Catch/catch.hpp"

#include <stdlib.h>
#include <string.h>
#include "../../src/doomu/doomu_http.c"

TEST_CASE("doomU http") {

    Buffer header, body;
    DoomUResponse response = newDoomUResponse(&header, &body);

    SECTION("get assigns response to input buffer") {
        get("https://github.com/tdekeyser/mixnet/blob/develop/README.md", &response);

        REQUIRE((response.body->size > 1 && response.header->size > 1));
    }

    SECTION("failed get throws error") {
        get("non_existing", &response);

        REQUIRE((response.body->size == 0 && response.header->size == 0));
    }

    destroyDoomUResponse(&response);
}
