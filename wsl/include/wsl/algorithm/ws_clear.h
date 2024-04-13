#ifndef WS_CLEAR_H
#define WS_CLEAR_H

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

#define __ws_clear__1(container) ws_clear_in(container, nullptr)
#define __ws_clear__2(container, predicate) ws_clear_in(container, predicate)
#define __ws_clear__select(_1, selected, ...) selected
#define ws_clear(container, ...) __ws_clear__select(__VA_ARGS__ __VA_OPT__(,) __ws_clear__2, __ws_clear__1)(container, __VA_ARGS__)

#ifndef WS_CLEAR_DEFINITION

void ws_clear_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_strategy* strategy);
void ws_clear_in(struct ws_container_interface* container, ws_strategy* strategy);

#else

void ws_clear_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_strategy* strategy);
void ws_clear_in(struct ws_container_interface* container, ws_strategy* strategy);

void ws_clear_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_strategy* strategy)
{
    if (strategy != nullptr)
    {
        for (size_t index = begin; index != end; index += 1)
        {
            void* currentValue = (void*)((uintptr_t)data + (index * elementSize));
            strategy(currentValue);
        }
    }

    memset(data, 0, end * elementSize);
}

void ws_clear_in(struct ws_container_interface* container, ws_strategy* strategy)
{
    struct ws_container_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_container_interface));
    ws_clear_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, strategy);
    containerInterface.size  = 0;
    containerInterface.begin = 0;
    containerInterface.end   = 0;
    memcpy(container, &containerInterface, sizeof(struct ws_container_interface));
}

#endif

#endif

