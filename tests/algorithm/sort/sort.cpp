#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>

#include <wsl/ws_vector.h>

WS_VECTOR(int)

int predicate(void const* lhs, void const* rhs)
{
    return *(int const*)lhs > *(int const*)rhs;
}

TEST(algorithm, vector_sort)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 720, 420));

    ws_sort(&vector, predicate);

    EXPECT_EQ(*ws_vector_int_at(vector, 0), 720);
    EXPECT_EQ(*ws_vector_int_at(vector, 1), 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2), 69);

    ws_vector_destroy(int, &vector);
}

TEST(algorithm, c_array_sort)
{
    int array[3] = { 69, 720, 420 };

    ws_sort_ex(array, 0, 2, sizeof(int), predicate);

    EXPECT_EQ(array[0], 720);
    EXPECT_EQ(array[1], 420);
    EXPECT_EQ(array[2], 69);
}

