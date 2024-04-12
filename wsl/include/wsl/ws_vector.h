#ifndef WS_VECTOR_H
#define WS_VECTOR_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ws_vector_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define __ws_vector_sort_1(type, vector, predicate) ws_vector_##type##_sort(vector, predicate)
#define __ws_vector_sort_2(type, vector, predicate, strategy) strategy(vector, predicate)
#define __ws_vector_sort_select(_1, _2, _3, selected, ...) selected
#define ws_vector_sort(type, ...) __ws_vector_sort_select(__VA_ARGS__, __ws_vector_sort_2, __ws_vector_sort_1, void)(type, __VA_ARGS__)

#define __ws_vector_copy_1(type, destination, source) ws_vector_##type##_copy(destination, source, nullptr)
#define __ws_vector_copy_2(type, destination, source, strategy) ws_vector_##type##_copy(destination, source, strategy)
#define __ws_vector_copy_select(_1, _2, _3, selected, ...) selected
#define ws_vector_copy(type, ...) __ws_vector_copy_select(__VA_ARGS__, __ws_vector_copy_2, __ws_vector_copy_1, void)(type, __VA_ARGS__)

#define __ws_vector_search_1(type, vector, value) ws_vector_##type##_search(vector, value, nullptr)
#define __ws_vector_search_2(type, vector, value, strategy) ws_vector_##type##_search(vector, value, strategy)
#define __ws_vector_search_select(_1, _2, _3, selected, ...) selected
#define ws_vector_search(type, ...) __ws_vector_search_select(__VA_ARGS__, __ws_vector_search_2, __ws_vector_search_1, void)(type, __VA_ARGS__)

#define __ws_vector_clear_1(type, vector) ws_vector_##type##_clear(vector, nullptr)
#define __ws_vector_clear_2(type, vector, strategy) ws_vector_##type##_clear(vector, strategy)
#define __ws_vector_clear_select(_1, _2, selected, ...) selected
#define ws_vector_clear(type, ...) __ws_vector_clear_select(__VA_ARGS__, __ws_vector_clear_2, __ws_vector_clear_1, void)(type, __VA_ARGS__)

#define __ws_vector_destroy_1(type, vector) ws_vector_##type##_destroy(vector, nullptr)
#define __ws_vector_destroy_2(type, vector, strategy) ws_vector_##type##_destroy(vector, strategy)
#define __ws_vector_destroy_select(_1, _2, selected, ...) selected
#define ws_vector_destroy(type, ...) __ws_vector_destroy_select(__VA_ARGS__, __ws_vector_destroy_2, __ws_vector_destroy_1, void)(type, __VA_ARGS__)

#ifndef WS_VECTOR_DEFINITION

#define WS_VECTOR(TYPE)                                                                                                                             \
                                                                                                                                                    \
struct ws_vector_##TYPE                                                                                                                             \
{                                                                                                                                                   \
    size_t begin;                                                                                                                                   \
    size_t end;                                                                                                                                     \
    size_t elementSize;                                                                                                                             \
    TYPE* data;                                                                                                                                     \
    size_t size;                                                                                                                                    \
    size_t capacity;                                                                                                                                \
};                                                                                                                                                  \
                                                                                                                                                    \
[[nodiscard]] size_t ws_vector_##TYPE##_size(struct ws_vector_##TYPE vector);                                                                       \
[[nodiscard]] bool ws_vector_##TYPE##_is_empty(struct ws_vector_##TYPE vector);                                                                     \
[[nodiscard]] TYPE* ws_vector_##TYPE##_at(struct ws_vector_##TYPE vector, size_t position);                                                         \
[[nodiscard]] TYPE* ws_vector_##TYPE##_front(struct ws_vector_##TYPE vector);                                                                       \
[[nodiscard]] TYPE* ws_vector_##TYPE##_back(struct ws_vector_##TYPE vector);                                                                        \
[[nodiscard]] TYPE* ws_vector_##TYPE##_search(struct ws_vector_##TYPE vector, TYPE value, int(*predicate)(TYPE const*, TYPE const*));               \
void ws_vector_##TYPE##_sort(struct ws_vector_##TYPE* vector, int(*predicate)(TYPE const*, TYPE const*));                                           \
void ws_vector_##TYPE##_copy(struct ws_vector_##TYPE* destination, struct ws_vector_##TYPE const* source, void(*strategy)(TYPE*));                  \
void ws_vector_##TYPE##_clear(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*));                                                             \
void __ws_vector_##TYPE##_realloc(struct ws_vector_##TYPE* vector);                                                                                 \
void ws_vector_##TYPE##_push(struct ws_vector_##TYPE* vector, TYPE value);                                                                          \
[[nodiscard]] TYPE ws_vector_##TYPE##_pop(struct ws_vector_##TYPE* vector);                                                                         \
[[nodiscard]] struct ws_vector_##TYPE ws_vector_##TYPE##_create(size_t count, ...);                                                                 \
void ws_vector_##TYPE##_destroy(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*));

#else

#define WS_VECTOR(TYPE)                                                                                                                             \
                                                                                                                                                    \
struct ws_vector_##TYPE                                                                                                                             \
{                                                                                                                                                   \
    size_t begin;                                                                                                                                   \
    size_t end;                                                                                                                                     \
    size_t elementSize;                                                                                                                             \
    TYPE* data;                                                                                                                                     \
    size_t size;                                                                                                                                    \
    size_t capacity;                                                                                                                                \
};                                                                                                                                                  \
                                                                                                                                                    \
size_t ws_vector_##TYPE##_size(struct ws_vector_##TYPE vector)                                                                                      \
{                                                                                                                                                   \
    return vector.size;                                                                                                                             \
}                                                                                                                                                   \
                                                                                                                                                    \
bool ws_vector_##TYPE##_is_empty(struct ws_vector_##TYPE vector)                                                                                    \
{                                                                                                                                                   \
    return vector.size == 0;                                                                                                                        \
}                                                                                                                                                   \
                                                                                                                                                    \
TYPE* ws_vector_##TYPE##_at(struct ws_vector_##TYPE vector, size_t position)                                                                        \
{                                                                                                                                                   \
    assert(position < vector.size && "INDEX OUT OF BOUNDS");                                                                                        \
    return &vector.data[position];                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
TYPE* ws_vector_##TYPE##_front(struct ws_vector_##TYPE vector)                                                                                      \
{                                                                                                                                                   \
    return &vector.data[0];                                                                                                                         \
}                                                                                                                                                   \
                                                                                                                                                    \
TYPE* ws_vector_##TYPE##_back(struct ws_vector_##TYPE vector)                                                                                       \
{                                                                                                                                                   \
    return &vector.data[vector.end];                                                                                                                \
}                                                                                                                                                   \
                                                                                                                                                    \
TYPE* ws_vector_##TYPE##_search(struct ws_vector_##TYPE vector, TYPE value, int(*predicate)(TYPE const*, TYPE const*))                              \
{                                                                                                                                                   \
    for (size_t index = 0llu; index != vector.size; index += 1)                                                                                     \
    {                                                                                                                                               \
        if (predicate != nullptr && predicate(&vector.data[index], &value))                                                                         \
        {                                                                                                                                           \
            return &vector.data[index];                                                                                                             \
        }                                                                                                                                           \
        else if (predicate == nullptr)                                                                                                              \
        {                                                                                                                                           \
            char valueLhs[sizeof(TYPE)] = {0};                                                                                                      \
            memcpy(valueLhs, &vector.data[index], sizeof(TYPE));                                                                                    \
            char valueRhs[sizeof(TYPE)] = {0};                                                                                                      \
            memcpy(valueRhs, &value, sizeof(TYPE));                                                                                                 \
                                                                                                                                                    \
            bool found = true;                                                                                                                      \
                                                                                                                                                    \
            for (size_t _index = 0llu; index != sizeof(TYPE); index += 1)                                                                           \
            {                                                                                                                                       \
                if (valueLhs[_index] != valueRhs[_index])                                                                                           \
                {                                                                                                                                   \
                    found = false;                                                                                                                  \
                    break;                                                                                                                          \
                }                                                                                                                                   \
            }                                                                                                                                       \
                                                                                                                                                    \
            if (found)                                                                                                                              \
            {                                                                                                                                       \
                return &vector.data[index];                                                                                                         \
            }                                                                                                                                       \
        }                                                                                                                                           \
    }                                                                                                                                               \
                                                                                                                                                    \
    return nullptr;                                                                                                                                 \
}                                                                                                                                                   \
                                                                                                                                                    \
void ws_vector_##TYPE##_sort(struct ws_vector_##TYPE* vector, int(*predicate)(TYPE const*, TYPE const*))                                            \
{                                                                                                                                                   \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                                         \
                                                                                                                                                    \
    while (true)                                                                                                                                    \
    {                                                                                                                                               \
        bool sorted = true;                                                                                                                         \
                                                                                                                                                    \
        for (size_t index = 1llu; index != vector->size; index += 1)                                                                                \
        {                                                                                                                                           \
            if (predicate(&vector->data[index], &vector->data[index - 1]))                                                                          \
            {                                                                                                                                       \
                TYPE copiedValue = { };                                                                                                             \
                memcpy(&copiedValue, &vector->data[index - 1], sizeof(TYPE));                                                                       \
                memcpy(&vector->data[index - 1], &vector->data[index], sizeof(TYPE));                                                               \
                memcpy(&vector->data[index], (TYPE*)&copiedValue, sizeof(TYPE));                                                                    \
                                                                                                                                                    \
                sorted = false;                                                                                                                     \
            }                                                                                                                                       \
        }                                                                                                                                           \
                                                                                                                                                    \
        if (sorted)                                                                                                                                 \
        {                                                                                                                                           \
            return;                                                                                                                                 \
        }                                                                                                                                           \
    }                                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
void ws_vector_##TYPE##_copy(struct ws_vector_##TYPE* destination, struct ws_vector_##TYPE const* source, void(*strategy)(TYPE*))                   \
{                                                                                                                                                   \
    if (ws_vector_##TYPE##_is_empty(*source))                                                                                                       \
    {                                                                                                                                               \
        return;                                                                                                                                     \
    }                                                                                                                                               \
                                                                                                                                                    \
    if (strategy != nullptr)                                                                                                                        \
    {                                                                                                                                               \
        for (size_t index = 0llu; index != destination->size; index += 1)                                                                           \
        {                                                                                                                                           \
            strategy(&destination->data[index]);                                                                                                    \
        }                                                                                                                                           \
    }                                                                                                                                               \
                                                                                                                                                    \
    free(destination->data);                                                                                                                        \
                                                                                                                                                    \
    destination->size     = source->size;                                                                                                           \
    destination->capacity = source->capacity;                                                                                                       \
    destination->begin    = source->begin;                                                                                                          \
    destination->end      = source->end;                                                                                                            \
    destination->data     = (TYPE*)malloc(destination->capacity * sizeof(TYPE));                                                                    \
                                                                                                                                                    \
    memcpy(destination->data, source->data, destination->capacity * sizeof(TYPE));                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
void ws_vector_##TYPE##_clear(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*))                                                              \
{                                                                                                                                                   \
    if (strategy != nullptr)                                                                                                                        \
    {                                                                                                                                               \
        for (size_t index = 0llu; index != vector->size; index += 1)                                                                                \
        {                                                                                                                                           \
            strategy(&vector->data[index]);                                                                                                         \
        }                                                                                                                                           \
    }                                                                                                                                               \
                                                                                                                                                    \
    memset(vector->data, 0, vector->capacity * sizeof(TYPE));                                                                                       \
    vector->size = 0;                                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
void __ws_vector_##TYPE##_realloc(struct ws_vector_##TYPE* vector)                                                                                  \
{                                                                                                                                                   \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                                         \
                                                                                                                                                    \
    TYPE* oldData = vector->data;                                                                                                                   \
    vector->capacity += vector->capacity;                                                                                                           \
    vector->data = (TYPE*)malloc(vector->capacity * sizeof(TYPE));                                                                                  \
    memset(vector->data, 0, vector->capacity * sizeof(TYPE));                                                                                       \
    memcpy(vector->data, oldData, vector->size * sizeof(TYPE));                                                                                     \
                                                                                                                                                    \
    free(oldData);                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
void ws_vector_##TYPE##_push(struct ws_vector_##TYPE* vector, TYPE value)                                                                           \
{                                                                                                                                                   \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                                         \
                                                                                                                                                    \
    if (vector->size >= vector->capacity) __ws_vector_##TYPE##_realloc(vector);                                                                     \
    if (vector->data == nullptr) vector->data = (TYPE*)malloc(vector->capacity * sizeof(TYPE));                                                     \
                                                                                                                                                    \
    memcpy(&vector->data[vector->size++], &value, sizeof(TYPE));                                                                                    \
    vector->end = vector->size - 1;                                                                                                                 \
}                                                                                                                                                   \
                                                                                                                                                    \
TYPE ws_vector_##TYPE##_pop(struct ws_vector_##TYPE* vector)                                                                                        \
{                                                                                                                                                   \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                                         \
    assert(vector->size && "TRIED TO POP AN EMPTY VECTOR");                                                                                         \
    vector->end = --vector->size;                                                                                                                   \
    return vector->data[vector->end];                                                                                                               \
}                                                                                                                                                   \
                                                                                                                                                    \
struct ws_vector_##TYPE ws_vector_##TYPE##_create(size_t count, ...)                                                                                \
{                                                                                                                                                   \
    struct ws_vector_##TYPE vector =                                                                                                                \
    {                                                                                                                                               \
        .begin       = 0,                                                                                                                           \
        .end         = 0,                                                                                                                           \
        .elementSize = sizeof(TYPE),                                                                                                                \
        .data        = nullptr,                                                                                                                     \
        .size        = 0,                                                                                                                           \
        .capacity    = 1,                                                                                                                           \
    };                                                                                                                                              \
                                                                                                                                                    \
    va_list values = {};                                                                                                                            \
    va_start(values, count);                                                                                                                        \
                                                                                                                                                    \
    for (size_t index = 0llu; index != count; index += 1)                                                                                           \
    {                                                                                                                                               \
        ws_vector_##TYPE##_push(&vector, va_arg(values, TYPE));                                                                                     \
    }                                                                                                                                               \
                                                                                                                                                    \
    va_end(values);                                                                                                                                 \
                                                                                                                                                    \
    return vector;                                                                                                                                  \
}                                                                                                                                                   \
                                                                                                                                                    \
void ws_vector_##TYPE##_destroy(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*))                                                            \
{                                                                                                                                                   \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                                         \
                                                                                                                                                    \
    if (strategy != nullptr)                                                                                                                        \
    {                                                                                                                                               \
        for (size_t index = 0llu; index != vector->size; index += 1)                                                                                \
        {                                                                                                                                           \
            strategy(&vector->data[index]);                                                                                                         \
        }                                                                                                                                           \
    }                                                                                                                                               \
                                                                                                                                                    \
    free(vector->data);                                                                                                                             \
    memset(vector, 0, sizeof(struct ws_vector_##TYPE));                                                                                             \
}

#endif

#endif

