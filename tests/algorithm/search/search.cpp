#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>

#include <wsl/ws_binary_tree.h>
#include <wsl/ws_hash_map.h>
#include <wsl/ws_queue.h>
#include <wsl/ws_stack.h>
#include <wsl/ws_string_builder.h>
#include <wsl/ws_string_view.h>
#include <wsl/ws_vector.h>

WS_VECTOR(int)
WS_STACK(int)
WS_QUEUE(int)
WS_BINARY_TREE(int)
WS_HASH_MAP(int)

TEST(algorithm, vector_search)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    int value = 420;
    EXPECT_NE(ws_search(&vector, &value), nullptr);
    ws_vector_destroy(int, &vector);
}

TEST(algorithm, stack_fail_search)
{
    struct ws_stack_int stack = ws_stack_int_create(ws_stack_initialize(int, 69, 720, 420));
    int value = 420;
    ASSERT_DEATH(ws_search(&stack, &value), "\"INVALID CONTAINER TYPE\"");
    ws_stack_destroy(int, &stack);
}

TEST(algorithm, queue_fail_search)
{
    struct ws_queue_int queue = ws_queue_int_create(ws_queue_initialize(int, 69, 720, 420));
    int value = 420;
    ASSERT_DEATH(ws_search(&queue, &value), "\"INVALID CONTAINER TYPE\"");
    ws_queue_destroy(int, &queue);
}

TEST(algorithm, string_view_fail_search)
{
    struct ws_string_view string = ws_string_view_create("world");
    int value = 69;
    ASSERT_DEATH(ws_search(&string, &value), "\"INVALID CONTAINER TYPE\"");
}

TEST(algorithm, string_builder_fail_search)
{
    struct ws_string_builder string = ws_string_builder_create("world");
    int value = 69;
    ASSERT_DEATH(ws_search(&string, &value), "\"INVALID CONTAINER TYPE\"");
    ws_string_builder_destroy(&string);
}

TEST(algorithm, binary_tree_int_fail_search)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();
    int value = 69;
    ASSERT_DEATH(ws_search(&tree, &value), "\"INVALID CONTAINER TYPE\"");
    ws_binary_tree_destroy(int, &tree);
}

TEST(algorithm, hash_map_int_fail_search)
{
    struct ws_hash_map_int map = ws_hash_map_int_create();
    int value = 69;
    ASSERT_DEATH(ws_search(&map, &value), "\"INVALID CONTAINER TYPE\"");
    ws_hash_map_destroy(int, &map);
}

