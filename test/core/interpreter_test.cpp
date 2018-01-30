#include "../Catch/catch.hpp"
#include "../../src/core/interpreter.c"


bool is_equal(StreamElement *first, StreamElement *second) {
    if (first->next != NULL) {
        if (second->next != NULL)
            return is_equal(first->next, second->next);
        return false;
    }
    if (second->next != NULL)
        return false;

    return (first->type == second->type) && (first->value == second->value);
}


TEST_CASE("read_as_stream") {

    SECTION("read_num_as_stream reads a list of long as a linked list") {
        char a_string[] = "[10,20,30]";
        StreamElement *first = new_StreamElement(Num, 10l);
        StreamElement *second = new_StreamElement(Num, 20l);
        StreamElement *third = new_StreamElement(Num, 30l);
        first->next = second; second->next = third;

        StreamElement *actual = read_num_as_stream(a_string);

        REQUIRE(is_equal(actual, first));
    }

    SECTION("read_string_as_stream reads a string as a linked list") {

    }

}

TEST_CASE("map") {
}

TEST_CASE("interpret") {
}