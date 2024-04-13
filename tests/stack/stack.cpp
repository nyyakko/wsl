#define WS_STACK_DEFINITION

#include <gtest/gtest.h>
#include <wsl/ws_stack.h>

WS_STACK(int)

TEST(stack, initialized_with_values)
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));

    EXPECT_EQ(*ws_stack_int_top(stack), 720);
    EXPECT_EQ(stack.end, stack.size);

    ws_stack_destroy(int, &stack);
}

TEST(stack, push_values)
{
    struct ws_stack_int stack = ws_stack_int_create(0);

    ws_stack_int_push(&stack, 69);
    EXPECT_EQ(*ws_stack_int_top(stack), 69);
    ws_stack_int_push(&stack, 420);
    EXPECT_EQ(*ws_stack_int_top(stack), 420);
    ws_stack_int_push(&stack, 720);
    EXPECT_EQ(*ws_stack_int_top(stack), 720);

    EXPECT_EQ(ws_stack_int_size(stack), 3);
    EXPECT_EQ(stack.end, stack.size);

    ws_stack_destroy(int, &stack);
}

TEST(stack, pop_values)
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_stack_int_size(stack),  3);
    EXPECT_EQ(ws_stack_int_pop(&stack), 720);
    EXPECT_EQ(ws_stack_int_size(stack),  2);
    EXPECT_EQ(ws_stack_int_pop(&stack), 420);
    EXPECT_EQ(ws_stack_int_size(stack),  1);
    EXPECT_EQ(ws_stack_int_pop(&stack), 69);

    EXPECT_EQ(ws_stack_int_size(stack),  0);
    EXPECT_EQ(stack.begin,  stack.end);

    ws_stack_destroy(int, &stack);
}

TEST(stack, pop_and_push_values)
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_stack_int_size(stack),  3);

    EXPECT_EQ(ws_stack_int_pop(&stack), 720);
    EXPECT_EQ(ws_stack_int_size(stack),  2);

    {
        ws_stack_int_push(&stack, 360);
        EXPECT_EQ(ws_stack_int_size(stack),  3);
        EXPECT_EQ(ws_stack_int_pop(&stack), 360);
    }

    EXPECT_EQ(ws_stack_int_size(stack),  2);
    EXPECT_EQ(ws_stack_int_pop(&stack), 420);
    EXPECT_EQ(ws_stack_int_size(stack),  1);
    EXPECT_EQ(ws_stack_int_pop(&stack), 69);

    EXPECT_EQ(ws_stack_int_size(stack),  0);

    EXPECT_EQ(stack.begin,  stack.end);

    ws_stack_destroy(int, &stack);
}

TEST(stack, copy_values_empty)
{
    struct ws_stack_int stackA = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));
    struct ws_stack_int stackB = ws_stack_int_create(0);

    ws_stack_copy(int, &stackB, &stackA);
    EXPECT_EQ(stackB.data[0], 69);
    EXPECT_EQ(stackB.data[1], 420);
    EXPECT_EQ(stackB.data[2], 720);

    EXPECT_EQ(stackB.begin, stackA.begin);
    EXPECT_EQ(stackB.end, stackA.end);
    EXPECT_EQ(stackB.size, stackA.size);
    EXPECT_EQ(stackB.capacity, stackA.capacity);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

TEST(stack, copy_values_non_empty)
{
    struct ws_stack_int stackA = ws_stack_int_create(ws_stack_initialize(int, 69, 420, 720));
    struct ws_stack_int stackB = ws_stack_int_create(ws_stack_initialize(int, 69420));

    ws_stack_copy(int, &stackB, &stackA);
    EXPECT_EQ(stackB.data[0], 69);
    EXPECT_EQ(stackB.data[1], 420);
    EXPECT_EQ(stackB.data[2], 720);

    EXPECT_EQ(stackB.begin, stackA.begin);
    EXPECT_EQ(stackB.end, stackA.end);
    EXPECT_EQ(stackB.size, stackA.size);
    EXPECT_EQ(stackB.capacity, stackA.capacity);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

TEST(stack, copy_empty)
{
    struct ws_stack_int stackA = ws_stack_int_create(0);
    struct ws_stack_int stackB = ws_stack_int_create(0);

    ws_stack_copy(int, &stackB, &stackA);

    EXPECT_EQ(stackB.begin, stackA.begin);
    EXPECT_EQ(stackB.end, stackA.end);
    EXPECT_EQ(stackB.size, stackA.size);
    EXPECT_EQ(stackB.capacity, stackA.capacity);

    ws_stack_destroy(int, &stackA);
    ws_stack_destroy(int, &stackB);
}

