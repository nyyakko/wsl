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

#ifndef WS_STRING_BUILDER_H
#define WS_STRING_BUILDER_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ws_string_builder
{
    char* data;
    size_t begin;
    size_t end;
    size_t size;
    size_t capacity;
};

size_t ws_string_builder_size(struct ws_string_builder string)
{
    return string.size - 1;
}

bool ws_string_builder_is_empty(struct ws_string_builder string)
{
    return string.size - 1 == 0;
}

bool ws_string_builder_equals(struct ws_string_builder lhs, struct ws_string_builder rhs)
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

char ws_string_builder_at(struct ws_string_builder string, size_t position)
{
    assert(position < string.size && "INDEX OUT OF BOUNDS");
    return string.data[position];
}

char ws_string_builder_front(struct ws_string_builder string)
{
    assert(string.size && "STRING WAS EMPTY");
    return string.data[0];
}

char ws_string_builder_back(struct ws_string_builder string)
{
    assert(string.size && "STRING WAS EMPTY");
    return string.data[string.size - 1];
}

size_t ws_string_builder_search_first(struct ws_string_builder string, char needle)
{
    for (size_t index = 0llu; index != string.size; index += 1)
    {
        if (string.data[index] == needle)
        {
            return index;
        }
    }

    return SIZE_MAX;
}

size_t ws_string_builder_search_last(struct ws_string_builder string, char needle)
{
    for (size_t index = string.size - 1; index != 0; index -= 1)
    {
        if (string.data[index] == needle)
        {
            return index;
        }
    }

    return SIZE_MAX;
}

#ifdef WS_HASHMAP_H

size_t ws_string_builder_hash(struct ws_string_builder string)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    return ws_hash_map_hash((char unsigned const*)string.data, string.size - 1);
}

#endif

void ws_string_builder_chop_until_first(struct ws_string_builder* string, char delimiter)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");

    size_t lastSeenDelimiterIndex = ws_string_builder_search_first(*string, delimiter);

    if (lastSeenDelimiterIndex == SIZE_MAX)
    {
        return;
    }

    char* buffer = (char*)malloc(string->size - (lastSeenDelimiterIndex + 1));
    memcpy(buffer, &string->data[lastSeenDelimiterIndex + 1], string->size - (lastSeenDelimiterIndex + 1));
    memset(string->data, '\0', string->size);
    memcpy(string->data, buffer, string->size - (lastSeenDelimiterIndex + 1));

    string->size -= lastSeenDelimiterIndex + 1;
    string->begin = 0;
    string->end   = string->size;

    free(buffer);
}

void ws_string_builder_chop_until_last(struct ws_string_builder* string, char delimiter)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");

    size_t lastSeenDelimiterIndex = ws_string_builder_search_last(*string, delimiter);
    
    if (lastSeenDelimiterIndex == SIZE_MAX)
    {
        return;
    }

    char* buffer = (char*)malloc(string->size - (lastSeenDelimiterIndex + 1));
    memcpy(buffer, &string->data[lastSeenDelimiterIndex + 1], string->size - (lastSeenDelimiterIndex + 1));
    memset(string->data, '\0', string->capacity);
    memcpy(string->data, buffer, string->size - (lastSeenDelimiterIndex + 1));

    string->size -= lastSeenDelimiterIndex + 1;
    string->begin = 0;
    string->end   = string->size;

    free(buffer);
}

void ws_string_builder_clear(struct ws_string_builder* string)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    memset(string->data, '\0', string->capacity);
    string->size = 1;
}

void ws_string_builder_realloc(struct ws_string_builder* string)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");

    char* oldData = string->data;
    string->capacity += string->capacity;
    string->data = (char*)malloc(string->capacity + 1);
    memset(string->data, '\0', string->capacity + 1);
    memcpy(string->data, oldData, string->size);

    free(oldData);
}

void ws_string_builder_append(struct ws_string_builder* string, char value)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");

    if (string->size >= string->capacity) ws_string_builder_realloc(string);
    if (string->data == nullptr) string->data = (char*)malloc(string->capacity + 1);
    
    string->data[string->size++ - 1] = value;
}

void ws_string_builder_append_string(struct ws_string_builder* string, char const* value)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");

    size_t stringLength = strlen(value);

    for (size_t index = 0llu; index != stringLength; index += 1)
    {
        ws_string_builder_append(string, value[index]);
    }
}

struct ws_string_builder ws_string_builder_substr(struct ws_string_builder string, size_t begin, size_t end)
{
    (void)string;
    (void)begin;
    (void)end;

    return string;
}

void ws_string_builder_copy(struct ws_string_builder* destination, struct ws_string_builder* source)
{
    assert(destination && "DESTINATION WAS NULL");
    assert(source && "SOURCE WAS NULL");
    assert(source->data && "SOURCE'S DATA WAS NULL");

    if (destination->data)
    {
        free(destination->data);
    }

    destination->data     = (char*)malloc(source->size);
    destination->begin    = 0;
    destination->end      = source->end;
    destination->size     = source->size;
    destination->capacity = source->capacity;

    memset(destination->data, '\0', source->size);
    memcpy(destination->data, source->data, source->size);
}

struct ws_string_builder ws_string_builder_create(char const* data)
{
    size_t length = strlen(data) + 1;

    // https://graphics.stanford.edu/%7Eseander/bithacks.html#RoundUpPowerOf2
    size_t roundedLength = length;

    roundedLength -= 1;
    roundedLength |= roundedLength >> 1;
    roundedLength |= roundedLength >> 2;
    roundedLength |= roundedLength >> 4;
    roundedLength |= roundedLength >> 8;
    roundedLength |= roundedLength >> 16;
    roundedLength += 1;

    struct ws_string_builder result =
    {
        .data     = (char*)malloc(roundedLength),
        .begin    = 0,
        .end      = length,
        .size     = length,
        .capacity = roundedLength
    };

    memset(result.data, '\0', roundedLength);
    memcpy(result.data, data, length - 1);

    return result;
}

void ws_string_builder_destroy(struct ws_string_builder* string)
{
    free(string->data);

    string->data     = nullptr;
    string->begin    = 0;
    string->end      = 0;
    string->capacity = 0;

    memset(string, 0, sizeof(struct ws_string_builder));
}

#endif
