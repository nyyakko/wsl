#ifndef WS_STRING_VIEW_H
#define WS_STRING_VIEW_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct ws_string_view
{
    size_t begin;
    size_t end;
    char const* data;
    size_t size;
};

#ifndef WS_STRING_VIEW_DEFINITION

size_t ws_string_view_size(struct ws_string_view view);
bool ws_string_view_is_empty(struct ws_string_view view);
bool ws_string_view_equals(struct ws_string_view lhs, struct ws_string_view rhs);
[[nodiscard]]char ws_string_view_at(struct ws_string_view view, size_t index);
[[nodiscard]]char ws_string_view_front(struct ws_string_view view);
[[nodiscard]]char ws_string_view_back(struct ws_string_view view);
size_t ws_string_view_search_first(struct ws_string_view view, char needle);
size_t ws_string_view_search_last(struct ws_string_view view, char needle);
void ws_string_view_chop_until_first(struct ws_string_view* view, char delimiter);
void ws_string_view_chop_until_last(struct ws_string_view* view, char delimiter);
[[nodiscard]]struct ws_string_view ws_string_view_subview(struct ws_string_view view, size_t begin, size_t end);
void ws_string_view_copy(struct ws_string_view* destination, struct ws_string_view const* source);
[[nodiscard]]struct ws_string_view ws_string_view_create(char const* data);

#else

#define WS_DECLARATION inline

WS_DECLARATION size_t ws_string_view_size(struct ws_string_view view)
{
    return view.size;
}

WS_DECLARATION bool ws_string_view_is_empty(struct ws_string_view view)
{
    return view.size == 0;
}

WS_DECLARATION bool ws_string_view_equals(struct ws_string_view lhs, struct ws_string_view rhs)
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

[[nodiscard]]WS_DECLARATION char ws_string_view_at(struct ws_string_view view, size_t index)
{
    assert(index <= view.size + view.begin && "INDEX OUT OF BOUNDS");
    return view.data[index];
}

[[nodiscard]]WS_DECLARATION char ws_string_view_front(struct ws_string_view view)
{
    return view.data[view.begin];
}

[[nodiscard]]WS_DECLARATION char ws_string_view_back(struct ws_string_view view)
{
    return view.data[view.end - 1];
}

WS_DECLARATION size_t ws_string_view_search_first(struct ws_string_view view, char needle)
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

WS_DECLARATION size_t ws_string_view_search_last(struct ws_string_view view, char needle)
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

WS_DECLARATION void ws_string_view_chop_until_first(struct ws_string_view* view, char delimiter)
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

WS_DECLARATION void ws_string_view_chop_until_last(struct ws_string_view* view, char delimiter)
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

[[nodiscard]]WS_DECLARATION struct ws_string_view ws_string_view_subview(struct ws_string_view view, size_t begin, size_t end)
{
    struct ws_string_view result = view;
    result.data += begin;
    result.begin = begin;
    result.end   = end;
    result.size  = end - begin;

    return result;
}

WS_DECLARATION void ws_string_view_copy(struct ws_string_view* destination, struct ws_string_view const* source)
{
    destination->data  = source->data;
    destination->begin = source->begin;
    destination->end   = source->end;
    destination->size  = source->size;
}

WS_DECLARATION struct ws_string_view ws_string_view_create(char const* data)
{
    size_t size = strlen(data) + 1;

    struct ws_string_view result =
    {
        .begin = 0,
        .end   = size,
        .data  = data,
        .size  = size,
    };

    return result;
}
#endif

#endif

