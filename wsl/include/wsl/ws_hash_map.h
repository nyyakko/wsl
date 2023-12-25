#ifndef WS_HASHMAP_H
#define WS_HASHMAP_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ws_hash_map_destroy_1(type, hash_map) ws_hash_map_##type##_destroy(hash_map, nullptr)
#define ws_hash_map_destroy_2(type, hash_map, strategy) ws_hash_map_##type##_destroy(hash_map, strategy)
#define ws_hash_map_destroy_select(_1, _2, selected, ...) selected
#define ws_hash_map_destroy(type, ...) ws_hash_map_destroy_select(__VA_ARGS__, ws_hash_map_destroy_2, ws_hash_map_destroy_1, void)(type, __VA_ARGS__)

#define WS_HASH_MAP(TYPE)                                                                                                                 \
                                                                                                                                          \
struct ws_hash_item_bucket                                                                                                                \
{                                                                                                                                         \
    struct ws_binary_tree_##TYPE tree;                                                                                                    \
    size_t size;                                                                                                                          \
};                                                                                                                                        \
                                                                                                                                          \
struct ws_hash_map_##TYPE                                                                                                                 \
{                                                                                                                                         \
    struct ws_hash_item_bucket* buckets;                                                                                                  \
    size_t size;                                                                                                                          \
    size_t capacity;                                                                                                                      \
};                                                                                                                                        \
                                                                                                                                          \
inline size_t ws_hash_map_##TYPE##_size(struct ws_hash_map_##TYPE hashMap)                                                                \
{                                                                                                                                         \
    return hashMap.size;                                                                                                                  \
}                                                                                                                                         \
                                                                                                                                          \
inline struct ws_binary_tree_##TYPE##_node* ws_hash_map_##TYPE##_search(struct ws_hash_map_##TYPE hashMap, size_t key)                    \
{                                                                                                                                         \
    for (size_t index = 0llu; index != hashMap.capacity; index += 1)                                                                      \
    {                                                                                                                                     \
        struct ws_hash_item_bucket workingBucket = hashMap.buckets[index];                                                                \
        struct ws_binary_tree_##TYPE##_node* result = ws_binary_tree_##TYPE##_search(workingBucket.tree, key);                            \
                                                                                                                                          \
        if (result != nullptr)                                                                                                            \
        {                                                                                                                                 \
            return result;                                                                                                                \
        }                                                                                                                                 \
    }                                                                                                                                     \
                                                                                                                                          \
    return nullptr;                                                                                                                       \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_hash_map_##TYPE##_push(struct ws_hash_map_##TYPE* hashMap, size_t key, TYPE value)                                         \
{                                                                                                                                         \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                             \
                                                                                                                                          \
    struct ws_binary_tree_##TYPE##_node* result = ws_hash_map_##TYPE##_search(*hashMap, key);                                             \
                                                                                                                                          \
    if (result != nullptr)                                                                                                                \
    {                                                                                                                                     \
        result->value = value;                                                                                                            \
        return;                                                                                                                           \
    }                                                                                                                                     \
                                                                                                                                          \
    struct ws_hash_item_bucket* workingBucket = &hashMap->buckets[key & (hashMap->capacity - 1)];                                         \
    ws_binary_tree_##TYPE##_push(&workingBucket->tree, key, value);                                                                       \
                                                                                                                                          \
    workingBucket->size += 1;                                                                                                             \
    hashMap->size += 1;                                                                                                                   \
}                                                                                                                                         \
                                                                                                                                          \
[[nodiscard]]inline TYPE ws_hash_map_##TYPE##_pop(struct ws_hash_map_##TYPE* hashMap, size_t key)                                         \
{                                                                                                                                         \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                             \
                                                                                                                                          \
    struct ws_hash_item_bucket* workingBucket = &hashMap->buckets[key & (hashMap->capacity - 1)];                                         \
    hashMap->size -= 1;                                                                                                                   \
    workingBucket->size -= 1;                                                                                                             \
                                                                                                                                          \
    return ws_binary_tree_##TYPE##_pop(&workingBucket->tree, key);                                                                        \
}                                                                                                                                         \
                                                                                                                                          \
[[nodiscard]]inline struct ws_hash_map_##TYPE ws_hash_map_##TYPE##_create()                                                               \
{                                                                                                                                         \
    struct ws_hash_map_##TYPE hashMap =                                                                                                   \
    {                                                                                                                                     \
        .buckets  = nullptr,                                                                                                              \
        .size     = 0,                                                                                                                    \
        .capacity = 16                                                                                                                    \
    };                                                                                                                                    \
                                                                                                                                          \
    hashMap.buckets = (struct ws_hash_item_bucket*)malloc(hashMap.capacity * sizeof(struct ws_hash_item_bucket));                         \
                                                                                                                                          \
    for (size_t index = 0llu; index != hashMap.capacity; index += 1)                                                                      \
    {                                                                                                                                     \
        hashMap.buckets[index].tree = ws_binary_tree_##TYPE##_create();                                                                   \
        hashMap.buckets[index].size = 0;                                                                                                  \
    }                                                                                                                                     \
                                                                                                                                          \
    return hashMap;                                                                                                                       \
}                                                                                                                                         \
                                                                                                                                          \
inline void ws_hash_map_##TYPE##_destroy(struct ws_hash_map_##TYPE* hashMap, void(*strategy)(TYPE*))                                      \
{                                                                                                                                         \
    assert(hashMap != nullptr && "HASHMAP POINTER WAS NULL");                                                                             \
                                                                                                                                          \
    for (size_t index = 0llu; index != hashMap->capacity; index += 1)                                                                     \
    {                                                                                                                                     \
        struct ws_hash_item_bucket workingBucket = hashMap->buckets[index];                                                               \
        ws_binary_tree_##TYPE##_destroy(&workingBucket.tree, strategy);                                                                   \
    }                                                                                                                                     \
                                                                                                                                          \
    free(hashMap->buckets);                                                                                                               \
    memset(hashMap, 0, sizeof(struct ws_hash_map_##TYPE));                                                                                \
}

// MurmurHash: https://en.wikipedia.org/wiki/MurmurHash

inline size_t ws_hash_map_hash(void const* bytes, size_t length)
{
    const unsigned long long m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;
    const unsigned long long seed = 69;

    unsigned long long h = seed ^ (length * m);

    const unsigned long long* data = (const unsigned long long*)bytes;
    const unsigned long long* end = data + (length / 8);

    while (data != end)
    {
#ifdef PLATFORM_BIG_ENDIAN
        uint64 k = *data++;
        char *p = (char *)&k;
        char c;
        c = p[0]; p[0] = p[7]; p[7] = c;
        c = p[1]; p[1] = p[6]; p[6] = c;
        c = p[2]; p[2] = p[5]; p[5] = c;
        c = p[3]; p[3] = p[4]; p[4] = c;
#else
        unsigned long long k = *data++;
#endif

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch (length & 7)
    {
        case 7: h ^= (unsigned long long)(data2[6]) << 48; [[fallthrough]];
        case 6: h ^= (unsigned long long)(data2[5]) << 40; [[fallthrough]];
        case 5: h ^= (unsigned long long)(data2[4]) << 32; [[fallthrough]];
        case 4: h ^= (unsigned long long)(data2[3]) << 24; [[fallthrough]];
        case 3: h ^= (unsigned long long)(data2[2]) << 16; [[fallthrough]];
        case 2: h ^= (unsigned long long)(data2[1]) << 8;  [[fallthrough]];
        case 1: h ^= (unsigned long long)(data2[0]);

        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

#endif

