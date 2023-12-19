#include <gtest/gtest.h>
#include <wsl/ws_string_view.h>

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
