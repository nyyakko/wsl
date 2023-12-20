#ifndef WS_ALGORITMH_H
#define WS_ALGORITMH_H

#include <assert.h>
#include <string.h>

struct ws_generic_interface_t
{
    size_t begin;
    size_t end;
    size_t elementSize;
    void* data;
};

#define ws_search_1(container, value) ws_search_in(container, value, nullptr)
#define ws_search_2(container, value, predicate) ws_search_in(container, value, predicate)
#define ws_search_select(_1, _2, selected, ...) selected
#define ws_search(container, ...) ws_search_select(__VA_ARGS__, ws_search_2, ws_search_1, void)(container, __VA_ARGS__)

inline void* ws_search_ex(void const* data, size_t begin, size_t end, size_t elementSize, void const* value, int(*predicate)(void const*, void const*))
{
    assert(data && "CONTAINER WAS NULL");

    for (size_t elementIndex = begin; elementIndex <= end; elementIndex += 1)
    {
        uintptr_t currentValue = (uintptr_t)data + (elementIndex * elementSize);

        if (predicate && predicate((void const*)(currentValue), value))
        {
            return (void*)(currentValue);
        }
        else if (!predicate)
        {
            char valueLhs[elementSize];
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

inline void* ws_search_in(void const* container, void const* value, int(*predicate)(void const*, void const*))
{
    struct ws_generic_interface_t containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface_t));

    return ws_search_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, value, predicate);
}

#define ws_sort(container, predicate) ws_sort_in(container, predicate)

inline void ws_sort_ex(void* data, size_t begin, size_t end, size_t elementSize, int(*predicate)(void const*, void const*))
{
    assert(data && "CONTAINER WAS NULL");
    assert(predicate && "PREDICATE WAS NULL");

    while (true)
    {
        bool sorted = true;

        for (size_t index = begin + 1llu; index <= end; index += 1)
        {
            void* currentValue  = (void*)((uintptr_t)data + (index * elementSize));
            void* previousValue = (void*)((uintptr_t)data + ((index - 1) * elementSize));

            if (predicate(currentValue, previousValue))
            {
                char valueTemporary[elementSize];

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

inline void ws_sort_in(void* container, int(*predicate)(void const*, void const*))
{
    struct ws_generic_interface_t containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface_t));

    return ws_sort_ex(containerInterface.data, containerInterface.begin, containerInterface.end, containerInterface.elementSize, predicate);
}

#endif
