#include <gtest/gtest.h>

#define WSL_DEFINITION
#include <wsl/wsl.h>

TEST(string_view, create_from_sv)
{
    struct ws_string_view other = ws_string_view_create("hello, world");
    struct ws_string_view view  = ws_string_view_create_from_sv(other);

    EXPECT_STREQ(other.data, view.data);
    EXPECT_EQ(other.data, view.data);
    EXPECT_EQ(other.begin, view.begin);
    EXPECT_EQ(other.end, view.end);
    EXPECT_EQ(other.size, view.size);
}

TEST(string_view, create_from_sb)
{
    struct ws_string_builder other = ws_string_builder_create("hello, world");
    struct ws_string_view view     = ws_string_view_create_from_sb(other);

    EXPECT_STREQ(other.data, view.data);
    EXPECT_EQ(other.data, view.data);
    EXPECT_EQ(other.begin, view.begin);
    EXPECT_EQ(other.end, view.end);
    EXPECT_EQ(other.size, view.size);

    ws_string_builder_destroy(&other);
}

TEST(string_view, chop_until_last)
{
    struct ws_string_view view = ws_string_view_create("Its so over");
    ws_string_view_chop_until_last(&view, ' ');
    EXPECT_STREQ(view.data, "over");
}

TEST(string_view, chop_until_first)
{
    struct ws_string_view view = ws_string_view_create("Its so over");
    ws_string_view_chop_until_first(&view, ' ');
    EXPECT_STREQ(view.data, "so over");
}

TEST(string_view, subview)
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("so over");
    EXPECT_STREQ(ws_string_view_subview(viewA, 4, viewA.size).data, viewB.data);
}

TEST(string_view, copy_values)
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("");
    ws_string_view_copy(&viewB, &viewA);
    EXPECT_STREQ(viewA.data, viewB.data);
}

TEST(string_view, copy_values_non_empty)
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("so over");
    ws_string_view_copy(&viewB, &viewA);
    EXPECT_STREQ(viewA.data, viewB.data);
}

TEST(string_view, copy_empty)
{
    struct ws_string_view viewA = ws_string_view_create("");
    struct ws_string_view viewB = ws_string_view_create("");
    ws_string_view_copy(&viewB, &viewA);
    EXPECT_STREQ(viewA.data, viewB.data);
}
