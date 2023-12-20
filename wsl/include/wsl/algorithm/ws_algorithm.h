#ifndef WS_ALGORITMH_H
#define WS_ALGORITMH_H

#include <cassert>
#include <string.h>

struct ws_generic_interface_t
{
    size_t begin;
    size_t end;
    void* data;
};

#define ws_search_1(container, value) ws_search_ex(container, sizeof(*value), value, nullptr)
#define ws_search_2(container, value, predicate) ws_search_ex(container, sizeof(*value), value, predicate)
#define ws_search_select(_1, _2, selected, ...) selected
#define ws_search(container, ...) ws_search_select(__VA_ARGS__, ws_search_2, ws_search_1, void)(container, __VA_ARGS__)

inline void* ws_search_ex(void const* container, size_t typeSize, void const* value, int(*predicate)(void const*, void const*))
{
    assert(container && "CONTAINER WAS NULL");

    struct ws_generic_interface_t containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface_t));

    assert(containerInterface.data && "INVALID CONTAINER TYPE");

    for (size_t index = containerInterface.begin; index <= containerInterface.end; index += 1)
    {
        void const* currentValue = (void const*)((uintptr_t)containerInterface.data + (index * typeSize));

        if (predicate && predicate(currentValue, value))
        {
            return (void*)((uintptr_t)containerInterface.data + (index * typeSize));
        }
        else if (!predicate)
        {
            char valueLhs[typeSize];
            memcpy(valueLhs, currentValue, typeSize);
            char valueRhs[typeSize];
            memcpy(valueRhs, value, typeSize);

            bool found = true;

            for (size_t _index = 0llu; _index != typeSize; _index += 1)
            {
                if (valueLhs[_index] != valueRhs[_index])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                return (void*)((uintptr_t)containerInterface.data + (index * typeSize));
            }
        }
    }

    return nullptr;
}

inline void ws_sort_ex(void* container, size_t typeSize, int(*predicate)(void const*, void const*))
{
    assert(container && "CONTAINER WAS NULL");
    assert(predicate && "PREDICATE WAS NULL");

    struct ws_generic_interface_t containerInterface = {};
    memcpy(&containerInterface, container, sizeof(struct ws_generic_interface_t));

    assert(containerInterface.data && "INVALID CONTAINER TYPE");

    while (true)
    {
        bool sorted = true;

        for (size_t index = containerInterface.begin + 1llu; index <= containerInterface.end; index += 1)
        {
            void* currentValue  = (void*)((uintptr_t)containerInterface.data + (index * typeSize));
            void* previousValue = (void*)((uintptr_t)containerInterface.data + ((index - 1) * typeSize));

            if (predicate(currentValue, previousValue))
            {
                char valueTemporary[typeSize];

                memset(valueTemporary, 0, typeSize);

                memcpy(valueTemporary, previousValue, typeSize);
                memcpy(previousValue, currentValue, typeSize);
                memcpy(currentValue, valueTemporary, typeSize);

                sorted = false;
            }
        }

        if (sorted)
        {
            return;
        }
    }
}

#endif
