#define WS_QUEUE_DEFINITION

#include <gtest/gtest.h>
#include <wsl/ws_queue.h>

WS_QUEUE(int)

TEST(queue, initialized_with_values)
{
    struct ws_queue_int queue = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));

    EXPECT_EQ(*ws_queue_int_back(queue), 720);

    ws_queue_destroy(int, &queue);
}

TEST(queue, push_values)
{
    struct ws_queue_int queue = ws_queue_int_create(0);

    ws_queue_int_push(&queue, 69);
    EXPECT_EQ(*ws_queue_int_back(queue), 69);
    ws_queue_int_push(&queue, 420);
    EXPECT_EQ(*ws_queue_int_back(queue), 420);
    ws_queue_int_push(&queue, 720);
    EXPECT_EQ(*ws_queue_int_back(queue), 720);

    EXPECT_EQ(ws_queue_int_size(queue), 3);

    ws_queue_destroy(int, &queue);
}

TEST(queue, pop_values)
{
    struct ws_queue_int queue = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_queue_int_size(queue), 3);
    EXPECT_EQ(ws_queue_int_pop(&queue), 69);
    EXPECT_EQ(ws_queue_int_size(queue), 2);
    EXPECT_EQ(ws_queue_int_pop(&queue), 420);
    EXPECT_EQ(ws_queue_int_size(queue), 1);
    EXPECT_EQ(ws_queue_int_pop(&queue), 720);
    EXPECT_EQ(ws_queue_int_size(queue), 0);

    ws_queue_destroy(int, &queue);
}

TEST(queue, copy_values)
{
    struct ws_queue_int queueA = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));
    struct ws_queue_int queueB = ws_queue_int_create(0);

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
}

TEST(queue, copy_values_non_empty)
{
    struct ws_queue_int queueA = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));
    struct ws_queue_int queueB = ws_queue_int_create(ws_queue_initialize(int, 69420));

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
}

TEST(queue, copy_empty)
{
    struct ws_queue_int queueA = ws_queue_int_create(0);
    struct ws_queue_int queueB = ws_queue_int_create(0);

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
}

