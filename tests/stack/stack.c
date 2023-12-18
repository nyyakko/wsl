#include "wsl/ws_stack.h"

#include <string.h>

WS_STACK(int)

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

void test_initialized_with_values()
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));

    WS_ASSERT(*ws_stack_int_top(stack) == 720);

    ws_stack_destroy(int, &stack);
}

void test_push_values()
{
    struct ws_stack_int stack = ws_stack_int_create(0);

    ws_stack_int_push(&stack, 69);
    WS_ASSERT(*ws_stack_int_top(stack) == 69);
    ws_stack_int_push(&stack, 420);
    WS_ASSERT(*ws_stack_int_top(stack) == 420);
    ws_stack_int_push(&stack, 720);
    WS_ASSERT(*ws_stack_int_top(stack) == 720);

    WS_ASSERT(ws_stack_int_size(stack) == 3);

    ws_stack_destroy(int, &stack);
}

void test_pop_values()
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));

    WS_ASSERT(ws_stack_int_size(stack)  == 3);
    WS_ASSERT(*ws_stack_int_pop(&stack) == 720);
    WS_ASSERT(ws_stack_int_size(stack)  == 2);
    WS_ASSERT(*ws_stack_int_pop(&stack) == 420);
    WS_ASSERT(ws_stack_int_size(stack)  == 1);
    WS_ASSERT(*ws_stack_int_pop(&stack) == 69);
    WS_ASSERT(ws_stack_int_size(stack)  == 0);

    ws_stack_destroy(int, &stack);
}

void test_copy_values()
{
    struct ws_stack_int stackA = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));
    struct ws_stack_int stackB = ws_stack_int_create(0);

    ws_stack_copy(int, &stackB, &stackA);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

void test_copy_values_non_empty()
{
    struct ws_stack_int stackA = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));
    struct ws_stack_int stackB = ws_stack_int_create(ws_stack_initialize(int, 69420));

    ws_stack_copy(int, &stackB, &stackA);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

void test_copy_empty()
{
    struct ws_stack_int stackA = ws_stack_int_create(0);
    struct ws_stack_int stackB = ws_stack_int_create(0);

    ws_stack_copy(int, &stackB, &stackA);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

int main(int argumentCount, char const** argumentValues)
{
    assert(argumentCount == 2);

    if (!strcmp(argumentValues[1], "initialized_with_values"))
    {
        test_initialized_with_values();
    }
    else if (!strcmp(argumentValues[1], "push_values"))
    {
        test_push_values();
    }
    else if (!strcmp(argumentValues[1], "pop_values"))
    {
        test_pop_values();
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
