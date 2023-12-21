#ifndef WS_STACK_H
#define WS_STACK_H

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ws_stack_initialize(type, ...) sizeof((type[]){ __VA_ARGS__ }) / sizeof(type) __VA_OPT__(,) __VA_ARGS__

#define ws_stack_copy_1(type, destination, source) ws_stack_##type##_copy(destination, source, nullptr)
#define ws_stack_copy_2(type, destination, source, strategy) ws_stack_##type##_copy(destination, source, strategy)
#define ws_stack_copy_select(_1, _2, _3, selected, ...) selected
#define ws_stack_copy(type, ...) ws_stack_copy_select(__VA_ARGS__, ws_stack_copy_2, ws_stack_copy_1, void)(type, __VA_ARGS__)

#define ws_stack_destroy_1(type, stack) ws_stack_##type##_destroy(stack, nullptr)
#define ws_stack_destroy_2(type, stack, strategy) ws_stack_##type##_destroy(stack, strategy)
#define ws_stack_destroy_select(_1, _2, selected, ...) selected
#define ws_stack_destroy(type, ...) ws_stack_destroy_select(__VA_ARGS__, ws_stack_destroy_2, ws_stack_destroy_1, void)(type, __VA_ARGS__)

#define WS_STACK(TYPE)                                                                                                                    \
                                                                                                                                          \
struct ws_stack_##TYPE                                                                                                                    \
{                                                                                                                                         \
    size_t begin;                                                                                                                         \
    size_t end;                                                                                                                           \
    TYPE* data;                                                                                                                           \
    size_t size;                                                                                                                          \
    size_t capacity;                                                                                                                      \
};                                                                                                                                        \
                                                                                                                                          \
inline size_t ws_stack_##TYPE##_size(struct ws_stack_##TYPE stack)                                                                        \
{                                                                                                                                         \
    return stack.size;                                                                                                                    \
}                                                                                                                                         \
                                                                                                                                          \
inline bool ws_stack_##TYPE##_is_empty(struct ws_stack_##TYPE stack)                                                                      \
{                                                                                                                                         \
    return stack.size == 0;                                                                                                               \
}                                                                                                                                         \
                                                                                                                                          \
inline TYPE* ws_stack_##TYPE##_search(struct ws_stack_##TYPE stack, TYPE value, int(*predicate)(TYPE const*, TYPE const*))                \
{                                                                                                                                         \
    for (size_t index = 0llu; index != stack.size; index += 1)                                                                            \
    {                                                                                                                                     \
        if (predicate(&stack.data[index], &value))                                                                                        \
        {                                                                                                                                 \
            return &stack.data[index];                                                                                                    \
        }                                                                                                                                 \
    }                                                                                                                                     \
                                                                                                                                          \
    return nullptr;                                                                                                                       \
}                                                                                                                                         \
                                                                                                                                          \
inline TYPE* ws_stack_##TYPE##_top(struct ws_stack_##TYPE stack)                                                                          \
{                                                                                                                                         \
    return &stack.data[stack.begin];                                                                                                      \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_stack_##TYPE##_copy(struct ws_stack_##TYPE* destination, struct ws_stack_##TYPE const* source, void(*strategy)(TYPE*))     \
{                                                                                                                                         \
    if (ws_stack_##TYPE##_is_empty(*source))                                                                                              \
    {                                                                                                                                     \
        return;                                                                                                                           \
    }                                                                                                                                     \
                                                                                                                                          \
    if (!ws_stack_##TYPE##_is_empty(*destination) && strategy != nullptr)                                                                 \
    {                                                                                                                                     \
        for (size_t index = 0llu; index != destination->size; index += 1)                                                                 \
        {                                                                                                                                 \
            strategy(&destination->data[index]);                                                                                          \
        }                                                                                                                                 \
                                                                                                                                          \
        free(destination->data);                                                                                                          \
    }                                                                                                                                     \
                                                                                                                                          \
    destination->size     = source->size;                                                                                                 \
    destination->capacity = source->capacity;                                                                                             \
    destination->begin    = source->begin;                                                                                                \
    destination->end      = source->end;                                                                                                  \
    destination->data     = (TYPE*)malloc(destination->capacity * sizeof(TYPE));                                                          \
                                                                                                                                          \
    memcpy(destination->data, source->data, destination->capacity * sizeof(TYPE));                                                        \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_stack_##TYPE##_realloc(struct ws_stack_##TYPE* stack)                                                                      \
{                                                                                                                                         \
    assert(stack != nullptr && "STACK POINTER WAS NULL");                                                                                 \
                                                                                                                                          \
    TYPE* oldData = stack->data;                                                                                                          \
    stack->capacity += stack->capacity;                                                                                                   \
    stack->data = (TYPE*)malloc(stack->capacity * sizeof(TYPE));                                                                          \
    memset(stack->data, 0, stack->capacity * sizeof(TYPE));                                                                               \
    memcpy(stack->data, oldData, stack->size * sizeof(TYPE));                                                                             \
                                                                                                                                          \
    free(oldData);                                                                                                                        \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_stack_##TYPE##_push(struct ws_stack_##TYPE* stack, TYPE value)                                                             \
{                                                                                                                                         \
    assert(stack != nullptr && "STACK POINTER WAS NULL");                                                                                 \
                                                                                                                                          \
    if (stack->size >= stack->capacity) ws_stack_##TYPE##_realloc(stack);                                                                 \
    if (stack->data == nullptr) stack->data = (TYPE*)malloc(stack->capacity * sizeof(TYPE));                                              \
                                                                                                                                          \
    memcpy(&stack->data[stack->size++], &value, sizeof(TYPE));                                                                            \
                                                                                                                                          \
    stack->begin = stack->size - 1;                                                                                                       \
}                                                                                                                                         \
                                                                                                                                          \
[[nodiscard]]inline TYPE* ws_stack_##TYPE##_pop(struct ws_stack_##TYPE* stack)                                                            \
{                                                                                                                                         \
    assert(stack != nullptr && "STACK POINTER WAS NULL");                                                                                 \
    assert(stack->size && "TRIED TO POP AN EMPTY STACK");                                                                                 \
                                                                                                                                          \
    stack->size -= 1;                                                                                                                     \
    stack->begin = stack->size;                                                                                                           \
                                                                                                                                          \
    return &stack->data[stack->begin];                                                                                                    \
}                                                                                                                                         \
                                                                                                                                          \
inline struct ws_stack_##TYPE ws_stack_##TYPE##_create(size_t count, ...)                                                                 \
{                                                                                                                                         \
    struct ws_stack_##TYPE stack =                                                                                                        \
    {                                                                                                                                     \
        .begin    = 0,                                                                                                                    \
        .end      = 0,                                                                                                                    \
        .data     = nullptr,                                                                                                              \
        .size     = 0,                                                                                                                    \
        .capacity = 1                                                                                                                     \
    };                                                                                                                                    \
                                                                                                                                          \
    va_list values = {};                                                                                                                  \
    va_start(values, count);                                                                                                              \
                                                                                                                                          \
    for (size_t index = 0llu; index != count; index += 1)                                                                                 \
    {                                                                                                                                     \
        ws_stack_##TYPE##_push(&stack, va_arg(values, TYPE));                                                                             \
    }                                                                                                                                     \
                                                                                                                                          \
    va_end(values);                                                                                                                       \
                                                                                                                                          \
    return stack;                                                                                                                         \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_stack_##TYPE##_destroy(struct ws_stack_##TYPE* stack, void(*strategy)(TYPE*))                                              \
{                                                                                                                                         \
    if (strategy != nullptr)                                                                                                              \
    {                                                                                                                                     \
        for (size_t index = 0llu; index != stack->size; index += 1)                                                                       \
        {                                                                                                                                 \
            strategy(&stack->data[index]);                                                                                                \
        }                                                                                                                                 \
    }                                                                                                                                     \
                                                                                                                                          \
    free(stack->data);                                                                                                                    \
    memset(stack, 0, sizeof(struct ws_stack_##TYPE));                                                                                     \
}

#endif

