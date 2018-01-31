#include "../Catch/catch.hpp"
#include "../../include/parser.h"
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

    SECTION("applies addition to all elements of the stream: 1 argument") {
        StreamElement *first = new_StreamElement(Num, 10l);
        StreamElement *second = new_StreamElement(Num, 20l);
        first->next = second;
        auto **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char func_body[] = "add:5:a";
        Lambda *lambda = new_Lambda(new_Arguments(1, args), new_TypedValue(Func, func_body));

        int result = map(first, lambda);

        StreamElement *expectedFirst = new_StreamElement(Num, 15l);
        StreamElement *expectedSecond = new_StreamElement(Num, 25l);
        expectedFirst->next = expectedSecond;
        REQUIRE(is_equal(expectedFirst, first));
        REQUIRE(result == 0);
        free(lambda);
    }

    SECTION("applies print string to all elements of the stream: 1 argument") {
        StreamElement *first = new_StreamElement(Str, (long) 'H');
        StreamElement *second = new_StreamElement(Str, (long) 'i');
        first->next = second;
        auto **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char func_body[] = "prints:a";
        Lambda *lambda = new_Lambda(new_Arguments(1, args), new_TypedValue(Func, func_body));

        int result = map(first, lambda);

        StreamElement *expectedFirst = new_StreamElement(Str, (long) 'H');
        StreamElement *expectedSecond = new_StreamElement(Str, (long) 'i');
        expectedFirst->next = expectedSecond;
        REQUIRE(is_equal(expectedFirst, first));
        REQUIRE(result == 0);
        free(lambda);
    }

    SECTION("applies print integer to all elements of the stream: 1 argument") {
        StreamElement *first = new_StreamElement(Num, 10l);
        StreamElement *second = new_StreamElement(Num, 20l);
        first->next = second;
        auto **args = (char**) malloc(ARG_LEN);
        args[0] = (char *) "a";
        char func_body[] = "printi:a";
        Lambda *lambda = new_Lambda(new_Arguments(1, args), new_TypedValue(Func, func_body));

        int result = map(first, lambda);

        StreamElement *expectedFirst = new_StreamElement(Num, 10l);
        StreamElement *expectedSecond = new_StreamElement(Num, 20l);
        expectedFirst->next = expectedSecond;
        REQUIRE(is_equal(expectedFirst, first));
        REQUIRE(result == 0);
        free(lambda);
    }

}

TEST_CASE("interpret") {

    SECTION("prints hello world") {
       Stream *stream = parse("../test/core/helloworld.du");

       REQUIRE(interpret(stream) == 0);
   }

   SECTION("prints a list of integers added five") {
        Stream *stream = parse("../test/core/map.du");

       REQUIRE(interpret(stream) == 0);
   }

}