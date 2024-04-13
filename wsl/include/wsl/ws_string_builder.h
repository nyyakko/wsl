#ifndef WS_STRING_BUILDER_H
#define WS_STRING_BUILDER_H

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ws_string_builder
{
    size_t begin;
    size_t end;
    char* data;
    size_t size;
    size_t capacity;
};

[[nodiscard]] size_t ws_string_builder_size(struct ws_string_builder string);
[[nodiscard]] bool ws_string_builder_is_empty(struct ws_string_builder string);
[[nodiscard]] bool ws_string_builder_equals(struct ws_string_builder lhs, struct ws_string_builder rhs);
[[nodiscard]] char ws_string_builder_at(struct ws_string_builder string, size_t position);
[[nodiscard]] char ws_string_builder_front(struct ws_string_builder string);
[[nodiscard]] char ws_string_builder_back(struct ws_string_builder string);
[[nodiscard]] size_t ws_string_builder_search_first(struct ws_string_builder string, char needle);
[[nodiscard]] size_t ws_string_builder_search_last(struct ws_string_builder string, char needle);
void ws_string_builder_remove_prefix(struct ws_string_builder* view, size_t count);
void ws_string_builder_remove_suffix(struct ws_string_builder* view, size_t count);
void ws_string_builder_chop_until_first(struct ws_string_builder* string, char delimiter);
void ws_string_builder_chop_until_last(struct ws_string_builder* string, char delimiter);
void ws_string_builder_clear(struct ws_string_builder* string);
void ws_string_builder_append(struct ws_string_builder* string, char value);
void ws_string_builder_append_string_while(struct ws_string_builder* destination, char const* value, int(*predicate)(int));
void ws_string_builder_append_string_while_not(struct ws_string_builder* destination, char const* value, int(*predicate)(int));
void ws_string_builder_append_string(struct ws_string_builder* string, char const* value);
[[nodiscard]] struct ws_string_builder ws_string_builder_substr(struct ws_string_builder string, size_t begin, size_t end);
void ws_string_builder_copy(struct ws_string_builder* destination, struct ws_string_builder const* source);
[[nodiscard]] struct ws_string_builder ws_string_builder_create(char const* data);
void ws_string_builder_destroy(struct ws_string_builder* string);

void __ws_string_builder_realloc(struct ws_string_builder* string);
size_t __ws_string_builder_round(size_t value);

#ifdef WS_STRING_BUILDER_DEFINITION

size_t ws_string_builder_size(struct ws_string_builder string)
{
    return string.size - 1;
}

bool ws_string_builder_is_empty(struct ws_string_builder string)
{
    return ws_string_builder_size(string) == 0;
}

bool ws_string_builder_equals(struct ws_string_builder lhs, struct ws_string_builder rhs)
{
    if (lhs.size != rhs.size)
    {
        return false;
    }

    for (size_t index = 0llu; index != lhs.size; index += 1)
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

void ws_string_builder_remove_prefix(struct ws_string_builder* string, size_t count)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");
    assert(count <= string->size);

    memmove(string->data, &string->data[count], string->size - count);
    memset(&string->data[string->size - count], 0, string->size - count);

    string->end  -= count;
    string->size -= count;
}

void ws_string_builder_remove_suffix(struct ws_string_builder* string, size_t count)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");
    assert(count <= string->size);

    memset(&string->data[string->size - (count)], 0, count);

    string->end  -= count;
    string->size -= count;
}

void ws_string_builder_chop_until_first(struct ws_string_builder* string, char delimiter)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");

    size_t position = ws_string_builder_search_first(*string, delimiter);

    if (position == SIZE_MAX)
    {
        return;
    }

    memmove(string->data, &string->data[position + 1], string->size - (position + 1));
    memset(&string->data[string->size - (position + 1)], 0, string->size - (position + 1));

    string->size  = string->size - position - 1;
    string->begin = 0;
    string->end   = string->size;
}

void ws_string_builder_chop_until_last(struct ws_string_builder* string, char delimiter)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(string->size != 0 && "STRING WAS EMPTY");

    size_t position = ws_string_builder_search_last(*string, delimiter);

    if (position == SIZE_MAX)
    {
        return;
    }

    // FIXME: solve the case where it may occoour an allocation of 0 bytes ?
    assert(string->size - (position + 1) && "HOW DID YOU DID THIS?");

    memmove(string->data, &string->data[position + 1], string->size - (position + 1));
    memset(&string->data[string->size - (position + 1)], 0, string->size - (position + 1));

    string->size -= position + 1;
    string->begin = 0;
    string->end   = string->size;
}

void ws_string_builder_clear(struct ws_string_builder* string)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    memset(string->data, '\0', string->capacity);
    string->size = 1;
}

void ws_string_builder_append(struct ws_string_builder* string, char value)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");

    if (string->size >= string->capacity) __ws_string_builder_realloc(string);
    if (string->data == nullptr) string->data = (char*)malloc(string->capacity + 1);

    string->data[string->size++] = value;
    string->end = string->size;
}

void ws_string_builder_append_string_while(struct ws_string_builder* destination, char const* value, int(*predicate)(int))
{
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");
    assert(value != nullptr && "SOURCE POINTER WAS NULL");

    size_t stringLength = strlen(value);

    for (size_t index = 0llu; index != stringLength && predicate(value[index]); index += 1)
    {
        ws_string_builder_append(destination, value[index]);
    }
}

void ws_string_builder_append_string_while_not(struct ws_string_builder* destination, char const* value, int(*predicate)(int))
{
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");
    assert(value != nullptr && "SOURCE POINTER WAS NULL");

    size_t stringLength = strlen(value);

    for (size_t index = 0llu; index != stringLength && !predicate(value[index]); index += 1)
    {
        ws_string_builder_append(destination, value[index]);
    }
}

void ws_string_builder_append_string(struct ws_string_builder* string, char const* value)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");
    assert(value != nullptr && "VALUE POINTER WAS NULL");

    size_t length = strlen(value);

    for (size_t index = 0llu; index != length; index += 1)
    {
        ws_string_builder_append(string, value[index]);
    }
}

struct ws_string_builder ws_string_builder_substr(struct ws_string_builder string, size_t begin, size_t end)
{
    assert(begin != end && "BEGIN CANNOT EQUAL TO END");

    size_t length        = end - (begin + 1);
    size_t roundedLength = __ws_string_builder_round(length);
    size_t capacity      = roundedLength > 16 ? roundedLength : 16;

    struct ws_string_builder result =
    {
        .begin    = 0,
        .end      = length,
        .data     = (char*)malloc(capacity),
        .size     = length,
        .capacity = capacity
    };

    memset(result.data, 0, capacity);
    memcpy(result.data, string.data += (begin + 1), length);

    return result;
}

void ws_string_builder_copy(struct ws_string_builder* destination, struct ws_string_builder const* source)
{
    assert(destination && "DESTINATION WAS NULL");
    assert(source && "SOURCE WAS NULL");
    assert(source->data && "SOURCE'S DATA WAS NULL");

    if (destination->data)
    {
        free(destination->data);
    }

    destination->data     = (char*)malloc(source->capacity);
    destination->begin    = 0;
    destination->end      = source->end;
    destination->size     = source->size;
    destination->capacity = source->capacity;

    memset(destination->data, 0, source->capacity);
    memcpy(destination->data, source->data, source->size);
}

struct ws_string_builder ws_string_builder_create(char const* data)
{
    size_t length        = strlen(data);
    size_t roundedLength = __ws_string_builder_round(length);
    size_t capacity      = roundedLength > 16 ? roundedLength : 16;

    struct ws_string_builder result =
    {
        .begin    = 0,
        .end      = length,
        .data     = (char*)malloc(capacity),
        .size     = length,
        .capacity = capacity
    };

    memset(result.data, 0, capacity);
    memcpy(result.data, data, length);

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

void __ws_string_builder_realloc(struct ws_string_builder* string)
{
    assert(string != nullptr && "STRING POINTER WAS NULL");

    char* oldData = string->data;
    string->capacity += string->capacity;
    string->data = (char*)malloc(string->capacity + 1);
    memset(string->data, '\0', string->capacity + 1);
    memcpy(string->data, oldData, string->size);

    free(oldData);
}

// https://graphics.stanford.edu/%7Eseander/bithacks.html#RoundUpPowerOf2
size_t __ws_string_builder_round(size_t value)
{
    value -= 1;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value += 1;

    return value;
}

#endif

#endif

