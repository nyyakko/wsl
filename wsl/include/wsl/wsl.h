#ifndef WSL_H
#define WSL_H

#ifdef WSL_DEFINITION

#define WS_BINARY_TREE_DEFINITION
#define WS_HASH_MAP_DEFINITION
#define WS_LINKED_LIST_DEFINITION
#define WS_QUEUE_DEFINITION
#define WS_STACK_DEFINITION
#define WS_STRING_BUILDER_DEFINITION
#define WS_STRING_VIEW_DEFINITION
#define WS_VECTOR_DEFINITION

#define WS_CLEAR_DEFINITION
#define WS_COUNT_DEFINITION
#define WS_SEARCH_DEFINITION
#define WS_SORT_DEFINITION

#define WS_ISTREAM_DEFINITION

#endif

#include "ws_binary_tree.h"
#include "ws_hash_map.h"
#include "ws_linked_list.h"
#include "ws_queue.h"
#include "ws_stack.h"
#include "ws_string_builder.h"
#include "ws_string_view.h"
#include "ws_vector.h"

#include "algorithm/ws_clear.h"
#include "algorithm/ws_count.h"
#include "algorithm/ws_search.h"
#include "algorithm/ws_sort.h"

#include "filesystem/ws_istream.h"

#ifndef WSL_DEFINITION
    #define WS_DECL extern
#else
    #define WS_DECL static
#endif

[[nodiscard]] WS_DECL struct ws_string_builder ws_string_builder_create_from_sv(struct ws_string_view other);
[[nodiscard]] WS_DECL struct ws_string_view ws_string_view_create_from_sb(struct ws_string_builder other);

#ifdef WSL_DEFINITION

struct ws_string_builder ws_string_builder_create_from_sv(struct ws_string_view other)
{
    size_t roundedLength = __ws_string_builder_round(other.size);
    size_t capacity      = roundedLength > 16 ? roundedLength : 16;

    struct ws_string_builder result =
    {
        .begin       = 0,
        .end         = other.end,
        .elementSize = sizeof(char),
        .data        = (char*)malloc(capacity),
        .size        = other.size,
        .capacity    = capacity
    };

    memset(result.data, 0, capacity);
    memcpy(result.data, other.data, capacity);

    return result;
}

struct ws_string_view ws_string_view_create_from_sb(struct ws_string_builder other)
{
    struct ws_string_view result =
    {
        .begin = other.begin,
        .end   = other.size,
        .data  = other.data,
        .size  = other.size,
    };

    return result;
}

#endif

#endif

