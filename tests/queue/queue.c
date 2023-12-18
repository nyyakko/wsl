#include "wsl/ws_queue.h"

#include <string.h>

WS_QUEUE(int)

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

void test_initialized_with_values()
{
    struct ws_queue_int queue = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));

    WS_ASSERT(*ws_queue_int_back(queue) == 720);

    ws_queue_destroy(int, &queue);
}

void test_push_values()
{
    struct ws_queue_int queue = ws_queue_int_create(0);

    ws_queue_int_push(&queue, 69);
    WS_ASSERT(*ws_queue_int_back(queue) == 69);
    ws_queue_int_push(&queue, 420);
    WS_ASSERT(*ws_queue_int_back(queue) == 420);
    ws_queue_int_push(&queue, 720);
    WS_ASSERT(*ws_queue_int_back(queue) == 720);

    WS_ASSERT(ws_queue_int_size(queue) == 3);

    ws_queue_destroy(int, &queue);
}

void test_pop_values()
{
    struct ws_queue_int queue = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));

    WS_ASSERT(ws_queue_int_size(queue)  == 3);
    WS_ASSERT(*ws_queue_int_pop(&queue) == 69);
    WS_ASSERT(ws_queue_int_size(queue)  == 2);
    WS_ASSERT(*ws_queue_int_pop(&queue) == 420);
    WS_ASSERT(ws_queue_int_size(queue)  == 1);
    WS_ASSERT(*ws_queue_int_pop(&queue) == 720);
    WS_ASSERT(ws_queue_int_size(queue)  == 0);

    ws_queue_destroy(int, &queue);
}

void test_copy_values()
{
    struct ws_queue_int queueA = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));
    struct ws_queue_int queueB = ws_queue_int_create(0);

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
}

void test_copy_values_non_empty()
{
    struct ws_queue_int queueA = ws_queue_int_create(ws_queue_initialize(int, 69, 420, 720));
    struct ws_queue_int queueB = ws_queue_int_create(ws_queue_initialize(int, 69420));

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
}

void test_copy_empty()
{
    struct ws_queue_int queueA = ws_queue_int_create(0);
    struct ws_queue_int queueB = ws_queue_int_create(0);

    ws_queue_copy(int, &queueB, &queueA);

    ws_queue_destroy(int, &queueA);
    ws_queue_destroy(int, &queueB);
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
