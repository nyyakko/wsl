#ifndef WS_LINKED_LIST_H
#define WS_LINKED_LIST_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ws_linked_list_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define __ws_linked_list_destroy_1(type, linked_list) ws_linked_list_##type##_destroy(linked_list, nullptr)
#define __ws_linked_list_destroy_2(type, linked_list, strategy) ws_linked_list_##type##_destroy(linked_list, strategy)
#define __ws_linked_list_destroy_select(_1, _2, selected, ...) selected
#define ws_linked_list_destroy(type, ...) __ws_linked_list_destroy_select(__VA_ARGS__, __ws_linked_list_destroy_2, __ws_linked_list_destroy_1, void)(type, __VA_ARGS__)

#ifndef WS_LINKED_LIST_DEFINITION

#define WS_LINKED_LIST(TYPE)                                                                                                                                                 \
                                                                                                                                                                             \
struct ws_linked_list_##TYPE##_node                                                                                                                                          \
{                                                                                                                                                                            \
    struct ws_linked_list_##TYPE##_node* previous;                                                                                                                           \
    struct ws_linked_list_##TYPE##_node* next;                                                                                                                               \
    TYPE value;                                                                                                                                                              \
};                                                                                                                                                                           \
                                                                                                                                                                             \
struct ws_linked_list_##TYPE                                                                                                                                                 \
{                                                                                                                                                                            \
    size_t size;                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* head;                                                                                                                               \
    struct ws_linked_list_##TYPE##_node* tail;                                                                                                                               \
};                                                                                                                                                                           \
                                                                                                                                                                             \
[[nodiscard]] size_t ws_linked_list_##TYPE##_size(struct ws_linked_list_##TYPE list);                                                                                        \
[[nodiscard]] TYPE* ws_linked_list_##TYPE##_front(struct ws_linked_list_##TYPE list);                                                                                        \
[[nodiscard]] TYPE* ws_linked_list_##TYPE##_back(struct ws_linked_list_##TYPE list);                                                                                         \
[[nodiscard]] TYPE ws_linked_list_##TYPE##_pop_front(struct ws_linked_list_##TYPE* list);                                                                                    \
[[nodiscard]] TYPE ws_linked_list_##TYPE##_pop_back(struct ws_linked_list_##TYPE* list);                                                                                     \
void ws_linked_list_##TYPE##_push_front(struct ws_linked_list_##TYPE* list, TYPE value);                                                                                     \
void ws_linked_list_##TYPE##_push_back(struct ws_linked_list_##TYPE* list, TYPE value);                                                                                      \
[[nodiscard]] struct ws_linked_list_##TYPE ws_linked_list_##TYPE##_create(size_t count, ...);                                                                                \
void ws_linked_list_##TYPE##_destroy(struct ws_linked_list_##TYPE* list, void(*strategy)(TYPE*));

#else

#define WS_LINKED_LIST(TYPE)                                                                                                                                                 \
                                                                                                                                                                             \
struct ws_linked_list_##TYPE##_node                                                                                                                                          \
{                                                                                                                                                                            \
    struct ws_linked_list_##TYPE##_node* previous;                                                                                                                           \
    struct ws_linked_list_##TYPE##_node* next;                                                                                                                               \
    TYPE value;                                                                                                                                                              \
};                                                                                                                                                                           \
                                                                                                                                                                             \
struct ws_linked_list_##TYPE                                                                                                                                                 \
{                                                                                                                                                                            \
    size_t size;                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* head;                                                                                                                               \
    struct ws_linked_list_##TYPE##_node* tail;                                                                                                                               \
};                                                                                                                                                                           \
                                                                                                                                                                             \
[[nodiscard]] size_t ws_linked_list_##TYPE##_size(struct ws_linked_list_##TYPE list);                                                                                        \
[[nodiscard]] TYPE* ws_linked_list_##TYPE##_front(struct ws_linked_list_##TYPE list);                                                                                        \
[[nodiscard]] TYPE* ws_linked_list_##TYPE##_back(struct ws_linked_list_##TYPE list);                                                                                         \
[[nodiscard]] TYPE ws_linked_list_##TYPE##_pop_front(struct ws_linked_list_##TYPE* list);                                                                                    \
[[nodiscard]] TYPE ws_linked_list_##TYPE##_pop_back(struct ws_linked_list_##TYPE* list);                                                                                     \
void ws_linked_list_##TYPE##_push_front(struct ws_linked_list_##TYPE* list, TYPE value);                                                                                     \
void ws_linked_list_##TYPE##_push_back(struct ws_linked_list_##TYPE* list, TYPE value);                                                                                      \
[[nodiscard]] struct ws_linked_list_##TYPE ws_linked_list_##TYPE##_create(size_t count, ...);                                                                                \
void ws_linked_list_##TYPE##_destroy(struct ws_linked_list_##TYPE* list, void(*strategy)(TYPE*));                                                                            \
                                                                                                                                                                             \
size_t ws_linked_list_##TYPE##_size(struct ws_linked_list_##TYPE list)                                                                                                       \
{                                                                                                                                                                            \
    return list.size;                                                                                                                                                        \
}                                                                                                                                                                            \
                                                                                                                                                                             \
TYPE* ws_linked_list_##TYPE##_front(struct ws_linked_list_##TYPE list)                                                                                                       \
{                                                                                                                                                                            \
    return &list.head->value;                                                                                                                                                \
}                                                                                                                                                                            \
                                                                                                                                                                             \
TYPE* ws_linked_list_##TYPE##_back(struct ws_linked_list_##TYPE list)                                                                                                        \
{                                                                                                                                                                            \
    return &list.tail->value;                                                                                                                                                \
}                                                                                                                                                                            \
                                                                                                                                                                             \
                                                                                                                                                                             \
TYPE ws_linked_list_##TYPE##_pop_front(struct ws_linked_list_##TYPE* list)                                                                                                   \
{                                                                                                                                                                            \
    assert(list != nullptr && "LINKED LIST POINTER WAS NULL");                                                                                                               \
    assert(list->head != nullptr && "LINKED LIST HEAD WAS NULL");                                                                                                            \
                                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* node = list->head;                                                                                                                  \
                                                                                                                                                                             \
    TYPE value = list->head->value;                                                                                                                                          \
    list->head = node->next ? node->next : nullptr;                                                                                                                          \
                                                                                                                                                                             \
    if (list->head != nullptr)                                                                                                                                               \
    {                                                                                                                                                                        \
        list->head->previous = nullptr;                                                                                                                                      \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    list->size -= 1;                                                                                                                                                         \
                                                                                                                                                                             \
    free(node);                                                                                                                                                              \
                                                                                                                                                                             \
    return value;                                                                                                                                                            \
}                                                                                                                                                                            \
                                                                                                                                                                             \
TYPE ws_linked_list_##TYPE##_pop_back(struct ws_linked_list_##TYPE* list)                                                                                                    \
{                                                                                                                                                                            \
    assert(list != nullptr && "LINKED LIST POINTER WAS NULL");                                                                                                               \
    assert(list->tail != nullptr && "LINKED LIST TAIL WAS NULL");                                                                                                            \
                                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* node = list->tail;                                                                                                                  \
                                                                                                                                                                             \
    TYPE value = list->tail->value;                                                                                                                                          \
    list->tail = node->previous ? node->previous : nullptr;                                                                                                                  \
                                                                                                                                                                             \
    if (list->tail != nullptr)                                                                                                                                               \
    {                                                                                                                                                                        \
        list->tail->next = nullptr;                                                                                                                                          \
    }                                                                                                                                                                        \
    else                                                                                                                                                                     \
    {                                                                                                                                                                        \
        list->head = nullptr;                                                                                                                                                \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    list->size -= 1;                                                                                                                                                         \
                                                                                                                                                                             \
    free(node);                                                                                                                                                              \
                                                                                                                                                                             \
    return value;                                                                                                                                                            \
}                                                                                                                                                                            \
                                                                                                                                                                             \
void ws_linked_list_##TYPE##_push_front(struct ws_linked_list_##TYPE* list, TYPE value)                                                                                      \
{                                                                                                                                                                            \
    assert(list != nullptr && "LINKED LIST POINTER WAS NULL");                                                                                                               \
                                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* newNode = (struct ws_linked_list_##TYPE##_node*)malloc(sizeof(struct ws_linked_list_##TYPE##_node));                                \
                                                                                                                                                                             \
    newNode->value = value;                                                                                                                                                  \
    list->size += 1;                                                                                                                                                         \
                                                                                                                                                                             \
    if (list->head != nullptr)                                                                                                                                               \
    {                                                                                                                                                                        \
        newNode->previous = nullptr;                                                                                                                                         \
        newNode->next = list->head;                                                                                                                                          \
                                                                                                                                                                             \
        list->head->previous = newNode;                                                                                                                                      \
        list->head = newNode;                                                                                                                                                \
                                                                                                                                                                             \
        return;                                                                                                                                                              \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    newNode->previous = nullptr;                                                                                                                                             \
    newNode->next = nullptr;                                                                                                                                                 \
                                                                                                                                                                             \
    list->head = newNode;                                                                                                                                                    \
    list->tail = newNode;                                                                                                                                                    \
}                                                                                                                                                                            \
                                                                                                                                                                             \
void ws_linked_list_##TYPE##_push_back(struct ws_linked_list_##TYPE* list, TYPE value)                                                                                       \
{                                                                                                                                                                            \
    assert(list != nullptr && "LINKED LIST POINTER WAS NULL");                                                                                                               \
                                                                                                                                                                             \
    struct ws_linked_list_##TYPE##_node* newNode = (struct ws_linked_list_##TYPE##_node*)malloc(sizeof(struct ws_linked_list_##TYPE##_node));                                \
                                                                                                                                                                             \
    newNode->value = value;                                                                                                                                                  \
    list->size += 1;                                                                                                                                                         \
                                                                                                                                                                             \
    if (list->tail != nullptr)                                                                                                                                               \
    {                                                                                                                                                                        \
        newNode->previous = list->tail;                                                                                                                                      \
        newNode->next = nullptr;                                                                                                                                             \
                                                                                                                                                                             \
        list->tail->next = newNode;                                                                                                                                          \
        list->tail = newNode;                                                                                                                                                \
                                                                                                                                                                             \
        return;                                                                                                                                                              \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    newNode->previous = nullptr;                                                                                                                                             \
    newNode->next = nullptr;                                                                                                                                                 \
                                                                                                                                                                             \
    list->head = newNode;                                                                                                                                                    \
    list->tail = newNode;                                                                                                                                                    \
}                                                                                                                                                                            \
                                                                                                                                                                             \
struct ws_linked_list_##TYPE ws_linked_list_##TYPE##_create(size_t count, ...)                                                                                               \
{                                                                                                                                                                            \
    struct ws_linked_list_##TYPE list =                                                                                                                                      \
    {                                                                                                                                                                        \
        .size = 0,                                                                                                                                                           \
        .head = nullptr,                                                                                                                                                     \
        .tail = nullptr                                                                                                                                                      \
    };                                                                                                                                                                       \
                                                                                                                                                                             \
    va_list values = {};                                                                                                                                                     \
    va_start(values, count);                                                                                                                                                 \
                                                                                                                                                                             \
    for (size_t index = 0llu; index != count; index += 1)                                                                                                                    \
    {                                                                                                                                                                        \
        ws_linked_list_##TYPE##_push_back(&list, va_arg(values, TYPE));                                                                                                      \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    va_end(values);                                                                                                                                                          \
                                                                                                                                                                             \
    return list;                                                                                                                                                             \
}                                                                                                                                                                            \
                                                                                                                                                                             \
void ws_linked_list_##TYPE##_destroy(struct ws_linked_list_##TYPE* list, void(*strategy)(TYPE*))                                                                             \
{                                                                                                                                                                            \
    assert(list != nullptr && "LINKED LIST POINTER WAS NULL");                                                                                                               \
                                                                                                                                                                             \
    for (struct ws_linked_list_##TYPE##_node* node = list->head; node != nullptr;)                                                                                           \
    {                                                                                                                                                                        \
        struct ws_linked_list_##TYPE##_node* nextNode = node->next;                                                                                                          \
                                                                                                                                                                             \
        if (strategy != nullptr)                                                                                                                                             \
        {                                                                                                                                                                    \
            strategy(&node->value);                                                                                                                                          \
        }                                                                                                                                                                    \
                                                                                                                                                                             \
        free(node);                                                                                                                                                          \
        node = nextNode;                                                                                                                                                     \
    }                                                                                                                                                                        \
                                                                                                                                                                             \
    memset(list, 0, sizeof(struct ws_linked_list_##TYPE));                                                                                                                   \
}

#endif

#endif

