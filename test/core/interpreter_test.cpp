#include "../Catch/catch.hpp"
#include "../../src/core/interpreter.c"


bool is_equal(StreamElement *first, StreamElement *second) {
    if (first->next != nullptr) {
        if (second->next != nullptr)
            return is_equal(first->next, second->next);
        return false;
    }
    if (second->next != nullptr)
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
        char a_string[] = "Hi?!";
        StreamElement *first = new_StreamElement(Str, (long) 'H');
        StreamElement *second = new_StreamElement(Str, (long) 'i');
        StreamElement *third = new_StreamElement(Str, (long) '?');
        StreamElement *fourth = new_StreamElement(Str, (long) '!');        
        first->next = second; second->next = third; third->next = fourth;

        StreamElement *actual = read_string_as_stream(a_string);     

        REQUIRE(is_equal(actual, first));
    }

}


TEST_CASE("map") {

    SECTION("applies a lambda operation to all elements of the stream") {
        StreamElement *first = new_StreamElement(Num, 10l);
        StreamElement *second = new_StreamElement(Num, 20l);
        first->next = second;
        auto **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char func_body[] = "add:a:5";
        Lambda *lambda = new_Lambda(new_Arguments(1, args), new_TypedValue(Func, func_body));

        int result = map(first, lambda);

        StreamElement *expectedFirst = new_StreamElement(Num, 15l);
        StreamElement *expectedSecond = new_StreamElement(Num, 25l);
        expectedFirst->next = expectedSecond;
        REQUIRE(is_equal(expectedFirst, first));
        REQUIRE(result == 0);
        free(lambda);
    }

}

TEST_CASE("interpret") {
}