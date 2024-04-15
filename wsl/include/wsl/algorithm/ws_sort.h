#ifndef WS_SORT_H
#define WS_SORT_H

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

#define __ws_sort__1(container, predicate) ws_sort_in(container, predicate, nullptr)
#define __ws_sort__2(container, predicate, projection) ws_sort_in(container, predicate, projection)
#define __ws_sort__select(_1, _2, selected, ...) selected
#define ws_sort(container, ...) __ws_sort__select(__VA_ARGS__, __ws_sort__2, __ws_sort__1, void)(container, __VA_ARGS__)

#ifndef WS_SORT_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL static
#endif

#ifndef WS_SORT_DEFINITION

WS_DECL void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_binary_predicate* predicate, ws_projection* projection);
WS_DECL void ws_sort_in(struct ws_container_interface* container, ws_binary_predicate* predicate, ws_projection* projection);

#else

WS_DECL void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_binary_predicate* predicate, ws_projection* projection);
WS_DECL void ws_sort_in(struct ws_container_interface* container, ws_binary_predicate* predicate, ws_projection* projection);

void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_binary_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");
    assert(predicate && "PREDICATE WAS NULL");

    char* valueTemporary = (char*)malloc(elementSize);

    while (true)
    {
        bool sorted = true;

        for (size_t elementIndex = begin + 1llu; elementIndex <= end; elementIndex += 1)
        {
            void* currentValue  = (void*)((uintptr_t)data + (elementIndex * elementSize));
            void* previousValue = (void*)((uintptr_t)data + ((elementIndex - 1) * elementSize));

            if (projection != nullptr && predicate(projection(currentValue), projection(previousValue)))
            {
                memcpy(valueTemporary, previousValue, elementSize);
                memcpy(previousValue, currentValue, elementSize);
                memcpy(currentValue, valueTemporary, elementSize);

                sorted = false;
            }
            else if (predicate(currentValue, previousValue))
            {
                memcpy(valueTemporary, previousValue, elementSize);
                memcpy(previousValue, currentValue, elementSize);
                memcpy(currentValue, valueTemporary, elementSize);

                sorted = false;
            }
        }

        if (sorted) break;
    }

    free(valueTemporary);
}

void ws_sort_in(struct ws_container_interface* container, ws_binary_predicate* predicate, ws_projection* projection)
{
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    ws_sort_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, predicate, projection);
}

#endif

#endif

