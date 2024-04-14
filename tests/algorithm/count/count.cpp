#include <gtest/gtest.h>

#define WS_COUNT_DEFINITION
#include <wsl/algorithm/ws_count.h>
#define WS_VECTOR_DEFINITION
#include <wsl/ws_vector.h>

WS_VECTOR(int)

TEST(algorithm, vector_count_non_existing)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 1, 2, 3, 4, 5, 6, 7, 8));
    EXPECT_EQ(ws_count((ws_container_interface const*)&vector, ws_prvalue(int, 69)), 0);
    ws_vector_destroy(int, &vector);
}

TEST(algorithm, vector_count_existing)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 1, 2, 3, 4, 5, 6, 7, 8));
    EXPECT_EQ(ws_count((ws_container_interface const*)&vector, ws_prvalue(int, 5)), 1);
    ws_vector_destroy(int, &vector);
}

int is_multiple_of_two(void const* value) { return *(int*)value % 2 == 0; }
int is_multiple_of_fifteen(void const* value) { return *(int*)value % 15 == 0; }

TEST(algorithm, vector_count_if_non_existing)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 1, 2, 3, 4, 5, 6, 7, 8));
    EXPECT_EQ(ws_count_if((ws_container_interface const*)&vector, (ws_unary_predicate*)is_multiple_of_fifteen), 0);
    ws_vector_destroy(int, &vector);
}

TEST(algorithm, vector_count_if_existing)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 1, 2, 3, 4, 5, 6, 7, 8));
    EXPECT_EQ(ws_count_if((ws_container_interface const*)&vector, (ws_unary_predicate*)is_multiple_of_two), 4);
    ws_vector_destroy(int, &vector);
}

