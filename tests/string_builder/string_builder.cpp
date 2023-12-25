#define WS_STRING_BUILDER_DEFINITION

#include <gtest/gtest.h>
#include <wsl/ws_string_builder.h>

TEST(string_builder, chop_until_last)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_last(&string, ' ');

    EXPECT_STREQ(string.data, "over");

    ws_string_builder_destroy(&string);
}

TEST(string_builder, chop_until_first)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_first(&string, ' ');

    EXPECT_STREQ(string.data, "so over");

    ws_string_builder_destroy(&string);
}

TEST(string_builder, substring)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");
    struct ws_string_builder stringC = ws_string_builder_substr(stringA, 4, stringA.size);

    EXPECT_STREQ(stringC.data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringC);
}

TEST(string_builder, copy_values)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    ws_string_builder_copy(&stringB, &stringA);

    EXPECT_STREQ(stringA.data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(string_builder, copy_empty)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("");

    ws_string_builder_copy(&stringA, &stringB);

    EXPECT_STREQ(stringA.data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(string_builder, append)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append(&string, 'w');
    ws_string_builder_append(&string, 'o');
    ws_string_builder_append(&string, 'r');
    ws_string_builder_append(&string, 'l');
    ws_string_builder_append(&string, 'd');
    ws_string_builder_append(&string, '!');

    EXPECT_STREQ(string.data, "Hello, world!");

    ws_string_builder_destroy(&string);
}

TEST(string_builder, append_while)
{
    struct ws_string_builder stringA = ws_string_builder_create("how are you, fine sankyou!");
    struct ws_string_builder stringB = ws_string_builder_create("");

    ws_string_builder_append_string_while(&stringB, stringA.data, isalpha);

    EXPECT_STREQ(stringB.data, "how");

    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringA);
}

TEST(string_builder, append_while_not)
{
    struct ws_string_builder stringA = ws_string_builder_create("how are you, fine sankyou!");
    struct ws_string_builder stringB = ws_string_builder_create("");

    ws_string_builder_append_string_while_not(&stringB, stringA.data, ispunct);

    EXPECT_STREQ(stringB.data, "how are you");

    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringA);
}

TEST(string_builder, append_string)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string(&string, "world!");
    EXPECT_STREQ(string.data, "Hello, world!");

    ws_string_builder_destroy(&string);
}

