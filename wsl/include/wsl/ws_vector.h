#ifndef WS_VECTOR_H
#define WS_VECTOR_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ws_vector_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define ws_vector_sort_1(type, vector, predicate) ws_vector_##type##_bubble_sort(vector, predicate)
#define ws_vector_sort_2(type, vector, predicate, strategy) strategy(vector, predicate)
#define ws_vector_sort_select(_1, _2, _3, selected, ...) selected
#define ws_vector_sort(type, ...) ws_vector_sort_select(__VA_ARGS__, ws_vector_sort_2, ws_vector_sort_1, void)(type, __VA_ARGS__)

#define ws_vector_copy_1(type, destination, source) ws_vector_##type##_copy(destination, source, nullptr)
#define ws_vector_copy_2(type, destination, source, strategy) ws_vector_##type##_copy(destination, source, strategy)
#define ws_vector_copy_select(_1, _2, _3, selected, ...) selected
#define ws_vector_copy(type, ...) ws_vector_copy_select(__VA_ARGS__, ws_vector_copy_2, ws_vector_copy_1, void)(type, __VA_ARGS__)

#define ws_vector_search_1(type, vector, value) ws_vector_##type##_search(vector, value, nullptr)
#define ws_vector_search_2(type, vector, value, strategy) ws_vector_##type##_search(vector, value, strategy)
#define ws_vector_search_select(_1, _2, _3, selected, ...) selected
#define ws_vector_search(type, ...) ws_vector_search_select(__VA_ARGS__, ws_vector_search_2, ws_vector_search_1, void)(type, __VA_ARGS__)

#define ws_vector_destroy_1(type, vector) ws_vector_##type##_destroy(vector, nullptr)
#define ws_vector_destroy_2(type, vector, strategy) ws_vector_##type##_destroy(vector, strategy)
#define ws_vector_destroy_select(_1, _2, selected, ...) selected
#define ws_vector_destroy(type, ...) ws_vector_destroy_select(__VA_ARGS__, ws_vector_destroy_2, ws_vector_destroy_1, void)(type, __VA_ARGS__)

#define WS_VECTOR(TYPE)                                                                                                                 \
                                                                                                                                        \
struct ws_vector_##TYPE                                                                                                                 \
{                                                                                                                                       \
    size_t begin;                                                                                                                       \
    size_t end;                                                                                                                         \
    TYPE* data;                                                                                                                         \
    size_t size;                                                                                                                        \
    size_t capacity;                                                                                                                    \
};                                                                                                                                      \
                                                                                                                                        \
inline size_t ws_vector_##TYPE##_size(struct ws_vector_##TYPE vector)                                                                   \
{                                                                                                                                       \
    return vector.size;                                                                                                                 \
}                                                                                                                                       \
                                                                                                                                        \
inline bool ws_vector_##TYPE##_is_empty(struct ws_vector_##TYPE vector)                                                                 \
{                                                                                                                                       \
    return vector.size == 0;                                                                                                            \
}                                                                                                                                       \
                                                                                                                                        \
inline TYPE* ws_vector_##TYPE##_at(struct ws_vector_##TYPE vector, size_t position)                                                     \
{                                                                                                                                       \
    assert(position < vector.size && "INDEX OUT OF BOUNDS");                                                                            \
    return &vector.data[position];                                                                                                      \
}                                                                                                                                       \
                                                                                                                                        \
inline TYPE* ws_vector_##TYPE##_front(struct ws_vector_##TYPE vector)                                                                   \
{                                                                                                                                       \
    return &vector.data[0];                                                                                                             \
}                                                                                                                                       \
                                                                                                                                        \
inline TYPE* ws_vector_##TYPE##_back(struct ws_vector_##TYPE vector)                                                                    \
{                                                                                                                                       \
    return &vector.data[vector.end];                                                                                                    \
}                                                                                                                                       \
                                                                                                                                        \
[[nodiscard]]inline TYPE* ws_vector_##TYPE##_search(struct ws_vector_##TYPE vector, TYPE value,                                         \
        int(*predicate)(TYPE const*, TYPE const*))                                                                                      \
{                                                                                                                                       \
    for (size_t index = 0llu; index != vector.size; index += 1)                                                                         \
    {                                                                                                                                   \
        if (predicate != nullptr)                                                                                                       \
        {                                                                                                                               \
            if (predicate(&vector.data[index], &value))                                                                                 \
            {                                                                                                                           \
                return &vector.data[index];                                                                                             \
            }                                                                                                                           \
        }                                                                                                                               \
        else if (vector.data[index] == value)                                                                                           \
        {                                                                                                                               \
            return &vector.data[index];                                                                                                 \
        }                                                                                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    return nullptr;                                                                                                                     \
}                                                                                                                                       \
                                                                                                                                        \
inline void ws_vector_##TYPE##_copy(struct ws_vector_##TYPE* destination, struct ws_vector_##TYPE const* source, void(*strategy)(TYPE*))\
{                                                                                                                                       \
    if (ws_vector_##TYPE##_is_empty(*source))                                                                                           \
    {                                                                                                                                   \
        return;                                                                                                                         \
    }                                                                                                                                   \
                                                                                                                                        \
    if (!ws_vector_##TYPE##_is_empty(*destination) && strategy != nullptr)                                                              \
    {                                                                                                                                   \
        for (size_t index = 0llu; index != destination->size; index += 1)                                                               \
        {                                                                                                                               \
            strategy(&destination->data[index]);                                                                                        \
        }                                                                                                                               \
                                                                                                                                        \
        free(destination->data);                                                                                                        \
    }                                                                                                                                   \
                                                                                                                                        \
    destination->size     = source->size;                                                                                               \
    destination->capacity = source->capacity;                                                                                           \
    destination->begin    = source->begin;                                                                                              \
    destination->end      = source->end;                                                                                                \
    destination->data     = (TYPE*)malloc(destination->capacity * sizeof(TYPE));                                                        \
                                                                                                                                        \
    memcpy(destination->data, source->data, destination->capacity * sizeof(TYPE));                                                      \
}                                                                                                                                       \
                                                                                                                                        \
inline void ws_vector_##TYPE##_realloc(struct ws_vector_##TYPE* vector)                                                                 \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
                                                                                                                                        \
    TYPE* oldData = vector->data;                                                                                                       \
    vector->capacity += vector->capacity;                                                                                               \
    vector->data = (TYPE*)malloc(vector->capacity * sizeof(TYPE));                                                                      \
    memset(vector->data, 0, vector->capacity * sizeof(TYPE));                                                                           \
    memcpy(vector->data, oldData, vector->size * sizeof(TYPE));                                                                         \
                                                                                                                                        \
    free(oldData);                                                                                                                      \
}                                                                                                                                       \
                                                                                                                                        \
inline void ws_vector_##TYPE##_push(struct ws_vector_##TYPE* vector, TYPE value)                                                        \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
                                                                                                                                        \
    if (vector->size >= vector->capacity) ws_vector_##TYPE##_realloc(vector);                                                           \
    if (vector->data == nullptr) vector->data = (TYPE*)malloc(vector->capacity * sizeof(TYPE));                                         \
                                                                                                                                        \
    memcpy(&vector->data[vector->size++], &value, sizeof(TYPE));                                                                        \
    vector->end = vector->size - 1;                                                                                                     \
}                                                                                                                                       \
                                                                                                                                        \
[[nodiscard]]inline TYPE* ws_vector_##TYPE##_pop(struct ws_vector_##TYPE* vector)                                                       \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
    assert(vector->size && "TRIED TO POP AN EMPTY VECTOR");                                                                             \
    vector->end = --vector->size;                                                                                                       \
    return &vector->data[vector->end];                                                                                                  \
}                                                                                                                                       \
                                                                                                                                        \
[[nodiscard]]inline struct ws_vector_##TYPE ws_vector_##TYPE##_create(size_t count, ...)                                                \
{                                                                                                                                       \
    struct ws_vector_##TYPE vector =                                                                                                    \
    {                                                                                                                                   \
        .data     = nullptr,                                                                                                            \
        .size     = 0,                                                                                                                  \
        .capacity = 1,                                                                                                                  \
    };                                                                                                                                  \
                                                                                                                                        \
    va_list values = {};                                                                                                                \
    va_start(values, count);                                                                                                            \
                                                                                                                                        \
    for (size_t index = 0llu; index != count; index += 1)                                                                               \
    {                                                                                                                                   \
        ws_vector_##TYPE##_push(&vector, va_arg(values, TYPE));                                                                         \
    }                                                                                                                                   \
                                                                                                                                        \
    va_end(values);                                                                                                                     \
                                                                                                                                        \
    return vector;                                                                                                                      \
}                                                                                                                                       \
                                                                                                                                        \
inline void ws_vector_##TYPE##_destroy(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*))                                         \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
                                                                                                                                        \
    if (strategy != nullptr)                                                                                                            \
    {                                                                                                                                   \
        for (size_t index = 0llu; index != vector->size; index += 1)                                                                    \
        {                                                                                                                               \
            strategy(&vector->data[index]);                                                                                             \
        }                                                                                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    free(vector->data);                                                                                                                 \
    memset(vector, 0, sizeof(struct ws_vector_##TYPE));                                                                                 \
}

#endif

