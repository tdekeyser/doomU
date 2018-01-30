
#include "../Catch/catch.hpp"
#include "../../include/parser.h"
#include "../../src/core/interpreter_old.c"


//TEST_CASE("interpret_lambda") {

    // SECTION("maps input to arguments and return values: 0 arguments") {
    //     auto **args = (char**) malloc(ARG_LEN);
    //     char hello[] = "\"Hello world!\"";
    //     Lambda *lambda = newLambda(newArguments(0, args), newTypedValue(Str, hello));

    //     TypedValue *actual = interpret_lambda(lambda, nullptr);

    //     REQUIRE(actual->type == Str);
    //     REQUIRE(memcmp(actual->value, hello, sizeof(actual->value)) == 0);
    // }

    // SECTION("maps input to arguments and return values: 1 argument") {
    //     long input[] = {1,2,3};
    //     auto **args = (char**) malloc(ARG_LEN);
    //     args[0] = (char *) "a";
    //     char func_body[] = "add:a:1";
    //     Lambda *lambda = newLambda(newArguments(1, args), newTypedValue(Func, func_body));

    //     TypedValue *actual = interpret_lambda(lambda, newTypedValue(Num, input));

    //     long expected[] = {2,3,4};
    //     REQUIRE(actual->type == Num);
    //     REQUIRE(memcmp(actual->value, expected, sizeof(actual->value)) == 0);
    // }

//    SECTION("can print a value from a lambda") {
//        auto **args = (char**) malloc(ARG_LEN);
//        args[0] = (char *) "a";
//        char print[] = "print:a";
//        char hello[] = "\"Hello world!\"";
//        Lambda *lambda = newLambda(newArguments(1, args), newTypedValue(Func, print));
//
//        TypedValue *actual = interpret_lambda(lambda, newTypedValue(Str, hello));
//
//        REQUIRE(actual->type == List);
//        REQUIRE(strcmp(actual->value, "") == 0);
//    }

//}


//TEST_CASE("interpret") {
//
//    SECTION("executes a lambda stream") {
//        Stream *stream = parse("../test/core/helloworld.du");
//
//        REQUIRE(interpret(stream) == 0);
//    }

//}