#include "wsl/ws_string_view.h"

#include <stdlib.h>
#include <string.h>

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

void test_chop_until_last()
{
    struct ws_string_view view = ws_string_view_create("Its so over");

    ws_string_view_chop_until_last(&view, ' ');

    WS_ASSERT(!strcmp(view.data, "over"));
}

void test_chop_until_first()
{
    struct ws_string_view view = ws_string_view_create("Its so over");

    ws_string_view_chop_until_first(&view, ' ');

    WS_ASSERT(!strcmp(view.data, "so over"));
}

void test_subview()
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("so over");

    WS_ASSERT(ws_string_view_equals(ws_string_view_subview(viewA, 4, viewA.size), viewB));
}

void test_copy_values()
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("");

    ws_string_view_copy(&viewB, &viewA);

    WS_ASSERT(ws_string_view_equals(viewA, viewB));
}

void test_copy_values_non_empty()
{
    struct ws_string_view viewA = ws_string_view_create("Its so over");
    struct ws_string_view viewB = ws_string_view_create("so over");

    ws_string_view_copy(&viewB, &viewA);

    WS_ASSERT(ws_string_view_equals(viewA, viewB));
}

void test_copy_empty()
{
    struct ws_string_view viewA = ws_string_view_create("");
    struct ws_string_view viewB = ws_string_view_create("");

    ws_string_view_copy(&viewB, &viewA);

    WS_ASSERT(ws_string_view_equals(viewA, viewB));
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
    else if (!strcmp(argumentValues[1], "subview"))
    {
        test_subview();
    }
    else if (!strcmp(argumentValues[1], "copy_values"))
    {
        test_copy_values();
    }
    else if (!strcmp(argumentValues[1], "copy_values_non_empty"))
    {
        test_copy_values_non_empty();
    }
    else if (!strcmp(argumentValues[1], "copy_empty"))
    {
        test_copy_empty();
    }

    return EXIT_SUCCESS;
}
