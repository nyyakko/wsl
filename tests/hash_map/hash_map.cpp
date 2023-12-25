#define WS_HASH_MAP_DEFINITION

#include <gtest/gtest.h>
#include <wsl/ws_hash_map.h>

WS_HASH_MAP(int)

TEST(hash_map, push_values)
{
    struct ws_hash_map_int hashMap = ws_hash_map_int_create();

    ws_hash_map_int_push(&hashMap, 0, 69);
    ws_hash_map_int_push(&hashMap, 1, 420);
    ws_hash_map_int_push(&hashMap, 2, 720);

    EXPECT_EQ(ws_hash_map_int_size(hashMap), 3);

    ws_hash_map_destroy(int, &hashMap);
}

TEST(hash_map, pop_values)
{
    struct ws_hash_map_int hashMap = ws_hash_map_int_create();

    ws_hash_map_int_push(&hashMap, 0, 69);
    EXPECT_EQ(ws_hash_map_int_pop(&hashMap, 0), 69);

    ws_hash_map_int_push(&hashMap, 1, 420);
    EXPECT_EQ(ws_hash_map_int_pop(&hashMap, 1), 420);

    ws_hash_map_int_push(&hashMap, 2, 720);
    EXPECT_EQ(ws_hash_map_int_pop(&hashMap, 2), 720);

    EXPECT_EQ(ws_hash_map_int_size(hashMap), 0);

    ws_hash_map_destroy(int, &hashMap);
}

TEST(hash_map, search_values)
{
    struct ws_hash_map_int hashMap = ws_hash_map_int_create();

    ws_hash_map_int_push(&hashMap, 0, 69);
    ws_hash_map_int_push(&hashMap, 1, 420);
    ws_hash_map_int_push(&hashMap, 2, 720);

    EXPECT_NE(ws_hash_map_int_search(hashMap, 2), nullptr);
    EXPECT_EQ(ws_hash_map_int_search(hashMap, 6), nullptr);

    EXPECT_EQ(ws_hash_map_int_pop(&hashMap, 2), 720);

    EXPECT_EQ(ws_hash_map_int_search(hashMap, 2), nullptr);

    ws_hash_map_destroy(int, &hashMap);
}

