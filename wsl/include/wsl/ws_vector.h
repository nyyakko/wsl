/*

                            Copyright <2023> <nyyakko@github>
                            
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
    associated documentation files (the “Software”), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
    OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

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

#define ws_vector_destroy_1(type, vector) ws_vector_##type##_destroy(vector, nullptr)
#define ws_vector_destroy_2(type, vector, strategy) ws_vector_##type##_destroy(vector, strategy)
#define ws_vector_destroy_select(_1, _2, selected, ...) selected
#define ws_vector_destroy(type, ...) ws_vector_destroy_select(__VA_ARGS__, ws_vector_destroy_2, ws_vector_destroy_1, void)(type, __VA_ARGS__)

#define WS_VECTOR(TYPE)                                                                                                                 \
                                                                                                                                        \
struct ws_vector_##TYPE                                                                                                                 \
{                                                                                                                                       \
    size_t size;                                                                                                                        \
    size_t capacity;                                                                                                                    \
    size_t begin;                                                                                                                       \
    size_t end;                                                                                                                         \
                                                                                                                                        \
    TYPE* data;                                                                                                                         \
};                                                                                                                                      \
                                                                                                                                        \
size_t ws_vector_##TYPE##_size(struct ws_vector_##TYPE vector)                                                                          \
{                                                                                                                                       \
    return vector.size;                                                                                                                 \
}                                                                                                                                       \
                                                                                                                                        \
bool ws_vector_##TYPE##_is_empty(struct ws_vector_##TYPE vector)                                                                        \
{                                                                                                                                       \
    return vector.size == 0;                                                                                                            \
}                                                                                                                                       \
                                                                                                                                        \
bool ws_vector_##TYPE##_is_sorted(struct ws_vector_##TYPE vector, int(*predicate)(TYPE const*, TYPE const*))                            \
{                                                                                                                                       \
    for (size_t index = 1llu; index != vector.size; index += 1)                                                                         \
    {                                                                                                                                   \
        if (!predicate(&vector.data[index - 1], &vector.data[index]))                                                                   \
        {                                                                                                                               \
            return false;                                                                                                               \
        }                                                                                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    return true;                                                                                                                        \
}                                                                                                                                       \
                                                                                                                                        \
TYPE* ws_vector_##TYPE##_at(struct ws_vector_##TYPE vector, size_t position)                                                            \
{                                                                                                                                       \
    assert(position < vector.size && "INDEX OUT OF BOUNDS");                                                                            \
    return &vector.data[position];                                                                                                      \
}                                                                                                                                       \
                                                                                                                                        \
TYPE* ws_vector_##TYPE##_front(struct ws_vector_##TYPE vector)                                                                          \
{                                                                                                                                       \
    return &vector.data[0];                                                                                                             \
}                                                                                                                                       \
                                                                                                                                        \
TYPE* ws_vector_##TYPE##_back(struct ws_vector_##TYPE vector)                                                                           \
{                                                                                                                                       \
    return &vector.data[vector.end];                                                                                                    \
}                                                                                                                                       \
                                                                                                                                        \
TYPE* ws_vector_##TYPE##_search(struct ws_vector_##TYPE vector, TYPE value, int(*predicate)(TYPE const*, TYPE const*))                  \
{                                                                                                                                       \
    for (size_t index = 0llu; index != vector.size; index += 1)                                                                         \
    {                                                                                                                                   \
        if (predicate(&vector.data[index], &value))                                                                                     \
        {                                                                                                                               \
            return &vector.data[index];                                                                                                 \
        }                                                                                                                               \
    }                                                                                                                                   \
                                                                                                                                        \
    return nullptr;                                                                                                                     \
}                                                                                                                                       \
                                                                                                                                        \
void ws_vector_##TYPE##_bubble_sort(struct ws_vector_##TYPE* vector, int(*predicate)(TYPE const*, TYPE const*))                         \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
    size_t counter = vector->size;                                                                                                      \
                                                                                                                                        \
    while (counter >= 1)                                                                                                                \
    {                                                                                                                                   \
        size_t current = 0llu;                                                                                                          \
                                                                                                                                        \
        for (size_t index = 1llu; index != vector->size; index += 1)                                                                    \
        {                                                                                                                               \
            if (predicate(&vector->data[index - 1], &vector->data[index]))                                                              \
            {                                                                                                                           \
                TYPE copiedValue = { };                                                                                                 \
                memcpy(&copiedValue, &vector->data[index - 1], sizeof(TYPE));                                                           \
                memcpy(&vector->data[index - 1], &vector->data[index], sizeof(TYPE));                                                   \
                memcpy(&vector->data[index], (TYPE*)&copiedValue, sizeof(TYPE));                                                        \
                                                                                                                                        \
                current = index;                                                                                                        \
            }                                                                                                                           \
        }                                                                                                                               \
                                                                                                                                        \
        counter = current;                                                                                                              \
    }                                                                                                                                   \
}                                                                                                                                       \
                                                                                                                                        \
void ws_vector_##TYPE##_copy(struct ws_vector_##TYPE* destination, struct ws_vector_##TYPE const* source, void(*strategy)(TYPE*))       \
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
void ws_vector_##TYPE##_realloc(struct ws_vector_##TYPE* vector)                                                                        \
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
void ws_vector_##TYPE##_push(struct ws_vector_##TYPE* vector, TYPE value)                                                               \
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
[[nodiscard]]TYPE* ws_vector_##TYPE##_pop(struct ws_vector_##TYPE* vector)                                                              \
{                                                                                                                                       \
    assert(vector != nullptr && "VECTOR POINTER WAS NULL");                                                                             \
    assert(vector->size && "TRIED TO POP AN EMPTY VECTOR");                                                                             \
    vector->end = --vector->size;                                                                                                       \
    return &vector->data[vector->end];                                                                                                  \
}                                                                                                                                       \
                                                                                                                                        \
[[nodiscard]]struct ws_vector_##TYPE ws_vector_##TYPE##_create(size_t count, ...)                                                       \
{                                                                                                                                       \
    struct ws_vector_##TYPE vector =                                                                                                    \
    {                                                                                                                                   \
        .size     = 0,                                                                                                                  \
        .capacity = 1,                                                                                                                  \
        .data     = nullptr                                                                                                             \
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
void ws_vector_##TYPE##_destroy(struct ws_vector_##TYPE* vector, void(*strategy)(TYPE*))                                                \
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
