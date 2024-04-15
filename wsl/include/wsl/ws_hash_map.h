#ifndef WS_HASHMAP_H
#define WS_HASHMAP_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define __ws_hash_map_destroy_1(type, hash_map) ws_hash_map_##type##_destroy(hash_map, nullptr)
#define __ws_hash_map_destroy_2(type, hash_map, strategy) ws_hash_map_##type##_destroy(hash_map, strategy)
#define __ws_hash_map_destroy_select(_1, _2, selected, ...) selected
#define ws_hash_map_destroy(type, ...) __ws_hash_map_destroy_select(__VA_ARGS__, __ws_hash_map_destroy_2, __ws_hash_map_destroy_1, void)(type, __VA_ARGS__)

#define __ws_hash_map_tree_destroy_1(type, tree) __ws_hash_map_tree_##type##_destroy(tree, nullptr)
#define __ws_hash_map_tree_destroy_2(type, tree, strategy) __ws_hash_map_tree_##type##_destroy(tree, strategy)
#define __ws_hash_map_tree_destroy_select(_1, _2, selected, ...) selected
#define __ws_hash_map_tree_destroy(type, ...) __ws_hash_map_tree_destroy_select(__VA_ARGS__, __ws_hash_map_tree_destroy_2, __ws_hash_map_tree_destroy_1, void)(type, __VA_ARGS__)

#define __WS_IS_TRIVIALLY_HASHABLE(CHECK)                                                                                                                                                         \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, char)                                                                                                                                                  \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, double)                                                                                                                                                \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, float)                                                                                                                                                 \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, int)                                                                                                                                                   \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, long)                                                                                                                                                  \
    __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, short)                                                                                                                                                 \
    false

#define __WS_IS_TRIVIALLY_HASHABLE_TYPE(CHECK, TYPE) !strcmp(CHECK, #TYPE) ||

#ifndef WS_HASH_MAP_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL static
#endif

[[nodiscard]] WS_DECL size_t ws_hash_map_hash(void const* bytes, size_t length);

#ifndef WS_HASH_MAP_DEFINITION

#define WS_HASH_MAP(TYPE)                                                                                                                                                                         \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node                                                                                                                                                           \
{                                                                                                                                                                                                 \
    size_t key;                                                                                                                                                                                   \
    TYPE value;                                                                                                                                                                                   \
    struct __ws_hash_map_tree_##TYPE##_node* parent;                                                                                                                                              \
    struct __ws_hash_map_tree_##TYPE##_node* left;                                                                                                                                                \
    struct __ws_hash_map_tree_##TYPE##_node* right;                                                                                                                                               \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE                                                                                                                                                                  \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE##_node* head;                                                                                                                                                \
    size_t size;                                                                                                                                                                                  \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
WS_DECL size_t __ws_hash_map_tree_##TYPE##_size(struct __ws_hash_map_tree_##TYPE tree);                                                                                                           \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_search(struct __ws_hash_map_tree_##TYPE tree, size_t key);                                                           \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_minimum(struct __ws_hash_map_tree_##TYPE##_node* head);                                                              \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_maximum(struct __ws_hash_map_tree_##TYPE##_node* head);                                                              \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_successor(struct __ws_hash_map_tree_##TYPE##_node* head);                                                            \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_predecessor(struct __ws_hash_map_tree_##TYPE##_node* head);                                                          \
WS_DECL void __ws_hash_map_tree_##TYPE##_shift_nodes(struct __ws_hash_map_tree_##TYPE* tree, struct __ws_hash_map_tree_##TYPE##_node* lhs, struct __ws_hash_map_tree_##TYPE##_node* rhs);         \
WS_DECL void __ws_hash_map_tree_##TYPE##_push(struct __ws_hash_map_tree_##TYPE* tree, size_t key, TYPE value);                                                                                    \
WS_DECL TYPE __ws_hash_map_tree_##TYPE##_pop(struct __ws_hash_map_tree_##TYPE* tree, size_t key);                                                                                                 \
WS_DECL struct __ws_hash_map_tree_##TYPE __ws_hash_map_tree_##TYPE##_create();                                                                                                                    \
WS_DECL void __ws_hash_map_tree_##TYPE##_destroy_branch(struct __ws_hash_map_tree_##TYPE##_node* head, void(*strategy)(TYPE*));                                                                   \
WS_DECL void __ws_hash_map_tree_##TYPE##_destroy(struct __ws_hash_map_tree_##TYPE* tree, void(*strategy)(TYPE*));                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_##TYPE##_bucket                                                                                                                                                              \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE tree;                                                                                                                                                        \
    size_t size;                                                                                                                                                                                  \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
struct ws_hash_map_##TYPE                                                                                                                                                                         \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_##TYPE##_bucket* buckets;                                                                                                                                                \
    size_t size;                                                                                                                                                                                  \
    size_t capacity;                                                                                                                                                                              \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
[[nodiscard]] WS_DECL size_t ws_hash_map_##TYPE##_size(struct ws_hash_map_##TYPE hashMap);                                                                                                        \
[[nodiscard]] WS_DECL TYPE* ws_hash_map_##TYPE##_search_hashed(struct ws_hash_map_##TYPE hashmap, TYPE value);                                                                                    \
[[nodiscard]] WS_DECL TYPE* ws_hash_map_##TYPE##_search(struct ws_hash_map_##TYPE hashMap, size_t key);                                                                                           \
WS_DECL void ws_hash_map_##TYPE##_push_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value);                                                                                                    \
WS_DECL void ws_hash_map_##TYPE##_push(struct ws_hash_map_##TYPE* hashMap, size_t key, TYPE value);                                                                                               \
[[nodiscard]] WS_DECL TYPE ws_hash_map_##TYPE##_pop_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value);                                                                                       \
[[nodiscard]] WS_DECL TYPE ws_hash_map_##TYPE##_pop(struct ws_hash_map_##TYPE* hashMap, size_t key);                                                                                              \
[[nodiscard]] WS_DECL struct ws_hash_map_##TYPE ws_hash_map_##TYPE##_create();                                                                                                                    \
WS_DECL void ws_hash_map_##TYPE##_destroy(struct ws_hash_map_##TYPE* hashMap, void(*strategy)(TYPE*));

#else

#define WS_HASH_MAP(TYPE)                                                                                                                                                                         \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node                                                                                                                                                           \
{                                                                                                                                                                                                 \
    size_t key;                                                                                                                                                                                   \
    TYPE value;                                                                                                                                                                                   \
    struct __ws_hash_map_tree_##TYPE##_node* parent;                                                                                                                                              \
    struct __ws_hash_map_tree_##TYPE##_node* left;                                                                                                                                                \
    struct __ws_hash_map_tree_##TYPE##_node* right;                                                                                                                                               \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE                                                                                                                                                                  \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE##_node* head;                                                                                                                                                \
    size_t size;                                                                                                                                                                                  \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
WS_DECL size_t __ws_hash_map_tree_##TYPE##_size(struct __ws_hash_map_tree_##TYPE tree);                                                                                                           \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_search(struct __ws_hash_map_tree_##TYPE tree, size_t key);                                                           \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_minimum(struct __ws_hash_map_tree_##TYPE##_node* head);                                                              \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_maximum(struct __ws_hash_map_tree_##TYPE##_node* head);                                                              \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_successor(struct __ws_hash_map_tree_##TYPE##_node* head);                                                            \
WS_DECL struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_predecessor(struct __ws_hash_map_tree_##TYPE##_node* head);                                                          \
WS_DECL void __ws_hash_map_tree_##TYPE##_shift_nodes(struct __ws_hash_map_tree_##TYPE* tree, struct __ws_hash_map_tree_##TYPE##_node* lhs, struct __ws_hash_map_tree_##TYPE##_node* rhs);         \
WS_DECL void __ws_hash_map_tree_##TYPE##_push(struct __ws_hash_map_tree_##TYPE* tree, size_t key, TYPE value);                                                                                    \
WS_DECL TYPE __ws_hash_map_tree_##TYPE##_pop(struct __ws_hash_map_tree_##TYPE* tree, size_t key);                                                                                                 \
WS_DECL struct __ws_hash_map_tree_##TYPE __ws_hash_map_tree_##TYPE##_create();                                                                                                                    \
WS_DECL void __ws_hash_map_tree_##TYPE##_destroy_branch(struct __ws_hash_map_tree_##TYPE##_node* head, void(*strategy)(TYPE*));                                                                   \
WS_DECL void __ws_hash_map_tree_##TYPE##_destroy(struct __ws_hash_map_tree_##TYPE* tree, void(*strategy)(TYPE*));                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_##TYPE##_bucket                                                                                                                                                              \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE tree;                                                                                                                                                        \
    size_t size;                                                                                                                                                                                  \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
struct ws_hash_map_##TYPE                                                                                                                                                                         \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_##TYPE##_bucket* buckets;                                                                                                                                                \
    size_t size;                                                                                                                                                                                  \
    size_t capacity;                                                                                                                                                                              \
};                                                                                                                                                                                                \
                                                                                                                                                                                                  \
[[nodiscard]] WS_DECL size_t ws_hash_map_##TYPE##_size(struct ws_hash_map_##TYPE hashMap);                                                                                                        \
[[nodiscard]] WS_DECL TYPE* ws_hash_map_##TYPE##_search_hashed(struct ws_hash_map_##TYPE hashmap, TYPE value);                                                                                    \
[[nodiscard]] WS_DECL TYPE* ws_hash_map_##TYPE##_search(struct ws_hash_map_##TYPE hashMap, size_t key);                                                                                           \
WS_DECL void ws_hash_map_##TYPE##_push_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value);                                                                                                    \
WS_DECL void ws_hash_map_##TYPE##_push(struct ws_hash_map_##TYPE* hashMap, size_t key, TYPE value);                                                                                               \
[[nodiscard]] WS_DECL TYPE ws_hash_map_##TYPE##_pop_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value);                                                                                       \
[[nodiscard]] WS_DECL TYPE ws_hash_map_##TYPE##_pop(struct ws_hash_map_##TYPE* hashMap, size_t key);                                                                                              \
[[nodiscard]] WS_DECL struct ws_hash_map_##TYPE ws_hash_map_##TYPE##_create();                                                                                                                    \
WS_DECL void ws_hash_map_##TYPE##_destroy(struct ws_hash_map_##TYPE* hashMap, void(*strategy)(TYPE*));                                                                                            \
                                                                                                                                                                                                  \
size_t __ws_hash_map_tree_##TYPE##_size(struct __ws_hash_map_tree_##TYPE tree)                                                                                                                    \
{                                                                                                                                                                                                 \
    return tree.size;                                                                                                                                                                             \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_search(struct __ws_hash_map_tree_##TYPE tree, size_t key)                                                                    \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE##_node* node = tree.head;                                                                                                                                    \
                                                                                                                                                                                                  \
    while (node)                                                                                                                                                                                  \
    {                                                                                                                                                                                             \
        if (key == (node)->key)                                                                                                                                                                   \
        {                                                                                                                                                                                         \
            return (node);                                                                                                                                                                        \
        }                                                                                                                                                                                         \
                                                                                                                                                                                                  \
        if (key < (node)->key)                                                                                                                                                                    \
            node = (node)->left;                                                                                                                                                                  \
        else                                                                                                                                                                                      \
            node = (node)->right;                                                                                                                                                                 \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return nullptr;                                                                                                                                                                               \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_minimum(struct __ws_hash_map_tree_##TYPE##_node* head)                                                                       \
{                                                                                                                                                                                                 \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                                   \
                                                                                                                                                                                                  \
    while (head->left != nullptr)                                                                                                                                                                 \
    {                                                                                                                                                                                             \
        head = head->left;                                                                                                                                                                        \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return head;                                                                                                                                                                                  \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_maximum(struct __ws_hash_map_tree_##TYPE##_node* head)                                                                       \
{                                                                                                                                                                                                 \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                                   \
                                                                                                                                                                                                  \
    while (head->right != nullptr)                                                                                                                                                                \
    {                                                                                                                                                                                             \
        head = head->right;                                                                                                                                                                       \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return head;                                                                                                                                                                                  \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_successor(struct __ws_hash_map_tree_##TYPE##_node* head)                                                                     \
{                                                                                                                                                                                                 \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                                   \
                                                                                                                                                                                                  \
    if (head->right != nullptr)                                                                                                                                                                   \
    {                                                                                                                                                                                             \
        return __ws_hash_map_tree_##TYPE##_minimum(head->right);                                                                                                                                  \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node* parent = head->parent;                                                                                                                               \
                                                                                                                                                                                                  \
    while (parent != nullptr && head == parent->right)                                                                                                                                            \
    {                                                                                                                                                                                             \
        head = parent;                                                                                                                                                                            \
        parent = parent->parent;                                                                                                                                                                  \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return parent;                                                                                                                                                                                \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE##_node* __ws_hash_map_tree_##TYPE##_predecessor(struct __ws_hash_map_tree_##TYPE##_node* head)                                                                   \
{                                                                                                                                                                                                 \
    assert(head != nullptr && "NODE WAS NULL");                                                                                                                                                   \
                                                                                                                                                                                                  \
    if (head->left != nullptr)                                                                                                                                                                    \
    {                                                                                                                                                                                             \
        return __ws_hash_map_tree_##TYPE##_maximum(head->left);                                                                                                                                   \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node* parent = head->parent;                                                                                                                               \
                                                                                                                                                                                                  \
    while (parent != nullptr && head == parent->left)                                                                                                                                             \
    {                                                                                                                                                                                             \
        head = parent;                                                                                                                                                                            \
        parent = parent->parent;                                                                                                                                                                  \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return parent;                                                                                                                                                                                \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void __ws_hash_map_tree_##TYPE##_shift_nodes(struct __ws_hash_map_tree_##TYPE* tree, struct __ws_hash_map_tree_##TYPE##_node* lhs, struct __ws_hash_map_tree_##TYPE##_node* rhs)                  \
{                                                                                                                                                                                                 \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                                   \
    assert(lhs != nullptr && "LHS NODE WAS NULL");                                                                                                                                                \
                                                                                                                                                                                                  \
    if (lhs->parent == nullptr)                                                                                                                                                                   \
    {                                                                                                                                                                                             \
        tree->head = rhs;                                                                                                                                                                         \
    }                                                                                                                                                                                             \
    else                                                                                                                                                                                          \
    {                                                                                                                                                                                             \
        if (lhs == lhs->parent->left)                                                                                                                                                             \
            lhs->parent->left = rhs;                                                                                                                                                              \
        else                                                                                                                                                                                      \
            lhs->parent->right = rhs;                                                                                                                                                             \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    if (rhs != nullptr)                                                                                                                                                                           \
    {                                                                                                                                                                                             \
        rhs->parent = lhs->parent;                                                                                                                                                                \
    }                                                                                                                                                                                             \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void __ws_hash_map_tree_##TYPE##_push(struct __ws_hash_map_tree_##TYPE* tree, size_t key, TYPE value)                                                                                             \
{                                                                                                                                                                                                 \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                                   \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node* newNode = (struct __ws_hash_map_tree_##TYPE##_node*)                                                                                                 \
        malloc(sizeof(struct __ws_hash_map_tree_##TYPE##_node));                                                                                                                                  \
                                                                                                                                                                                                  \
    newNode->key    = key;                                                                                                                                                                        \
    newNode->value  = value;                                                                                                                                                                      \
    newNode->parent = nullptr;                                                                                                                                                                    \
    newNode->left   = nullptr;                                                                                                                                                                    \
    newNode->right  = nullptr;                                                                                                                                                                    \
                                                                                                                                                                                                  \
    tree->size += 1;                                                                                                                                                                              \
                                                                                                                                                                                                  \
    if (tree->head == nullptr)                                                                                                                                                                    \
    {                                                                                                                                                                                             \
        tree->head = newNode;                                                                                                                                                                     \
        return;                                                                                                                                                                                   \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node** node = &tree->head;                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE##_node** parentNode = node;                                                                                                                                  \
                                                                                                                                                                                                  \
    while (*node)                                                                                                                                                                                 \
    {                                                                                                                                                                                             \
        parentNode = node;                                                                                                                                                                        \
                                                                                                                                                                                                  \
        if (key < (*node)->key)                                                                                                                                                                   \
            node = &(*node)->left;                                                                                                                                                                \
        else                                                                                                                                                                                      \
            node = &(*node)->right;                                                                                                                                                               \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    newNode->parent = *parentNode;                                                                                                                                                                \
    *node = newNode;                                                                                                                                                                              \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
TYPE __ws_hash_map_tree_##TYPE##_pop(struct __ws_hash_map_tree_##TYPE* tree, size_t key)                                                                                                          \
{                                                                                                                                                                                                 \
    assert(tree->size && "TREE WAS EMPTY");                                                                                                                                                       \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node* node = __ws_hash_map_tree_##TYPE##_search(*tree, key);                                                                                               \
    assert(node && "CANNOT POP A NON EXISTING NODE");                                                                                                                                             \
                                                                                                                                                                                                  \
    TYPE returnValue = node->value;                                                                                                                                                               \
                                                                                                                                                                                                  \
    tree->size -= 1;                                                                                                                                                                              \
                                                                                                                                                                                                  \
    if (node->left == nullptr || node->right == nullptr)                                                                                                                                          \
    {                                                                                                                                                                                             \
        if (node->left == nullptr)                                                                                                                                                                \
        {                                                                                                                                                                                         \
            __ws_hash_map_tree_##TYPE##_shift_nodes(tree, node, node->right);                                                                                                                     \
        }                                                                                                                                                                                         \
        else if (node->right == nullptr)                                                                                                                                                          \
        {                                                                                                                                                                                         \
            __ws_hash_map_tree_##TYPE##_shift_nodes(tree, node, node->left);                                                                                                                      \
        }                                                                                                                                                                                         \
                                                                                                                                                                                                  \
        memset(node, 0, sizeof(struct __ws_hash_map_tree_##TYPE##_node));                                                                                                                         \
        assert(tree->head != node && "HOW DID YOU DO THAT");                                                                                                                                      \
        free(node);                                                                                                                                                                               \
                                                                                                                                                                                                  \
        return returnValue;                                                                                                                                                                       \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    struct __ws_hash_map_tree_##TYPE##_node* nodePredecessor = __ws_hash_map_tree_##TYPE##_predecessor(node);                                                                                     \
                                                                                                                                                                                                  \
    if (nodePredecessor->parent != node)                                                                                                                                                          \
    {                                                                                                                                                                                             \
        __ws_hash_map_tree_##TYPE##_shift_nodes(tree, nodePredecessor, nodePredecessor->left);                                                                                                    \
        nodePredecessor->left = node->left;                                                                                                                                                       \
        nodePredecessor->left->parent = nodePredecessor;                                                                                                                                          \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    __ws_hash_map_tree_##TYPE##_shift_nodes(tree, node, nodePredecessor);                                                                                                                         \
    nodePredecessor->right = node->right;                                                                                                                                                         \
    nodePredecessor->right->parent = nodePredecessor;                                                                                                                                             \
                                                                                                                                                                                                  \
    memset(node, 0, sizeof(struct __ws_hash_map_tree_##TYPE##_node));                                                                                                                             \
    assert(tree->head != node && "HOW DID YOU DO THAT");                                                                                                                                          \
    free(node);                                                                                                                                                                                   \
                                                                                                                                                                                                  \
    return returnValue;                                                                                                                                                                           \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct __ws_hash_map_tree_##TYPE __ws_hash_map_tree_##TYPE##_create()                                                                                                                             \
{                                                                                                                                                                                                 \
    struct __ws_hash_map_tree_##TYPE tree =                                                                                                                                                       \
    {                                                                                                                                                                                             \
        .head     = nullptr,                                                                                                                                                                      \
        .size     = 0                                                                                                                                                                             \
    };                                                                                                                                                                                            \
                                                                                                                                                                                                  \
    return tree;                                                                                                                                                                                  \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void __ws_hash_map_tree_##TYPE##_destroy_branch(struct __ws_hash_map_tree_##TYPE##_node* head, void(*strategy)(TYPE*))                                                                            \
{                                                                                                                                                                                                 \
    if (head == nullptr)                                                                                                                                                                          \
    {                                                                                                                                                                                             \
        return;                                                                                                                                                                                   \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    assert(head != head->left && "HOW DID YOU DO THAT");                                                                                                                                          \
    __ws_hash_map_tree_##TYPE##_destroy_branch(head->left, strategy);                                                                                                                             \
                                                                                                                                                                                                  \
    assert(head != head->right && "HOW DID YOU DO THAT");                                                                                                                                         \
    __ws_hash_map_tree_##TYPE##_destroy_branch(head->right, strategy);                                                                                                                            \
                                                                                                                                                                                                  \
    if (strategy != nullptr)                                                                                                                                                                      \
    {                                                                                                                                                                                             \
        strategy(&head->value);                                                                                                                                                                   \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    memset(head, 0, sizeof(struct __ws_hash_map_tree_##TYPE##_node));                                                                                                                             \
    free(head);                                                                                                                                                                                   \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void __ws_hash_map_tree_##TYPE##_destroy(struct __ws_hash_map_tree_##TYPE* tree, void(*strategy)(TYPE*))                                                                                          \
{                                                                                                                                                                                                 \
    assert(tree != nullptr && "TREE WAS NULL");                                                                                                                                                   \
    __ws_hash_map_tree_##TYPE##_destroy_branch(tree->head, strategy);                                                                                                                             \
    memset(tree, 0, sizeof(struct __ws_hash_map_tree_##TYPE));                                                                                                                                    \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
size_t ws_hash_map_##TYPE##_size(struct ws_hash_map_##TYPE hashMap)                                                                                                                               \
{                                                                                                                                                                                                 \
    return hashMap.size;                                                                                                                                                                          \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
TYPE* ws_hash_map_##TYPE##_search(struct ws_hash_map_##TYPE hashMap, size_t key)                                                                                                                  \
{                                                                                                                                                                                                 \
    for (size_t index = 0llu; index != hashMap.capacity; index += 1)                                                                                                                              \
    {                                                                                                                                                                                             \
        struct __ws_hash_map_##TYPE##_bucket workingBucket = hashMap.buckets[index];                                                                                                              \
        struct __ws_hash_map_tree_##TYPE##_node* result = __ws_hash_map_tree_##TYPE##_search(workingBucket.tree, key);                                                                            \
                                                                                                                                                                                                  \
        if (result != nullptr)                                                                                                                                                                    \
        {                                                                                                                                                                                         \
            return &result->value;                                                                                                                                                                \
        }                                                                                                                                                                                         \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return nullptr;                                                                                                                                                                               \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
TYPE* ws_hash_map_##TYPE##_search_hashed(struct ws_hash_map_##TYPE hashmap, TYPE value)                                                                                                           \
{                                                                                                                                                                                                 \
    if (!(__WS_IS_TRIVIALLY_HASHABLE(#TYPE)))                                                                                                                                                     \
    {                                                                                                                                                                                             \
        assert(false && "SINCE THIS LANGUAGE IS GARBAGE, YOUR TYPE CANNOT BE HASHED TRIVALLY! :(");                                                                                               \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    char bytes[sizeof(TYPE)] = {0};                                                                                                                                                               \
    memcpy(bytes, &value, sizeof(TYPE));                                                                                                                                                          \
    size_t hash = ws_hash_map_hash(bytes, sizeof(TYPE));                                                                                                                                          \
    return ws_hash_map_##TYPE##_search(hashmap, hash);                                                                                                                                            \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void ws_hash_map_##TYPE##_push(struct ws_hash_map_##TYPE* hashMap, size_t key, TYPE value)                                                                                                        \
{                                                                                                                                                                                                 \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                                                                                     \
                                                                                                                                                                                                  \
    TYPE* result = ws_hash_map_##TYPE##_search(*hashMap, key);                                                                                                                                    \
                                                                                                                                                                                                  \
    if (result != nullptr)                                                                                                                                                                        \
    {                                                                                                                                                                                             \
        *result = value;                                                                                                                                                                          \
        return;                                                                                                                                                                                   \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    struct __ws_hash_map_##TYPE##_bucket* workingBucket = &hashMap->buckets[key & (hashMap->capacity - 1)];                                                                                       \
    __ws_hash_map_tree_##TYPE##_push(&workingBucket->tree, key, value);                                                                                                                           \
                                                                                                                                                                                                  \
    workingBucket->size += 1;                                                                                                                                                                     \
    hashMap->size += 1;                                                                                                                                                                           \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void ws_hash_map_##TYPE##_push_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value)                                                                                                             \
{                                                                                                                                                                                                 \
    if (!(__WS_IS_TRIVIALLY_HASHABLE(#TYPE)))                                                                                                                                                     \
    {                                                                                                                                                                                             \
        assert(false && "SINCE THIS LANGUAGE IS GARBAGE, YOUR TYPE CANNOT BE HASHED TRIVALLY! :(");                                                                                               \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    char bytes[sizeof(TYPE)] = {0};                                                                                                                                                               \
    memcpy(bytes, &value, sizeof(TYPE));                                                                                                                                                          \
    size_t hash = ws_hash_map_hash(bytes, sizeof(TYPE));                                                                                                                                          \
    ws_hash_map_##TYPE##_push(hashmap, hash, value);                                                                                                                                              \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
TYPE ws_hash_map_##TYPE##_pop(struct ws_hash_map_##TYPE* hashMap, size_t key)                                                                                                                     \
{                                                                                                                                                                                                 \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                                                                                     \
                                                                                                                                                                                                  \
    struct __ws_hash_map_##TYPE##_bucket* workingBucket = &hashMap->buckets[key & (hashMap->capacity - 1)];                                                                                       \
    hashMap->size -= 1;                                                                                                                                                                           \
    workingBucket->size -= 1;                                                                                                                                                                     \
                                                                                                                                                                                                  \
    return __ws_hash_map_tree_##TYPE##_pop(&workingBucket->tree, key);                                                                                                                            \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
TYPE ws_hash_map_##TYPE##_pop_hashed(struct ws_hash_map_##TYPE* hashmap, TYPE value)                                                                                                              \
{                                                                                                                                                                                                 \
    if (!(__WS_IS_TRIVIALLY_HASHABLE(#TYPE)))                                                                                                                                                     \
    {                                                                                                                                                                                             \
        assert(false && "SINCE THIS LANGUAGE IS GARBAGE, YOUR TYPE CANNOT BE HASHED TRIVALLY! :(");                                                                                               \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    char bytes[sizeof(TYPE)] = {0};                                                                                                                                                               \
    memcpy(bytes, &value, sizeof(TYPE));                                                                                                                                                          \
    size_t hash = ws_hash_map_hash(bytes, sizeof(TYPE));                                                                                                                                          \
    return ws_hash_map_##TYPE##_pop(hashmap, hash);                                                                                                                                               \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
struct ws_hash_map_##TYPE ws_hash_map_##TYPE##_create()                                                                                                                                           \
{                                                                                                                                                                                                 \
    struct ws_hash_map_##TYPE hashMap =                                                                                                                                                           \
    {                                                                                                                                                                                             \
        .buckets  = nullptr,                                                                                                                                                                      \
        .size     = 0,                                                                                                                                                                            \
        .capacity = 16                                                                                                                                                                            \
    };                                                                                                                                                                                            \
                                                                                                                                                                                                  \
    hashMap.buckets = (struct __ws_hash_map_##TYPE##_bucket*)malloc(hashMap.capacity * sizeof(struct __ws_hash_map_##TYPE##_bucket));                                                             \
                                                                                                                                                                                                  \
    for (size_t index = 0llu; index != hashMap.capacity; index += 1)                                                                                                                              \
    {                                                                                                                                                                                             \
        hashMap.buckets[index].tree = __ws_hash_map_tree_##TYPE##_create();                                                                                                                       \
        hashMap.buckets[index].size = 0;                                                                                                                                                          \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    return hashMap;                                                                                                                                                                               \
}                                                                                                                                                                                                 \
                                                                                                                                                                                                  \
void ws_hash_map_##TYPE##_destroy(struct ws_hash_map_##TYPE* hashMap, void(*strategy)(TYPE*))                                                                                                     \
{                                                                                                                                                                                                 \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                                                                                     \
                                                                                                                                                                                                  \
    for (size_t index = 0llu; index != hashMap->capacity; index += 1)                                                                                                                             \
    {                                                                                                                                                                                             \
        struct __ws_hash_map_##TYPE##_bucket workingBucket = hashMap->buckets[index];                                                                                                             \
        __ws_hash_map_tree_##TYPE##_destroy(&workingBucket.tree, strategy);                                                                                                                       \
    }                                                                                                                                                                                             \
                                                                                                                                                                                                  \
    free(hashMap->buckets);                                                                                                                                                                       \
    memset(hashMap, 0, sizeof(struct ws_hash_map_##TYPE));                                                                                                                                        \
}

// MurmurHash: https://en.wikipedia.org/wiki/MurmurHash
size_t ws_hash_map_hash(void const* bytes, size_t length)
{
    const unsigned long long m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;
    const unsigned long long seed = 69;

    unsigned long long h = seed ^ (length * m);

    const unsigned long long* data = (const unsigned long long*)bytes;
    const unsigned long long* end = data + (length / 8);

    while (data != end)
    {
#ifdef PLATFORM_BIG_ENDIAN
        uint64 k = *data++;
        char *p = (char *)&k;
        char c;
        c = p[0]; p[0] = p[7]; p[7] = c;
        c = p[1]; p[1] = p[6]; p[6] = c;
        c = p[2]; p[2] = p[5]; p[5] = c;
        c = p[3]; p[3] = p[4]; p[4] = c;
#else
        unsigned long long k = *data++;
#endif

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch (length & 7)
    {
        case 7: h ^= (unsigned long long)(data2[6]) << 48; [[fallthrough]];
        case 6: h ^= (unsigned long long)(data2[5]) << 40; [[fallthrough]];
        case 5: h ^= (unsigned long long)(data2[4]) << 32; [[fallthrough]];
        case 4: h ^= (unsigned long long)(data2[3]) << 24; [[fallthrough]];
        case 3: h ^= (unsigned long long)(data2[2]) << 16; [[fallthrough]];
        case 2: h ^= (unsigned long long)(data2[1]) << 8;  [[fallthrough]];
        case 1: h ^= (unsigned long long)(data2[0]);

        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

#endif

#endif

