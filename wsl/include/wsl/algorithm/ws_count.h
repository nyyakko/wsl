#ifndef WS_COUNT_H
#define WS_COUNT_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifndef WS_GENERIC_CONTAINER_INTERFACE
#define WS_GENERIC_CONTAINER_INTERFACE
struct ws_container_interface
{
    size_t begin;
    size_t end;
    size_t elementSize;
    void* data;
    size_t size;
};

typedef struct ws_container_interface ws_container_interface;

typedef void const*(ws_projection)(void const*);
typedef int(ws_unary_predicate)(void const*);
typedef int(ws_binary_predicate)(void const*, void const*);
typedef void(ws_strategy)(void*);
#endif

#ifndef WS_PRVALUE
#define WS_PRVALUE
#define ws_prvalue(TYPE, value) ({ TYPE _ = value; &_; })
#endif

#define __ws_count__1(container, value) ws_count_in(container, value, nullptr)
#define __ws_count__2(container, value, projection) ws_count_in(container, value, projection)
#define __ws_count__select(_1, _2, selected, ...) selected
#define ws_count(container, ...) __ws_count__select(__VA_ARGS__, __ws_count__2, __ws_count__1, void)(container, __VA_ARGS__)

#define __ws_count_if__1(container, predicate) ws_count_if_in(container, predicate, nullptr)
#define __ws_count_if__2(container, predicate, projection) ws_count_if_in(container, predicate, projection)
#define __ws_count_if__select(_1, _2, selected, ...) selected
#define ws_count_if(container, ...) __ws_count_if__select(__VA_ARGS__, __ws_count_if__2, __ws_count_if__1, void)(container, __VA_ARGS__)

#ifndef WS_COUNT_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL
#endif

#ifndef WS_COUNT_DEFINITION

[[nodiscard]] WS_DECL size_t ws_count_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_in(struct ws_container_interface const* container, void const* value, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_if_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_unary_predicate* predicate, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_if_in(struct ws_container_interface const* container, ws_unary_predicate* predicate, ws_projection* projection);

#else

[[nodiscard]] WS_DECL size_t ws_count_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_in(struct ws_container_interface const* container, void const* value, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_if_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_unary_predicate* predicate, ws_projection* projection);
[[nodiscard]] WS_DECL size_t ws_count_if_in(struct ws_container_interface const* container, ws_unary_predicate* predicate, ws_projection* projection);

[[nodiscard]] size_t ws_count_if_ex(void const* data, size_t begin, size_t end, size_t elementSize, ws_unary_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");
    assert(predicate && "PREDICATE WAS NULL");

    size_t occurences = 0;

    for (size_t index = begin; index != end; index += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (index * elementSize);

        if (projection != nullptr && predicate(projection((void const*)currentValue)))
            occurences += 1;
        else if (predicate((void const*)currentValue))
            occurences += 1;
    }

    return occurences;
}

[[nodiscard]] size_t ws_count_if_in(struct ws_container_interface const* container, ws_unary_predicate* predicate, ws_projection* projection)
{
    assert(container && "CONTAINER WAS NULL");
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    return ws_count_if_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, predicate, projection);
}

size_t ws_count_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");

    size_t occurences = 0;

    char* valueLhs = (char*)malloc(elementSize);
    char* valueRhs = (char*)malloc(elementSize);

    for (size_t index = begin; index != end; index += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (index * elementSize);

        if (projection != nullptr)
            memcpy(valueLhs, projection((void const*)currentValue), elementSize);
        else
            memcpy(valueLhs, (void const*)currentValue, elementSize);

        memcpy(valueRhs, value, elementSize);

        bool found = true;

        for (size_t byteIndex = 0llu; byteIndex != elementSize; byteIndex += 1)
        {
            if (valueLhs[byteIndex] != valueRhs[byteIndex])
            {
                found = false;
                break;
            }
        }

        if (found) occurences += 1;
    }

    free(valueLhs);
    free(valueRhs);

    return occurences;
}

size_t ws_count_in(struct ws_container_interface const* container, void const* value, ws_projection* projection)
{
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    return ws_count_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, value, projection);
}

#endif

#endif
