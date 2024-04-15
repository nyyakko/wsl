#ifndef WS_QUEUE_H
#define WS_QUEUE_H

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ws_queue_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define __ws_queue_copy_1(type, destination, source) ws_queue_##type##_copy(destination, source, nullptr)
#define __ws_queue_copy_2(type, destination, source, strategy) ws_queue_##type##_copy(destination, source, strategy)
#define __ws_queue_copy_select(_1, _2, _3, selected, ...) selected
#define ws_queue_copy(type, ...) __ws_queue_copy_select(__VA_ARGS__, __ws_queue_copy_2, __ws_queue_copy_1, void)(type, __VA_ARGS__)

#define __ws_queue_destroy_1(type, queue) ws_queue_##type##_destroy(queue, nullptr)
#define __ws_queue_destroy_2(type, queue, strategy) ws_queue_##type##_destroy(queue, strategy)
#define __ws_queue_destroy_select(_1, _2, selected, ...) selected
#define ws_queue_destroy(type, ...) __ws_queue_destroy_select(__VA_ARGS__, __ws_queue_destroy_2, __ws_queue_destroy_1, void)(type, __VA_ARGS__)

#ifndef WS_QUEUE_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL
#endif

#ifndef WS_QUEUE_DEFINITION

#define WS_QUEUE(TYPE)                                                                                                                            \
                                                                                                                                                  \
struct ws_queue_##TYPE                                                                                                                            \
{                                                                                                                                                 \
    size_t begin;                                                                                                                                 \
    size_t end;                                                                                                                                   \
    TYPE* data;                                                                                                                                   \
    size_t size;                                                                                                                                  \
    size_t capacity;                                                                                                                              \
};                                                                                                                                                \
                                                                                                                                                  \
[[nodiscard]] WS_DECL size_t ws_queue_##TYPE##_size(struct ws_queue_##TYPE queue);                                                                \
[[nodiscard]] WS_DECL bool ws_queue_##TYPE##_is_empty(struct ws_queue_##TYPE queue);                                                              \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_front(struct ws_queue_##TYPE queue);                                                                \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_back(struct ws_queue_##TYPE queue);                                                                 \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_search(struct ws_queue_##TYPE queue, TYPE value, bool(*predicate)(TYPE const*, TYPE const*));       \
WS_DECL void ws_queue_##TYPE##_push(struct ws_queue_##TYPE* queue, TYPE value);                                                                   \
[[nodiscard]] WS_DECL TYPE ws_queue_##TYPE##_pop(struct ws_queue_##TYPE* queue);                                                                  \
WS_DECL void ws_queue_##TYPE##_copy(struct ws_queue_##TYPE* destination, struct ws_queue_##TYPE const* source, void(*strategy)(TYPE*));           \
[[nodiscard]] WS_DECL struct ws_queue_##TYPE ws_queue_##TYPE##_create(size_t count, ...);                                                         \
WS_DECL void ws_queue_##TYPE##_destroy(struct ws_queue_##TYPE* queue, void(*strategy)(TYPE*));                                                    \
                                                                                                                                                  \
WS_DECL void __ws_queue_##TYPE##_realloc(struct ws_queue_##TYPE* queue);

#else

#define WS_QUEUE(TYPE)                                                                                                                            \
                                                                                                                                                  \
struct ws_queue_##TYPE                                                                                                                            \
{                                                                                                                                                 \
    size_t begin;                                                                                                                                 \
    size_t end;                                                                                                                                   \
    TYPE* data;                                                                                                                                   \
    size_t size;                                                                                                                                  \
    size_t capacity;                                                                                                                              \
};                                                                                                                                                \
                                                                                                                                                  \
[[nodiscard]] WS_DECL size_t ws_queue_##TYPE##_size(struct ws_queue_##TYPE queue);                                                                \
[[nodiscard]] WS_DECL bool ws_queue_##TYPE##_is_empty(struct ws_queue_##TYPE queue);                                                              \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_front(struct ws_queue_##TYPE queue);                                                                \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_back(struct ws_queue_##TYPE queue);                                                                 \
[[nodiscard]] WS_DECL TYPE* ws_queue_##TYPE##_search(struct ws_queue_##TYPE queue, TYPE value, bool(*predicate)(TYPE const*, TYPE const*));       \
WS_DECL void ws_queue_##TYPE##_push(struct ws_queue_##TYPE* queue, TYPE value);                                                                   \
[[nodiscard]] WS_DECL TYPE ws_queue_##TYPE##_pop(struct ws_queue_##TYPE* queue);                                                                  \
WS_DECL void ws_queue_##TYPE##_copy(struct ws_queue_##TYPE* destination, struct ws_queue_##TYPE const* source, void(*strategy)(TYPE*));           \
[[nodiscard]] WS_DECL struct ws_queue_##TYPE ws_queue_##TYPE##_create(size_t count, ...);                                                         \
WS_DECL void ws_queue_##TYPE##_destroy(struct ws_queue_##TYPE* queue, void(*strategy)(TYPE*));                                                    \
                                                                                                                                                  \
WS_DECL void __ws_queue_##TYPE##_realloc(struct ws_queue_##TYPE* queue);                                                                          \
                                                                                                                                                  \
size_t ws_queue_##TYPE##_size(struct ws_queue_##TYPE queue)                                                                                       \
{                                                                                                                                                 \
    return queue.size;                                                                                                                            \
}                                                                                                                                                 \
                                                                                                                                                  \
bool ws_queue_##TYPE##_is_empty(struct ws_queue_##TYPE queue)                                                                                     \
{                                                                                                                                                 \
    return queue.size == 0;                                                                                                                       \
}                                                                                                                                                 \
                                                                                                                                                  \
TYPE* ws_queue_##TYPE##_front(struct ws_queue_##TYPE queue)                                                                                       \
{                                                                                                                                                 \
    return &queue.data[queue.begin];                                                                                                              \
}                                                                                                                                                 \
                                                                                                                                                  \
TYPE* ws_queue_##TYPE##_back(struct ws_queue_##TYPE queue)                                                                                        \
{                                                                                                                                                 \
    return &queue.data[queue.end - 1];                                                                                                            \
}                                                                                                                                                 \
                                                                                                                                                  \
TYPE* ws_queue_##TYPE##_search(struct ws_queue_##TYPE queue, TYPE value, bool(*predicate)(TYPE const*, TYPE const*))                              \
{                                                                                                                                                 \
    for (size_t index = 0llu; index != queue.size; index += 1)                                                                                    \
    {                                                                                                                                             \
        if (predicate(&queue.data[index], &value))                                                                                                \
        {                                                                                                                                         \
            return &queue.data[index];                                                                                                            \
        }                                                                                                                                         \
    }                                                                                                                                             \
                                                                                                                                                  \
    return nullptr;                                                                                                                               \
}                                                                                                                                                 \
                                                                                                                                                  \
void ws_queue_##TYPE##_push(struct ws_queue_##TYPE* queue, TYPE value)                                                                            \
{                                                                                                                                                 \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                         \
    if (queue->size >= queue->capacity) __ws_queue_##TYPE##_realloc(queue);                                                                       \
    if (queue->data == nullptr) queue->data = (TYPE*)malloc(queue->capacity * sizeof(TYPE));                                                      \
    memcpy(&queue->data[queue->end++], &value, sizeof(TYPE));                                                                                     \
    queue->size += 1;                                                                                                                             \
}                                                                                                                                                 \
                                                                                                                                                  \
TYPE ws_queue_##TYPE##_pop(struct ws_queue_##TYPE* queue)                                                                                         \
{                                                                                                                                                 \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                         \
    assert(queue->size && "TRIED TO POP AN EMPTY QUEUE");                                                                                         \
    queue->begin += 1;                                                                                                                            \
    queue->size  -= 1;                                                                                                                            \
    return queue->data[queue->begin - 1];                                                                                                         \
}                                                                                                                                                 \
                                                                                                                                                  \
void ws_queue_##TYPE##_copy(struct ws_queue_##TYPE* destination, struct ws_queue_##TYPE const* source, void(*strategy)(TYPE*))                    \
{                                                                                                                                                 \
    if (ws_queue_##TYPE##_is_empty(*source)) return;                                                                                              \
                                                                                                                                                  \
    if (strategy != nullptr)                                                                                                                      \
    {                                                                                                                                             \
        for (size_t index = 0llu; index != destination->size; index += 1)                                                                         \
        {                                                                                                                                         \
            strategy(&destination->data[index]);                                                                                                  \
        }                                                                                                                                         \
    }                                                                                                                                             \
                                                                                                                                                  \
    free(destination->data);                                                                                                                      \
                                                                                                                                                  \
    destination->size     = source->size;                                                                                                         \
    destination->capacity = source->capacity;                                                                                                     \
    destination->begin    = source->begin;                                                                                                        \
    destination->end      = source->end;                                                                                                          \
    destination->data     = (TYPE*)malloc(destination->capacity * sizeof(TYPE));                                                                  \
                                                                                                                                                  \
    memcpy(destination->data, source->data, destination->capacity * sizeof(TYPE));                                                                \
}                                                                                                                                                 \
                                                                                                                                                  \
struct ws_queue_##TYPE ws_queue_##TYPE##_create(size_t count, ...)                                                                                \
{                                                                                                                                                 \
    struct ws_queue_##TYPE queue =                                                                                                                \
    {                                                                                                                                             \
        .begin    = 0,                                                                                                                            \
        .end      = 0,                                                                                                                            \
        .data     = nullptr,                                                                                                                      \
        .size     = 0,                                                                                                                            \
        .capacity = 1,                                                                                                                            \
    };                                                                                                                                            \
                                                                                                                                                  \
    va_list values = {};                                                                                                                          \
    va_start(values, count);                                                                                                                      \
                                                                                                                                                  \
    for (size_t index = 0llu; index != count; index += 1)                                                                                         \
    {                                                                                                                                             \
        ws_queue_##TYPE##_push(&queue, va_arg(values, TYPE));                                                                                     \
    }                                                                                                                                             \
                                                                                                                                                  \
    va_end(values);                                                                                                                               \
                                                                                                                                                  \
    return queue;                                                                                                                                 \
}                                                                                                                                                 \
                                                                                                                                                  \
void ws_queue_##TYPE##_destroy(struct ws_queue_##TYPE* queue, void(*strategy)(TYPE*))                                                             \
{                                                                                                                                                 \
    if (strategy != nullptr)                                                                                                                      \
    {                                                                                                                                             \
        for (size_t index = 0llu; index != queue->size; index += 1)                                                                               \
        {                                                                                                                                         \
            strategy(&queue->data[index]);                                                                                                        \
        }                                                                                                                                         \
    }                                                                                                                                             \
                                                                                                                                                  \
    free(queue->data);                                                                                                                            \
    memset(queue, 0, sizeof(struct ws_queue_##TYPE));                                                                                             \
}                                                                                                                                                 \
                                                                                                                                                  \
void __ws_queue_##TYPE##_realloc(struct ws_queue_##TYPE* queue)                                                                                   \
{                                                                                                                                                 \
    assert(queue != nullptr && "QUEUE POINTER WAS NULL");                                                                                         \
                                                                                                                                                  \
    TYPE* oldData = queue->data;                                                                                                                  \
    queue->capacity += queue->capacity;                                                                                                           \
    queue->data = (TYPE*)malloc(queue->capacity * sizeof(TYPE));                                                                                  \
    memset(queue->data, 0, queue->capacity * sizeof(TYPE));                                                                                       \
    memcpy(queue->data, oldData, queue->size * sizeof(TYPE));                                                                                     \
                                                                                                                                                  \
    free(oldData);                                                                                                                                \
}

#endif

#endif

