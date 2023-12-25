#define WS_BINARY_TREE_DEFINITION

#include <gtest/gtest.h>
#include <wsl/ws_binary_tree.h>

WS_BINARY_TREE(int)

TEST(binary_tree, push_values)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();

    ws_binary_tree_int_push(&tree, 1, 69);
    EXPECT_EQ(tree.head->value, 69);
    ws_binary_tree_int_push(&tree, 0, 420);
    EXPECT_EQ(tree.head->left->value, 420);
    ws_binary_tree_int_push(&tree, 2, 720);
    EXPECT_EQ(tree.head->right->value, 720);

    EXPECT_EQ(ws_binary_tree_int_size(tree), 3);

    ws_binary_tree_destroy(int, &tree);
}

TEST(binary_tree, pop_values)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();

    ws_binary_tree_int_push(&tree, 1, 69);
    EXPECT_EQ(tree.head->value, 69);
    EXPECT_EQ(ws_binary_tree_int_pop(&tree, 1), 69);

    ws_binary_tree_int_push(&tree, 0, 420);
    EXPECT_EQ(tree.head->value, 420);
    EXPECT_EQ(ws_binary_tree_int_pop(&tree, 0), 420);

    ws_binary_tree_int_push(&tree, 2, 720);
    EXPECT_EQ(tree.head->value, 720);
    EXPECT_EQ(ws_binary_tree_int_pop(&tree, 2), 720);

    EXPECT_EQ(ws_binary_tree_int_size(tree), 0);

    ws_binary_tree_destroy(int, &tree);
}

TEST(binary_tree, search_values)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();

    ws_binary_tree_int_push(&tree, 1, 69);
    ws_binary_tree_int_push(&tree, 0, 420);
    ws_binary_tree_int_push(&tree, 2, 720);

    EXPECT_NE(ws_binary_tree_int_search(tree, 0), nullptr);
    EXPECT_EQ(ws_binary_tree_int_search(tree, 6), nullptr);

    ws_binary_tree_destroy(int, &tree);
}

TEST(binary_tree, maximum)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();

    ws_binary_tree_int_push(&tree, 1, 69);
    ws_binary_tree_int_push(&tree, 0, 420);
    ws_binary_tree_int_push(&tree, 2, 720);

    EXPECT_EQ(ws_binary_tree_int_maximum(tree.head)->value, 720);

    ws_binary_tree_destroy(int, &tree);
}

TEST(binary_tree, minimum)
{
    struct ws_binary_tree_int tree = ws_binary_tree_int_create();

    ws_binary_tree_int_push(&tree, 1, 69);
    ws_binary_tree_int_push(&tree, 0, 420);
    ws_binary_tree_int_push(&tree, 2, 720);

    EXPECT_EQ(ws_binary_tree_int_minimum(tree.head)->value, 420);

    ws_binary_tree_destroy(int, &tree);
}

