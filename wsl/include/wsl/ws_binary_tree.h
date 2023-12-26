#ifndef WS_BINARY_TREE_H
#define WS_BINARY_TREE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define __ws_binary_tree_destroy_1(type, binary_tree) ws_binary_tree_##type##_destroy(binary_tree, nullptr)
#define __ws_binary_tree_destroy_2(type, binary_tree, strategy) ws_binary_tree_##type##_destroy(binary_tree, strategy)
#define __ws_binary_tree_destroy_select(_1, _2, selected, ...) selected
#define ws_binary_tree_destroy(type, ...) __ws_binary_tree_destroy_select(__VA_ARGS__, __ws_binary_tree_destroy_2, __ws_binary_tree_destroy_1, void)(type, __VA_ARGS__)

#ifndef WS_BINARY_TREE_DEFINITION

#define WS_BINARY_TREE(TYPE)                                                                                                                                                     \
                                                                                                                                                                                 \
struct ws_binary_tree_##TYPE##_node                                                                                                                                              \
{                                                                                                                                                                                \
    size_t key;                                                                                                                                                                  \
    TYPE value;                                                                                                                                                                  \
    struct ws_binary_tree_##TYPE##_node* parent;                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* left;                                                                                                                                   \
    struct ws_binary_tree_##TYPE##_node* right;                                                                                                                                  \
};                                                                                                                                                                               \
                                                                                                                                                                                 \
struct ws_binary_tree_##TYPE                                                                                                                                                     \
{                                                                                                                                                                                \
    struct ws_binary_tree_##TYPE##_node* head;                                                                                                                                   \
    size_t size;                                                                                                                                                                 \
};                                                                                                                                                                               \
                                                                                                                                                                                 \
size_t ws_binary_tree_##TYPE##_size(struct ws_binary_tree_##TYPE tree);                                                                                                          \
[[nodiscard]]struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_search(struct ws_binary_tree_##TYPE tree, size_t key);                                                 \
[[nodiscard]]struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_minimum(struct ws_binary_tree_##TYPE##_node* head);                                                    \
[[nodiscard]]struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_maximum(struct ws_binary_tree_##TYPE##_node* head);                                                    \
[[nodiscard]]struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_successor(struct ws_binary_tree_##TYPE##_node* head);                                                  \
[[nodiscard]]struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_predecessor(struct ws_binary_tree_##TYPE##_node* head);                                                \
void ws_binary_tree_##TYPE##_shift_nodes(struct ws_binary_tree_##TYPE* tree, struct ws_binary_tree_##TYPE##_node* lhs, struct ws_binary_tree_##TYPE##_node* rhs);                \
void ws_binary_tree_##TYPE##_push(struct ws_binary_tree_##TYPE* tree, size_t key, TYPE value);                                                                                   \
[[nodiscard]]TYPE ws_binary_tree_##TYPE##_pop(struct ws_binary_tree_##TYPE* tree, size_t key);                                                                                   \
[[nodiscard]]struct ws_binary_tree_##TYPE ws_binary_tree_##TYPE##_create();                                                                                                      \
void ws_binary_tree_##TYPE##_destroy_branch(struct ws_binary_tree_##TYPE##_node* head, void(*strategy)(TYPE*));                                                                  \
void ws_binary_tree_##TYPE##_destroy(struct ws_binary_tree_##TYPE* tree, void(*strategy)(TYPE*));

#else

#define WS_DECLARATION inline

#define WS_BINARY_TREE(TYPE)                                                                                                                                                     \
                                                                                                                                                                                 \
struct ws_binary_tree_##TYPE##_node                                                                                                                                              \
{                                                                                                                                                                                \
    size_t key;                                                                                                                                                                  \
    TYPE value;                                                                                                                                                                  \
    struct ws_binary_tree_##TYPE##_node* parent;                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* left;                                                                                                                                   \
    struct ws_binary_tree_##TYPE##_node* right;                                                                                                                                  \
};                                                                                                                                                                               \
                                                                                                                                                                                 \
struct ws_binary_tree_##TYPE                                                                                                                                                     \
{                                                                                                                                                                                \
    struct ws_binary_tree_##TYPE##_node* head;                                                                                                                                   \
    size_t size;                                                                                                                                                                 \
};                                                                                                                                                                               \
                                                                                                                                                                                 \
WS_DECLARATION size_t ws_binary_tree_##TYPE##_size(struct ws_binary_tree_##TYPE tree)                                                                                            \
{                                                                                                                                                                                \
    return tree.size;                                                                                                                                                            \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_search(struct ws_binary_tree_##TYPE tree, size_t key)                                   \
{                                                                                                                                                                                \
    struct ws_binary_tree_##TYPE##_node* node = tree.head;                                                                                                                       \
                                                                                                                                                                                 \
    while (node)                                                                                                                                                                 \
    {                                                                                                                                                                            \
        if (key == (node)->key)                                                                                                                                                  \
        {                                                                                                                                                                        \
            return (node);                                                                                                                                                       \
        }                                                                                                                                                                        \
                                                                                                                                                                                 \
        if (key < (node)->key)                                                                                                                                                   \
            node = (node)->left;                                                                                                                                                 \
        else                                                                                                                                                                     \
            node = (node)->right;                                                                                                                                                \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    return nullptr;                                                                                                                                                              \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_minimum(struct ws_binary_tree_##TYPE##_node* head)                                      \
{                                                                                                                                                                                \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                  \
                                                                                                                                                                                 \
    while (head->left != nullptr)                                                                                                                                                \
    {                                                                                                                                                                            \
        head = head->left;                                                                                                                                                       \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    return head;                                                                                                                                                                 \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_maximum(struct ws_binary_tree_##TYPE##_node* head)                                      \
{                                                                                                                                                                                \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                  \
                                                                                                                                                                                 \
    while (head->right != nullptr)                                                                                                                                               \
    {                                                                                                                                                                            \
        head = head->right;                                                                                                                                                      \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    return head;                                                                                                                                                                 \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_successor(struct ws_binary_tree_##TYPE##_node* head)                                    \
{                                                                                                                                                                                \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                  \
                                                                                                                                                                                 \
    if (head->right != nullptr)                                                                                                                                                  \
    {                                                                                                                                                                            \
        return ws_binary_tree_##TYPE##_minimum(head->right);                                                                                                                     \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* parent = head->parent;                                                                                                                  \
                                                                                                                                                                                 \
    while (parent != nullptr && head == parent->right)                                                                                                                           \
    {                                                                                                                                                                            \
        head = parent;                                                                                                                                                           \
        parent = parent->parent;                                                                                                                                                 \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    return parent;                                                                                                                                                               \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE##_node* ws_binary_tree_##TYPE##_predecessor(struct ws_binary_tree_##TYPE##_node* head)                                  \
{                                                                                                                                                                                \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                  \
                                                                                                                                                                                 \
    if (head->left != nullptr)                                                                                                                                                   \
    {                                                                                                                                                                            \
        return ws_binary_tree_##TYPE##_maximum(head->left);                                                                                                                      \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* parent = head->parent;                                                                                                                  \
                                                                                                                                                                                 \
    while (parent != nullptr && head == parent->left)                                                                                                                            \
    {                                                                                                                                                                            \
        head = parent;                                                                                                                                                           \
        parent = parent->parent;                                                                                                                                                 \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    return parent;                                                                                                                                                               \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
WS_DECLARATION void ws_binary_tree_##TYPE##_shift_nodes(struct ws_binary_tree_##TYPE* tree, struct ws_binary_tree_##TYPE##_node* lhs, struct ws_binary_tree_##TYPE##_node* rhs)  \
{                                                                                                                                                                                \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                  \
    assert(lhs != nullptr && "LHS NODE WAS NULL");                                                                                                                               \
                                                                                                                                                                                 \
    if (lhs->parent == nullptr)                                                                                                                                                  \
    {                                                                                                                                                                            \
        tree->head = rhs;                                                                                                                                                        \
    }                                                                                                                                                                            \
    else                                                                                                                                                                         \
    {                                                                                                                                                                            \
        if (lhs == lhs->parent->left)                                                                                                                                            \
            lhs->parent->left = rhs;                                                                                                                                             \
        else                                                                                                                                                                     \
            lhs->parent->right = rhs;                                                                                                                                            \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    if (rhs != nullptr)                                                                                                                                                          \
    {                                                                                                                                                                            \
        rhs->parent = lhs->parent;                                                                                                                                               \
    }                                                                                                                                                                            \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
WS_DECLARATION void ws_binary_tree_##TYPE##_push(struct ws_binary_tree_##TYPE* tree, size_t key, TYPE value)                                                                     \
{                                                                                                                                                                                \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                  \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* newNode = (struct ws_binary_tree_##TYPE##_node*)                                                                                        \
        malloc(sizeof(struct ws_binary_tree_##TYPE##_node));                                                                                                                     \
                                                                                                                                                                                 \
    newNode->key    = key;                                                                                                                                                       \
    newNode->value  = value;                                                                                                                                                     \
    newNode->parent = nullptr;                                                                                                                                                   \
    newNode->left   = nullptr;                                                                                                                                                   \
    newNode->right  = nullptr;                                                                                                                                                   \
                                                                                                                                                                                 \
    tree->size += 1;                                                                                                                                                             \
                                                                                                                                                                                 \
    if (tree->head == nullptr)                                                                                                                                                   \
    {                                                                                                                                                                            \
        tree->head = newNode;                                                                                                                                                    \
        return;                                                                                                                                                                  \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node** node = &tree->head;                                                                                                                    \
    struct ws_binary_tree_##TYPE##_node** parentNode = node;                                                                                                                     \
                                                                                                                                                                                 \
    while (*node)                                                                                                                                                                \
    {                                                                                                                                                                            \
        parentNode = node;                                                                                                                                                       \
                                                                                                                                                                                 \
        if (key < (*node)->key)                                                                                                                                                  \
            node = &(*node)->left;                                                                                                                                               \
        else                                                                                                                                                                     \
            node = &(*node)->right;                                                                                                                                              \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    newNode->parent = *parentNode;                                                                                                                                               \
    *node = newNode;                                                                                                                                                             \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION TYPE ws_binary_tree_##TYPE##_pop(struct ws_binary_tree_##TYPE* tree, size_t key)                                                                     \
{                                                                                                                                                                                \
    assert(tree->size && "TREE WAS EMPTY");                                                                                                                                      \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* node = ws_binary_tree_##TYPE##_search(*tree, key);                                                                                      \
    assert(node && "CANNOT POP A NON EXISTING NODE");                                                                                                                            \
                                                                                                                                                                                 \
    TYPE returnValue = node->value;                                                                                                                                              \
                                                                                                                                                                                 \
    tree->size -= 1;                                                                                                                                                             \
                                                                                                                                                                                 \
    if (node->left == nullptr || node->right == nullptr)                                                                                                                         \
    {                                                                                                                                                                            \
        if (node->left == nullptr)                                                                                                                                               \
        {                                                                                                                                                                        \
            ws_binary_tree_##TYPE##_shift_nodes(tree, node, node->right);                                                                                                        \
        }                                                                                                                                                                        \
        else if (node->right == nullptr)                                                                                                                                         \
        {                                                                                                                                                                        \
            ws_binary_tree_##TYPE##_shift_nodes(tree, node, node->left);                                                                                                         \
        }                                                                                                                                                                        \
                                                                                                                                                                                 \
        memset(node, 0, sizeof(struct ws_binary_tree_##TYPE##_node));                                                                                                            \
        assert(tree->head != node && "HOW DID YOU DO THAT");                                                                                                                     \
        free(node);                                                                                                                                                              \
                                                                                                                                                                                 \
        return returnValue;                                                                                                                                                      \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    struct ws_binary_tree_##TYPE##_node* nodePredecessor = ws_binary_tree_##TYPE##_predecessor(node);                                                                            \
                                                                                                                                                                                 \
    if (nodePredecessor->parent != node)                                                                                                                                         \
    {                                                                                                                                                                            \
        ws_binary_tree_##TYPE##_shift_nodes(tree, nodePredecessor, nodePredecessor->left);                                                                                       \
        nodePredecessor->left = node->left;                                                                                                                                      \
        nodePredecessor->left->parent = nodePredecessor;                                                                                                                         \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    ws_binary_tree_##TYPE##_shift_nodes(tree, node, nodePredecessor);                                                                                                            \
    nodePredecessor->right = node->right;                                                                                                                                        \
    nodePredecessor->right->parent = nodePredecessor;                                                                                                                            \
                                                                                                                                                                                 \
    memset(node, 0, sizeof(struct ws_binary_tree_##TYPE##_node));                                                                                                                \
    assert(tree->head != node && "HOW DID YOU DO THAT");                                                                                                                         \
    free(node);                                                                                                                                                                  \
                                                                                                                                                                                 \
    return returnValue;                                                                                                                                                          \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
[[nodiscard]]WS_DECLARATION struct ws_binary_tree_##TYPE ws_binary_tree_##TYPE##_create()                                                                                        \
{                                                                                                                                                                                \
    struct ws_binary_tree_##TYPE tree =                                                                                                                                          \
    {                                                                                                                                                                            \
        .head     = nullptr,                                                                                                                                                     \
        .size     = 0                                                                                                                                                            \
    };                                                                                                                                                                           \
                                                                                                                                                                                 \
    return tree;                                                                                                                                                                 \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
WS_DECLARATION void ws_binary_tree_##TYPE##_destroy_branch(struct ws_binary_tree_##TYPE##_node* head, void(*strategy)(TYPE*))                                                    \
{                                                                                                                                                                                \
    if (head == nullptr)                                                                                                                                                         \
    {                                                                                                                                                                            \
        return;                                                                                                                                                                  \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    assert(head != head->left && "HOW DID YOU DO THAT");                                                                                                                         \
    ws_binary_tree_##TYPE##_destroy_branch(head->left, strategy);                                                                                                                \
                                                                                                                                                                                 \
    assert(head != head->right && "HOW DID YOU DO THAT");                                                                                                                        \
    ws_binary_tree_##TYPE##_destroy_branch(head->right, strategy);                                                                                                               \
                                                                                                                                                                                 \
    if (strategy != nullptr)                                                                                                                                                     \
    {                                                                                                                                                                            \
        strategy(&head->value);                                                                                                                                                  \
    }                                                                                                                                                                            \
                                                                                                                                                                                 \
    memset(head, 0, sizeof(struct ws_binary_tree_##TYPE##_node));                                                                                                                \
    free(head);                                                                                                                                                                  \
}                                                                                                                                                                                \
                                                                                                                                                                                 \
WS_DECLARATION void ws_binary_tree_##TYPE##_destroy(struct ws_binary_tree_##TYPE* tree, void(*strategy)(TYPE*))                                                                  \
{                                                                                                                                                                                \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                  \
    ws_binary_tree_##TYPE##_destroy_branch(tree->head, strategy);                                                                                                                \
    memset(tree, 0, sizeof(struct ws_binary_tree_##TYPE));                                                                                                                       \
}

#endif

#endif

