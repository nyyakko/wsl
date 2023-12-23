#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>

#include <wsl/ws_vector.h>

WS_VECTOR(int)

TEST(algorithm, vector_clear)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 720, 420));

    ws_clear(&vector, nullptr);

    EXPECT_EQ(vector.data[0], 0);
    EXPECT_EQ(vector.data[1], 0);
    EXPECT_EQ(vector.data[2], 0);

    EXPECT_EQ(ws_vector_int_size(vector), 0);

    ws_vector_destroy(int, &vector);
}

TEST(algorithm, c_array_clear)
{
    int array[3] = { 69, 720, 420 };

    ws_clear_ex(array, 0, 2, sizeof(int), nullptr);

    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
}

