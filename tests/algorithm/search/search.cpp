#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>
#include <wsl/ws_vector.h>

WS_VECTOR(int)

int comparator(void const* lhs, void const* rhs)
{
    return *(int const*)lhs > *(int const*)rhs;
}

TEST(algorithm, vector_search)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    int value = 420;

    EXPECT_NE(ws_search(&vector, &value), nullptr);

    ws_vector_destroy(int, &vector);
}

TEST(algorithm, vector_sort)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 720, 420));

    ws_sort_ex(&vector, sizeof(int), comparator);

    EXPECT_EQ(*ws_vector_int_at(vector, 0), 720);
    EXPECT_EQ(*ws_vector_int_at(vector, 1), 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2), 69);

    ws_vector_destroy(int, &vector);
}

