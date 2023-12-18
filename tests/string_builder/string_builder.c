#include "wsl/ws_string_builder.h"

#include <stdlib.h>
#include <string.h>

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

void test_chop_until_last()
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_last(&string, ' ');

    WS_ASSERT(!strcmp(string.data, "over"));

    ws_string_builder_destroy(&string);
}

void test_chop_until_first()
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_first(&string, ' ');

    WS_ASSERT(!strcmp(string.data, "so over"));

    ws_string_builder_destroy(&string);
}

void test_substring()
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    WS_ASSERT(ws_string_builder_equals(ws_string_builder_substr(stringA, 4, stringA.size), stringB));

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

void test_copy_values()
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    ws_string_builder_copy(&stringB, &stringA);

    WS_ASSERT(ws_string_builder_equals(stringA, stringB));

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

void test_copy_empty()
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("");

    ws_string_builder_copy(&stringA, &stringB);

    WS_ASSERT(ws_string_builder_equals(stringA, stringB));

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

void test_append()
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append(&string, 'w');
    ws_string_builder_append(&string, 'o');
    ws_string_builder_append(&string, 'r');
    ws_string_builder_append(&string, 'l');
    ws_string_builder_append(&string, 'd');
    ws_string_builder_append(&string, '!');

    WS_ASSERT(!strcmp(string.data, "Hello, world!"));

    ws_string_builder_destroy(&string);
}

void test_append_string()
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string(&string, "world!");
    WS_ASSERT(!strcmp(string.data, "Hello, world!"));

    ws_string_builder_destroy(&string);
}

int main(int argumentCount, char const** argumentValues)
{
    assert(argumentCount == 2);

    if (!strcmp(argumentValues[1], "chop_until_last"))
    {
        test_chop_until_last();
    }
    else if (!strcmp(argumentValues[1], "chop_until_first"))
    {
        test_chop_until_first();
    }
    else if (!strcmp(argumentValues[1], "substring"))
    {
        test_substring();
    }
    else if (!strcmp(argumentValues[1], "copy_values"))
    {
        test_copy_values();
    }
    else if (!strcmp(argumentValues[1], "copy_empty"))
    {
        test_copy_empty();
    }
    else if (!strcmp(argumentValues[1], "append"))
    {
        test_append();
    }
    else if (!strcmp(argumentValues[1], "append_string"))
    {
        test_append_string();
    }

    return EXIT_SUCCESS;
}
