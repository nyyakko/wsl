/*

                            Copyright <2023> <nyyakko@github>
                            
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
    associated documentation files (the “Software”), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.
    
    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
    OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
*/

#ifndef WS_STRING_VIEW_H
#define WS_STRING_VIEW_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct ws_string_view
{
    char const* data;
    size_t begin;
    size_t end;
    size_t size;
};

size_t ws_string_view_size(struct ws_string_view view)
{
    return view.size;
}

bool ws_string_view_is_empty(struct ws_string_view view)
{
    return view.size == 0;
}

bool ws_string_view_equals(struct ws_string_view lhs, struct ws_string_view rhs)
{
    size_t lhsSize = lhs.size;
    size_t rhsSize = rhs.size;

    if (lhsSize != rhsSize)
    {
        return false;
    }

    for (size_t index = 0llu; index != (((lhsSize > rhsSize) ? rhsSize : lhsSize) - 1); index += 1)
    {
        if (lhs.data[index] != rhs.data[index])
        {
            return false;
        }
    }

    return true;
}

char ws_string_view_at(struct ws_string_view view, size_t index)
{
    assert(index <= view.size + view.begin && "INDEX OUT OF BOUNDS");
    return view.data[index];
}

char ws_string_view_front(struct ws_string_view view)
{
    return view.data[view.begin];
}

char ws_string_view_back(struct ws_string_view view)
{
    return view.data[view.end - 1];
}

#ifdef WS_HASHMAP_H

size_t ws_string_view_hash(struct ws_string_view view)
{
    return ws_hash_map_hash((char unsigned const*)view.data, view.size);
}

#endif

size_t ws_string_view_search_first(struct ws_string_view view, char needle)
{
    for (size_t index = 0llu; index != view.size; index += 1)
    {
        if (view.data[index] == needle)
        {
            return index;
        }
    }

    return SIZE_MAX;
}

size_t ws_string_view_search_last(struct ws_string_view view, char needle)
{
    for (size_t index = view.size - 1; index != 0; index -= 1)
    {
        if (view.data[index] == needle)
        {
            return index;
        }
    }

    return SIZE_MAX;
}

void ws_string_view_chop_until_first(struct ws_string_view* view, char delimiter)
{
    assert(view != nullptr && "STRING POINTER WAS NULL");
    assert(view->size != 0 && "STRING WAS EMPTY");

    size_t lastSeenDelimiterIndex = ws_string_view_search_first(*view, delimiter);

    if (lastSeenDelimiterIndex == SIZE_MAX)
    {
        return;
    }

    view->size -= lastSeenDelimiterIndex + 1;
    view->begin = lastSeenDelimiterIndex + 1;
    view->data  += view->begin;
}

void ws_string_view_chop_until_last(struct ws_string_view* view, char delimiter)
{
    assert(view != nullptr && "STRING POINTER WAS NULL");
    assert(view->size != 0 && "STRING WAS EMPTY");

    size_t lastSeenDelimiterIndex = ws_string_view_search_last(*view, delimiter);
    
    if (lastSeenDelimiterIndex == SIZE_MAX)
    {
        return;
    }

    view->size -= lastSeenDelimiterIndex + 1;
    view->begin = lastSeenDelimiterIndex + 1;
    view->data  += view->begin;
}

[[nodiscard]]struct ws_string_view ws_string_view_subview(struct ws_string_view view, size_t begin, size_t end)
{
    struct ws_string_view result = view;
    result.data += begin;
    result.begin = begin;
    result.end   = end;
    result.size  = end - begin;

    return result;
}

void ws_string_view_copy(struct ws_string_view* destination, struct ws_string_view const* source)
{
    destination->data  = source->data;
    destination->begin = source->begin;
    destination->end   = source->end;
    destination->size  = source->size;
}

struct ws_string_view ws_string_view_create(char const* data)
{
    size_t size = strlen(data) + 1;

    struct ws_string_view result =
    {
        .data  = data,
        .begin = 0,
        .end   = size,
        .size  = size
    };

    return result;
}

#endif
