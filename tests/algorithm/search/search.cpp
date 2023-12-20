#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>

#include <wsl/ws_vector.h>

WS_VECTOR(int)

TEST(algorithm, vector_search)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    int value = 420;
    EXPECT_NE(ws_search(&vector, &value), nullptr);

    ws_vector_destroy(int, &vector);
}

TEST(algorithm, c_array_search)
{
    int array[3] = { 69, 720, 420 };

    int value = 420;
    EXPECT_NE(ws_search_ex(array, 0, 2, sizeof(int), &value, nullptr), nullptr);
}

