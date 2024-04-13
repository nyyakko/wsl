#ifndef WS_SEARCH_H
#define WS_SEARCH_H

#include <assert.h>
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
typedef int(ws_predicate)(void const*, void const*);
typedef void(ws_strategy)(void*);
#endif

#define __ws_search__1(container, value) ws_search_in(container, value, nullptr, nullptr)
#define __ws_search__2(container, value, projection) ws_search_in(container, value, projection, nullptr)
#define __ws_search__3(container, value, projection, predicate) ws_search_in(container, value, projection, predicate)
#define __ws_search__select(_1, _2, _3, selected, ...) selected
#define ws_search(container, ...) __ws_search__select(__VA_ARGS__, __ws_search__3, __ws_search__2, __ws_search__1, void)(container, __VA_ARGS__)

#ifndef WS_SEARCH_DEFINITION

[[nodiscard]] void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_predicate* predicate, ws_projection* projection);
[[nodiscard]] void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_predicate* predicate, ws_projection* projection);

#else

[[nodiscard]] void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_predicate* predicate, ws_projection* projection);
[[nodiscard]] void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_predicate* predicate, ws_projection* projection);

void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");

    for (size_t index = begin; index != end; index += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (index * elementSize);

        if (predicate != nullptr)
        {
            if (projection != nullptr && predicate(projection((void const*)currentValue), value))
                return (void*)(currentValue);
            if (predicate((void const*)currentValue, value))
                return (void*)(currentValue);
        }
        else
        {
            char valueLhs[elementSize];

            if (projection != nullptr)
                memcpy(valueLhs, projection((void const*)currentValue), elementSize);
            else
                memcpy(valueLhs, (void const*)currentValue, elementSize);

            char valueRhs[elementSize];
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

            if (found) return (void*)(currentValue);
        }
    }

    return nullptr;
}

void* ws_search_in(struct ws_container_interface const* container, void const* value, ws_predicate* predicate, ws_projection* projection)
{
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    return ws_search_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, value, predicate, projection);
}

#endif

#endif

