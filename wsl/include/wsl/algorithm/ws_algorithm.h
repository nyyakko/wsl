#ifndef WS_ALGORITMH_H
#define WS_ALGORITMH_H

#include <assert.h>
#include <string.h>

struct ws_generic_interface
{
    size_t begin;
    size_t end;
    size_t elementSize;
    void* data;
    size_t size;
};

typedef void const*(ws_projection)(void const*);
typedef int(ws_predicate)(void const*, void const*);
typedef void(ws_strategy)(void*);

#define ws_search_1(container, value) ws_search_in(container, value, nullptr, nullptr)
#define ws_search_2(container, value, projection) ws_search_in(container, value, projection, nullptr)
#define ws_search_3(container, value, projection, predicate) ws_search_in(container, value, projection, predicate)
#define ws_search_select(_1, _2, _3, selected, ...) selected
#define ws_search(container, ...) ws_search_select(__VA_ARGS__, ws_search_3, ws_search_2, ws_search_1, void)(container, __VA_ARGS__)

#define ws_sort_1(container, predicate) ws_sort_in(container, predicate, nullptr)
#define ws_sort_2(container, predicate, projection) ws_sort_in(container, predicate, projection)
#define ws_sort_select(_1, _2, selected, ...) selected
#define ws_sort(container, ...) ws_sort_select(__VA_ARGS__, ws_sort_2, ws_sort_1, void)(container, __VA_ARGS__)

#define ws_clear_1(container) ws_clear_in(container, nullptr)
#define ws_clear_2(container, predicate) ws_clear_in(container, predicate)
#define ws_clear_select(_1, selected, ...) selected
#define ws_clear(container, ...) ws_clear_select(__VA_ARGS__ __VA_OPT__(,) ws_clear_2, ws_clear_1)(container, __VA_ARGS__)

#ifndef WS_ALGORITHM_DEFINITION

void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_predicate* predicate, ws_projection* projection);
void* ws_search_in(void const* container, void const* value, ws_predicate* predicate, ws_projection* projection);
void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_predicate* predicate, ws_projection* projection);
void ws_sort_in(void* container, ws_predicate* predicate, ws_projection* projection);
void ws_clear_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_strategy* strategy);
void ws_clear_in(void* container, ws_strategy* strategy);

#else

inline void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, ws_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");

    for (size_t elementIndex = begin; elementIndex <= end; elementIndex += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (elementIndex * elementSize);

        if (predicate != nullptr)
        {
            if (projection != nullptr && predicate(projection((void const*)currentValue), value))
            {
                return (void*)(currentValue);
            }
            else if (predicate((void const*)currentValue, value))
            {
                return (void*)(currentValue);
            }
        }
        else if (predicate == nullptr)
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

            if (found)
            {
                return (void*)(currentValue);
            }
        }
    }

    return nullptr;
}

inline void* ws_search_in(void const* container, void const* value, ws_predicate* predicate, ws_projection* projection)
{
    struct ws_generic_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface));

    return ws_search_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, value, predicate, projection);
}

inline void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_predicate* predicate, ws_projection* projection)
{
    assert(data && "CONTAINER WAS NULL");
    assert(predicate && "PREDICATE WAS NULL");

    while (true)
    {
        bool sorted = true;

        for (size_t elementIndex = begin + 1llu; elementIndex <= end; elementIndex += 1)
        {
            void* currentValue  = (void*)((uintptr_t)data + (elementIndex * elementSize));
            void* previousValue = (void*)((uintptr_t)data + ((elementIndex - 1) * elementSize));

            char valueTemporary[elementSize];

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

        if (sorted)
        {
            return;
        }
    }
}

inline void ws_sort_in(void* container, ws_predicate* predicate, ws_projection* projection)
{
    struct ws_generic_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface));

    ws_sort_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, predicate, projection);
}

inline void ws_clear_ex(void* data, size_t begin, size_t end, size_t elementSize, ws_strategy* strategy)
{
    if (strategy != nullptr)
    {
        for (size_t index = begin; index <= end; index += 1)
        {
            void* currentValue = (void*)((uintptr_t)data + (index * elementSize));
            strategy(currentValue);
        }
    }

    // FIXME: this is assuming the end value will always be zero indexed.
    // i need to find a better way of doing this. this should work for now though.
    memset(data, 0, (end + 1) * elementSize);
}

inline void ws_clear_in(void* container, ws_strategy* strategy)
{
    struct ws_generic_interface containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface));

    containerInterface.size = 0;

    ws_clear_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, strategy);

    memcpy(container, &containerInterface, sizeof(struct ws_generic_interface));
}

#endif

#endif
