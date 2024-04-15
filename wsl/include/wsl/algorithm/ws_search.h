#ifndef WS_SEARCH_H
#define WS_SEARCH_H

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

#define __ws_search__1(container, value) ws_search_in(container, value, nullptr, nullptr)
#define __ws_search__2(container, value, predicate) ws_search_in(container, value, predicate, nullptr)
#define __ws_search__3(container, value, predicate, projection) ws_search_in(container, value, predicate, projection)
#define __ws_search__select(_1, _2, _3, selected, ...) selected
#define ws_search(container, ...) __ws_search__select(__VA_ARGS__, __ws_search__3, __ws_search__2, __ws_search__1, void)(container, __VA_ARGS__)

#ifndef WS_SEARCH_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL static
#endif

#ifndef WS_SEARCH_DEFINITION

[[nodiscard]] WS_DECL void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_binary_predicate* predicate, ws_projection* projection);
[[nodiscard]] WS_DECL void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_binary_predicate* predicate, ws_projection* projection);

#else

[[nodiscard]] WS_DECL void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_binary_predicate* predicate, ws_projection* projection);
[[nodiscard]] WS_DECL void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_binary_predicate* predicate, ws_projection* projection);

void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_binary_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");

    char* valueLhs = (char*)malloc(elementSize);
    char* valueRhs = (char*)malloc(elementSize);

    void* result = nullptr;

    for (size_t index = begin; index != end; index += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (index * elementSize);

        if (predicate != nullptr)
        {
            if (projection != nullptr && predicate(projection((void const*)currentValue), value))
            {
                result = (void*)(currentValue);
                break;
            }
            if (predicate((void const*)currentValue, value))
            {
                result = (void*)(currentValue);
                break;
            }
        }
        else
        {
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

            if (found)
            {
                result = (void*)(currentValue);
                break;
            }
        }
    }

    free(valueLhs);
    free(valueRhs);

    return result;
}

void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_binary_predicate* predicate, ws_projection* projection)
{
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    return ws_search_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, value, predicate, projection);
}

#endif

#endif

