#include <gtest/gtest.h>
#include <wsl/ws_string_builder.h>

TEST(chop_until_last, string_builder)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_last(&string, ' ');

    EXPECT_STREQ(string.data, "over");

    ws_string_builder_destroy(&string);
}

TEST(chop_until_first, string_builder)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_first(&string, ' ');

    EXPECT_STREQ(string.data, "so over");

    ws_string_builder_destroy(&string);
}

TEST(substring, string_builder)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    EXPECT_STREQ(ws_string_builder_substr(stringA, 4, stringA.size).data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(copy_values, string_builder)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    ws_string_builder_copy(&stringB, &stringA);

    EXPECT_STREQ(stringA.data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(copy_empty, string_builder)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("");

    ws_string_builder_copy(&stringA, &stringB);

    EXPECT_STREQ(stringA.data, stringB.data);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(append, string_builder)
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

TEST(append_string, string_builder)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string(&string, "world!");
    EXPECT_STREQ(string.data, "Hello, world!");

    ws_string_builder_destroy(&string);
}

