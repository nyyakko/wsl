#ifndef WS_QUEUE_H
#define WS_QUEUE_H

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ws_queue_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define ws_queue_copy_1(type, destination, source) ws_queue_##type##_copy(destination, source, nullptr)
#define ws_queue_copy_2(type, destination, source, strategy) ws_queue_##type##_copy(destination, source, strategy)
#define ws_queue_copy_select(_1, _2, _3, selected, ...) selected
#define ws_queue_copy(type, ...) ws_queue_copy_select(__VA_ARGS__, ws_queue_copy_2, ws_queue_copy_1, void)(type, __VA_ARGS__)

#define ws_queue_destroy_1(type, queue) ws_queue_##type##_destroy(queue, nullptr)
#define ws_queue_destroy_2(type, queue, strategy) ws_queue_##type##_destroy(queue, strategy)
#define ws_queue_destroy_select(_1, _2, selected, ...) selected
#define ws_queue_destroy(type, ...) ws_queue_destroy_select(__VA_ARGS__, ws_queue_destroy_2, ws_queue_destroy_1, void)(type, __VA_ARGS__)

#define WS_QUEUE(TYPE)                                                                                                                   \
                                                                                                                                         \
struct ws_queue_##TYPE                                                                                                                   \
{                                                                                                                                        \
    size_t begin;                                                                                                                        \
    size_t end;                                                                                                                          \
    TYPE* data;                                                                                                                          \
    size_t size;                                                                                                                         \
    size_t capacity;                                                                                                                     \
};                                                                                                                                       \
                                                                                                                                         \
inline size_t ws_queue_##TYPE##_size(struct ws_queue_##TYPE queue)                                                                       \
{                                                                                                                                        \
    return queue.size;                                                                                                                   \
}                                                                                                                                        \
                                                                                                                                         \
inline bool ws_queue_##TYPE##_is_empty(struct ws_queue_##TYPE queue)                                                                     \
{                                                                                                                                        \
    return queue.size == 0;                                                                                                              \
}                                                                                                                                        \
                                                                                                                                         \
inline TYPE* ws_queue_##TYPE##_front(struct ws_queue_##TYPE queue)                                                                       \
{                                                                                                                                        \
    return &queue.data[queue.begin];                                                                                                     \
}                                                                                                                                        \
                                                                                                                                         \
inline TYPE* ws_queue_##TYPE##_back(struct ws_queue_##TYPE queue)                                                                        \
{                                                                                                                                        \
    return &queue.data[queue.end];                                                                                                       \
}                                                                                                                                        \
                                                                                                                                         \
inline TYPE* ws_queue_##TYPE##_search(struct ws_queue_##TYPE queue, TYPE value, bool(*predicate)(TYPE const*, TYPE const*))              \
{                                                                                                                                        \
    for (size_t index = 0llu; index != queue.size; index += 1)                                                                           \
    {                                                                                                                                    \
        if (predicate(&queue.data[index], &value))                                                                                       \
        {                                                                                                                                \
            return &queue.data[index];                                                                                                   \
        }                                                                                                                                \
    }                                                                                                                                    \
                                                                                                                                         \
    return nullptr;                                                                                                                      \
}                                                                                                                                        \
                                                                                                                                         \
inline void ws_queue_##TYPE##_copy(struct ws_queue_##TYPE* destination, struct ws_queue_##TYPE const* source, void(*strategy)(TYPE*))    \
{                                                                                                                                        \
    if (ws_queue_##TYPE##_is_empty(*source))                                                                                             \
    {                                                                                                                                    \
        return;                                                                                                                          \
    }                                                                                                                                    \
                                                                                                                                         \
    if (strategy != nullptr)                                                                                                             \
    {                                                                                                                                    \
        for (size_t index = 0llu; index != destination->size; index += 1)                                                                \
        {                                                                                                                                \
            strategy(&destination->data[index]);                                                                                         \
        }                                                                                                                                \
    }                                                                                                                                    \
                                                                                                                                         \
    free(destination->data);                                                                                                             \
                                                                                                                                         \
    destination->size     = source->size;                                                                                                \
    destination->capacity = source->capacity;                                                                                            \
    destination->begin    = source->begin;                                                                                               \
    destination->end      = source->end;                                                                                                 \
    destination->data     = (TYPE*)malloc(destination->capacity * sizeof(TYPE));                                                         \
                                                                                                                                         \
    memcpy(destination->data, source->data, destination->capacity * sizeof(TYPE));                                                       \
}                                                                                                                                        \
                                                                                                                                         \
inline void ws_queue_##TYPE##_realloc(struct ws_queue_##TYPE* queue)                                                                     \
{                                                                                                                                        \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                \
                                                                                                                                         \
    TYPE* oldData = queue->data;                                                                                                         \
    queue->capacity += queue->capacity;                                                                                                  \
    queue->data = (TYPE*)malloc(queue->capacity * sizeof(TYPE));                                                                         \
    memset(queue->data, 0, queue->capacity * sizeof(TYPE));                                                                              \
    memcpy(queue->data, oldData, queue->size * sizeof(TYPE));                                                                            \
                                                                                                                                         \
    free(oldData);                                                                                                                       \
}                                                                                                                                        \
                                                                                                                                         \
inline void ws_queue_##TYPE##_push(struct ws_queue_##TYPE* queue, TYPE value)                                                            \
{                                                                                                                                        \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                \
                                                                                                                                         \
    if (queue->size >= queue->capacity) ws_queue_##TYPE##_realloc(queue);                                                                \
    if (queue->data == nullptr) queue->data = (TYPE*)malloc(queue->capacity * sizeof(TYPE));                                             \
                                                                                                                                         \
    memcpy(&queue->data[queue->size++], &value, sizeof(TYPE));                                                                           \
                                                                                                                                         \
    queue->end = queue->size - 1;                                                                                                        \
}                                                                                                                                        \
                                                                                                                                         \
[[nodiscard]]inline TYPE ws_queue_##TYPE##_pop(struct ws_queue_##TYPE* queue)                                                            \
{                                                                                                                                        \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                \
    assert(queue->size && "TRIED TO POP AN EMPTY QUEUE");                                                                                \
                                                                                                                                         \
    queue->size  -= 1;                                                                                                                   \
    queue->begin += 1;                                                                                                                   \
                                                                                                                                         \
    return queue->data[queue->begin - 1];                                                                                                \
}                                                                                                                                        \
                                                                                                                                         \
inline struct ws_queue_##TYPE ws_queue_##TYPE##_create(size_t count, ...)                                                                \
{                                                                                                                                        \
    struct ws_queue_##TYPE queue =                                                                                                       \
    {                                                                                                                                    \
        .data     = nullptr,                                                                                                             \
        .size     = 0,                                                                                                                   \
        .capacity = 1,                                                                                                                   \
    };                                                                                                                                   \
                                                                                                                                         \
    va_list values = {};                                                                                                                 \
    va_start(values, count);                                                                                                             \
                                                                                                                                         \
    for (size_t index = 0llu; index != count; index += 1)                                                                                \
    {                                                                                                                                    \
        ws_queue_##TYPE##_push(&queue, va_arg(values, TYPE));                                                                            \
    }                                                                                                                                    \
                                                                                                                                         \
    va_end(values);                                                                                                                      \
                                                                                                                                         \
    return queue;                                                                                                                        \
}                                                                                                                                        \
                                                                                                                                         \
inline void ws_queue_##TYPE##_destroy(struct ws_queue_##TYPE* queue, void(*strategy)(TYPE*))                                             \
{                                                                                                                                        \
    if (strategy != nullptr)                                                                                                             \
    {                                                                                                                                    \
        for (size_t index = 0llu; index != queue->size; index += 1)                                                                      \
        {                                                                                                                                \
            strategy(&queue->data[index]);                                                                                               \
        }                                                                                                                                \
    }                                                                                                                                    \
                                                                                                                                         \
    free(queue->data);                                                                                                                   \
    memset(queue, 0, sizeof(struct ws_queue_##TYPE));                                                                                    \
}

#endif

