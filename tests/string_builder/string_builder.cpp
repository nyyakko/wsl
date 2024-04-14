#include <gtest/gtest.h>

#define WSL_DEFINITION
#include <wsl/wsl.h>

TEST(string_builder, create_from_sb)
{
    struct ws_string_builder other  = ws_string_builder_create("hello, world!");
    struct ws_string_builder string = ws_string_builder_create_from_sb(other);

    EXPECT_STREQ(other.data, string.data);

    ws_string_builder_destroy(&string);
    ws_string_builder_destroy(&other);
}

TEST(string_builder, create_from_sv)
{
    struct ws_string_view view      = ws_string_view_create("hello, world!");
    struct ws_string_builder string = ws_string_builder_create_from_sv(view);

    EXPECT_STREQ(view.data, string.data);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, remove_prefix)
{
    struct ws_string_builder string = ws_string_builder_create("xxxx56789");

    ws_string_builder_remove_prefix(&string, 4);

    EXPECT_STREQ(string.data, "56789");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 5);
    EXPECT_EQ(string.size, 5);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, remove_suffix)
{
    struct ws_string_builder string = ws_string_builder_create("12345xxxx");

    ws_string_builder_remove_suffix(&string, 4);

    EXPECT_STREQ(string.data, "12345");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 5);
    EXPECT_EQ(string.size, 5);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, chop_until_first)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_first(&string, ' ');

    EXPECT_STREQ(string.data, "so over");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 7);
    EXPECT_EQ(string.size, 7);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, chop_until_last)
{
    struct ws_string_builder string = ws_string_builder_create("Its so over");

    ws_string_builder_chop_until_last(&string, ' ');

    EXPECT_STREQ(string.data, "over");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 4);
    EXPECT_EQ(string.size, 4);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, append)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append(&string, 'w');
    ws_string_builder_append(&string, 'o');
    ws_string_builder_append(&string, 'r');
    ws_string_builder_append(&string, 'l');
    ws_string_builder_append(&string, 'd');

    EXPECT_STREQ(string.data, "Hello, world");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 12);
    EXPECT_EQ(string.size, 12);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, append_string)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string(&string, "world");
    EXPECT_STREQ(string.data, "Hello, world");
    EXPECT_EQ(string.begin, 0);
    EXPECT_EQ(string.end, 12);
    EXPECT_EQ(string.size, 12);

    ws_string_builder_destroy(&string);
}

TEST(string_builder, append_string_while)
{
    struct ws_string_builder stringA = ws_string_builder_create("What a beautiful world");
    struct ws_string_builder stringB = ws_string_builder_create("Hello, ");

    ws_string_builder_chop_until_last(&stringA, ' ');
    ws_string_builder_append_string_while(&stringB, stringA.data, isalpha);

    EXPECT_STREQ(stringB.data, "Hello, world");
    EXPECT_EQ(stringB.begin, 0);
    EXPECT_EQ(stringB.end, 12);
    EXPECT_EQ(stringB.size, 12);

    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringA);
}

TEST(string_builder, append_string_while_not)
{
    struct ws_string_builder stringA = ws_string_builder_create("World of mine");
    struct ws_string_builder stringB = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string_while_not(&stringB, stringA.data, isspace);

    EXPECT_STREQ(stringB.data, "Hello, World");
    EXPECT_EQ(stringB.begin, 0);
    EXPECT_EQ(stringB.end, 12);
    EXPECT_EQ(stringB.size, 12);

    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringA);
}

TEST(string_builder, substring)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    struct ws_string_builder stringC = ws_string_builder_substr(stringA, 3, stringA.size);

    EXPECT_STREQ(stringC.data, stringB.data);
    EXPECT_EQ(stringC.begin, 0);
    EXPECT_EQ(stringC.end, 7);
    EXPECT_EQ(stringC.size, 7);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringC);
}

TEST(string_builder, copy_values_non_empty)
{
    struct ws_string_builder stringA = ws_string_builder_create("Its so over");
    struct ws_string_builder stringB = ws_string_builder_create("so over");

    ws_string_builder_copy(&stringB, &stringA);

    EXPECT_STREQ(stringB.data, stringA.data);
    EXPECT_EQ(stringB.begin, 0);
    EXPECT_EQ(stringB.end, 11);
    EXPECT_EQ(stringB.size, 11);

    ws_string_builder_destroy(&stringA);
    ws_string_builder_destroy(&stringB);
}

TEST(string_builder, copy_empty)
{
    {
        struct ws_string_builder stringA = ws_string_builder_create("");
        struct ws_string_builder stringB = ws_string_builder_create("Its so over");

        ws_string_builder_copy(&stringB, &stringA);

        EXPECT_STREQ(stringB.data, stringA.data);
        EXPECT_EQ(stringB.begin, 0);
        EXPECT_EQ(stringB.end, 0);
        EXPECT_EQ(stringB.size, 0);

        ws_string_builder_destroy(&stringA);
        ws_string_builder_destroy(&stringB);
    }
    {
        struct ws_string_builder stringA = ws_string_builder_create("");
        struct ws_string_builder stringB = ws_string_builder_create("");

        ws_string_builder_copy(&stringB, &stringA);

        EXPECT_STREQ(stringB.data, stringA.data);
        EXPECT_EQ(stringB.begin, 0);
        EXPECT_EQ(stringB.end, 0);
        EXPECT_EQ(stringB.size, 0);

        ws_string_builder_destroy(&stringA);
        ws_string_builder_destroy(&stringB);
    }
}

